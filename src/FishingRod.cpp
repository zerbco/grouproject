#include "FishingRod.h"
#include <cstdlib>
#include <ctime>

FishingRod::FishingRod(float str, float spd, int rar): strength(str), speed(spd), rarity(rar) {
    srand(time(0));
    std::cout << "Fishing Rod Initialized" << std::endl;
}

// Getter
float FishingRod::getStrength() const { 
    return strength; 
}
float FishingRod::getSpeed() const { 
    return speed; 
}
int FishingRod::getRarity() const { 
    return rarity; 
}


// Setter
void FishingRod::setStrength(float str) { 
    strength = str; 
}
void FishingRod::setSpeed(float spd) {
    speed = spd;
}
void FishingRod::setRarity(int rar) {
    rarity = rar; 
}
//bite was used to simulate if a fish is catched while fishing
Fish* FishingRod::bite(Randomizer *rd) const {
    // A random number between 0 and 9 is generated.
    // If this random number is less than rarity, a fish has been caught.
    
    if ( rand() %10 < rarity){
        float restRange[2] = {2.0f, 4.0f};
        FishingInfo info(0.1f, 1.5f, restRange); // speed = 1.5s
        return new Fish(2.0f, 1, info, "Bass", "A common freshwater fish");
    } else {
        return nullptr; // No fish bit the bait
    }
}
