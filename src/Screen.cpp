#include "Screen.h"
#include <windows.h>
#include<iostream>
#include<sstream>
#include<vector>
#include<algorithm>

Screen::Screen(int xSize, int ySize) {
    xSize_ = xSize;
    ySize_ = ySize;
    void* hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND cWindow = GetConsoleWindow();
    COORD bufferSize = { (SHORT)xSize_, (SHORT)ySize_ };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    SMALL_RECT windowSize = { 0, 0, (SHORT)(xSize_ - 1), (SHORT)(ySize_ - 1) };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    CONSOLE_FONT_INFO fontInfo;
    GetCurrentConsoleFont(hConsole, FALSE, &fontInfo);

    int pixelWidth = xSize_ * fontInfo.dwFontSize.X + 35;
    int pixelHeight = ySize_ * fontInfo.dwFontSize.Y + 45;

    MoveWindow(cWindow, 100, 100, pixelWidth, pixelHeight, TRUE);
}
void Screen::Render(const std::vector<std::vector<double>> greyScale) {
    std::ostringstream oss;
    for (int i=0; i<std::min((size_t)ySize_, greyScale.size()); i++) {
        for (int j=0; j<std::min((size_t)xSize_, greyScale[0].size()); j++) {
            oss<<GetASCII(greyScale[i][j]);
        }
        oss<<"\n";
    }
    std::cout<<oss.str();
}
char Screen::GetASCII(double grey) {
    //grey ranges from 0-1
    if (grey<0.2) return ' ';
    if (grey<0.4) return '.';
    if (grey<0.6) return '*';
    if (grey<0.8) return '#';
    return '@';
}