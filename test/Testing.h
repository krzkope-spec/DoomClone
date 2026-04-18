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
        double **greyScale = new double*[s.GetHeight()];
        for (int i=0; i<s.GetHeight(); i++) {
            greyScale[i] = new double[s.GetWidth()];
            for (int j=0; j<s.GetWidth(); j++) {
                greyScale[i][j] = (double)(i*j)/(double)(s.GetWidth()*s.GetHeight());
            }
        }
        g_.getScreen().Render(greyScale);
    }
    void mainTest() {

    }
};


#endif //DOOMCLONE_TESTING_H