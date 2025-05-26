#include "Shop.h"
#include <iostream>

Shop::Shop(Player* p) : player(p), selected_item(0), is_open(false) {

    background.setSize(sf::Vector2f(300, 400));
    background.setPosition(50, 50);
    background.setFillColor(sf::Color(50, 50, 50, 200));
    

    item_background.setSize(sf::Vector2f(280, 40));
    item_background.setFillColor(sf::Color(70, 70, 70));
    

    initializeShop();
    
    std::cout << "Shop Initialized" << std::endl;
}

void Shop::initializeShop() {

    shop_items.clear();
    

    auto basic_rod = std::make_shared<FishingRod>(0.7f, 0.2f, 1);
    shop_items.emplace_back(basic_rod, 0.0f, "Basic Rod", "A simple fishing rod");
    shop_items[0].isOwned = true; 
    

    auto improved_rod = std::make_shared<FishingRod>(0.8f, 0.3f, 2);
    shop_items.emplace_back(improved_rod, 100.0f, "Improved Rod", "Better catch rate and control");
    
 
    auto advanced_rod = std::make_shared<FishingRod>(0.9f, 0.4f, 3);
    shop_items.emplace_back(advanced_rod, 250.0f, "Advanced Rod", "High-quality rod for experienced anglers");
    

    auto master_rod = std::make_shared<FishingRod>(0.95f, 0.5f, 4);
    shop_items.emplace_back(master_rod, 500.0f, "Master Rod", "The finest rod money can buy");
    

    auto pro_rod = std::make_shared<FishingRod>(0.98f, 0.6f, 5);
    shop_items.emplace_back(pro_rod, 1000.0f, "Professional Rod", "For the most dedicated fishers");
}

void Shop::render(sf::RenderWindow* window) {
    if (!is_open) return;
    

    window->draw(background);
    

    

    for (size_t i = 0; i < shop_items.size(); i++) {
        sf::Vector2f item_pos(60, 100 + i * 50);
        item_background.setPosition(item_pos);
        

        if (i == selected_item) {
            item_background.setFillColor(sf::Color(100, 150, 100));
        } else if (shop_items[i].isOwned) {
            item_background.setFillColor(sf::Color(100, 100, 150));
        } else {
            item_background.setFillColor(sf::Color(70, 70, 70));
        }
        
        window->draw(item_background);
        

        sf::RectangleShape price_indicator;
        price_indicator.setSize(sf::Vector2f(20, 20));
        price_indicator.setPosition(item_pos.x + 250, item_pos.y + 10);
        
        if (shop_items[i].isOwned) {
            price_indicator.setFillColor(sf::Color::Green); // Owned
        } else if (player->getMoney() >= shop_items[i].price) {
            price_indicator.setFillColor(sf::Color::Yellow); // Can afford
        } else {
            price_indicator.setFillColor(sf::Color::Red); // Can't afford
        }
        
        window->draw(price_indicator);
    }
    

    static int last_selected = -1;
    if (last_selected != selected_item) {
        last_selected = selected_item;
        std::cout << "\n=== SHOP ===" << std::endl;
        std::cout << "Money: $" << player->getMoney() << std::endl;
        std::cout << "Selected: " << shop_items[selected_item].name << std::endl;
        std::cout << "Price: $" << shop_items[selected_item].price << std::endl;
        std::cout << "Description: " << shop_items[selected_item].description << std::endl;
        std::cout << "Owned: " << (shop_items[selected_item].isOwned ? "Yes" : "No") << std::endl;
        std::cout << "Controls: W/S to navigate, E to buy/equip, Q to close" << std::endl;
    }
}

void Shop::handleInputs() {
    if (!is_open) return;
    
    static sf::Clock input_timer;
    if (input_timer.getElapsedTime().asMilliseconds() < 200) return; // Input delay
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && selected_item > 0) {
        selected_item--;
        input_timer.restart();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && selected_item < shop_items.size() - 1) {
        selected_item++;
        input_timer.restart();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        if (shop_items[selected_item].isOwned) {
            equipSelectedItem();
        } else {
            buySelectedItem();
        }
        input_timer.restart();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        close();
        input_timer.restart();
    }
}

void Shop::update() {
    if (is_open) {
        updateOwnedItems();
    }
}

void Shop::buySelectedItem() {
    ShopItem& item = shop_items[selected_item];
    
    if (item.isOwned) {
        std::cout << "You already own this item!" << std::endl;
        return;
    }
    
    if (player->getMoney() >= item.price) {
        player->spendMoney(item.price);
        player->addRod(item.rod);
        item.isOwned = true;
        std::cout << "Bought " << item.name << " for $" << item.price << "!" << std::endl;
    } else {
        std::cout << "Not enough money! Need $" << item.price << ", have $" << player->getMoney() << std::endl;
    }
}

void Shop::equipSelectedItem() {
    ShopItem& item = shop_items[selected_item];
    
    if (!item.isOwned) {
        std::cout << "You don't own this item!" << std::endl;
        return;
    }
    
    player->changeEquipped(item.rod);
    std::cout << "Equipped " << item.name << "!" << std::endl;
}

void Shop::updateOwnedItems() {
    // Update which items are owned based on player's inventory
    for (auto& item : shop_items) {
        item.isOwned = player->ownsRod(item.rod);
    }
}