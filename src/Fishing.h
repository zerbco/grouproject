#pragma once
#include "Renderable.h"
#include "Fish.h"
#include "Randomizer.h"
#include "Util.h"
#include "FishingRod.h"


class Fishing: public Renderable {
    public:
        sf::Vector2u position;

        sf::CircleShape fish_texture;
        sf::RectangleShape capture_box_texture;
        sf::RectangleShape play_area_texture;
        // sf::RectangleShape capture_percentage_texture;

        FishingInfo fish_info;
        FishingRod *rod;

        int state; //0 is resting, 1 is moving
        float velocity;
        float fish_position;
        float capture_box_position;
        sf::Clock clock;
        sf::Time time_at_last_move;
        float fish_rest_time;
        std::uniform_real_distribution<float> rest_time_generator;
        std::normal_distribution<float> erraticness_generator;
        float fish_destination;
        float movement_step;

        float capture_percentage;
        
        
        Fishing(FishingInfo info, sf::Vector2u position, FishingRod *rod);

        void setPosition(sf::Vector2u _position) {position=_position;};
        const sf::Vector2u getPosition() {return position;};

        void handleInputs();
        void updatePhysics();
        void updateFish(Randomizer *rd);
        void updatePositions();
        void updateProgress();
        void update(Randomizer *rd);
        
        int checkWin(); // -1 is loss, 0 is still going, 1 is win

        void render(sf::RenderWindow *window);
};