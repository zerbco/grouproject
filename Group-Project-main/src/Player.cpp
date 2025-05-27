#include "Player.h"
#include "FishingStats.h"
#include <iostream>

Player::Player(int x, int y, Randomizer *randomizer)
:   
    position(sf::Vector2f(x,y)),
    size(sf::Vector2u(10,20)),
    CollisionRect(position.x,position.y,size.x,size.y),
    fishing(nullptr),
    current_fish(nullptr),
    state(0),
    money(0.0f),
    rd(randomizer)
    {
        sprite=sf::RectangleShape((sf::Vector2f)size);
        equipped_rod = nullptr;
        sprite.setPosition(sf::Vector2f(position.x,position.y));
        sprite.setFillColor(sf::Color(175,175,175));
        std::cout << "Player Initialized" << std::endl;
    }


void Player::updateStats(Fish* fish) {
    if (!fish) return;

    for (auto stats : fish_stats) {
        if (stats.fish_name == fish->getName()) {
            stats.number_caught++;
            
            if (fish->getSize() > stats.max_size) {
                stats.max_size = fish->getSize();
            }

            if (fish->getSize() < stats.min_size || stats.min_size == 0) {
                stats.min_size = fish->getSize();
            }
            stats.total_value += fish->getValue();

            std::cout << "Updated stats for " << fish->getName() << std::endl;
            return;
        }
    }

    FishingStats newStats = {};
    newStats.fish_name = fish->getName();
    newStats.number_caught = 1;
    newStats.max_size = fish->getSize();
    newStats.min_size = fish->getSize();
    newStats.total_value = fish->getValue();

    fish_stats.push_back(newStats);
    std::cout << "Started tracking stats for " << fish->getName() << std::endl;
        
}

void Player::buyRod(FishingRod rod) {
    std::shared_ptr<FishingRod> rod_ptr = std::make_shared<FishingRod>(rod);

    float rodPrice = 50.0f; 

    if(money >= rodPrice) {
        
        money -= rodPrice;
        obtained_rods.push_back(rod_ptr);
        std::cout << "Bought a new fishing rod!" << std::endl;
    }  else {
        std::cout << "Not enough money to buy the rod!" << std::endl;
    }
}

void Player::changeEquipped(std::shared_ptr<FishingRod> rod) {
    bool found = false;
    for (auto& r : obtained_rods) {
        if (r == rod) {
            found = true;
            break;
        }
    }
    if (found) {
        equipped_rod = rod;
        std::cout << "Equipped a new fishing rod!" << std::endl;
    } else {
        std::cout << "You don't own this rod!" << std::endl;
    }
}

void Player::sellFish(Fish* fish) {
    if (!fish) return;

    float value = fish->getValue();
    money += value;
    std::cout << "Sold fish for " << value << " coins!" << std::endl;
}



void Player::render(sf::RenderWindow *window) {
    window->draw(sprite);
    if (state==2){
        fishing->render(window);
    }
    if (state == 1 || state == 2) {
        sf::VertexArray line(sf::PrimitiveType::LineStrip,3);
        line[0].position = sf::Vector2f(size.x,0) +(sf::Vector2f)position;
        line[1].position = sf::Vector2f(size.x+TILE_PIXEL_SIZE/8, TILE_PIXEL_SIZE) + (sf::Vector2f)position;
        line[2].position = sf::Vector2f(size.x+TILE_PIXEL_SIZE/8, 2*TILE_PIXEL_SIZE) + (sf::Vector2f)position;
        line[0].color = sf::Color(100,100,100);
        line[1].color = sf::Color(100,100,100);
        line[2].color = sf::Color(100,100,100);
        window->draw(line);
    }
    // add fishing line with vertex array with primitive type line
}

void Player::handleInputs(){
    // std::cout <<state <<'\n';
    if (state==0){
        sf::Vector2f dir;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            dir.y=-1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            dir.x=-1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            dir.y=1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            dir.x=1;
        }
        position += dir*(speed/FPS);
    }
    if(state==1){
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
            state=0;
        }
    }
    if(state==2){
        if (fishing){
            fishing->handleInputs();
        }
    }
}

void Player::update(){
    if (state == 2) {fishing->update();}
    // std::cout << position.x << 'a'<< position.y << '\n';
    if (fishing) {
        int fishing_state = fishing->checkWin();
        if (fishing_state == 1){
            updateStats(current_fish);
            sellFish(current_fish);
        }
        
        if (fishing_state!=0){
            delete current_fish;
            current_fish=nullptr;
            delete fishing;
            fishing=nullptr;
            state=0;
        }
    }
    
    sprite.setPosition(position);
    // std::cout << "Player Updated" << std::endl;
}

void Player::probeBite(){
    Fish* fish = equipped_rod->bite();
    if (fish){
        std::cout <<fish<<'\n';
        current_fish = fish;
        state=2;
        if (fishing){ delete fishing;}
        sf::Vector2f pos = position+sf::Vector2f(50,0);
        
        fishing = new Fishing(fish->getFishingInfo(),sf::Vector2u(pos.x,pos.y), equipped_rod.get(), rd);
    }
    
}

float Player::getMoney() const { 
    return money; 
}

void Player::addMoney(float amount) { 
    money += amount; 
    std::cout << "Gained $" << amount << ". Total: $" << money << std::endl;
}

void Player::spendMoney(float amount) { 
    money -= amount; 
    std::cout << "Spent $" << amount << ". Remaining: $" << money << std::endl;
}

void Player::addRod(std::shared_ptr<FishingRod> rod) { 
    obtained_rods.push_back(rod); 
}

bool Player::ownsRod(std::shared_ptr<FishingRod> rod) const {
    for (const auto& owned_rod : obtained_rods) {
        if (owned_rod == rod) return true;
    }
    return false;
}


void Player::saveStats(std::ofstream *input){
    *input << (int)fish_stats.size() << '\n';
    for (int i=0; i< fish_stats.size(); i++){
        *input << fish_stats[i].fish_name <<'\n';
        *input << fish_stats[i].max_size <<'\n';
        *input << fish_stats[i].min_size <<'\n';
        *input << fish_stats[i].number_caught <<'\n';
        *input << fish_stats[i].total_value <<'\n';
    }
}
void Player::loadStats(std::ifstream *input){
    
    std::string temp;
    getline(*input, temp);
    int size = std::stoi(temp);
    for (int i=0; i< size; i++){
        FishingStats stat = {};
        getline(*input, temp);
        stat.fish_name = temp;
        getline(*input, temp);
        stat.max_size = std::stof(temp);
        getline(*input, temp);
        stat.min_size = std::stof(temp);
        getline(*input, temp);
        stat.number_caught = std::stoi(temp);
        getline(*input, temp);
        stat.total_value = std::stof(temp);
        fish_stats.push_back(stat);
    }
}