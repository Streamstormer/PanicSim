#ifndef FILEHANDLER_H
#define FILEHANDLER_H


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
        //int writeLevel(std::string fileName, ClArea *pArea, sf::Vector2f *levelSize, sf::Color *bgColor);
        int readLevel(std::string fileName, ClArea *pArea);
        //int readLevel(std::string fileName, ClArea *pArea, sf::Vector2f *levelSize, sf::Color *bgColor);
        int openFile(std::string fileName);
        ClArea * getArea(){return myArea;};

        /********************************************************
        Methods forwarded from Area
        *******************************************************/

        sf::Vector2i getLevelSize(){if(isArea) return myArea->getLevelSize();};
        sf::Color getBgColor(){if(isArea) return myArea->getBgColor();};
        int getNumberOfStaticObjects(){if(isArea) return myArea->getNumberOfStaticObjects();};
        const sf::Vector2f & getPosition(int id){if(isArea) return myArea->getPosition(id);};   // returns position of a StaticObject via id
        const sf::Vector2f & getSize(int id){if(isArea) return myArea->getSize(id);};      // returns size of a StaticObject via id
        float getRotation(int id){if(isArea) return myArea->getRotation(id);};                  // returns rotation of a StaticObject via id

        /*
        Return codes:
        0: No error
        1: Error while opening file
        2: Number of static objects nan (First line first item has to be a numchar seperated by blank or ";")
        3: Object Type from file out of range (enum staticObjects), autocorrection to WALL
        4: Unexpected token at line 2 of csv file when loading. Only ";" and numbers [0-9] are allowed, except first column.
        5: Unexpected RGB number in line 2 of csv file too long. Only [0-255] are allowed.
        6: Unexpected error reading line 2 of csv file: negative number.
        7: StaticObject numchar nan
        */


    private:



        /*This is a call block.
        Expects file ending with ".csv", by ';' delimited (created by the Editor).
        Object of ClArea will be created and filled with objects of given file.
        After call of this function the file is closed, but Area object stays.
        Area object can be gathered by getArea() method.
        */
        int openExistingFile(const char *fileName);
        int importLevelDetails(ClArea *pArea);
        int importStaticObjects(ClArea *pArea);

        //if file exists it will be deleted, creates new file, ending required, optimized for ".csv"
        int createFile(const char *fileName);

        /*ONLY TO CALL WITHIN writeLevel(), FOR REQUIREMENTS
        */
        int writeHeader(ClArea *pArea);
        /*ONLY TO CALL WITHIN writeLevel(), FOR REQUIREMENTS
        */
        int writeLevelDetails(ClArea *pArea);
        /*ONLY TO CALL WITHIN writeLevel(), FOR REQUIREMENTS
        Writes static objects within the given Area object into the opened myFile.
        */
        int writeStaticObjects(ClArea *pArea);


        unsigned int inNrOfObjects;
        std::ifstream inFile;
        std::ofstream myFile;
        ClArea *myArea;
        bool isArea;
};

#endif // FILEHANDLER_H
