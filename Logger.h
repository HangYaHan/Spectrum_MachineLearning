#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <mutex>

class Logger {
public:
    enum class LogLevel {
        INFO,
        WARNING,
        ERROR,
        DEBUG
    };

    // Singleton instance access
    static Logger& getInstance();

    // Set log file path
    void setLogFile(const std::string& filePath);

    // Set the minimum log level to output
    void setLogLevel(LogLevel level);

    // Log a message with a specific log level
    void log(LogLevel level, const std::string& message);

    // Convenience methods for specific log levels
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    void debug(const std::string& message);

private:
    Logger(); // Private constructor for singleton
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::ofstream logFile;
    LogLevel currentLogLevel;
    std::mutex logMutex;

    // Helper to convert LogLevel to string
    std::string logLevelToString(LogLevel level);
};

#endif // LOGGER_H