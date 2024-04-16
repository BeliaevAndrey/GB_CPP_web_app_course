#include "matchbox.h"


MatchBox::MatchBox(int inAmt)
{
    amount = int(inAmt);
    matches = new Match * [amount];
    for (int i = 0; i < amount; i++)
    {
        matches[i] = new Match;
    }
}
MatchBox::~MatchBox()
{
    for (int i = 0; i < amount; i++)
    {
        delete matches[i];
    }
    delete matches;
}

bool MatchBox::pullMatch(int count)
{
    if (current + count > amount) {
        current = amount;
        return false;
    }

    current += count;

    return true;
}
