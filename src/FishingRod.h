#pragma once

#include <string>
#include "Fish.h"
#include "Randomizer.h"
using namespace std;

class FishingRod {
private:
    float strength; // 1 minus the percentage lost per second when capture box is not on fish
    float speed; // percentage gained per second when capture box is on fish
    int rarity;
public:
    // Constructor
    FishingRod(float str, float spd, int rar);

    // Getters
    float getStrength() const;
    float getSpeed() const;
    int getRarity() const;

    // Setters
    void setStrength(float str);
    void setSpeed(float spd);
    void setRarity(int rar);

    // Method to simulate a fish bite
    Fish* bite(Randomizer *rd)const;
};

