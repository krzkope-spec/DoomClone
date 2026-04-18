#include<iostream>
#include "Game.h"
#include "Testing.h"
int main() {
    Game game = Game(80,30);
    Testing testing = Testing(game);
    testing.printMap();
    std::cin.get();
    return EXIT_SUCCESS;
}
