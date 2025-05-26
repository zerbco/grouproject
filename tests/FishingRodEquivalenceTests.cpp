#include <iostream>
#include "../src/FishingRod.h"

class FishingRodEquivalenceTests {
public:
    // Run all equivalence tests
    void runTests() {
        testLowRarityRod();      // Low rarity rod: unlikely to catch a fish
        testMediumRarityRod();   // Medium rarity rod: moderate chance
        testHighRarityRod();     // High rarity rod: very likely to succeed
        testZeroStrengthRod();   // Edge case: strength = 0
        testHighSpeedRod();      // Edge case: very high speed
    }

private:
    // Test rod with rarity = 1 (low probability of catching fish)
    void testLowRarityRod() {
        FishingRod rod(3, 1.5f, 1, "low.png");
        Fish* fish = rod.bite();
        if (fish) {
            std::cout << "Low rarity rod test: Caught fish" << "\n";
        } else {
            std::cout << "Low rarity rod test: No fish" << "\n";
        }
        delete fish;
    }

    // Test rod with rarity = 5 (moderate probability)
    void testMediumRarityRod() {
        FishingRod rod(3, 1.5f, 5, "medium.png");
        Fish* fish = rod.bite();
        if (fish) {
            std::cout << "Medium rarity rod test: Caught fish" << "\n";
        } else {
            std::cout << "Medium rarity rod test: No fish" << "\n";
        }
        delete fish;
    }

    // Test rod with rarity = 10 (maximum probability)
    void testHighRarityRod() {
        FishingRod rod(3, 1.5f, 10, "high.png");
        Fish* fish = rod.bite();
        if (fish) {
            std::cout << "High rarity rod test: Caught fish" << "\n";
        } else {
            std::cout << "High rarity rod test: No fish" << "\n";
        }
        delete fish;
    }

    // Test rod with strength = 0 (edge case)
    void testZeroStrengthRod() {
        FishingRod rod(0, 1.0f, 5, "zero_strength.png");
        std::cout << "Zero strength rod test: Strength = " << rod.getStrength() << "\n";
    }

    // Test rod with very high speed (edge case）
    void testHighSpeedRod() {
        FishingRod rod(5, 100.0f, 5, "fast.png");
        std::cout << "High speed rod test: Speed = " << rod.getSpeed() << "\n";
    }
};
