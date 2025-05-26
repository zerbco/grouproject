#pragma once
#include "Menu.h"
#include "Player.h"
#include "Randomizer.h"
#include "Shop.h" 
#include <algorithm>


FishingGame::FishingGame() : shop(&player) {  // Initialize shop with player reference
    player = Player(50,50);
    
    // Give player some starting money
    player.addMoney(200.0f);
    
    std::cout << "Fishing Game Initialized" << std::endl;
}

// Update handleInputs() method in FishingGame.cpp:
void FishingGame::handleInputs(){
    // Handle shop input first
    if (shop.isOpen()) {
        shop.handleInputs();
        return; // Don't process other inputs when shop is open
    }
    
    // Open shop with TAB key
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
        static sf::Clock shop_timer;
        if (shop_timer.getElapsedTime().asMilliseconds() > 300) {
            shop.open();
            shop_timer.restart();
        }
    }
    
    // Existing player input handling
    player.handleInputs();
    sf::Vector2u player_tile_pos = (sf::Vector2u)((sf::Vector2f)player.getPosition()/(float)TILE_PIXEL_SIZE);
    if (player_tile_pos.y+2<MAP_HEIGHT){
        if (player.getState()==0 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && MAP[player_tile_pos.y+2][player_tile_pos.x]==1){
            player.setState(1);
        }
    }
}

// Update render() method in FishingGame.cpp:
void FishingGame::render(sf::RenderWindow *window){
    // Render game world
    for (int y=0;  y < MAP_HEIGHT; y++){
        for (int x=0; x<MAP_WIDTH; x++){
            tiles[MAP[y][x]].setPosition(sf::Vector2f(x*TILE_PIXEL_SIZE,y*TILE_PIXEL_SIZE));
            window->draw(tiles[MAP[y][x]]);
        }
    }

    player.render(window);
    
    // Render shop on top if open
    shop.render(window);
}

// Update update() method in FishingGame.cpp:
void FishingGame::update(){
    handlePhysics();
    
    if (!shop.isOpen()) {
        player.update(&randomizer);
        
        if (player.getState() == 1) {
            float current_time = game_clock.getElapsedTime().asSeconds();
            if ((current_time-(int)current_time) <= 0.02 &&  (current_time-(int)current_time)>=-0.02 ){
                player.probeBite(&randomizer);
            }
        }
    }
    
    shop.update();
}