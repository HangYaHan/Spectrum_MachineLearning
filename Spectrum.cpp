#include "Spectrum.h"
#include "FileSystemManger.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

void SpectrumData::load(const std::string& filepath) {
    this->filepath = filepath;

    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }

    wavelengths.clear();
    intensities.clear();

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        double wavelength, intensity;
        if (iss >> wavelength >> intensity) {
            wavelengths.push_back(wavelength);
            intensities.push_back(intensity);
        }
    }

    file.close();
}

void SpectrumData::print() const {
    std::cout << "Spectrum Data from file: " << filename << "\n";
    std::cout << "Wavelengths and Intensities:\n";
    for (size_t i = 0; i < wavelengths.size(); ++i) {
        std::cout << wavelengths[i] << "\t" << intensities[i] << "\n";
    }
}

SpectrumData SpectrumLoader::loadSpectrum_average_integer(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }
    
    SpectrumData processed_Spectra;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        double wavelength, intensity;
        if (iss >> wavelength >> intensity) {
            wavelength = static_cast<int>(wavelength);
            intensity = static_cast<int>(intensity);
            processed_Spectra.push_back(wavelength, intensity);
        }
        else {
            std::cerr << "In file: " << filepath << "\n";
            std::cerr << "Error reading line: " << line << "\n";
        }
    }

    
   file.close();
    return processed_Spectra;
}

// int SpectrumLoader::saveSpectrum(const std::string& filepath, const SpectrumData& spectrum) {
//     std::ofstream file(filepath);
//     if (!file.is_open()) {
//         throw std::runtime_error("Failed to open file for writing: " + filepath);
//     }

//     for (size_t i = 0; i < spectrum.wavelengths.size(); ++i) {
//         file << spectrum.wavelengths[i] << "\t" << spectrum.intensities[i] << "\n";
//     }

//     file.close();
//     return 0;
// }

// SpectrumData SpectrumLoader::loadSpectrum_direct(const std::string &filepath)
// {
//     SpectrumData spectrumData;
//     spectrumData.load(filepath);
//     return spectrumData;
// }
