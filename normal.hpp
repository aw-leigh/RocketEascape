/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the "normal" terrain specification file for the final project
**               Inheirits from terrain class 
**
**               Travel time: 1
**               Initially hidden: yes
**               Interaction: none
***************************************************************/

#ifndef NORMAL_HPP
#define NORMAL_HPP

#include "terrain.hpp"

class Normal : public Terrain
{
    protected:

    public:
        Normal();
        Normal(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard, int number);
        Normal(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard);
        virtual ~Normal();
        virtual bool interact(Terrain * in, int maxRows, int maxCols, Terrain*** &gameBoard);
        virtual void print();
};

#endif  //normal