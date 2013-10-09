#include "../../include/Common/FileHandler.hpp"

FileHandler::FileHandler()
{

}

FileHandler::~FileHandler()
{
    //dtor
}

bool FileHandler::createFile(const char *fileName){
    myFile.open(fileName);
    return 0;
}

bool FileHandler::writeLevelDetails(ClArea *pArea){
return 0;
}

bool FileHandler::writeStaticObjects(ClArea *pArea){
    int x = pArea->getNumberOfStaticObjects();
    sf::Vector2f sOPosition;
    sf::Vector2f sOSize;
    float sORotation;
    int sOType = 0;
    for(int i = 1; i<= x; i++){
        sOPosition = pArea->getPosition(i);
        sOSize = pArea->getSize(i);
        sORotation = pArea->getRotation(i);
        //sOType = pArea->getType(i);

    }
    return 0;
}

bool FileHandler::closeFile(){

    myFile.close();
    return 0;
}

bool FileHandler::writeArea(std::string fileName, ClArea *pArea){
    createFile(fileName.c_str());
    writeStaticObjects(pArea);
    return 0;
}
