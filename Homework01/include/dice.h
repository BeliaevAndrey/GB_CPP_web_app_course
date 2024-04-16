#pragma once

#include <stdlib.h>
#include <ctime>

/**
 * @brief Кость с номерами 1-6;
 * определяет количество спичек, которое должен тянуть игрок;
 */
class Dice
{
private:
    int previous;
public:
    
    int toss();
};
