#ifndef SPECTRUMDATA_H
#define SPECTRUMDATA_H

#include <vector>
#include <string>
#include "FileSystemManger.h"

class SpectrumData {
private:
    // Member variables
    std::vector<int> wavelengths; // Wavelength data
    std::vector<int> intensities; // Intensity data
    std::string filename;            // Name of the data file
    std::string filepath;            // Path of the data file

public:
    // Member functions
    void load(const std::string& filepath); // Load data from a file
    void print() const;                     // Print spectrum data (for debugging)
    void push_back(int wavelength, int intensity) { // Add data to the vectors
        wavelengths.push_back(wavelength);
        intensities.push_back(intensity);
    }
};

class SpectrumLoader {
private:
    FileSystemManager fs; // File system manager instance
public:
    SpectrumLoader(const std::string& rootDir) : fs(rootDir) {} // Constructor
    // Load spectrum data from a file

    // The following funtion process only one file
    SpectrumData loadSpectrum_average_integer(const std::string& filepath);
    int saveSpectrum(const std::string& filepath, const SpectrumData& spectrum); // Save spectrum data to a file
};

class SpectrumProcessor {
private:
    virtual void process(const std::vector<SpectrumData>& spectra) = 0;
};
#endif // SPECTRUMDATA_H
