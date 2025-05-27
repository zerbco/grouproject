#pragma once
#include "Menu.h"
class GameFunctionality {
    private:
        Menu **menus; // Menus need to be stored in the same order to maintain save file cohesion
        int num_menus;
        int selected_menu;
        int created_menus;
    public:
        GameFunctionality(int menu_num);
        ~GameFunctionality() {delete[] menus; }
        void addMenu(Menu *menu);
        void swap_menus(int selected);
        void save();
        void load();
        void update();
        void handleInputs();
        void render(sf::RenderWindow *window);
};