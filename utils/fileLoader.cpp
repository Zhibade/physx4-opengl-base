#include "fileLoader.h"

#include <fstream>
#include <iostream>
#include <string>

std::string fileLoader::readTextFile(const char *filePath)
{
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open())
    {
        std::cerr << "Could not read file: " + std::string(filePath) << std::endl;
        return "";
    }

    std::string fileContents;
    std::string currentLine;

    while (!fileStream.eof())
    {
        std::getline(fileStream, currentLine);
        fileContents.append(currentLine + "\n");
    }

    fileStream.close();
    return fileContents;
}