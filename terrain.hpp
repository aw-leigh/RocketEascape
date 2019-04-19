/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the terrain specification file for the final project
**               All spaces on the board inheirit from this virtual class 
***************************************************************/

#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <iostream>
#include "color.hpp"
#include "item.hpp"
class Item; //forward declaration

class Terrain
{
    protected:
        Terrain * up = nullptr;
        Terrain * down = nullptr;
        Terrain * left = nullptr;
        Terrain * right = nullptr;
        Item * contents = nullptr;
        int row;
        int col;
        bool fogOfWar;
        bool isLava = false;
        bool isNormal = false;
        int travelTime;

    public:
        Terrain() {};
        Terrain(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard, int number);
        Terrain(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard);
        virtual ~Terrain();

        virtual Terrain * getUp();
        virtual Terrain * getDown();
        virtual Terrain * getLeft();
        virtual Terrain * getRight();
        virtual Item * getContents();
        virtual bool getIsLava();
        virtual bool getIsNormal();
        virtual int getTravelTime();
        virtual void setUp(Terrain * in);
        virtual void setDown(Terrain * in);
        virtual void setLeft(Terrain * in);
        virtual void setRight(Terrain * in);
        virtual void setContents(Item * in);

        virtual void deleteTerrain(int maxRows, int maxCols);
        virtual bool interact(Terrain * playerSpace, int maxRows, int maxCols, Terrain*** &gameBoard) = 0;
        virtual void print();
        virtual void updatePointers(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard);
        virtual void setFOW(bool in);
        virtual void updateFOW(int maxRow, int maxCol, Terrain*** &gameBoard);
};

#endif