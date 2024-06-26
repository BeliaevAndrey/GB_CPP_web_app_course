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
    std::cout << "\nMATCHES GAME\n" << std::endl;

    Game* game;

    int users(0);
    int total(0);

    std::cout << "Input amount of human-players: ";
    std::cin >> users;
    std::cout << "Input total amount of players: ";
    std::cin >> total;

    if (total < users) total = users;
    else if (total + users == 0) {
        std::cout << "Exiting..." << std::endl;
        exit(0);
    }

    if (users == 0)
        game = new Game(total);
    else
        game = new Game(total, users);

    game->play();


    std::cout << "\nGame finished.\n" << std::endl;
    delete game;
    return 0;
}
