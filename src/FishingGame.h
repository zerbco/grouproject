#pragma once
#include "Menu.h"
#include "Player.h"
#include "Randomizer.h"



class FishingGame: public Menu {
    private:
        Player player;
        sf::RectangleShape *tiles;
        sf::Clock game_clock;
        Randomizer randomizer = Randomizer(); 

    public:
        FishingGame();
        ~FishingGame() {delete[] tiles;}
        void render(sf::RenderWindow *window);
        void update();
        void handleInputs();
        void handlePhysics();
};