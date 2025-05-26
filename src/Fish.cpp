#include "Fish.h"

FishingInfo::FishingInfo(float e, float s, float *rr): erraticness(e), speed(s) { 
    rest_duration_range[0] = rr[0];
    rest_duration_range[1] = rr[1];
    std::cout << "Fishing Info Initialized" << std::endl;
}

Fish::Fish(float s, int r, FishingInfo fi, std::string n, std::string d): size(s), rarity(r), fishing_info(fi), name(n), description(d) {
    std::cout << "Fish Initialized" << std::endl;
}

// Getters
float Fish::getSize() const { return size; }
int Fish::getRarity() const { return rarity; }
FishingInfo Fish::getFishingInfo() const { return fishing_info; }
std::string Fish::getName() const { return name; }
std::string Fish::getDescription() const { return description; }

// Setters
void Fish::setSize(float s) { size = s; }
void Fish::setRarity(int r) { rarity = r; }
void Fish::setFishingInfo(FishingInfo fi) { fishing_info = fi; }
void Fish::setName(const std::string& n) { name = n; }
void Fish::setDescription(const std::string& d) { description = d; }

// Methods
float Fish::getValue() const {
    return size * rarity * fishing_info.erraticness;
}

void Fish::display() const {
    std::cout << "Fish Name: " << name << "\nDescription: " << description
         << "\nSize: " << size << "\nRarity: " << rarity << "\n";
}
