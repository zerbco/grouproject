#include "GameFunctionality.h"
#include <iostream>
#include <filesystem>

GameFunctionality::GameFunctionality(int menu_num): num_menus(menu_num) {
    menus = new Menu*[num_menus];
};

void GameFunctionality::swap_menus(int selected){
    if (selected<0 || selected >= created_menus) {
        std::cout << "Bad menu selection" << std::endl;
        return;
    }
    selected_menu=selected;
}

void GameFunctionality::save(){
    std::filesystem::remove("./assets/save/save.txt");
    std::ofstream file("./assets/save/save.txt");
    for (int i=0; i<num_menus; i++){
        menus[i]->save(&file);
    }
}
void GameFunctionality::load(){
    std::ifstream file("./assets/save/save.txt");
    if (!file.good()) {return;}
    for (int i=0; i<num_menus; i++){
        menus[i]->load(&file);
    }
}

void GameFunctionality::update(){
    menus[selected_menu]->update(); 
}

void GameFunctionality::handleInputs(){
    menus[selected_menu]->handleInputs();
    
    static sf::Clock input_timer;
    if (input_timer.getElapsedTime().asMilliseconds() < 200) return; // Input delay
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
        swap_menus(selected_menu+1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
        swap_menus(selected_menu-1);
    }
}

void GameFunctionality::render(sf::RenderWindow *window){
    menus[selected_menu]->render(window);
}

void GameFunctionality::addMenu(Menu *menu){
    if (selected_menu >= num_menus){return;}
    menus[created_menus] = menu;
    created_menus++;
}