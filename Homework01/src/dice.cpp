#include "dice.h"

int Dice::toss()
{
    int seed = time(nullptr);
    seed = (seed == previous) ? (seed / 3) * 2 / 3 : seed;
    srand(seed);
    int number = rand() % 6 + 1;
    previous = seed;

    return number;
}