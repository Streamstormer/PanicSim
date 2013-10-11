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

        /*
        Return codes:
        0: No error
        1: Error while opening file
        3: Object Type from file out of range (enum staticObjects), autocorrection to WALL
        */


    private:
        int createFile(const char *fileName);           //if file exists it will be deleted, creates by ';' delimited file, file ending required, optimized for ".csv"
        int openExistingFile(const char *fileName);     //expects file ending with ".csv"
        int writeLevelDetails();
        int writeStaticObjects(ClArea *pArea);
        int importStaticObjects(ClArea *pArea);
        int importLevelDetails();
        int writeHeader(ClArea *pArea);


        unsigned int inNrOfObjects;
        std::ifstream inFile;
        std::ofstream myFile;
};

#endif // FILEHANDLER_H
