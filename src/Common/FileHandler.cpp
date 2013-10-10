#include "../../include/Common/FileHandler.hpp"

ClFileHandler::ClFileHandler()
{

}

ClFileHandler::~ClFileHandler()
{
    //dtor
}

int ClFileHandler::createFile(const char *fileName){
    myFile.open(fileName, std::ios::trunc);
    return 0;
}



int ClFileHandler::writeLevelDetails(){
    myFile << "Details;;;;;;;1000;1000;green;1000\n";
return 0;
}

int ClFileHandler::writeStaticObjects(ClArea *pArea){
    int x = pArea->getNumberOfStaticObjects();
    sf::Vector2f sOPosition;
    sf::Vector2f sOSize;
    float sORotation;
    int sOType = 0;
    //myFile << "StaticObjectId " << x << "; Position Xf; Position Yf; Size Xf; Size Yf; Rotation f; Type i\n";
    for(int i = 1; i<= x; i++){
        sOPosition = pArea->getPosition(i);
        sOSize = pArea->getSize(i);
        sORotation = pArea->getRotation(i);
        sOType = pArea->getType(i);
        myFile << i << ";" << sOPosition.x << ";" << sOPosition.y << ";" << sOSize.x << ";" << sOSize.y << ";" << sORotation << ";" << sOType << ";\n";
    }
    return 0;
}

int ClFileHandler::closeFile(){

    myFile.close();
    return 0;
}

int ClFileHandler::writeHeader(ClArea *pArea){
    int x = pArea->getNumberOfStaticObjects();
    myFile << x << " StaticObjectId" << "; Position Xf; Position Yf; Size Xf; Size Yf; Rotation f; Type i; Levelsize X; Levelsize Y; BGColor; Persons count\n";
    return 0;
}

int ClFileHandler::openExistingFile(const char *fileName){
    inFile.open(fileName);
    return 0;
}

int ClFileHandler::writeLevel(std::string fileName, ClArea *pArea){
    std::string aFileName = fileName + ".csv";
    createFile(aFileName.c_str());
    writeHeader(pArea);
    writeLevelDetails();
    writeStaticObjects(pArea);
    closeFile();
    //readLevel("test.csv", pArea);
    return 0;
}

    int ClFileHandler::importStaticObjects(ClArea *pArea){
        char str[1000];
        float props[7];
        int multiplier = 10;
        int divider = 1;
        for(unsigned int i = 0; i < inNrOfObjects; i++){
        inFile.getline(str,1000);
            for(int k = 0; k<7; k++){
                int j = 0;
                while(str[j] != ';'){
                    if(str[j] != '.'){
                        if(multiplier == 1)
                            divider = divider * 10;
                        props[k] = multiplier * props[k] + (str[j] - 48) / divider;
                    }
                    else{
                        multiplier = 1;
                        divider = 10;
                    }
                    j++;
                }
            }
            sf::Vector2f position;
            position.x = props[1];
            position.y = props[2];
            sf::Vector2f objectSize;
            objectSize.x = props[3];
            objectSize.y = props[4];
            int type = (int) props[6];
            pArea->insertStObj(type,position,objectSize,props[5]);


        }
        return 0;
    }

    int ClFileHandler::importLevelDetails(){
        char str[1000];
        inFile.getline(str, 1000);

        /*Read Nr of Static Objects to Class Variable*/
        int j = 0;
        while(str[j] != ' '){
            inNrOfObjects = 10 * inNrOfObjects + (str[j] - 48);
            j++;
        }

        inFile.getline(str, 1000);
        std::cout << str << "\n" << inNrOfObjects;
    return 0;
    }

int ClFileHandler::readLevel(std::string fileName, ClArea *pArea){

    openExistingFile(fileName.c_str());
    importLevelDetails();
    importStaticObjects(pArea);
    closeFile();

    return 0;
}
