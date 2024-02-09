#include "InternalLogging.h"

#include "utils.h"

#include "std.h"

#include <magic_enum.hpp>

namespace SparkInternal::Logging {

	// Blocking function, will handle all the logs in queue
	void handleLogs();

	std::queue<SparkInternal::Logging::Log> logQueue;
	std::mutex logQueueMutex;
	std::condition_variable logQueueCondition;

	std::thread thread(handleLogs);

	void handleLogs() {
		thread.detach();
		while (true) {
			std::unique_lock<std::mutex> lock(logQueueMutex);
			logQueueCondition.wait(lock, [] { return !logQueue.empty(); });

			const auto log = std::move(logQueue.front());
			logQueue.pop();

			lock.unlock();

			const std::string currentTime = Spark::Utils::getDateTimeString();
			const std::string logLevelName = log.debug ? "DEBUG" : std::string(magic_enum::enum_name(log.level));
			const std::string logString = "[" + currentTime + "] [" + logLevelName + "] " + "[" + log.loggerName + "] " + log.message;

			std::cout << logString;

			if (log.level >= Spark::Logging::LogLevel::SEVERE) {
				std::cout << std::endl;
			}
			else {
				std::cout << "\n";
			}
		}
	}

	void log(const std::chrono::system_clock::time_point& time, const Spark::Logging::LogLevel& level, const std::string& loggerName, const std::string& message, const bool debug) {
		{
			std::lock_guard<std::mutex> lock(logQueueMutex);
			logQueue.emplace(time, level, loggerName, message, debug);
		}
		logQueueCondition.notify_one();
	}
}
