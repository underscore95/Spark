#pragma once

#include <chrono>
#include <string>

namespace Spark::Utils {
	const std::string getDateTimeString(std::chrono::system_clock::time_point time = std::chrono::system_clock::now());
}