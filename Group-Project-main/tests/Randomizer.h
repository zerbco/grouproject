#pragma once
#include <random>

struct Randomizer{
    std::random_device rd;
    std::mt19937 gen; 
    Randomizer():rd(), gen(rd()) {};
};