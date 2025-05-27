#include "CollisionRect.h"

CollisionRect::CollisionRect(int x, int y, int width, int height) {
    position = sf::Vector2u(x,y);
    size = sf::Vector2u(width,height);
}

//******I'm not sure about this line, please check again*****// ( used AABB algorithm)
bool CollisionRect::collide(sf::Vector2u point) const {
    return (point.x >= position.x && point.x <= position.x + size.x &&
    point.y >= position.y && point.y <= position.y + size.y);
}

// ** added this for collision with another rectangle 
bool CollisionRect::collide(const CollisionRect& rect) const{
    int left1 = position.x;
    int right1 = position.x + size.x;
    int top1 = position.y;
    int bottom1 = position.y + size.y;

    int left2 = rect.position.x;
    int right2 = rect.position.x + rect.size.x;
    int top2 = rect.position.y;
    int bottom2 = rect.position.y + rect.size.y;

    //* to check if rect overlap!
    return (left1 < right2 && right1 > left2 && top1 < bottom2 && bottom1 > top2);
}

const sf::Vector2u CollisionRect::getPosition() const{
    return position;
}

const sf::Vector2u CollisionRect::getSize() const{
    return size;
}

void CollisionRect::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void CollisionRect::setSize(int width,int height) {
    size.x = width;
    size.y = height;
}

