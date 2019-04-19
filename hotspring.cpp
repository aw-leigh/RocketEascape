/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the "hotspring" terrain implementation file for the final project
**               Inheirits from terrain class 
**
**               Travel time: 3
**               Initially hidden: yes
**               Interaction: heal
***************************************************************/

#include "terrain.hpp"
#include "hotspring.hpp"
#include "validation.hpp"

//Default constructor, unused.
HotSpring::HotSpring()
{
    this->fogOfWar = true;
    this->travelTime = 3;
}

//Constructor. Called on creation of terrain after initialization, updates its and its neighbor's pointers. Normal terrain takes 1 time to traverse and is hidden by default
HotSpring::HotSpring(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard): Terrain(row, col, maxRows, maxCols, gameBoard)
{
    this->row = row;
    this->col = col;
    this->fogOfWar = true;
    this->travelTime = 3;
}

//Destructor.
HotSpring::~HotSpring() {}

//Moves to space
bool HotSpring::interact(Terrain * playerSpace, int maxRows, int maxCols, Terrain*** &gameBoard)
{
    int choice;
    std::cout << "Take a dip in the hot spring to fully heal HP?" << std::endl  
              <<  "This takes 3 time instead of 1!  (1 = Yes  2 = No): ";
    choice = validateInt(1,2);
    if(choice == 1)
    {
        playerSpace->getContents()->setHP(15);
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
void HotSpring::print()
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
    else   //otherwise, print blue
    {
        std::cout << Color::BG_BLUE << Color::FG_CYAN << char(177)
                  << Color::BG_DEFAULT << Color::FG_DEFAULT;
    }
}