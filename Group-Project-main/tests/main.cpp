#include "FishEquivalenceTests.h"
#include "FishingRodEquivalenceTests.h"

int main(){
    FishEquivalenceTests fish_tests = FishEquivalenceTests();
    FishingRodEquivalenceTests fishing_rod_tests = FishingRodEquivalenceTests();
    fish_tests.runTests();
    fishing_rod_tests.runTests();
}