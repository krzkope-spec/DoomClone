//
// Created by krzko on 19/04/2026.
//

#include "Player.h"

#include <cmath>

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
    if (canMove(delta)) {
        pos_[0] += delta[0];
        pos_[1] += delta[1];
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
            return std::vector{0, SPEED};
        case 83: //s
            return std::vector{0, -SPEED};
        case 65: //a
            return std::vector<double>{-SPEED, 0};
        case 68: //d
            return std::vector<double>{SPEED, 0};
    }
}
