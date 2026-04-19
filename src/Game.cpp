//
// Created by krzko on 18/04/2026.
//

#include "Game.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include<iostream>
#include<windows.h>
int Game::LoadMap(const char *filename) {
    int mapX, mapY, channels;
    unsigned char *img = stbi_load(filename, &mapX, &mapY, &channels, 3);
    if (img == nullptr) {
        std::cout << "Blad ladowania mapy: " << stbi_failure_reason() << std::endl;
        return 1;
    }
    map_ = std::vector (mapX, std::vector(mapY, false));
    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++) {
            int index = (y * mapX + x) * 3;

            unsigned char r = img[index + 0];
            unsigned char g = img[index + 1];
            unsigned char b = img[index + 2];
            if (r == 0 && g == 0 && b == 0) {
                map_[y][x] = true;
            }
            else if (g==0&&b==0) {
                player_.setPos(x,y);
                map_[y][x] = false;
            }
            else {
                map_[y][x] = false;
            }
        }
    }
    stbi_image_free(img);
    player_.UploadMap(map_);
    return 0;
}
void Game::Start() {
    s_.ShowConsoleCursor(false);
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
    eventMngr_.AddEventListener(EventManager::KEYBOARD_DOWN, [this](int input){MovePlayer(input);});
    while (true) {
        Update();
        Sleep(deltaTime_);
    }
}
void Game::MovePlayer(int input) {
    player_.Move(input);
}
void Game::Update() {
    ProcessInput(&mouseX_, &mouseY_);

}
void Game::ProcessInput(int* x, int* y) {
    void* hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD numEvents;
    INPUT_RECORD inputBuffer[32];

    // Sprawdź, czy są jakieś zdarzenia w kolejce (nie blokuje programu)
    GetNumberOfConsoleInputEvents(hInput, &numEvents);

    if (numEvents > 0) {
        ReadConsoleInput(hInput, inputBuffer, 32, &numEvents);

        for (DWORD i = 0; i < numEvents; i++) {
            if (inputBuffer[i].EventType == KEY_EVENT) {
                auto& keyEvent = inputBuffer[i].Event.KeyEvent;
                if (keyEvent.bKeyDown) {
                    // keyEvent.wVirtualKeyCode zawiera kod klawisza (np. VK_UP)
                    eventMngr_.KeyboardDown(keyEvent.wVirtualKeyCode);}
            }
            else if (inputBuffer[i].EventType == MOUSE_EVENT) {
                auto& mouseEv = inputBuffer[i].Event.MouseEvent;
                // Sprawdzenie, czy zdarzenie to faktycznie ruch (MOUSE_MOVED)
                if (mouseEv.dwEventFlags & MOUSE_MOVED) {
                    int currentX = mouseEv.dwMousePosition.X;
                    int currentY = mouseEv.dwMousePosition.Y;
                    // Obliczenie delty (różnicy)
                    int deltaX = currentX - *x;
                    int deltaY = currentY - *y;

                    if (deltaX != 0 || deltaY != 0) {
                        eventMngr_.MouseMove(deltaX, deltaY);
                    }
                    *x = currentX;
                    *y = currentY;
                }
            }
        }
    }
}