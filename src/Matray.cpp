//
// Created by krzko on 22/04/2026.
//
#include "matray.hpp"
#include <math.h>
#include <numeric>
#include<algorithm>

void RotateVector(std::vector<double>& v_ad, double angle_rad) {
    double x = v_ad[0];
    double y = v_ad[1];
    double rotationMatrix[2][2] = {{cos(angle_rad), -sin(angle_rad)},{sin(angle_rad), cos(angle_rad)}};
    v_ad[0] = x * rotationMatrix[0][0] + y * rotationMatrix[0][1];
    v_ad[1] = x * rotationMatrix[1][0] + y * rotationMatrix[1][1];
}
void MultiplyVector(std::vector<double>& v_ad, double scalar) {
    v_ad[0] *=scalar;
    v_ad[1] *=scalar;
}
void NormalizeVector(std::vector<double>& v) {
    double sqr = std::accumulate(v.begin(), v.end(), 0.0, [](double acc, double elem){return acc+elem*elem;});
    double len = sqrt(sqr);
    for (double &i : v) {
        i/=len;
    }
}
std::vector<double> AddVectors(std::vector<double> v1, std::vector<double> v2) {
    std::vector<double> result(v1.size());
    std::transform(v1.begin(), v1.end(), v2.begin(), result.begin(), std::plus<>());
    return result;

}