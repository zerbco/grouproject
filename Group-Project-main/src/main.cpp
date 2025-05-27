#include <SFML/Graphics.hpp>
#include "FishingGame.h"
#include "GameFunctionality.h"
#include "Shop.h"
#include "Randomizer.h"



int main()
{
    Randomizer r = Randomizer();
    FishingGame fs = FishingGame();
    Shop shop = Shop(fs.getPlayer());
    GameFunctionality gf = GameFunctionality(2);
    gf.addMenu(&fs);
    gf.addMenu(&shop);
    gf.load();
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH,WINDOW_HEIGHT}), "Fishing game");
    sf::Time mspf= sf::milliseconds(1000/FPS);
    sf::Clock time_since_last_frame;
    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        gf.update();
        gf.handleInputs();

        window.clear();
        gf.render(&window);
        window.display();
        gf.save();
        sf::sleep(mspf-time_since_last_frame.getElapsedTime());
        time_since_last_frame.restart();
        
    }
}
