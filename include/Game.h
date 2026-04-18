#ifndef DOOMCLONE_GAME_H
#define DOOMCLONE_GAME_H
#include "Screen.h"

class Game {
private:
    Screen s_;
public:
    Game(int xSize, int ySize) : s_(xSize, ySize){};
    Screen getScreen() const {return s_;}
};


#endif //DOOMCLONE_GAME_H