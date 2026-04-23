#include "Screen.h"
#include <windows.h>
#include<iostream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<cmath>
#include "Matray.hpp"


Screen::Screen(int xSize, int ySize) {
    xSize_ = xSize;
    ySize_ = ySize;
    void* hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND cWindow = GetConsoleWindow();
    COORD bufferSize = { (SHORT)xSize_, (SHORT)ySize_ };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    SMALL_RECT windowSize = { 0, 0, (SHORT)(xSize_ ), (SHORT)(ySize_ -1) };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    CONSOLE_FONT_INFO fontInfo;
    GetCurrentConsoleFont(hConsole, FALSE, &fontInfo);

    int pixelWidth = xSize_ * fontInfo.dwFontSize.X + 35;
    int pixelHeight = ySize_ * fontInfo.dwFontSize.Y + 45;

    MoveWindow(cWindow, 100, 100, pixelWidth, pixelHeight, TRUE);
}
void Screen::Render(const std::vector<std::vector<double>> greyScale) const{
    std::ostringstream oss;
    for (int i=0; i<std::min((size_t)ySize_, greyScale.size()); i++) {
        for (int j=0; j<std::min((size_t)xSize_, greyScale[0].size()); j++) {
            oss<<GetASCII(greyScale[i][j]);
        }
        oss<<"\n";
    }
    CursorToZero();
    std::cout<<oss.str();
}
void Screen::CursorToZero() const{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
}
void Screen::ShowConsoleCursor (bool showFlag) const {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
char Screen::GetASCII(double grey) const{
    //grey ranges from 0-1
    if (grey<0) return 'X'; //symbol gracza w 2D
    if (grey<0.2) return ' ';
    if (grey<0.4) return '.';
    if (grey<0.6) return '*';
    if (grey<0.8) return '#';
    return '@';
}
std::vector<std::vector<double>> Screen::Raycast(double x, double y, double angle, std::vector<std::vector<bool>> map) const{
    std::vector<double> direction = {1,0};
    RotateVector(direction, angle);
    std::vector<double> screenMax = direction;
    RotateVector(screenMax, M_PI/2);
    std::vector<std::vector<double>> results;
    for (int i=0; i<xSize_; i++) {
        std::vector<double> screenDir = screenMax;
        MultiplyVector(screenDir, FOV*((double)(i-xSize_/2)/(double)xSize_));
        std::vector<double> target = AddVectors(direction, screenDir);
        NormalizeVector(target);
        results.push_back(castSingleRay(x,y, target, map));
    }
    return results;
}
void Screen::Render3D(double x, double y, double angle, std::vector<std::vector<bool>> map) const{
    std::vector<std::vector<double>> raycastResults = Raycast(x,y, angle, map);
    const double maxDistance = 80;
    const int maxHeight = ySize_-4;
    std::vector screen(maxHeight, std::vector(xSize_, 0.0));
    for (int i=0; i<xSize_; i++) {
        double distance = raycastResults[i][0];
        double greyscale = raycastResults[i][1]==0 ? 0.5 : 0.6;
        int height = floor(std::max((maxDistance-distance)/maxDistance*(double)maxHeight, 0.0));
        int startHeight = (ySize_-height)/2;
        for (int j=0; j<height-2; j++) {
            screen[j+startHeight][i] = greyscale;
        }
    }
   /* for (int i=0; i<xSize_; i++) {
        for (int j=0; j<ySize_; j++) {
            std::cout<<screen[i][j]<<" ";
        }
        std::cout<<std::endl;
    }*/
    Render(screen);
}
std::vector<double> Screen::castSingleRay(double x, double y, std::vector<double> direction, std::vector<std::vector<bool>> map) const {
    int mapX, mapY;
    mapX = (int)x;
    mapY = (int)y;
    double sideDistX, sideDistY;
    double side0X, side0Y;

    double deltaDistX = (direction[0]==0) ? 1e30 : std::abs(1/direction[0]);
    double deltaDistY = (direction[1]==0) ? 1e30 : std::abs(1/direction[1]);

    int stepX, stepY;
    bool hit = false;
    int side = 0;
    if (direction[0]<0) {
        sideDistX = (x-mapX)*deltaDistX;
        stepX = -1;
    }
    else {
        sideDistX = (x+1.0-mapX)*deltaDistX;
        stepX = 1;
    }
    if (direction[1]<0) {
        sideDistY = (y-mapY)*deltaDistY;
        stepY = -1;
    }
    else {
        sideDistY = (y+1.0-mapY)*deltaDistY;
        stepY = 1;
    }
    side0X = sideDistX;
    side0Y = sideDistY;
    while (!hit) {
        if (sideDistX<sideDistY) {
            sideDistX += deltaDistX;
            mapX+=stepX;
            side = 0;
        }
        else {
            sideDistY += deltaDistY;
            mapY+=stepY;
            side = 1;
        }
        if (mapX>=map.size()||mapY>=map[0].size()||mapX<0||mapY<0) {
            {
                //nie trafiliśmy na nic
                return std::vector<double>{-1,-1,-1};
            }
        }
        hit = map[mapX][mapY];
    }
    double perpWallDist = (side==0) ? (sideDistX-deltaDistX) : (sideDistY-deltaDistY);
    return std::vector{perpWallDist, static_cast<double>(side)}; //side = 0 dla ściany pionowej, side = 1 dla ściany poziomej
}