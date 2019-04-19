/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the "spikes" terrain specification file for the final project
**               Inheirits from terrain class 
**
**               Travel time: 1
**               Initially hidden: yes
**               Interaction: damage
***************************************************************/

#ifndef SPIKES_HPP
#define SPIKES_HPP

#include "terrain.hpp"

class Spikes : public Terrain
{
    protected:

    public:
        Spikes();
        Spikes(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard);
        virtual ~Spikes();
        virtual bool interact(Terrain * in, int maxRows, int maxCols, Terrain*** &gameBoard);
        virtual void print();
};

#endif  //spikes