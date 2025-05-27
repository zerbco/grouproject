#include "Button.h"

Button::Button(float x, float y , float width , float height, sf::Color colour)
:   pos(sf::Vector2f(x,y)), size(sf::Vector2f(width,height)){
    shape = sf::RectangleShape(size);
    shape.setFillColor(colour);
    shape.setPosition(pos);
}


void Button::handleInputs(){
    active=0;
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {return;}
    sf::Vector2f mouse_pos = (sf::Vector2f)sf::Mouse::getPosition();
    sf::Vector2f pos2 = pos+size;
    if (
        mouse_pos.x >= pos.x && mouse_pos.x <=pos2.x &&
        mouse_pos.y >=pos.y && mouse_pos.y <=pos2.y
    ){
        active=1;
    }
    
}

void Button::render(sf::RenderWindow *window){
    window->draw(shape);
}