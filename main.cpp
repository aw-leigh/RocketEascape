/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the main file for the final project
***************************************************************/
#include <iostream>
#include <cstdlib> 		//seeding random function
#include <ctime> 		//time() used in seeding the random function
#include "game.hpp"
#include "headerGraphics.hpp"
#include "validation.hpp"

int main()
{
    srand(time(NULL));
    titleScreen();
    
    Game game(21, 21);
    if(game.runGame()) //returns true if player wins, false if player dies
    {
        youWin();
    }
    else
    {
        youLose();
    }
    
    return 0;
}