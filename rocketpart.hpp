/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the "rocketpart" item specification file for the final project
**               Inheirits from item class 
**
**               Name: Rocketpart
**               Initially hidden: yes
***************************************************************/

#ifndef ROCKETPART_HPP
#define ROCKETPART_HPP

#include "item.hpp"

class Rocketpart : public Item
{
    protected:

    public:
        Rocketpart();
        Rocketpart(Terrain * space);
        virtual ~Rocketpart();
};

#endif  //Rocketpart