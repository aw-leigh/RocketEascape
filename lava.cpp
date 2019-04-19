/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the "lava" terrain implementation file for the final project
**               Inheirits from terrain class 
**
**               Travel time: 1
**               Initially hidden: yes
**               Interaction: none
***************************************************************/

#include "terrain.hpp"
#include "lava.hpp"
#include "validation.hpp"

//Default constructor, unused.
Lava::Lava()
{
    this->fogOfWar = true;
    this->travelTime = 1;
    this->isLava = true;
}

//Constructor. Called on creation of terrain after initialization, updates its and its neighbor's pointers. Normal terrain takes 1 time to traverse and is hidden by default
Lava::Lava(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard): Terrain(row, col, maxRows, maxCols, gameBoard)
{
    this->row = row;
    this->col = col;
    this->fogOfWar = true;
    this->travelTime = 1;
    this->isLava = true;
}

//Destructor.
Lava::~Lava() {}

//Moves to space
bool Lava::interact(Terrain * playerSpace, int maxRows, int maxCols, Terrain*** &gameBoard)
{
    int choice;
    std::cout << "Are you sure you want to step into lava? (1 = Yes  2 = No): ";
    choice = validateInt(1,2);
    if(choice == 1)
    {
        this->setContents(playerSpace->getContents());  //point new space to player
        playerSpace->setContents(nullptr);
        return true;
    }
    else
    {
        return false;
    }
}

//Grey if unfound, blank if found
void Lava::print()
{
    if(this->fogOfWar)  //grey if fog of war
    {
        std::cout << Color::BG_DARK_GRAY << ' ' << Color::BG_DEFAULT;
    }
    else  //otherwise prints hot lava colors
    {
        std::cout << Color::BG_RED << Color::FG_LIGHT_RED << '#'
                  << Color::BG_DEFAULT << Color::FG_DEFAULT;  
    }
}