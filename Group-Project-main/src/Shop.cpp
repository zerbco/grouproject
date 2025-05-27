#include "Shop.h"
#include <iostream>
#include <format>
Shop::Shop(Player* p) : player(p), selected_item(0), buy_button(Button(60,400,300,40,sf::Color::Green)){


    background.setSize(sf::Vector2f(300, 400));
    background.setPosition(sf::Vector2f(50, 50));
    background.setFillColor(sf::Color(50, 50, 50, 200));
    

    item_background.setSize(sf::Vector2f(280, 40));
    item_background.setFillColor(sf::Color(70, 70, 70));
    

    shop_items.clear();
    shop_items.emplace_back(std::make_shared<FishingRod>(BASIC_ROD));
    shop_items.emplace_back(std::make_shared<FishingRod>(IMPROVED_ROD));
    shop_items.emplace_back(std::make_shared<FishingRod>(ADVANCED_ROD));
    shop_items.emplace_back(std::make_shared<FishingRod>(MASTER_ROD));
    shop_items.emplace_back(std::make_shared<FishingRod>(PRO_ROD));

    font = sf::Font("./assets/fonts/calibri.ttf");


    selected_item=0;
    buySelectedItem();
    
    std::cout << "Shop Initialized" << std::endl;
}


void Shop::render(sf::RenderWindow* window) {
    

    window->draw(background);
    
    sf::Text money_text(font);
    money_text.setString(std::format("Money:${}", player->getMoney()));
    money_text.setCharacterSize(20);
    money_text.setFillColor(sf::Color::White);
    window->draw(money_text);
    
    sf::Text buy_text(font);
    buy_text.setString("Buy");
    buy_text.setCharacterSize(20);
    buy_text.setFillColor(sf::Color::White);
    buy_text.setPosition(buy_button.getPos()+buy_button.getSize()/2.f-buy_text.getLocalBounds().size/2.f);

    

    for (size_t i = 0; i < shop_items.size(); i++) {

        sf::Vector2f item_pos(60, 100 + i * 50);


        sf::Text rod_name(font);
        rod_name.setString(shop_items[i].rod->getName());
        rod_name.setCharacterSize(20);
        rod_name.setFillColor(sf::Color::White);
        rod_name.setPosition(item_pos + sf::Vector2f(10,10));

        sf::Text rod_price(font);
        rod_price.setString(std::format("${}",round(shop_items[i].rod->getPrice())));
        rod_price.setCharacterSize(20);
        rod_price.setFillColor(sf::Color::White);
        rod_price.setPosition(item_pos + sf::Vector2f(240-rod_price.getLocalBounds().size.x,10));

        item_background.setPosition(item_pos);

        if (i == selected_item) {
            item_background.setFillColor(sf::Color(100, 150, 100));
        } else if (shop_items[i].isOwned) {
            item_background.setFillColor(sf::Color(100, 100, 150));
        } else {
            item_background.setFillColor(sf::Color(70, 70, 70));
        }
        
        

        sf::RectangleShape price_indicator;
        price_indicator.setSize(sf::Vector2f(20, 20));
        price_indicator.setPosition(item_pos + sf::Vector2f(250,10));
        
        if (shop_items[i].isOwned) {
            price_indicator.setFillColor(sf::Color::Green); // Owned
        } else if (player->getMoney() >= shop_items[i].rod->getPrice()) {
            price_indicator.setFillColor(sf::Color::Yellow); // Can afford
        } else {
            price_indicator.setFillColor(sf::Color::Red); // Can't afford
        }
        

        window->draw(item_background);
        window->draw(price_indicator);
        window->draw(rod_name);
        window->draw(rod_price);
    }
    
    window->draw(buy_text);
    buy_button.render(window);

    static int last_selected = -1;
    if (last_selected != selected_item) {
        last_selected = selected_item;
        std::cout << "\n=== SHOP ===" << std::endl;
        std::cout << "Money: $" << player->getMoney() << std::endl;
        std::cout << "Selected: " << shop_items[selected_item].rod->getName()<< std::endl;
        std::cout << "Price: $" << shop_items[selected_item].rod->getPrice() << std::endl;
        std::cout << "Description: " << shop_items[selected_item].rod->getDesc() << std::endl;
        std::cout << "Owned: " << (shop_items[selected_item].isOwned ? "Yes" : "No") << std::endl;
        std::cout << "Controls: W/S to navigate, E to buy/equip, Q to close" << std::endl;
    }
}

void Shop::handleInputs() {    
    static sf::Clock input_timer;
    if (input_timer.getElapsedTime().asMilliseconds() < 200) return; // Input delay
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && selected_item > 0) {
        selected_item--;
        input_timer.restart();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && selected_item < shop_items.size() - 1) {
        selected_item++;
        input_timer.restart();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
        if (shop_items[selected_item].isOwned) {
            equipSelectedItem();
        } else {
            buySelectedItem();
        }
        input_timer.restart();
    }
}

void Shop::update() {
    updateOwnedItems();
}

void Shop::buySelectedItem() {
    ShopItem& item = shop_items[selected_item];
    
    if (item.isOwned) {
        std::cout << "You already own this item!" << std::endl;
        return;
    }
    
    if (player->getMoney() >= item.rod->getPrice()) {
        player->spendMoney(item.rod->getPrice());
        player->addRod(item.rod);
        item.isOwned = true;
        std::cout << "Bought " << item.rod->getName() << " for $" << item.rod->getPrice() << "!" << std::endl;
    } else {
        std::cout << "Not enough money! Need $" << item.rod->getPrice() << ", have $" << player->getMoney() << std::endl;
    }
}

void Shop::equipSelectedItem() {
    ShopItem& item = shop_items[selected_item];
    
    if (!item.isOwned) {
        std::cout << "You don't own this item!" << std::endl;
        return;
    }
    
    player->changeEquipped(item.rod);
    std::cout << "Equipped " << item.rod->getName() << "!" << std::endl;
}

void Shop::updateOwnedItems() {
    // Update which items are owned based on player's inventory
    for (auto& item : shop_items) {
        item.isOwned = player->ownsRod(item.rod);
    }
}

void Shop::save(std::ofstream *input){
    *input << player->getMoney() << '\n';
    for(int i=0; i<5; i++){
        *input << shop_items[i].isOwned << '\n';
    }
}

void Shop::load(std::ifstream *input){
    std::string temp;
    getline(*input, temp);
    player->addMoney(std::stof(temp));
    for(int i=0; i<5; i++){
        getline(*input, temp);
        bool owned = std::stoi(temp);
        shop_items[i].isOwned=owned;
        if (owned){
            player->addRod(shop_items[i].rod);
            player->changeEquipped(shop_items[i].rod);
        }
    }
}