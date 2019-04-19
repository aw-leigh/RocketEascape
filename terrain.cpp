/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the terrain specification file for the final project
**               All spaces on the board inheirit from this virtual class 
***************************************************************/
#include <iostream>
#include "terrain.hpp"

//Constructor. Called on creation of terrain after initialization, updates its and its neighbor's pointers. 
Terrain::Terrain(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard)
{
    if(row == 0){  //if we're in the top row, up is null
        this->up = nullptr;
    }
    else{
        this->up = gameBoard[row - 1][col];
        this->up->setDown(this); 
    }

    if(row == maxRows-1){  //if we're in the bottom row, down is null
        this->down = nullptr;
    }
    else{
        this->down = gameBoard[row + 1][col];
        gameBoard[row + 1][col]->setUp(this);
    }

    if(col == 0){  //if we're in the left col, left is null
        this->left = nullptr;
    }
    else{
        this->left = gameBoard[row][col - 1];
        this->left->setRight(this);
    }

    if(col == maxCols-1){  //if we're in the right col, right is null
        this->right = nullptr;
    }
    else{
        this->right = gameBoard[row][col + 1];
        this->right->setLeft(this); 
    }
}
//Constructor. Called only on board construction, updates only its pointers.
Terrain::Terrain(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard, int number)
{
    if(row == 0){  //if we're in the top row, up is null
        this->up = nullptr;
    }
    else{
        this->up = gameBoard[row - 1][col];
    }

    if(row == maxRows-1){  //if we're in the bottom row, down is null
        this->down = nullptr;
    }
    else{
        this->down = gameBoard[row + 1][col];
    }

    if(col == 0){  //if we're in the left col, left is null
        this->left = nullptr;
    }
    else{
        this->left = gameBoard[row][col - 1];
    }

    if(col == maxCols-1){  //if we're in the right col, right is null
        this->right = nullptr;
    }
    else{
        this->right = gameBoard[row][col + 1];
    }    
}

Terrain::~Terrain()
{
    if(this->contents != nullptr) //if it contains something, delete it. This should delete all items (incl. player)
    {
        delete this->contents;
        this->contents = nullptr;
    }
}

void Terrain::deleteTerrain(int maxRows, int maxCols)
{
    if(row != 0){  //unless we're in the top row, set the above space's down pointer to null
        this->up->setDown(nullptr);
    }

    if(row != maxRows-1){  //unless we're in the bottom row, set the below space's up pointer to null
        this->down->setUp(nullptr);
    }

    if(col != 0){  //unless we're in the left col, set the left space's right pointer to null
        this->left->setRight(nullptr);
    }

    if(col != maxCols-1){  //unless we're in the right col, set the right space's right pointer to null
        this->right->setLeft(nullptr); 
    }
    delete this;
}

void Terrain::updatePointers(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard)
{
    if(row != 0){  //unless we're in the top row, set the above space's down pointer to this
        this->up = gameBoard[row-1][col];
        this->up->setDown(this);
    }

    if(row != maxRows-1){  //unless we're in the bottom row, set the below space's up pointer to this
        this->down = gameBoard[row+1][col];
        this->down->setUp(this);
    }

    if(col != 0){  //unless we're in the left col, set the left space's right pointer to this
        this->left = gameBoard[row][col-1];
        this->left->setRight(this);
    }

    if(col != maxCols-1){  //unless we're in the right col, set the right space's right pointer to this
        this->right = gameBoard[row][col+1];
        this->right->setLeft(this); 
    }    
}
//Default constructor. Normal terrain takes 1 time to traverse and is hidden by default
Terrain * Terrain::getUp()
{
    return this->up;
}
Terrain * Terrain::getDown()
{
    return this->down;
}
Terrain * Terrain::getLeft()
{
    return this->left;
}
Terrain * Terrain::getRight()
{
    return this->right;
}
Item * Terrain::getContents()
{
    return this->contents;
}
bool Terrain::getIsLava()
{
    return this->isLava;
}
bool Terrain::getIsNormal()
{
    return this->isNormal;
}
int Terrain::getTravelTime()
{
    return this->travelTime;
}
void Terrain::setUp(Terrain * in)
{
    this->up = in;
}
void Terrain::setDown(Terrain * in)
{
    this->down = in;
}
void Terrain::setLeft(Terrain * in)
{
    this->left = in;
}
void Terrain::setRight(Terrain * in)
{
    this->right = in;
}
void Terrain::setContents(Item * in)
{
    this->contents = in;
}
void Terrain::setFOW(bool in)
{
    this->fogOfWar = in;
}

void Terrain::updateFOW(int maxRow, int maxCol, Terrain*** &gameBoard)
{
    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            //don't dereference null pointers
            if(this->row + i < maxRow && this->row + i >= 0 && this->col + j < maxCol && this->col + j >= 0)
            {
                gameBoard[this->row + i][this->col + j]->setFOW(false);
            }
        }
    }
}

void Terrain::print()
{
    if(this->contents != nullptr)
    {
        if(this->contents->getName() == "Player")
        std::cout << 'P';
    }
}