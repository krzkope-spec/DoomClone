#include<iostream>
#include "Game.h"
#include "Testing.h"
int main() {
    Game game = Game(120,45);
    Testing testing = Testing(game);
    //testing.printMap();
    //testing.Raycasting();
    game.Start();
    return EXIT_SUCCESS;
}
