#include "Screen.h"
#include <windows.h>
#include<iostream>

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