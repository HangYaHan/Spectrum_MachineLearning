#ifndef FILE_SYSTEM_MANAGER_H
#define FILE_SYSTEM_MANAGER_H

#include <string>
#include <vector>
#include <iostream>

class FileSystemManager {
private:
    std::string root_directory; // Root directory path

public:
    // Constructor
    FileSystemManager(const std::string& rootDir) : root_directory(rootDir) {}

    // List all file paths in the specified directory
    std::vector<std::string> listFiles(const std::string& directory);

    // List all subdirectory paths in the specified directory
    std::vector<std::string> listDirectories(const std::string& directory);

    // Display the contents of a string vector
    void displayVector(const std::vector<std::string>& vec) const;
};

#endif // FILE_SYSTEM_MANAGER_H