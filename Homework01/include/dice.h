#pragma once

#include <stdlib.h>
#include <ctime>

/**
 * @brief Кость с номерами 1-6;
 * определяет количество спичек, которое должен тянуть автоматический игрок;
 */
class Dice
{
private:
    int previous;   // предыдущее значение зерна для rand()
public:
    
    int toss();     // бросить кость
};
