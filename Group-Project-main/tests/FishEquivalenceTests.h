#include "../src/Fish.h"
#include <iostream>

class FishEquivalenceTests {
public:
    void runTests() {
        testCommonFish();
        testRareFish();
        testSmallFish();
        testBigFish();
        testEdgeCaseFish();
    }

private:
    void testCommonFish() {
        float rest[2] = {1.0f, 2.0f};
        FishingInfo info(0.2f, 1.0f, rest);
        Fish fish(2.0f, 1, info, "common fish", "A common pond fish");

        if (fish.getValue() != 0.4f) {
            std::cout << "Common fish test failed\n";
        } else {
            std::cout << "Common fish test passed\n";
        }
    }

    void testRareFish() {
        float rest[2] = {1.0f, 3.0f};
        FishingInfo info(0.5f, 2.0f, rest);
        Fish fish(3.0f, 5, info, "rare fish", "A rare and valuable fish");

        if (fish.getValue() != 7.5f) {
            std::cout << "Rare fish test failed\n";
        } else {
            std::cout << "Rare fish test passed\n";
        }
    }

    void testSmallFish() {
        float rest[2] = {0.5f, 1.5f};
        FishingInfo info(0.6f, 1.2f, rest);
        Fish fish(0.1f, 2, info, "small fish", "A very small fish");

        if (abs(fish.getValue() - 0.12f) > 0.001f) {
            std::cout << "Small fish test failed\n";
        } else {
            std::cout << "Small fish test passed\n";
        }
    }

    void testBigFish() {
        float rest[2] = {2.0f, 4.0f};
        FishingInfo info(0.3f, 2.5f, rest);
        Fish fish(10.0f, 3, info, "big fish", "A large sea fish");

        if (fish.getValue() != 9.0f) {
            std::cout << "Big fish test failed\n";
        } else {
            std::cout << "Big fish test passed\n";
        }
    }

    void testEdgeCaseFish() {
        float rest[2] = {0.0f, 0.0f};
        FishingInfo info(0.0f, 0.0f, rest);
        Fish fish(0.0f, 0, info, "Fish", "A fish from legend");

        if (fish.getValue() != 0.0f) {
            std::cout << "Edge case fish test failed\n";
        } else {
            std::cout << "Edge case fish test passed\n";
        }
    }
};
