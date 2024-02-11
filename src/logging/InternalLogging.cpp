#include "InternalLogging.h"

#include "utils/DateUtils.h"
#include "Logger.h"

#include <magic_enum.hpp>

namespace SparkInternal::Logging {

	// Blocking function, will handle all the logs in queue
	void handleLogs();

	std::queue<SparkInternal::Logging::Log> logQueue;
	std::mutex logQueueMutex;
	std::condition_variable logQueueCondition;

	std::thread loggingThread(handleLogs);
	bool handlingLogs = false;

	void handleLogs() {
		handlingLogs = true;
		while (handlingLogs) {
			// Consume the next log
			std::unique_lock<std::mutex> lock(logQueueMutex);
			logQueueCondition.wait(lock, [] { return !logQueue.empty(); });

			const auto log = std::move(logQueue.front());
			logQueue.pop();

			lock.unlock();

			// Build log message
			const std::string currentTime = Spark::Utils::getDateTimeString();
			const std::string logLevelName = log.debug ? "DEBUG" : std::string(magic_enum::enum_name(log.level));
			std::stringstream ss;
			ss << "[" << currentTime << "] [" << logLevelName << "] " << "[" << log.loggerName << "] " << log.message;

			// Add endl if severe log
			if (log.level >= Spark::Logging::LogLevel::SEVERE)
				ss << std::endl;
			else
				ss << "\n";

			// Print to console
			const std::string s = ss.str();
			std::cout << s;

			if (log.logToFile) {
				// Add to log file
				std::stringstream fileName;
				fileName << "logs/" << log.loggerName << "/";
				std::filesystem::create_directories(fileName.str());
				fileName << log.loggerCreationTime << ".log";

				std::ofstream file(fileName.str(), std::ios::app); // Open file in append mode
				if (file.is_open()) {
					file << s;
					file.close();
				}
				else {
					std::cout << "Failed to open log file: " << fileName.str() << std::endl;
				}
			}
		}
	}

	void log(const std::chrono::system_clock::time_point& time, const Spark::Logging::LogLevel& level, const std::string& loggerName, const std::string& loggerCreationTime,
		const std::string& message, const bool debug, const bool logToFile) {
			{
				std::lock_guard<std::mutex> lock(logQueueMutex);
				logQueue.emplace(time, level, loggerName, loggerCreationTime, message, debug, logToFile);
			}
			logQueueCondition.notify_one();
	}

	void onExit()
	{
		handlingLogs = false;
		loggingThread.join();
	}
}
