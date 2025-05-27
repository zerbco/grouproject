#pragma once

#include <SFML/Graphics.hpp>

class Renderable {
    public:
    virtual ~Renderable() = default;
    
    virtual void render(sf::RenderWindow *window) = 0;
    virtual void handleInputs() {};
    virtual void update() {};
    
};