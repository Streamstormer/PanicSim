/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Patrick Senneka und Victor Schwartz
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    creates a label and two buttons to set the "Besucheranzahl"
---------------------------------------------------------------------------------------------------------------------------------------
*/
#ifndef SimpleParamField_HPP_INCLUDED
#define SimpleParamField_INCLUDED

#include "SimpleLabel.hpp"
#include "SimpleButton.hpp"
#include <SFML/Graphics.hpp>

class ClSimpleParamField
{
public:
    ClSimpleParamField();
    ~ClSimpleParamField();

    int getValue();

private:
    int value;

};
#endif // PATH_HPP_INCLUDED
