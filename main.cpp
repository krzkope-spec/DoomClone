#include<iostream>
#include "Game.h"
#include "Testing.h"
int main() {
    Game game = Game(80,30);
    Testing testing = Testing(game);
    testing.PrintGreyScaleOnScreen();
    std::cin.get();
    return EXIT_SUCCESS;
}
