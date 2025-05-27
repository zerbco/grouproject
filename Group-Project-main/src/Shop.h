#pragma once
#include "Menu.h"
#include "Player.h"
#include "FishingRod.h"
#include "Button.h"
#include <vector>
#include <memory>

struct ShopItem {
    std::shared_ptr<FishingRod> rod;
    bool isOwned;
    
    ShopItem(std::shared_ptr<FishingRod> r): rod(r), isOwned(false) {}
};

class Shop : public Menu {
    private:
        std::vector<ShopItem> shop_items;
        Player* player;
        int selected_item;
        sf::RectangleShape background;
        sf::RectangleShape item_background;
        Button buy_button;
        // sf::Text title_text;
        // sf::Text money_text;
        // sf::Text item_text;
        // sf::Text price_text;
        // sf::Text description_text;
        // sf::Text controls_text;
        sf::Font font;

    public:
        Shop(Player* p);
        void render(sf::RenderWindow* window) override;
        void handleInputs() override;
        void update() override;
        void buySelectedItem();
        void equipSelectedItem();
        void updateOwnedItems();
        void save(std::ofstream *input);
        void load(std::ifstream *input);
};

