#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <chrono>
#include <iostream>
#include <string>

std::string GetDateAndTime();




class Logger
{
private:

public:
	template <typename T, typename... Args>
	static void Log(const T& msg, const Args&... args)
	{
 		std::string timestamp = GetDateAndTime();
		std::cout << startColorCode << "LOG::" << timestamp << ": " << msg;
		((std::cout << " " << args), ...);
		std::cout << endColorCode << std::endl;
	}

	template <typename T, typename... Args>
	static void Log_(const T& msg, const Args&... args) // log without timestamp
	{
		std::cout << "LOG:: "  << msg;
		((std::cout << " " << args), ...);
		std::cout << std::endl;
	}


	static void Err(const std::string& err);
	static void Err(const std::string& err, const char* errMsg);

};



#endif // end logger