#include "Spectrum.h"
#include "FileSystemManger.h"
#include <iostream>
#include <filesystem>
#include <vector>

#define DEBUG_PATH "D:\\Code\\Spectrum_MachineLearning\\Data\\2025_04_26\\1\\Spectrum-1.txt"

int main()
{
    SpectrumLoader ldr(DEBUG_PATH);
    SpectrumData dt;
    std::cout << "Current path: " << std::filesystem::current_path() << std::endl;
    dt = ldr.loadSpectrum_average_integer(DEBUG_PATH);
    dt.print();
    std::cout << "Hello World!" << std::endl;
    getchar(); 
    return 0;
}