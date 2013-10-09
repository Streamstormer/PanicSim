#include "../../include/Common/FileHandler.hpp"

ClFileHandler::ClFileHandler()
{

}

ClFileHandler::~ClFileHandler()
{
    //dtor
}

bool ClFileHandler::createFile(const char *fileName){
    myFile.open(fileName, std::ios::trunc);
    return 0;
}

bool ClFileHandler::writeLevelDetails(){
return 0;
}

bool ClFileHandler::writeStaticObjects(ClArea *pArea){
    int x = pArea->getNumberOfStaticObjects();
    sf::Vector2f sOPosition;
    sf::Vector2f sOSize;
    float sORotation;
    int sOType = 0;
    myFile << "StaticObjectId " << x << "; Position Xf; Position Yf; Size Xf; Size Yf; Rotation f; Type i\n";
    for(int i = 1; i<= x; i++){
        sOPosition = pArea->getPosition(i);
        sOSize = pArea->getSize(i);
        sORotation = pArea->getRotation(i);
        sOType = pArea->getType(i);
        myFile << i << ";" << sOPosition.x << ";" << sOPosition.y << ";" << sOSize.x << ";" << sOSize.y << ";" << sORotation << ";" << sOType << "\n";
    }
    return 0;
}

bool ClFileHandler::closeFile(){

    myFile.close();
    return 0;
}

bool ClFileHandler::writeLevel(std::string fileName, ClArea *pArea){
    std::string aFileName = fileName + "A.csv";
    createFile(aFileName.c_str());
    writeLevelDetails();
    closeFile();
    std::string sOFileName = fileName + "sO.csv";
    createFile(sOFileName.c_str());
    writeStaticObjects(pArea);
    closeFile();
    return 0;
}
