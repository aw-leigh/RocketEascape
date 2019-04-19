/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the "rocketpart" item specification file for the final project
**               Inheirits from object class 
**
**               Name: rocketpart
**               Initially hidden: no
***************************************************************/

#include "item.hpp"
#include "rocketpart.hpp"

//Default constructor.
Rocketpart::Rocketpart()
{
    this->name = "Rocket part";
}
Rocketpart::Rocketpart(Terrain * space)
{
    this->name = "Rocket part";
}
Rocketpart::~Rocketpart() {}