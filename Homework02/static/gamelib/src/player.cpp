#include "player.h"

Player::Player(int pID)
{
    this->pID = pID;
    this->name = new std::string("Player # " + std::to_string(pID));
}

Player::Player(std::string name)
{
    this->name = new std::string(name);
    this->user = true;
}
Player::~Player()
{
    delete name;
}


std::string Player::getName() { return *name; }

bool Player::isInGame() { return inGame; }

bool Player::isUser() { return user; }

void Player::setInGame(bool status) { inGame = status; }

void Player::matchesAmt(Dice* dice, int& count)
{
    count = dice->toss();
}

void Player::matchesAmt(int& count) {
    std::cout << "Input amount of matches to take: ";
    std::cin >> count;
}
