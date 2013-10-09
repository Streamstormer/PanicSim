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
    myFile << "Details.";
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

bool openFile(const char *fileName){

    return 0;
}

bool ClFileHandler::writeLevel(std::string fileName, ClArea *pArea){
    std::string aFileName = fileName + "L.csv";
    createFile(aFileName.c_str());
    writeLevelDetails();
    closeFile();
    std::string sOFileName = fileName + "O.csv";
    createFile(sOFileName.c_str());
    writeStaticObjects(pArea);
    closeFile();
    return 0;
}

    bool ClFileHandler::importStaticObjects(ClArea *pArea){

    return 0;
    }

    bool ClFileHandler::importLevelDetails(){

    return 0;
    }

bool ClFileHandler::readLevel(std::string fileName, ClArea *pArea){

    /*
    openExistingFile(fileName.c_str());
    importStaticObjects(pArea);
    closeFile();

    std::string lFileName;
    lFileName.resize(strcspn(fileName.c_str(),"O.csv"));
    lFileName += "L.csv";
    openExistingFile(lFileName.c_str());
    importLevelDetails();
    closeFile();
    */
    return 0;
}
