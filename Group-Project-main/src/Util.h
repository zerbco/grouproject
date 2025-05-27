#pragma once
#define FPS 60
#include <SFML/Graphics.hpp>
#include "FishingRod.h"
const uint MAP[20][20] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
}; // ground is 0, water is 1


const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 20;
const int TILE_PIXEL_SIZE = 20;
const int WINDOW_WIDTH = MAP_WIDTH*TILE_PIXEL_SIZE;
const int WINDOW_HEIGHT = MAP_HEIGHT*TILE_PIXEL_SIZE;


const FishingRod BASIC_ROD(0.7f, 0.2f, 1, 0.0f, "Basic Rod", "A simple fishing rod");
const FishingRod IMPROVED_ROD(0.8f, 0.3f, 2, 100.0f, "Improved Rod", "Better catch rate and control");
const FishingRod ADVANCED_ROD(0.9f, 0.4f, 3, 250.0f, "Advanced Rod", "High-quality rod for experienced anglers");
const FishingRod MASTER_ROD(0.95f, 0.5f, 4, 500.0f, "Master Rod", "The finest rod money can buy");
const FishingRod PRO_ROD(0.98f, 0.6f, 5, 1000.0f, "Professional Rod", "For the most dedicated fishers");