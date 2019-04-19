/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the "rocket" item specification file for the final project
**               Inheirits from item class 
**
**               Name: Rocket
**               Initially hidden: no
***************************************************************/

#ifndef ROCKET_HPP
#define ROCKET_HPP

#include "item.hpp"

class Rocket : public Item
{
    protected:

    public:
        Rocket();
        Rocket(Terrain * space);
        virtual ~Rocket();
};

#endif  //Rocket