//
// Created by krzko on 19/04/2026.
//

#include "Player.h"

#include <cmath>
#include<iostream>
#include<Matray.hpp>

Player::Player(double x, double y) : pos_(2) {
    pos_[0] = x;
    pos_[1] = y;
    direction = 0;
}
void Player::setPos(double x, double y) {
    pos_[0] = x;
    pos_[1] = y;
}
void Player::Move(int input) {
    std::vector<double> delta = inputToMovement(input);
    if (delta[0]==0||delta[1]==0&&!(delta[1]==0&&delta[0]==0)) {
        RotateVector(delta, direction);
        if (canMove(delta)) {
            pos_[0] += delta[0];
            pos_[1] += delta[1];
        }
    }
    else {
        Rotate(delta[0]*ROT_SPEED);
    }
}
bool Player::canMove(std::vector<double> direction) {
    int targX = round(pos_[0]+direction[0]);
    int targY = round(pos_[1]+direction[1]);
    return !map_[targX][targY];
}
std::vector<double> Player::inputToMovement(int keyCode) {
    switch (keyCode) {
        case 87: //w
            return std::vector<double>{SPEED, 0};
        case 83: //s
            return std::vector<double>{-SPEED, 0};
        case 65: //a
            return std::vector<double>{0, -SPEED};
        case 68: //d
            return std::vector<double>{0, SPEED};
        case 74:
            return std::vector<double>{-1,-1};
        case 76:
            return std::vector<double>{1,1};
        default:
            return std::vector<double>{0,0};
    }
}
void Player::Rotate(double angle) {
    direction+=angle;
}