/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Patrick Senneka und Victor Schwartz
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    creates a label and two buttons to set the "Besucheranzahl"
---------------------------------------------------------------------------------------------------------------------------------------
*/
#include "../../include/Simulator/SimpleParamField.hpp"

ClSimpleParamField::ClSimpleParamField()
{
    this->value = 0;
}
ClSimpleParamField::~ClSimpleParamField()
{
    //dtor
}
int ClSimpleParamField::getValue()
{
    return value;
}
