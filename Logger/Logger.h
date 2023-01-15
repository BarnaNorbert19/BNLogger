#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <mutex>

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#define BN_LOGGER_COLOR_BLUE 34
#define BN_LOGGER_COLOR_YELLOW 93
#define BN_LOGGER_COLOR_BRIGHT_RED 31
#define BN_LOGGER_COLOR_RED 91

namespace BNEngine
{
	class Logger
	{
	private:
		struct DateTime
		{
			std::string Date;
			std::string Time;

			DateTime(std::string, std::string);
		};

		static bool PlaceStringToPosition(std::string& result, const std::string& arg, int pos);
		static bool WriteToFile(std::string log);
		static Logger::DateTime GetDateTime();
		static std::mutex Mutex;
		static bool ANSISupport;

	public:
		static void SetTerminal();

		static const char* FilePath;

		template <class ... Args>
		static void LogInfo(const char* message, Args && ... args)
		{
			std::scoped_lock lock = std::scoped_lock(Mutex);

			int i = 0;
			std::string messageStringFormat = message;

			([&]
				{
					std::stringstream sStream;
			sStream << args;

			PlaceStringToPosition(messageStringFormat, sStream.str(), i);

			i++;
				} (), ...);

			std::string log = GetDateTime().Time + " [Info] " + messageStringFormat;

			if (ANSISupport)
				std::cout << "\033[1;" << BN_LOGGER_COLOR_BLUE << "m" << log << "\033[0m\n" << std::endl;
			else
				std::cout << log << std::endl;
		}

		template <class ... Args>
		static void LogWarning(const char* message, Args && ... args)
		{
			std::scoped_lock lock = std::scoped_lock(Mutex);

			int i = 0;
			std::string messageStringFormat = message;

			([&]
				{
					std::stringstream sStream;
			sStream << args;

			PlaceStringToPosition(messageStringFormat, sStream.str(), i);

			i++;
				} (), ...);

			std::string log = GetDateTime().Time + " [Warning] " + messageStringFormat;

			if (ANSISupport)
				std::cout << "\033[1;" << BN_LOGGER_COLOR_YELLOW << "m" << log << "\033[0m\n" << std::endl;
			else
				std::cout << log << std::endl;
		}

		template <class ... Args>
		static void LogError(const char* message, Args && ... args)
		{
			std::scoped_lock lock = std::scoped_lock(Mutex);

			int i = 0;
			std::string messageStringFormat = message;

			([&]
				{
					std::stringstream sStream;
			sStream << args;

			PlaceStringToPosition(messageStringFormat, sStream.str(), i);

			i++;
				} (), ...);

			DateTime dateTime = GetDateTime();

			std::string log = dateTime.Time + " [Error] " + messageStringFormat;

			if (ANSISupport)
				std::cout << "\033[1;" << BN_LOGGER_COLOR_BRIGHT_RED << "m" << log << "\033[0m\n" << std::endl;
			else
				std::cout << log << std::endl;

			WriteToFile(dateTime.Date + "-" + log);
		}

		template <class ... Args>
		static void LogFatal(const char* message, Args && ... args)
		{
			std::scoped_lock lock = std::scoped_lock(Mutex);

			int i = 0;
			std::string messageStringFormat = message;

			([&]
				{
					std::stringstream sStream;
			sStream << args;

			PlaceStringToPosition(messageStringFormat, sStream.str(), i);

			i++;
				} (), ...);

			DateTime dateTime = GetDateTime();

			std::string log = dateTime.Time + " [Fatal] " + messageStringFormat;

			if (ANSISupport)
				std::cout << "\033[1;" << BN_LOGGER_COLOR_RED << "m" << log << "\033[0m\n" << std::endl;
			else
				std::cout << log << std::endl;

			WriteToFile(dateTime.Date + "-" + log);
		}
	};
}