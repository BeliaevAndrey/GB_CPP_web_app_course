/*
Реализуйте игру в спички в нескольких заголовочных файлах (каждый класс или
логически связанный набор функций в отдельном файле). Напишите CMake который в
результате отработки генерирует исполняемый файл.

Игра в спички:
определенное количество спичек задается в начале игры. После этого каждый из
игроков тянет от 1 до N спичек — проигрывает тот кто вытянул последнюю спичку.
*/
#include <iostream>


struct Match {};


class FistfulOfMatches
{
private:
    int amount;
    Match** matches = nullptr;
public:
    FistfulOfMatches(int inAmt)
    {
        amount = int(inAmt);
        matches = new Match * [amount];
        for (int i = 0; i < amount; i++)
        {
            matches[i] = new Match;
        }
    }
    ~FistfulOfMatches()
    {
        for (int i=0; i < amount; i++)
        {
            delete this->matches[i];
            std::cout << "deleted" << i << "\n";
        }
        std::cout << std::endl;
    }

    void pullMatch() {

    }
};


class Dice
{
public:
    int throwDice() { return (rand() + 1) % 6; }
};


class Player
{
private:
    const char* name;
    int pID;
    Dice* dice;
public:
    Player(int pID)
    {
        this->pID = pID;
        this->dice = new Dice();
        this->name = "Player # " + pID;
    }
    ~Player()
    {
        delete name;
        delete dice;
    }

    int dropDice()
    {
        return dice->throwDice();
    }

    const char* getName()
    {
        return name;
    }

};

int main()
{
    FistfulOfMatches* fm = new FistfulOfMatches(20);

    delete fm;
    return 0;
}