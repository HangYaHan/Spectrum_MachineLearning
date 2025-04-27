#include "FileSystemManger.h"
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

std::vector<std::string> FileSystemManager::listFiles(const std::string& directory) {
    std::vector<std::string> files;
    try {
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            if (entry.is_regular_file()) {
                files.push_back(entry.path().string());
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
    }
    return files;
}

std::vector<std::string> FileSystemManager::listDirectories(const std::string& directory) {
    std::vector<std::string> directories;
    try {
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            if (entry.is_directory()) {
                directories.push_back(entry.path().string());
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
    }
    return directories;
}

void FileSystemManager::displayVector(const std::vector<std::string>& vec) const {
    for (const auto& item : vec) {
        std::cout << item << std::endl;
    }
}