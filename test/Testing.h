//
// Created by krzko on 18/04/2026.
//

#ifndef DOOMCLONE_TESTING_H
#define DOOMCLONE_TESTING_H
#include<Game.h>
#include <iostream>
#include <ostream>


class Testing {
private:
    Game g_;
public:
    Testing(const Game& g): g_(g){};
    void PrintGreyScaleOnScreen() {
        Screen s = g_.getScreen();
        std::vector greyScale(s.GetHeight(), std::vector<double>(s.GetWidth()));
        for (int i=0; i<s.GetHeight(); i++) {
            for (int j=0; j<s.GetWidth(); j++) {
                greyScale[i][j] = (double)(i*j)/(double)(s.GetWidth()*s.GetHeight());
            }
        }
        g_.getScreen().Render(greyScale);

    }
    void printMap() {
        g_.LoadMap("../maps/mapa_test.png");
        g_.getScreen().Render(mapindoubles(g_.getMap()));
    }
    std::vector<std::vector<double>> mapindoubles(std::vector<std::vector<bool>> map) {
        std::vector result(map.size(), std::vector<double>(map[0].size()));
        for (int i=0; i<map.size(); i++) {
            for (int j=0; j<map[0].size(); j++) {
                if (map[i][j]) {
                    result[i][j] = 1;
                }
                else {
                    result[i][j] = 0;
                }
            }
        }
        return result;
    }
    void mainTest() {

    }
};


#endif //DOOMCLONE_TESTING_H