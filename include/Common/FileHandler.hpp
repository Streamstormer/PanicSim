#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <cstring>
#include <vector>
#include "../Simulator/Area.hpp"

class FileHandler
{
    public:
        FileHandler();
        ~FileHandler();
        bool writeArea(std::string fileName, ClArea *pArea);


    private:
        bool createFile(const char *fileName);
        bool writeLevelDetails(ClArea *pArea);
        bool writeStaticObjects(ClArea *pArea);
        bool closeFile();
        std::ofstream myFile;
};

#endif // FILEHANDLER_H
