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
public:
    void Render(std::vector<std::vector<double>> greyscale) const;
    Screen(int xSize, int ySize);
    int GetWidth() const {return xSize_;}
    int GetHeight() const {return ySize_;}
    void ShowConsoleCursor(bool showFlag) const;
    void CursorToZero() const;
};


#endif //DOOMCLONE_SCREEN_H