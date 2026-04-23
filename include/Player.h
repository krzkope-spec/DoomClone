//
// Created by krzko on 19/04/2026.
//

#ifndef DOOMCLONE_PLAYER_H
#define DOOMCLONE_PLAYER_H
#include<vector>

#define SPEED 0.1
#define ROT_SPEED 0.05

class Player {
private:
    std::vector<double> pos_;
    std::vector<std::vector<bool>> map_;
    std::vector<double> inputToMovement(int keyCode);
    bool canMove(std::vector<double> direction);
    double direction; //kąt w który patrzymy w radianach
public:
    Player(double x, double y);
    void UploadMap(std::vector<std::vector<bool>> map){map_ = map;};
    void Move(int keyCode);
    std::vector<double> getPos() const {return pos_;};
    void setPos(double x, double y);
    void Rotate(double angle);
    double getAngle() const {return direction;}
};

#endif //DOOMCLONE_PLAYER_H