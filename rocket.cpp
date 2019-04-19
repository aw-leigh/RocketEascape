/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the "rocket" item specification file for the final project
**               Inheirits from object class 
**
**               Name: Rocket
**               Initially hidden: no
***************************************************************/

#include "item.hpp"
#include "rocket.hpp"

//Default constructor.
Rocket::Rocket()
{
    this->name = "Rocket";
}
Rocket::Rocket(Terrain * space)
{
    this->name = "Rocket";
}

Rocket::~Rocket() {}