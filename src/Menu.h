#pragma once
#include "Renderable.h"

class Menu: public Renderable {
    public:
        virtual void handleInputs()=0;
        virtual void update() {};
};