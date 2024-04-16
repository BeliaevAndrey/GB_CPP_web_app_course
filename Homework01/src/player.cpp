#include "player.h"

Player::Player(int pID)
{
    this->pID = pID;
    this->name = new std::string("Player # " + std::to_string(pID));
}

Player::Player(int pID, std::string name)
{
    this->pID = pID;
    this->name = new std::string(name);
    this->isHuman = true;
}
Player::~Player()
{
    delete name;

}

int Player::throwDice(Dice* dice) { return dice->toss(); }

std::string Player::getName() { return *name; }

bool Player::isInGame() { return inGame; }

void Player::setInGame(bool status) { inGame = status; }