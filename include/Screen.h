//
// Created by krzko on 18/04/2026.
//

#ifndef DOOMCLONE_SCREEN_H
#define DOOMCLONE_SCREEN_H
#include<vector>

class Screen {
private:
    int xSize_;
    int ySize_;
    char GetASCII(double grey) const; //skala: ' ', '.', '*', '%', '@'
    std::vector<double> castSingleRay(double x, double y, std::vector<double> direction, std::vector<std::vector<bool>> map) const;
    double FOV = 1.5;
public:
    void Render(std::vector<std::vector<double>> greyscale) const;
    Screen(int xSize, int ySize);
    int GetWidth() const {return xSize_;}
    int GetHeight() const {return ySize_;}
    void ShowConsoleCursor(bool showFlag) const;
    void CursorToZero() const;
    std::vector<std::vector<double>> Raycast(double x, double y, double angle, std::vector<std::vector<bool>> map) const;
    void Render3D(double x, double y, double angle, std::vector<std::vector<bool>> map) const;
};
#endif //DOOMCLONE_SCREEN_H