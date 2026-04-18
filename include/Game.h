#ifndef DOOMCLONE_GAME_H
#define DOOMCLONE_GAME_H
#include "Screen.h"
#include <vector>
#include<string>
class Game {
private:
    Screen s_;
    std::vector<std::vector<bool>> map_;
public:
    Game(int xSize, int ySize) : s_(xSize, ySize){};
    Screen getScreen() const {return s_;}
    int LoadMap(const char* filename);
    std::vector<std::vector<bool>> getMap() const {return map_;}
};


#endif //DOOMCLONE_GAME_H