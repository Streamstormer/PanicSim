#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <cstring>
#include <vector>
#include "../Simulator/Area.hpp"

class ClFileHandler
{
    public:
        ClFileHandler();
        ~ClFileHandler();
        bool writeLevel(std::string fileName, ClArea *pArea);
        bool readLevel(std::string fileName, ClArea *pArea);


    private:
        bool createFile(const char *fileName);  //expects filename without ending
        bool openExistingFile(const char *fileName);    //expects file ending with O.csv
        bool writeLevelDetails();
        bool writeStaticObjects(ClArea *pArea);
        bool closeFile();
        bool importStaticObjects(ClArea *pArea);
        bool importLevelDetails();

        std::ofstream myFile;
};

#endif // FILEHANDLER_H
