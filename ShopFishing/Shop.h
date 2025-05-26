#pragma once
#include "Menu.h"
#include "Player.h"
#include "FishingRod.h"
#include <vector>
#include <memory>

struct ShopItem {
    std::shared_ptr<FishingRod> rod;
    float price;
    std::string name;
    std::string description;
    bool isOwned;
    
    ShopItem(std::shared_ptr<FishingRod> r, float p, std::string n, std::string d) 
        : rod(r), price(p), name(n), description(d), isOwned(false) {}
};

class shop : public Menu {
private:
std::vector<ShopItem> items;
Player* player;
int selected_item;
sf::RectangleShape background;
 sf::RectangleShape item_background;
    sf::Text title_text;
    sf::Text money_text;
    sf::Text item_text;
    sf::Text price_text;
    sf::Text description_text;
    sf::Text controls_text;
    sf::Font font;
    bool is_open;

    public:
    
    Shop(Player* p);
    void initializeShop();
    void render(sf::RenderWindow* window) override;
    void handleInputs() override;
    void update() override;
    void buySelectedItem();
    void equipSelectedItem();
    bool isOpen() const { return is_open; }
    void open() { is_open = true; }
    void close() { is_open = false; }
    void updateOwnedItems();
};

