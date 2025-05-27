#pragma once
#include "Renderable.h"

class Button: public Renderable{
    private:
        bool active;
        sf::Vector2f pos;
        sf::Vector2f size;
        sf::RectangleShape shape;
    public:
    Button(float x, float y, float width, float height, sf::Color colour);    

    sf::Vector2f getPos() {return pos;};
    sf::Vector2f getSize() {return size;};

    void handleInputs();
    bool isActive() {return active;};
    void render(sf::RenderWindow *window);
};