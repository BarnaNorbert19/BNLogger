#pragma once

#include "Logger.h"
#include <regex>
#include <fstream>
#include <ctime>

const char* BNEngine::Logger::FilePath;
std::mutex BNEngine::Logger::Mutex;
bool BNEngine::Logger::ANSISupport;

#ifdef _WIN32

void BNEngine::Logger::SetTerminal()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hOut == INVALID_HANDLE_VALUE)
	{
		ANSISupport = false;
		return;
	}

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
	{
		ANSISupport = false;
		return;
	}

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if (!SetConsoleMode(hOut, dwMode))
	{
		ANSISupport = false;
		return;
	}

	ANSISupport = true;
}

#elif __LINUX__ || __APPLE__

if (getenv("TERM"))
{
	ANSISupport = true;
}
else
{
	ANSISupport = false;
}
#endif // _WIN32

bool BNEngine::Logger::PlaceStringToPosition(std::string & result, const std::string & arg, int pos)
{
	std::string from;
	from.append("{").append(std::to_string(pos).append("}"));

	size_t start_pos = result.find(from);
	if (start_pos == std::string::npos)
		return false;
	result.replace(start_pos, from.length(), arg);
	return true;
}

bool BNEngine::Logger::WriteToFile(std::string log)
{
	std::ofstream file = std::ofstream(FilePath, std::ios_base::app);

	file << log << std::endl;

	file.close();

	return true;
}

BNEngine::Logger::DateTime BNEngine::Logger::GetDateTime()
{
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	char date[80];
	char time[80];

	strftime(date, sizeof(date), "%Y.%m.%d", &newtime);
	strftime(time, sizeof(time), "%X", &newtime);

	return Logger::DateTime(date, time);
}

BNEngine::Logger::DateTime::DateTime(std::string date, std::string time)
{
	Date = date;
	Time = time;
}
