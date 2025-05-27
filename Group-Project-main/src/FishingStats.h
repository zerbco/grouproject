#pragma once
#include <string>

struct FishingStats {
    std::string fish_name;
    int number_caught;
    float max_size;
    float min_size;
    float total_value;

    FishingStats()
    : fish_name(""),
      number_caught(0),
      max_size(0.0f),
      min_size(0.0f),
      total_value(0.0f) {}
};