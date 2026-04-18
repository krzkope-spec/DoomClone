#ifndef DOOMCLONE_GAME_H
#define DOOMCLONE_GAME_H
#include "Screen.h"
#include <vector>
#include<string>
#include "EventManager.h"
class Game {
private:
    Screen s_;
    EventManager eventMngr_;
    int mouseX_, mouseY_;
    std::vector<std::vector<bool>> map_;
    int deltaTime_ = 10;
    void Update();
    void ProcessInput(int* x, int* y);
public:
    Game(int xSize, int ySize) : s_(xSize, ySize), eventMngr_(), mouseX_(0), mouseY_(0) {
    };
    Screen* getScreen()  {return &s_;}
    int LoadMap(const char* filename);
    std::vector<std::vector<bool>> getMap() const {return map_;}
    void Start();
    EventManager& getEventManager() {return eventMngr_;}
};


#endif //DOOMCLONE_GAME_H