#pragma once


#include <string>


namespace fileLoader
{
    /**
     * Reads the file at the given path and returns the contents
     * @param filePath - Full file path
     * @return - Contents of the file or empty if file is not found
     */
    std::string readTextFile(const char* filePath);
}
