#include "InternalLogging.h"
#include <queue>
#include <mutex>
#include <thread>
#include "utils/DateUtils.h"
#include <iostream>
#include <magic_enum.hpp>

namespace SparkInternal::Logging {
	// Blocking function, will handle all the logs in queue
	void handleLogs();

	std::queue<SparkInternal::Logging::Log> logQueue;
	std::mutex logQueueMutex;

	std::thread thread(handleLogs);

	void handleLogs()
	{
		thread.detach();
        while (true) {
            logQueueMutex.lock();
            if (logQueue.empty()) {
                logQueueMutex.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(25));
            }
            else {
                const auto log = std::move(logQueue.front());
                logQueue.pop();
                logQueueMutex.unlock();

                const std::string currentTime = Spark::Utils::getDateTimeString();
                const std::string logLevelName = log.debug ? "DEBUG" : std::string(magic_enum::enum_name(log.level));
                const std::string logString = "[" + currentTime + "] [" + logLevelName + "] " + "[" + log.loggerName + "] " + log.message;

                std::cout << "3" << logString;

                if (log.level >= Spark::Logging::LogLevel::SEVERE) {
                    std::cout << std::endl;
                }
                else {
                    std::cout << "\n";
                }
            }
        }
	}
    void log(const std::chrono::system_clock::time_point& time, const Spark::Logging::LogLevel& level, const std::string& loggerName, const std::string& message, const bool debug)
    {
        logQueueMutex.lock();
        logQueue.emplace(time, level, loggerName, message, debug);
        logQueueMutex.unlock();
    }
}