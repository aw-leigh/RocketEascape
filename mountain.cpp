/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the "mountain" terrain implementation file for the final project
**               Inheirits from terrain class 
**
**               Travel time: 2
**               Initially hidden: yes
**               Interaction: climb
***************************************************************/

#include "terrain.hpp"
#include "mountain.hpp"
#include "validation.hpp"

//Default constructor, unused.
Mountain::Mountain()
{
    this->fogOfWar = true;
    this->travelTime = 3;
}

//Constructor. Called on creation of terrain after initialization, updates its and its neighbor's pointers. Normal terrain takes 1 time to traverse and is hidden by default
Mountain::Mountain(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard): Terrain(row, col, maxRows, maxCols, gameBoard)
{
    this->row = row;
    this->col = col;
    this->fogOfWar = true;
    this->travelTime = 3;
}

//Destructor.
Mountain::~Mountain() {}

//Moves to space
bool Mountain::interact(Terrain * playerSpace, int maxRows, int maxCols, Terrain*** &gameBoard)
{
    int choice;
    std::cout << "Climb the mountain to see farther?" << std::endl  
              <<  "This takes 3 time instead of 1!  (1 = Yes  2 = No): ";
    choice = validateInt(1,2);
    if(choice == 1)
    {
        this->setContents(playerSpace->getContents());  //point new space to player
        playerSpace->setContents(nullptr);
        this->getLeft()->getUp()->updateFOW(maxRows, maxCols, gameBoard);
        this->getLeft()->getDown()->updateFOW(maxRows, maxCols, gameBoard);
        this->getRight()->getUp()->updateFOW(maxRows, maxCols, gameBoard);
        this->getRight()->getDown()->updateFOW(maxRows, maxCols, gameBoard);
        return true;
    }
    else
    {
        return false;
    }
}

//Grey if unfound, blank if found
void Mountain::print()
{
    if(this->fogOfWar)  //grey if fog of war
    {
        std::cout << Color::BG_DARK_GRAY << ' ' << Color::BG_DEFAULT;  //prints gray tile if hidden
    }
    else if(this->contents != nullptr)
    {
        if(this->contents->getName() == "Player"){
            std::cout << 'P';
        }
    }
    else   //otherwise, print grey M
    {
        std::cout << Color::FG_DARK_GRAY << 'M' 
                  << Color::BG_DEFAULT << Color::FG_DEFAULT;  //otherwise prints hot lava colors
    }
}