#pragma once

#include <iostream>
#include <string>
#include <array>

struct FishingInfo {
    float erraticness;
    float speed; // in seconds it takes to reach destination
    float rest_duration_range[2];

    FishingInfo(float e, float speed, float *rr);
};

class Fish {
private:
    float size;
    int rarity;
    FishingInfo fishing_info;
    std::string name;
    std::string description;
public:
    Fish(float s, int r, FishingInfo fi, std::string n, std::string d);

    float getSize() const;
    int getRarity() const;
    FishingInfo getFishingInfo() const;
    std::string getName() const;
    std::string getDescription() const;
    float getHeight() const;

    void setSize(float s);
    void setRarity(int r);
    void setFishingInfo(FishingInfo fi);
    void setName(const std::string& n);
    void setDescription(const std::string& d);
    void setHeight(float h);

    float getValue() const;
    void display() const;
};
