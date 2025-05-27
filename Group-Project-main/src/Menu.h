#pragma once
#include "Renderable.h"
#include <fstream>
// a special type of renderable for the purposes of menu switching
class Menu: public Renderable {
    public:
        virtual void save(std::ofstream *input)=0;
        virtual void load(std::ifstream *input)=0;
}; 