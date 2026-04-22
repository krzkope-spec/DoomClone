//
// Created by krzko on 18/04/2026.
//

#ifndef DOOMCLONE_TESTING_H
#define DOOMCLONE_TESTING_H
#include<Game.h>
#include <iostream>
#include <ostream>
#include<cmath>

class Testing {
private:
    Game& g_;
public:
    Testing(Game& g): g_(g){};
    void PrintGreyScaleOnScreen() {
        Screen *s = g_.getScreen();
        std::vector greyScale(s->GetHeight(), std::vector<double>(s->GetWidth()));
        for (int i=0; i<s->GetHeight(); i++) {
            for (int j=0; j<s->GetWidth(); j++) {
                greyScale[i][j] = (double)(i*j)/(double)(s->GetWidth()*s->GetHeight());
            }
        }
        s->Render(greyScale);

    }
    void printMap() {
        g_.LoadMap("../maps/mapa_test.png");
        std::cout<<"Zaladowano"<<std::endl;
        g_.getEventManager().AddEventListener(EventManager::KEYBOARD_DOWN, [this](int key){mapPrint(key);});
    }
    void mapPrint(int key) {
        //std::cout<<key<<std::endl;
        g_.getScreen()->Render(mapindoubles(g_.getMap(), g_.getPlayer()->getPos()));
    }
    std::vector<std::vector<double>> mapindoubles(std::vector<std::vector<bool>> map, std::vector<double> pPos) {
        std::vector result(map.size(), std::vector<double>(map[0].size()));
        for (int i=0; i<map.size(); i++) {
            for (int j=0; j<map[0].size(); j++) {
                if (map[i][j]) {
                    result[j][i] = 1;
                }
                else {
                    result[j][i] = 0;
                }
            }
        }
        result[round(pPos[1])][round(pPos[0])] = -1;
        return result;
    }
    void MouseMovement() {
        g_.getEventManager().AddEventListener(EventManager::MOUSE_MOVE,[](int x, int y){std::cout<<"Ruszono o: "<<x<<" "<<y<<std::endl;});
        g_.getEventManager().AddEventListener(EventManager::KEYBOARD_DOWN,[](int x){std::cout<<"Wcisnieto: "<<x<<std::endl;});
    }
    void Raycasting() {
        std::vector<double> pPos = g_.getPlayer()->getPos();
        std::vector<double> screenMax = g_.getScreen()->Raycast(pPos[0], pPos[1], 1, g_.getMap())[0];
        std::cout<<screenMax[0]<<" "<<screenMax[1]<<std::endl;
    }

};


#endif //DOOMCLONE_TESTING_H