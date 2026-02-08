#include <iostream>
#include <ctime>
#include <string>
#include "logger.h"

Logger::Logger(const std::string &path)
    : file(path, std::ios::app)
{
    if (!file) {
        throw std::runtime_error("Failed to open file!");
    }
}

std::string to_string(LogEvent level) {
    switch (level) {
        case LogEvent::INFO:  return "INFO";
        case LogEvent::WARN:  return "WARN";
        case LogEvent::ERROR: return "ERROR";
    }
    return "UNKNOWN";
}


void Logger::log(const std::string &content, LogEvent logEvent) {
    time_t timestamp = time(nullptr);
    struct tm datetime = *std::localtime(&timestamp);
    char formatted[50];
    std::strftime(formatted, sizeof(formatted), "%m-%d-%y %I:%M:%S %p", &datetime);

    file << "\n[ " << formatted << " ] "
         << "[ " << to_string(logEvent) << " ] "
         << content
         << std::flush;
}