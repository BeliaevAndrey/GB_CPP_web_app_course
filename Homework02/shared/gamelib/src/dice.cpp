#include "dice.h"

int Dice::toss()
{
    return rand() % 6 + 1;
}