#include "FishingGame.h"
#include "CollisionRect.h"

FishingGame::FishingGame() {
    player = Player(50,50);
    tiles = new sf::RectangleShape[2] {
        sf::RectangleShape(sf::Vector2f(TILE_PIXEL_SIZE,TILE_PIXEL_SIZE)),
        sf::RectangleShape(sf::Vector2f(TILE_PIXEL_SIZE,TILE_PIXEL_SIZE))
    };
    tiles[0].setFillColor(sf::Color(0,0,0,0));
    tiles[1].setFillColor(sf::Color(255,255,255,255));
    game_clock = sf::Clock();
    std::cout << "Fishing Game Initialized" << std::endl;
}


void FishingGame::render(sf::RenderWindow *window){
    for (int y=0;  y < MAP_HEIGHT; y++){
        for (int x=0; x<MAP_WIDTH; x++){
            tiles[MAP[y][x]].setPosition(sf::Vector2f(x*TILE_PIXEL_SIZE,y*TILE_PIXEL_SIZE));
            window->draw(tiles[MAP[y][x]]);
        }
    }

    player.render(window);
    // std::cout << "FishingGame Rendered" << std::endl;
}

void FishingGame::handleInputs(){
    player.handleInputs();
    sf::Vector2u player_tile_pos = (sf::Vector2u)((sf::Vector2f)player.getPosition()/(float)TILE_PIXEL_SIZE);
    if (player_tile_pos.y+2<MAP_HEIGHT){
        if (player.getState()==0 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && MAP[player_tile_pos.y+2][player_tile_pos.x]==1){
            player.setState(1);
        }
    }
}

void FishingGame::handlePhysics(){
    // DO COLLISION HERE

    for(int y=0; y<MAP_HEIGHT; y++){
        for (int x=0; x<MAP_WIDTH; x++){
            if (MAP[y][x]==1){
                sf::Vector2f player_pos = (sf::Vector2f)player.getPosition();
                sf::Vector2f player_size = (sf::Vector2f)player.getSize();
                sf::Vector2f tile_size = sf::Vector2f(TILE_PIXEL_SIZE,TILE_PIXEL_SIZE);
                sf::Vector2f tile_pos = sf::Vector2f(x,y).componentWiseMul(tile_size);
                CollisionRect player_rect(player_pos.x,player_pos.y,player_size.x,player_size.y);
                CollisionRect tile_rect(tile_pos.x,tile_pos.y,tile_size.x,tile_size.y);
                if (!player_rect.collide(tile_rect)) {continue;}
                sf::Vector2f diff = player_pos-tile_pos;
                if (diff.x>diff.y){
                    if (player_pos.y+player_size.y <= tile_pos.y+tile_size.y){
                    player_pos.y=tile_pos.y-player_size.y;
                    }
                    if (player_pos.y > tile_pos.y){
                        player_pos.y=tile_pos.y;
                    }
                } else{
                    if (player_pos.x+player_size.x <= tile_pos.x+tile_size.x){
                        player_pos.x=tile_pos.x-player_size.x;
                    }
                    
                    if (player_pos.x > tile_pos.x){
                        player_pos.x=tile_pos.x;
                    }
                }
                player.setPosition(player_pos);
            }
        }
    }
}

void FishingGame::update(){
    handlePhysics();
    player.update(&randomizer);
    if (player.getState() == 1) {
        float current_time = game_clock.getElapsedTime().asSeconds();
        // std::cout << (current_time-(int)current_time) << '\n';
        // std::cout <<'a'<<((current_time-(int)current_time) <= 0.02) <<'\n';
        // std::cout <<'b'<<((current_time-(int)current_time) >= -0.02) <<'\n';
        // std::cout <<'c'<<((current_time-(int)current_time) <= 0.02) && ((current_time-(int)current_time) >= -0.02) << '\n';
        if ((current_time-(int)current_time) <= 0.02 &&  (current_time-(int)current_time)>=-0.02 ){
            player.probeBite(&randomizer);
        }
    }
    // std::cout << "FishingGame Updated" << std::endl;
}