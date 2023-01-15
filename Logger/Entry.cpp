#include <iostream>
#include "Logger.h"

int main()
{
    BNEngine::Logger::SetTerminal();

    BNEngine::Logger::FilePath = "test.log";

    BNEngine::Logger::LogInfo("{2} First: {0}, Second: {1}, Third: , Fourth: {3}", 1, 100, "asd");
    BNEngine::Logger::LogWarning("{2} First: {0}, Second: {1}, Third: , Fourth: {3}", 1, 100, "asd");
    BNEngine::Logger::LogError("{2} First: {0}, Second: {1}, Third: , Fourth: {3}", 1, 100, "asd");
    BNEngine::Logger::LogFatal("{2} First: {0}, Second: {1}, Third: , Fourth: {3}", 1, 100, "asd");
}