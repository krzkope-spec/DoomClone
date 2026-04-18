//
// Created by krzko on 18/04/2026.
//

#include "Game.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include<iostream>

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
            } else {
                map_[y][x] = false;
            }
        }
    }
    stbi_image_free(img);
    return 0;
}