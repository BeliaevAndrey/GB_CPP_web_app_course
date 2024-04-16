/*
Реализуйте игру в спички в нескольких заголовочных файлах (каждый класс или
логически связанный набор функций в отдельном файле). Напишите CMake который в
результате отработки генерирует исполняемый файл.

Игра в спички:
определенное количество спичек задается в начале игры. После этого каждый из
игроков тянет от 1 до N спичек — проигрывает тот кто вытянул последнюю спичку.
*/
#include <iostream>

#include "game.h"


int main()
{
    Game* game;

    int humans(0);
    int total(0);

    std::cout << "Input amount of human-players: ";
    std::cin >> humans;
    std::cout << "Input total amount of players: ";
    std::cin >> total;

    if(total < humans) total = humans;
    
    if(humans == 0)
        game = new Game(total);
    else
        game = new Game(total, humans);

    game->play();


    delete game;
    return 0;
}