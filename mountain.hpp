/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the "mountain" terrain specification file for the final project
**               Inheirits from terrain class 
**
**               Travel time: 2
**               Initially hidden: yes
**               Interaction: climb
***************************************************************/

#ifndef MOUNTAIN_HPP
#define MOUNTAIN_HPP

#include "terrain.hpp"
#include "game.hpp"

class Game; //forward declaration

class Mountain : public Terrain
{
    protected:

    public:
        Mountain();
        Mountain(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard);
        virtual ~Mountain();
        virtual bool interact(Terrain * in, int maxRows, int maxCols, Terrain*** &gameBoard);
        virtual void print();
};

#endif  //Mountain