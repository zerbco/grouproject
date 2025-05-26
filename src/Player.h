#pragma once
#include "FishingRod.h"
#include "Fish.h"
#include "FishingStats.h"
#include "Fishing.h"
#include "Util.h"
#include <vector>

class Player : public Renderable{
    private:
        float speed = 50;
        sf::Vector2f position;
        sf::Vector2u size;
        sf::RectangleShape sprite;
        std::shared_ptr<FishingRod> equipped_rod;
        std::vector<std::shared_ptr<FishingRod>> obtained_rods;
        std::vector<FishingStats> fish_stats;
        Fishing *fishing;
        Fish* current_fish;
        float money;
        int state; // 0 is walking, 1 is casting a line, 2 is fishing

    public:

    Player(int x = 0, int y = 0);
    ~Player() { delete fishing; delete current_fish;};

    void updateStats(Fish* fish);
    void buyRod(FishingRod rod);
    void changeEquipped(std::shared_ptr<FishingRod> rod);
    void sellFish(Fish* fish);

    int getState() {return state;};
    void setState(int _state) {state=_state;};
    sf::Vector2u getSize() {return size;};

    void render(sf::RenderWindow *window) override;
    const sf::Vector2u getPosition() {return sf::Vector2u(position.x,position.y);};
    void setPosition(sf::Vector2f pos) {position = pos;};
    void handleInputs();
    void update(Randomizer *rd);
    void probeBite(Randomizer *rd);
};