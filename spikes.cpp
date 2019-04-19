/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the "spikes" terrain implementation file for the final project
**               Inheirits from terrain class 
**
**               Travel time: 1
**               Initially hidden: yes
**               Interaction: damage
***************************************************************/

#include "terrain.hpp"
#include "spikes.hpp"
#include "validation.hpp"

//Default constructor, unused.
Spikes::Spikes()
{
    this->fogOfWar = true;
    this->travelTime = 1;
}

//Constructor. Called on creation of terrain after initialization, updates its and its neighbor's pointers. Normal terrain takes 1 time to traverse and is hidden by default
Spikes::Spikes(int row, int col, int maxRows, int maxCols, Terrain*** &gameBoard): Terrain(row, col, maxRows, maxCols, gameBoard)
{
    this->row = row;
    this->col = col;
    this->fogOfWar = true;
    this->travelTime = 1;
}

//Destructor.
Spikes::~Spikes() {}

//Moves to space
bool Spikes::interact(Terrain * playerSpace, int maxRows, int maxCols, Terrain*** &gameBoard)
{
    int choice;
    std::cout << "Cross the spikes?" << std::endl  
              <<  "You'll take 3 HP damage!  (1 = Yes  2 = No): ";
    choice = validateInt(1,2);
    if(choice == 1)
    {
        playerSpace->getContents()->damageHP(3);
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
void Spikes::print()
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
    else   //otherwise, print spikes
    {
        std::cout << Color::FG_DARK_GRAY << '+'
                  << Color::BG_DEFAULT << Color::FG_DEFAULT;
    }
}