#include "Logger.hpp"

void Logger::Err(const std::string& err)
{
	std::cout << "ERROR:: " << err << std::endl;
}

void Logger::Err(const std::string& err, const char* errMsg)
{
	std::cout << "ERROR:: " << err << " " << errMsg << std::endl;
}

#pragma warning(push)
#pragma warning(disable: 4996)
std::string GetDateAndTime()
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	return ss.str();
}
#pragma warning(pop)