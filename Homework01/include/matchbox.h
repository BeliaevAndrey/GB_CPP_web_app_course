#pragma once

#include <iostream>
#include "match.h"

/**
 * @brief Коробка спичек;
 *
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
