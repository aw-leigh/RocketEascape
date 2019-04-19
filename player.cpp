/***************************************************************
** Program name: Final.cpp
** Author:       Andrew Wilson
** Date:         Mar 11, 2019
** Description:  This is the "player" item specification file for the final project
**               Inheirits from item class 
***************************************************************/

#include "item.hpp"
#include "player.hpp"

//Default constructor.
Player::Player()
{
    this->name = "Player";
    this->HP = 15;
}

Player::Player(Terrain * space)
{
    this->name = "Player";
    this->HP = 15;
}

Player::~Player()
{
    while(!inventory.empty()) //delete objects in inventory
    {
        delete inventory.back();
        inventory.pop_back();
    }
}
//adds to inventory and returns true if player has 4 or less parts in possession, false if 5 or more
bool Player::addToInventory(Item * item) 
{
    if(countRocketParts() > 4)
    {
        std::cout << "You already have enough rocket parts! Get to your ship!\n";
        return false;
    }
    else
    {
        this->inventory.push_back(item);
        return true;
    }
}

void Player::setHP(int HP) 
{
    this->HP = HP;
}

void Player::damageHP(int damage) 
{
    this->HP -= damage;
}

int Player::getHP()
{
    return this->HP;
}

int Player::countRocketParts()
{
    int counter = 0;
    
    //look through player's inventory for "Rocket part"s.
    for(auto i : inventory)
    {
        if(i->getName() == "Rocket part")
        {
            counter++;
        }
    }
    return counter;
}