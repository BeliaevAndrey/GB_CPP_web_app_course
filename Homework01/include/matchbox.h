#pragma once

#include <iostream>
#include "match.h"

/**
 * @brief Коробка спичек:
 * из неё спички тянут
 */
class MatchBox
{
private:
    int amount;
    Match** matches = nullptr;
    int current;
public:
    MatchBox(int);
    ~MatchBox();

    bool pullMatch(int);

};
