#ifndef DOOMCLONE_GAME_H
#define DOOMCLONE_GAME_H
#include "Screen.h"
#include <vector>
#include<string>
#include "EventManager.h"
#include "Player.h"

class Game {
private:
    Screen s_;
    EventManager eventMngr_;
    int mouseX_, mouseY_;
    const double DPI = 0.05;
    std::vector<std::vector<bool>> map_;
    Player player_;
    int deltaTime_ = 10;
    void Update();
    void ProcessInput(int* x, int* y);
    void MovePlayer(int input);
    void RotatePlayer(double angle);
public:
    Game(int xSize, int ySize) : s_(xSize, ySize), eventMngr_(), mouseX_(0), mouseY_(0), player_(1,1){
    };
    Screen* getScreen()  {return &s_;}
    int LoadMap(const char* filename);
    std::vector<std::vector<bool>> getMap() const {return map_;}
    void Start();
    EventManager& getEventManager() {return eventMngr_;}
    Player* getPlayer() {return &player_;}
};


#endif //DOOMCLONE_GAME_H