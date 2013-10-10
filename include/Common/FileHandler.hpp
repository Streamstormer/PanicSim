#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <cmath>
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include "../Simulator/Area.hpp"

class ClFileHandler
{
    public:
        ClFileHandler();
        ~ClFileHandler();
        int writeLevel(std::string fileName, ClArea *pArea);
        int readLevel(std::string fileName, ClArea *pArea);


    private:
        int createFile(const char *fileName);  //expects filename without ending
        int openExistingFile(const char *fileName);    //expects file ending with ".csv"
        int writeLevelDetails();
        int writeStaticObjects(ClArea *pArea);
        int closeFile();
        int importStaticObjects(ClArea *pArea);
        int importLevelDetails();
        int writeHeader(ClArea *pArea);


        unsigned int inNrOfObjects;
        std::ifstream inFile;
        std::ofstream myFile;
};

#endif // FILEHANDLER_H
