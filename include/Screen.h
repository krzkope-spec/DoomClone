//
// Created by krzko on 18/04/2026.
//

#ifndef DOOMCLONE_SCREEN_H
#define DOOMCLONE_SCREEN_H


class Screen {
private:
    int xSize_;
    int ySize_;
    char GetASCII(int grey); //skala: ' ', '.', '*', '%', '@'
    void CursorVisibility(bool value);
public:
    void Render(int** greyscale);
    Screen(int xSize, int ySize);
};


#endif //DOOMCLONE_SCREEN_H