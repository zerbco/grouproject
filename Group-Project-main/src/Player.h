#pragma once
#include "FishingRod.h"
#include "Fish.h"
#include "FishingStats.h"
#include "Fishing.h"
#include "Util.h"
#include "CollisionRect.h"
#include <vector>
#include <fstream>

class Player : public Renderable, public CollisionRect{
    private:
        Randomizer *rd;
        float speed = 50;
        sf::Vector2f position;
        sf::Vector2f size;
        sf::RectangleShape sprite;
        std::shared_ptr<FishingRod> equipped_rod;
        std::vector<std::shared_ptr<FishingRod>> obtained_rods;
        std::vector<FishingStats> fish_stats;
        Fishing *fishing;
        Fish* current_fish;
        float money;
        int state; // 0 is walking, 1 is casting a line, 2 is fishing

    public:

    Player(int x, int y, Randomizer *randomizer);
    ~Player() { delete fishing; delete current_fish;};

    void updateStats(Fish* fish);
    void buyRod(FishingRod rod);
    void changeEquipped(std::shared_ptr<FishingRod> rod);
    void sellFish(Fish* fish);

    int getState() {return state;};
    void setState(int _state) {state=_state;};
    sf::Vector2f getSize() {return size;};

    float getMoney() const;
    void addMoney(float amount);
    void spendMoney(float amount);
    void addRod(std::shared_ptr<FishingRod> rod);
    bool ownsRod(std::shared_ptr<FishingRod> rod) const;

    void saveStats(std::ofstream *input);
    void loadStats(std::ifstream *input);


    void render(sf::RenderWindow *window) override;
    const sf::Vector2f getPosition() {return sf::Vector2f(position.x,position.y);};
    void setPosition(sf::Vector2f pos) {position = pos;};
    void handleInputs();
    void update();
    void probeBite();
};