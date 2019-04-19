/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the "lava" terrain specification file for the final project
**               Inheirits from terrain class 
**
**               Travel time: 1
**               Initially hidden: yes
**               Interaction: death
***************************************************************/

#ifndef LAVA_HPP
#define LAVA_HPP

#include "terrain.hpp"

class Lava : public Terrain
{
    protected:

    public:
        Lava();
        Lava(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard);
        virtual ~Lava();
        virtual bool interact(Terrain * in, int maxRows, int maxCols, Terrain*** &gameBoard);
        virtual void print();
};

#endif  //Lava