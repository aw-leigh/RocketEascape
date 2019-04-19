/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the "normal" terrain implementation file for the final project
**               Inheirits from terrain class 
**
**               Travel time: 1
**               Initially hidden: yes
**               Interaction: none
***************************************************************/

#include "terrain.hpp"
#include "normal.hpp"

//Default constructor, unused.
Normal::Normal()
{
    this->fogOfWar = true;
    this->travelTime = 1;
    this->isNormal = true;
}

//Constructor. Called only on board construction, updates only its pointers.
Normal::Normal(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard, int number): Terrain(row, col, maxRows, maxCols, gameBoard, number)
{
    this->row = row;
    this->col = col;
    this->fogOfWar = true;
    this->travelTime = 1;
    this->isNormal = true;
}

//Constructor. Called on creation of terrain after initialization, updates its and its neighbor's pointers. Normal terrain takes 1 time to traverse and is hidden by default
Normal::Normal(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard): Terrain(row, col, maxRows, maxCols, gameBoard)
{
    this->row = row;
    this->col = col;
    this->fogOfWar = true;
    this->travelTime = 1;
    this->isNormal = true;
}

//Destructor.
Normal::~Normal() {}

//Moves to space
bool Normal::interact(Terrain * playerSpace, int maxRows, int maxCols, Terrain*** &gameBoard)
{
    this->setContents(playerSpace->getContents());  //point new space to player
    playerSpace->setContents(nullptr);
    
    return true;
}

//Grey if unfound, blank if found
void Normal::print()
{
    if(this->fogOfWar)  //grey if fog of war
    {
        std::cout << Color::BG_DARK_GRAY << ' ' << Color::BG_DEFAULT;  //prints gray tile if hidden
    }
    else if(this->contents != nullptr) //if it's not empty, print what it holds
    {
        if(this->contents->getName() == "Player"){
            std::cout << 'P';
        }
        else if(this->contents->getName() == "Rocket"){
            std::cout << Color::FG_MAGENTA << 'R' << Color::FG_DEFAULT;
        }
        else if(this->contents->getName() == "Rocket part"){
            std::cout << Color::FG_MAGENTA << 'r' << Color::FG_DEFAULT;
        }
    }
    else  //if it's empty, print blank
    {
        std::cout << ' ';  //otherwise prints default blank square
    }
}