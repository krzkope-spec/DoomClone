//
// Created by krzko on 22/04/2026.
//

#ifndef DOOMCLONE_MATRAY_HPP
#define DOOMCLONE_MATRAY_HPP
#include <vector>

void RotateVector(std::vector<double>& v_ad, double angle);
void MultiplyVector(std::vector<double>& v_ad, double scalar);
void NormalizeVector(std::vector<double>& v);
std::vector<double> AddVectors(std::vector<double> v1, std::vector<double> v2);
#endif //DOOMCLONE_MATRAY_HPP