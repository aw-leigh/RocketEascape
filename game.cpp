/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the game implementation file for the final project
** Methods:      
***************************************************************/
#include <iostream>

#include "game.hpp"
#include "validation.hpp"
#include "terrain.hpp"
#include "normal.hpp"
#include "lava.hpp"
#include "mountain.hpp"
#include "hotspring.hpp"
#include "spikes.hpp"
#include "player.hpp"
#include "rocket.hpp"
#include "rocketpart.hpp"

const int LAVA_FREQUENCY = 12;
const int NUM_ROCKET_PARTS = 6;

//constructor. Initializes the board
Game::Game(int rows, int cols)
{
    this->numRows = rows;
    this->numCols = cols;
    this->playerDeath = false;
    this->playerWin = false;
    this->lavaTimer = LAVA_FREQUENCY;

    //create the board
    gameBoard = new Terrain**[this->numRows];

    for (int i = 0; i < this->numRows; i++)
    {
        gameBoard[i] = new Terrain*[this->numCols];
    }
    //initialize board to normal terrain
    for(int i = 0; i < this->numRows; i++)
    {
        for(int j = 0; j < this->numCols; j++)
        {
            gameBoard[i][j] = new Normal(i, j, rows, cols, gameBoard, 1);
        }
    }
    //fix all the pointers because I can't figure out how to do it in one go; now everything is doubly pointing to its neighbours.
    for(int i = 0; i < this->numRows; i++)
    {
        for(int j = 0; j < this->numCols; j++)
        {
            gameBoard[i][j]->updatePointers(i, j, rows, cols, gameBoard);
        }
    }
    
    //create the rocket in the top row, in the middle. Manually remove fog so it's visible to start.
    gameBoard[0][cols/2]->setContents(new Rocket());
    gameBoard[0][cols/2]->setFOW(false);

    //create the player on the 2nd bottom row, in the middle
    gameBoard[rows-2][cols/2]->setContents(new Player());
    playerPtr = gameBoard[rows-2][cols/2];

    addSpikes(rows-3, cols/2);

    //add items here
    for (int i = 0; i < NUM_ROCKET_PARTS; i++)
    {
        //The While-loop picks a random row/col, attempts to place a rocket part
        //if unsuccessful pick another random row/col until success
        while (!addRocketPart(rand() % this->numRows, rand() % this->numCols));
    }

    //add other terrain types here
    for (int i = 0; i < (rows*cols)/25; i++) //4% mountain
    {
        //mountains can't spawn on outside edge, only in rows 1-(numRows-2)
        while (!addMountain((rand() % (this->numRows - 2)) + 1, (rand() % (this->numCols - 2)) + 1));
    }
    
    for (int i = 0; i < (rows*cols)/20; i++) //5% spikes
    {
        while (!addSpikes(rand() % this->numRows, rand() % this->numCols));
    }
    
    for (int i = 0; i < (rows*cols)/50; i++) //2% springs
    {
        while (!addHotSpring(rand() % this->numRows, rand() % this->numCols));
    }


    /*
    for(int i = 0; i < 21; i++){
        delete gameBoard[rows-1][i]; //delete the old terrain
        gameBoard[rows-1][i] = new Lava(rows-1, i, this->numRows, this->numCols, gameBoard);  //replace it with lava
        gameBoard[rows-1][i]->setFOW(false); //set it to visible, for testing
        gameBoard[rows-1][i]->updatePointers(row, col, this->numRows, this->numCols, gameBoard);
    }*/
}

//constructor. Initializes the board
Game::~Game()
{
    //Deallocate memory for the dynamic arrow.
    for (int i = 0; i < numRows; i++)
    {
        for(int j = 0; j < numCols; j++)
        {
            delete gameBoard[i][j];
        }
        delete [] gameBoard[i];
    }
    delete [] gameBoard;
    gameBoard = nullptr;
}

//prints the board
void Game::printBoard()
{
    //print lava timer health, yellow if 3, light red if 2, red if 1
    std::cout << "Remaining turns until lava flood: ";
    if(this->lavaTimer > 3)
    {
        std::cout << this->lavaTimer << std::endl;
    }
    if(this->lavaTimer == 3)
    {
        std::cout << Color::FG_YELLOW << this->lavaTimer << Color::FG_DEFAULT << std::endl;
    }
    else if(this->lavaTimer == 2)
    {
        std::cout << Color::FG_LIGHT_RED << this->lavaTimer << Color::FG_DEFAULT << std::endl;
    }
    else if(this->lavaTimer <= 1)
    {
        std::cout << Color::FG_RED << this->lavaTimer << Color::FG_DEFAULT << std::endl;
    }

    //print player health, yellow if 6-10, red if 1-5
    if(playerPtr->getContents()->getHP() <= 5)
    {
        std::cout << "HP: " << Color::FG_LIGHT_RED << playerPtr->getContents()->getHP() << Color::FG_DEFAULT << "/15" << std::endl;
    }
    else if(playerPtr->getContents()->getHP() <= 10)
    {
        std::cout << "HP: " << Color::FG_YELLOW << playerPtr->getContents()->getHP() << Color::FG_DEFAULT << "/15" << std::endl;
    }
    else
    {
        std::cout << "HP: " << playerPtr->getContents()->getHP() << "/15" << std::endl;
    }

    //print rocket parts held in default color if 0-4
    if(playerPtr->getContents()->countRocketParts() < 5)
    {
        std::cout << "Rocket parts: " << playerPtr->getContents()->countRocketParts() << "/5" << std::endl;
    }
    else  //print magenta if 5/5
    {
        std::cout << "Rocket parts: " << Color::FG_MAGENTA << playerPtr->getContents()->countRocketParts() << "/5" << Color::FG_DEFAULT  << std::endl;
    }

    
    //reveal terrain adjacent to player
    playerPtr->updateFOW(this->numRows, this->numCols, this->gameBoard);

    //Top border
    std::cout.width(numCols + 2);
    std::cout.fill('-');
    std::cout << '-' << std::endl;
    std::cout.fill(' ');

    for(int i = 0; i < numRows; i++)
    {
        //if there are 3 or fewer turns before lava, print the border left side bars yellow -> light red -> red as a warning
        if(this->lavaTimer == 3 && i == (this->numRows - this->lavaCounter)){ 
            std::cout << Color::FG_YELLOW << "|" << Color::FG_DEFAULT;
        }
        else if(this->lavaTimer == 2 && i == (this->numRows - this->lavaCounter)){ 
            std::cout << Color::FG_LIGHT_RED << "|" << Color::FG_DEFAULT;
        }
        else if(this->lavaTimer == 1 && i == (this->numRows - this->lavaCounter)){ 
            std::cout << Color::FG_RED << "|" << Color::FG_DEFAULT;
        }
        else{
            std::cout << "|";
        }

        //print the board
        for(int j = 0; j < numCols; j++)
        {
            gameBoard[i][j]->print();
        }

        //if there are 3 or fewer turns before lava, print border right side bars yellow -> light red -> red as a warning
        if(this->lavaTimer == 3 && i == (this->numRows - this->lavaCounter)){ 
            std::cout << Color::FG_YELLOW << "|\n" << Color::FG_DEFAULT;
        }
        else if(this->lavaTimer == 2 && i == (this->numRows - this->lavaCounter)){ 
            std::cout << Color::FG_LIGHT_RED << "|\n" << Color::FG_DEFAULT;
        }
        else if(this->lavaTimer == 1 && i == (this->numRows - this->lavaCounter)){ 
            std::cout << Color::FG_RED << "|\n" << Color::FG_DEFAULT;
        }        
        else{
            std::cout << "|\n";
        }
    }

    //Bottom border
    std::cout.width(numCols + 2);
    std::cout.fill('-');
    std::cout << '-' << std::endl;
    std::cout.fill(' ');
}

//prints the board
bool Game::runGame()
{
    while(!this->playerDeath && !this->playerWin)  //loop until player wins or dies
    {
        int direction;
        bool moved = false;
        printBoard();

        //Player interact/move
        do{
            //choose direction
            std::cout << "Choose a direction to move (1 = Up  2 = Left  3 = Down  4 = Right): ";
            direction = validateInt(1, 4);
            
            switch(direction)
            {
                case 1: 
                {
                    if(playerPtr->getUp() == nullptr){
                        std::cout << "You can't move any further in this direction!" << std::endl;
                    }
                    else{
                        moved = move(playerPtr->getUp(), this->numRows, this->numCols, gameBoard);
                    }
                } break;
                case 2:
                {
                    if(playerPtr->getLeft() == nullptr){
                        std::cout << "You can't move any further in this direction!" << std::endl;
                    }
                    else{
                        moved = move(playerPtr->getLeft(), this->numRows, this->numCols, gameBoard);
                    }
                } break;
                case 3:
                {
                    if(playerPtr->getDown() == nullptr){
                        std::cout << "You can't move any further in this direction!" << std::endl;
                    }
                    else{
                        moved = move(playerPtr->getDown(), this->numRows, this->numCols, gameBoard);
                    }
                } break;
                case 4:
                {
                    if(playerPtr->getRight() == nullptr){
                        std::cout << "You can't move any further in this direction!" << std::endl;
                    }
                    else{
                        moved = move(playerPtr->getRight(), this->numRows, this->numCols, gameBoard);
                    }
                } break;
            }
        }while(!moved);

        //decrement time remaining until lava. if >= 0, lava, and reset timer
        lavaCalc(playerPtr->getTravelTime());

        //check if player is on lava or at 0 HP
        if(playerPtr->getIsLava() || playerPtr->getContents()->getHP() < 1)
        {
            playerDeath = true;
        }
    }
    if(playerDeath)
    {
        return false;
    }
    if(playerWin)
    {
        return true;
    }
}

bool Game::move(Terrain* destination, int maxRows, int maxCols, Terrain*** &gameBoard)
{
    //clearScreen();
    if(destination->getContents() != nullptr)
    {
        if(destination->getContents()->getName() == "Rocket part") //add part to player inventory
        {
            //pick it up, if player has 4 or fewer in inventory
            if(playerPtr->getContents()->addToInventory(destination->getContents()))
            {
                destination->setContents(nullptr);
                std::cout << "You found a rocket part!" << std::endl;
            }
            else //player limited to 5 rocket parts
            {
                return false;
            }
        }
        else if(destination->getContents()->getName() == "Rocket") //check if player has 5 rocket parts
        {
            if(playerPtr->getContents()->countRocketParts() >= 5) //player has enough parts to win
            {
                playerWin = true;
                return true;
            }
            else
            {
                std::cout << "You need " << Color::FG_MAGENTA << 5 - playerPtr->getContents()->countRocketParts() 
                          << Color::FG_DEFAULT <<" more parts to repair your rocket!" << std::endl;
                return false;
            }
        }        
    }
    if(destination->interact(playerPtr, maxRows, maxCols, gameBoard)) //if interation was succesful, update player pointer
    {
        playerPtr = destination;
        return true;
    }
    else //if interaction was not successful, kick them back to the direction choice switch
    {
        return false;
    }
}

void Game::lavaCalc(int input)
{
    this->lavaTimer -= input;
    if(this->lavaTimer <= 0)
    {
        for(int i = 0; i < this->numCols; i++)
        {
            addLava(this->numRows - this->lavaCounter, i);
            gameBoard[this->numRows - this->lavaCounter][i]->setFOW(false);
        }
        for(int i = 0; i < this->numCols; i++) //fix the pointers...
        {
            gameBoard[this->numRows - this->lavaCounter][i]->updatePointers(this->numRows - this->lavaCounter, i, this->numRows, this->numCols, gameBoard);
        }
        //change row - lavaCounter to lava panels
        this->lavaTimer += LAVA_FREQUENCY;
        this->lavaCounter++;
    }
}

bool Game::addRocketPart(int row, int col)
{
    if (gameBoard[row][col]->getContents() == nullptr) //if the space doesn't have an item already
    {
        gameBoard[row][col]->setContents(new Rocketpart()); //put rocket part there
        return true;
    }
    else  //if the board spot is already filled, return false
    {
        return false;
    }
}

bool Game::addLava(int row, int col)
{
    if (gameBoard[row][col]->getContents() != nullptr) //if the space has an item,
    {
        if(gameBoard[row][col]->getContents()->getName() == "Player") //if it's the player, kill him
        {
            this->playerDeath = true;
        }
        else //if it's anything besides the player, delete it
        {
            delete gameBoard[row][col]->getContents();
            gameBoard[row][col]->setContents(nullptr);
        }
    }
    delete gameBoard[row][col];  //delete the old terrain, add lava, update pointers
    gameBoard[row][col] = new Lava(row, col, this->numRows, this->numCols, gameBoard);
    gameBoard[row][col]->updatePointers(row, col, this->numRows, this->numCols, gameBoard);
    return true;
}

bool Game::addMountain(int row, int col)
{
    //if the space holds an item or if it's non-normal terrain
    if(gameBoard[row][col]->getContents() != nullptr || !gameBoard[row][col]->getIsNormal())
    {
        return false;
    }
    else
    {
        delete gameBoard[row][col];  //delete the old terrain, add a mountain, update pointers
        gameBoard[row][col] = new Mountain(row, col, this->numRows, this->numCols, gameBoard); 
        gameBoard[row][col]->updatePointers(row, col, this->numRows, this->numCols, gameBoard);
        //gameBoard[row][col]->setFOW(false);  uncomment to see where they are; for testing
        return true;
    }
}

bool Game::addHotSpring(int row, int col)
{
    //if the space holds an item or if it's non-normal terrain
    if(gameBoard[row][col]->getContents() != nullptr || !gameBoard[row][col]->getIsNormal())
    {
        return false;
    }
    else
    {
        delete gameBoard[row][col];  //delete the old terrain, add a mountain, update pointers
        gameBoard[row][col] = new HotSpring(row, col, this->numRows, this->numCols, gameBoard); 
        gameBoard[row][col]->updatePointers(row, col, this->numRows, this->numCols, gameBoard);
        //gameBoard[row][col]->setFOW(false);  uncomment to see where they are; for testing
        return true;
    }
}

bool Game::addSpikes(int row, int col)
{
    //if the space holds an item or if it's non-normal terrain
    if(gameBoard[row][col]->getContents() != nullptr || !gameBoard[row][col]->getIsNormal())
    {
        return false;
    }
    else
    {
        delete gameBoard[row][col];  //delete the old terrain, add a mountain, update pointers
        gameBoard[row][col] = new Spikes(row, col, this->numRows, this->numCols, gameBoard); 
        gameBoard[row][col]->updatePointers(row, col, this->numRows, this->numCols, gameBoard);
        //gameBoard[row][col]->setFOW(false);  uncomment to see where they are; for testing
        return true;
    }
}