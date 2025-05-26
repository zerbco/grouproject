#include <SFML/Graphics.hpp>
#include "FishingGame.h"
#include "Randomizer.h"



int main()
{
    Randomizer r = Randomizer();
    FishingGame fs = FishingGame();
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
        fs.update();
        fs.handleInputs();

        window.clear();
        fs.render(&window);
        window.display();
        sf::sleep(mspf-time_since_last_frame.getElapsedTime());
        time_since_last_frame.restart();
    }
}
