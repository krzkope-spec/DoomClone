//
// Created by krzko on 18/04/2026.
//

#ifndef DOOMCLONE_SCREEN_H
#define DOOMCLONE_SCREEN_H


class Screen {
private:
    int xSize_;
    int ySize_;
    char GetASCII(double grey); //skala: ' ', '.', '*', '%', '@'
    void CursorVisibility(bool value);
public:
    void Render(double** greyscale);
    Screen(int xSize, int ySize);
    int GetWidth() {return xSize_;}
    int GetHeight() {return ySize_;}
};


#endif //DOOMCLONE_SCREEN_H