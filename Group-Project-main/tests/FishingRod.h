#pragma once

#include <string>
#include "Fish.h"
#include "Randomizer.h"

class FishingRod {
private:
    float strength; // 1 minus the percentage lost per second when capture box is not on fish
    float speed; // percentage gained per second when capture box is on fish
    int rarity;

    float price;
    std::string name;
    std::string description;
public:
    // Constructor
    FishingRod(float str, float spd, int rar, float price, std::string name, std::string desc);

    // Getters
    float getStrength() const;
    float getSpeed() const;
    int getRarity() const;
    float getPrice() const;
    std::string getName() const;
    std::string getDesc() const;

    // // Setters
    // void setStrength(float str);
    // void setSpeed(float spd);
    // void setRarity(int rar);

    // Method to simulate a fish bite
    Fish* bite()const;
};

