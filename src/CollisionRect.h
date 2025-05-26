#pragma once
#include "Util.h"

class CollisionRect {
    protected:
        sf::Vector2u position;
        sf::Vector2u size;

    public:
        CollisionRect(int x = 0, int y = 0, int width = 0, int height = 0);

        bool collide(sf::Vector2u point) const;
        bool collide(const CollisionRect& rect) const;

        const sf::Vector2u getPosition() const;
        const sf::Vector2u getSize() const;

        void setPosition(int x, int y);
        void setSize(int width, int height);
};