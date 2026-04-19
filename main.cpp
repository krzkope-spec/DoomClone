#include<iostream>
#include "Game.h"
#include "Testing.h"
int main() {
    Game game = Game(80,35);
    Testing testing = Testing(game);
    testing.printMap();
    game.Start();
    return EXIT_SUCCESS;
}
