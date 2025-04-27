// filepath: d:\Code\FPGA_Competition\main\State_Test\Logger.cpp
#include "Logger.h"
#include <iostream>
#include <stdexcept>
#include <ctime>

// Singleton instance access
Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

// Set log file path
void Logger::setLogFile(const std::string& filePath) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (logFile.is_open()) {
        logFile.close();
    }
    logFile.open(filePath, std::ios::out | std::ios::app);
    if (!logFile) {
        throw std::runtime_error("Failed to open log file: " + filePath);
    }
}

// Set the minimum log level to output
void Logger::setLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(logMutex);
    currentLogLevel = level;
}

// Log a message with a specific log level
void Logger::log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (level < currentLogLevel) {
        return;
    }

    std::string logMessage = "[" + logLevelToString(level) + "] " + message;

    // Add timestamp
    std::time_t now = std::time(nullptr);
    char timeBuffer[20];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    logMessage = std::string(timeBuffer) + " " + logMessage;

    if (logFile.is_open()) {
        logFile << logMessage << std::endl;
    } else {
        std::cerr << logMessage << std::endl;
    }
}

// Convenience methods for specific log levels
void Logger::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

void Logger::warning(const std::string& message) {
    log(LogLevel::WARNING, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::ERROR, message);
}

void Logger::debug(const std::string& message) {
    log(LogLevel::DEBUG, message);
}

// Private constructor for singleton
Logger::Logger() : currentLogLevel(LogLevel::INFO) {}

// Destructor
Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

// Helper to convert LogLevel to string
std::string Logger::logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::DEBUG: return "DEBUG";
        default: return "UNKNOWN";
    }
}