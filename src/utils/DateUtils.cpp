#include "DateUtils.h"

const std::string Spark::Utils::getDateTimeString(std::chrono::system_clock::time_point time)
{
    std::time_t time_t = std::chrono::system_clock::to_time_t(time);
    std::tm tm = *std::localtime(&time_t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
