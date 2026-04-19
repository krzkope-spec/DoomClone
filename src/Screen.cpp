#include "Screen.h"
#include <windows.h>
#include<iostream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<cmath>

#define FOV 1

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
std::vector<std::vector<double>> Screen::Raycast(double x, double y, double angle, std::vector<std::vector<double>> map) const{
    std::vector<std::vector<double>> result;
    for (int i=0; i<xSize_; i++) {
        double angleRelative = atan(FOV*i-xSize_/2);
        double angleFull = angle+angleRelative;
        result.push_back(castSingleRay(x,y, angleFull, map));
    }
    //return: xHit, yHit, kąt normalnej dla każdego z promineni
    return result;
}
std::vector<double> Screen::castSingleRay(double x, double y, double angle, std::vector<std::vector<double>> map) const{
    return std::vector{0.0,0.0,0.0};
}