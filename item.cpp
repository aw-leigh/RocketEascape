/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the object implementation file for the final project
**               Objects are held by terrain or the player. 
***************************************************************/
#include <iostream>

#include "item.hpp"

Item::Item()
{
    this->name = "ERROR1337";
}
Item::Item(Terrain * space)
{
    this->name = "ERROR1337";
    this->space = space;
}
std::string Item::getName()
{
    return this->name;
}