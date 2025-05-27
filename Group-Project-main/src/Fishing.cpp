#include "Fishing.h"
#include <math.h>
#include <algorithm>

const int PLAYSPACE_WIDTH = 20;
const int PLAYSPACE_HEIGHT = 200; 
const int CAPTURE_BOX_HEIGHT = 65; 
const int PROGRESSBAR_WIDTH = 5;
const int FISH_RADIUS = PLAYSPACE_WIDTH/2;
const float FISHING_PIXEL_SIZE = PLAYSPACE_HEIGHT;

Fishing::Fishing(FishingInfo _info, sf::Vector2u _position, FishingRod *rod, Randomizer *rd): fish_info(_info), position(_position), capture_percentage(0), rod(rod), rd(rd){

    play_area_texture = sf::RectangleShape(sf::Vector2f(PLAYSPACE_WIDTH,PLAYSPACE_HEIGHT));
    play_area_texture.setFillColor(sf::Color(50,50,50));
    fish_texture = sf::CircleShape(FISH_RADIUS);
    fish_texture.setFillColor(sf::Color(50,100,250));
    capture_box_texture = sf::RectangleShape(sf::Vector2f(PLAYSPACE_WIDTH,CAPTURE_BOX_HEIGHT));
    capture_box_texture.setFillColor(sf::Color(100,250,50));
    
    velocity=0;
    fish_position = 0.25;
    capture_box_position = 0;
    capture_percentage = 0.25;

    if (position.x+PLAYSPACE_WIDTH+PROGRESSBAR_WIDTH>WINDOW_WIDTH-10) {position.x = WINDOW_WIDTH-PLAYSPACE_WIDTH-PROGRESSBAR_WIDTH-10;}
    if (position.y+PLAYSPACE_HEIGHT>WINDOW_HEIGHT-10) {position.y = WINDOW_HEIGHT-PLAYSPACE_HEIGHT-10;}
    if (position.x<10) {position.x = 10;}
    if (position.y<10) {position.y =10;}


    play_area_texture.setPosition((sf::Vector2f)position);
    capture_box_texture.setPosition(sf::Vector2f(position.x,position.y+(PLAYSPACE_HEIGHT-CAPTURE_BOX_HEIGHT)-(FISHING_PIXEL_SIZE*capture_box_position)));
    fish_texture.setPosition(sf::Vector2f(position.x,position.y+(PLAYSPACE_HEIGHT-2*FISH_RADIUS)-(FISHING_PIXEL_SIZE*fish_position)));


    clock.restart();
    rest_time_generator = std::uniform_real_distribution(fish_info.rest_duration_range[0], fish_info.rest_duration_range[1]);
    erraticness_generator = std::normal_distribution(0.f, fish_info.erraticness);

    
    state=1;
    time_at_last_move = clock.getElapsedTime();
    fish_rest_time = 0.1;

    std::cout << "Fishing Minigame Initialized" << std::endl;

}

void Fishing::handleInputs(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
        velocity+=0.1/FPS;
    }
    velocity-=0.02/FPS;
    
}

void Fishing::updatePhysics(){
    capture_box_position+=velocity;
    if (capture_box_position < 0 || capture_box_position>1-(CAPTURE_BOX_HEIGHT/FISHING_PIXEL_SIZE)){
        velocity *=-0.5;
        capture_box_position=std::clamp(capture_box_position,0.f,1-(CAPTURE_BOX_HEIGHT/FISHING_PIXEL_SIZE));
    }
}
void Fishing::updateFish(){
        if (state == 1){
        if ((clock.getElapsedTime() - time_at_last_move).asSeconds() > fish_rest_time){
            fish_destination = std::clamp((float)(((fish_position<=0.5)? (0.75):(0.25)) + erraticness_generator(rd->gen)),0.f,(1-(2*FISH_RADIUS/FISHING_PIXEL_SIZE)));
            movement_step = (fish_destination - fish_position)/(fish_info.speed*FPS);
            state=0;
        }
    }
    
    if (state == 0) {
        if (fish_destination-0.01 <= fish_position && fish_position <=fish_destination+0.01){
            time_at_last_move = clock.getElapsedTime();
            fish_rest_time = std::max(rest_time_generator(rd->gen)+ erraticness_generator(rd->gen),0.1f);
            state=1;
        } else {
            fish_position+=movement_step;
        }
    }    
}

void Fishing::updateProgress(){
    if (fish_position>=capture_box_position && fish_position+(2*FISH_RADIUS/FISHING_PIXEL_SIZE) <= capture_box_position+ (CAPTURE_BOX_HEIGHT/FISHING_PIXEL_SIZE)){
        capture_percentage += rod->getSpeed()/FPS;
    } else {
        capture_percentage -= std::min(1-rod->getStrength(),0.01f)/FPS;
    }
}

void Fishing::updatePositions(){
    capture_box_texture.setPosition(sf::Vector2f(position.x,position.y+(PLAYSPACE_HEIGHT-CAPTURE_BOX_HEIGHT)-(FISHING_PIXEL_SIZE*capture_box_position)));
    fish_texture.setPosition(sf::Vector2f(position.x,position.y+(PLAYSPACE_HEIGHT-2*FISH_RADIUS)-(FISHING_PIXEL_SIZE*fish_position)));
}

void Fishing::update(){
    updateFish();
    updatePhysics();
    updatePositions();
    updateProgress();
}


int Fishing::checkWin(){
    if (capture_percentage <0){ return -1;}
    if (capture_percentage >1){ return 1;}
    return 0;
}



void Fishing::render(sf::RenderWindow *window){
    
        window->draw(play_area_texture);
        window->draw(capture_box_texture);
        window->draw(fish_texture);

        sf::VertexArray progress_bar(sf::PrimitiveType::TriangleStrip,4);
        progress_bar[0].position = sf::Vector2f(position.x+PLAYSPACE_WIDTH,position.y+(PLAYSPACE_HEIGHT*(1-capture_percentage)));
        progress_bar[0].color= sf::Color::Green;
        progress_bar[1].position = sf::Vector2f(position.x+PLAYSPACE_WIDTH+PROGRESSBAR_WIDTH,position.y+(PLAYSPACE_HEIGHT*(1-capture_percentage)));
        progress_bar[1].color= sf::Color::Green;
        progress_bar[2].position = sf::Vector2f(position.x+PLAYSPACE_WIDTH+PROGRESSBAR_WIDTH,position.y+PLAYSPACE_HEIGHT);
        progress_bar[2].color= sf::Color::Green;
        progress_bar[3].position = sf::Vector2f(position.x+PLAYSPACE_WIDTH,position.y+PLAYSPACE_HEIGHT);
        progress_bar[3].color= sf::Color::Green;
        window->draw(progress_bar);
}

