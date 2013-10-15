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
/* Doesn't need to be encapsulated
int ClFileHandler::closeFile(){

    myFile.close();
    return 0;
}
*/

int ClFileHandler::writeHeader(ClArea *pArea){
    int x = pArea->getNumberOfStaticObjects();
    myFile << x << " StaticObjectId" << "; Position Xf; Position Yf; Size Xf; Size Yf; Rotation f; Type i; Levelsize X; Levelsize Y; BGColor; Persons count\n";
    return 0;
}

int ClFileHandler::openExistingFile(const char *fileName){
    try{
        inFile.open(fileName);
    }catch(std::ios_base::failure){
        std::cout<<"Error";
        return 1;
    }
    return 0;
}

int ClFileHandler::writeLevel(std::string fileName, ClArea *pArea){

    int code = createFile(fileName.c_str());
    if(code != 0)
        return code;
    code = writeHeader(pArea);
    if(code != 0)
        return code;
    code = writeLevelDetails();
    if(code != 0)
        return code;
    code = writeStaticObjects(pArea);
    if(code != 0)
        return code;
    myFile.flush();
    myFile.close();
    //readLevel("test.csv", pArea);
    return 0;
}

    int ClFileHandler::importStaticObjects(ClArea *pArea){
        int returnCode = 0;
        char str[1000];
        float props[7];
        int multiplier = 10;
        int divider = 1;
        for(unsigned int i = 0; i < inNrOfObjects; i++){
        inFile.getline(str,1000);
            int j = 0;
            for(int k = 0; k<7; k++){
            props[k] = 0;

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
                j++;
            }
            sf::Vector2f position;
            position.x = props[1];
            position.y = props[2];
            sf::Vector2f objectSize;
            objectSize.x = props[3];
            objectSize.y = props[4]; // not unsigned, because then it is always false
            int type = (int) props[6];
            if(type < 0 || type > MAXSTATICOBJECTTYPES){
                type = (int) WALL;
                returnCode = 3;
            }
            pArea->insertStObj((enum staticObjects)type,objectSize,position,props[5]);


        }
        return returnCode;
    }

    int ClFileHandler::importLevelDetails(){
        char str[1000];
        inFile.getline(str, 1000);

        /*Read Nr of Static Objects to Class Variable*/
        int j = inNrOfObjects = 0;
        while(str[j] != ' '){
            inNrOfObjects = 10 * inNrOfObjects + (str[j] - 48);
            j++;
        }

        inFile.getline(str, 1000);
        std::cout << str << "\n" << inNrOfObjects;
    return 0;
    }

int ClFileHandler::readLevel(std::string fileName, ClArea *pArea){
    int code = openExistingFile(fileName.c_str());
    if(code != 0)
        return code;
    code = importLevelDetails();
    if(code != 0)
        return code;
    code = importStaticObjects(pArea);
    if(code != 0)
        return code;
    inFile.close();

    return 0;
}
