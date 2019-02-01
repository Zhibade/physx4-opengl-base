#ifndef PHYSX4_FILELOADER_H
#define PHYSX4_FILELOADER_H

class ifstream;

namespace fileLoader
{
    /* Reads text file at the given path and returns the contents */
    std::string readTextFile(const char* filePath);
}

#endif //PHYSX4_FILELOADER_H
