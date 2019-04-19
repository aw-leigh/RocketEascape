/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the "hotspring" terrain specification file for the final project
**               Inheirits from terrain class 
**
**               Travel time: 3
**               Initially hidden: yes
**               Interaction: heal
***************************************************************/

#ifndef HOTSPRING_HPP
#define HOTSPRING_HPP

#include "terrain.hpp"

class HotSpring : public Terrain
{
    protected:

    public:
        HotSpring();
        HotSpring(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard);
        virtual ~HotSpring();
        virtual bool interact(Terrain * in, int maxRows, int maxCols, Terrain*** &gameBoard);
        virtual void print();
};

#endif  //hotspring