#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Grid.h"

using std::cout;
using std::endl;


int main()
{
    srand(static_cast<unsigned>(time(0)));
    int level = 1;
    Grid grid(level);
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "", sf::Style::Close);
    window.setTitle(sf::String("Joe's Hidden Maze Game"));
    float GameWindowSize = 40*20.0f;
    sf::RectangleShape border(sf::Vector2f(GameWindowSize, GameWindowSize));
    border.setFillColor(sf::Color(150, 50, 250));

    // set a 10-pixel wide orange outline
    border.setOutlineThickness(20);
    border.setOutlineColor(sf::Color(250, 150, 100));
    border.setPosition(100.0f, 100.0f);

    sf::RectangleShape door1(sf::Vector2f(20.0f, 20.0f));
    door1.setFillColor(sf::Color(0,0,0));
    door1.setPosition(100.0f - 20.0f, 100.0f + 0 * 20.0f);
    sf::RectangleShape door2(sf::Vector2f(20.0f, 20.0f));
    door2.setFillColor(sf::Color(0,0,0));
    door2.setPosition(100.0f + 40 * 20.0f, 100.0f + 39 * 20.0f);

    //sf::RectangleShape wall(sf::Vector2f(20.0f, 20.0f));
    //wall.setFillColor(sf::Color(20,0,20));

    sf::Texture arrowTexture;
    arrowTexture.loadFromFile("c:/temp/arrow.jpg");
    sf::Sprite arrow1;
    arrow1.setTexture(arrowTexture);
    arrow1.setPosition(100.0f - 40.0f, 100.0f + 0 * 20.0f);
    sf::Sprite arrow2;
    arrow2.setTexture(arrowTexture);
    arrow2.setPosition(100.0f + 41 * 20.0f, 100.0f + 39 * 20.0f);
    grid.generate_path();
    grid.print_path();

    // Run the program as long as the window is open
    while (window.isOpen())
    {
        // Check all the window's events that were triggered
        // since the last iteration of the main loop.
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close event so we close the window
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            // Escape key pressed
            if ((event.type == sf::Event::KeyPressed)
                && (event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
        }
        window.draw(border);
        window.draw(door1);
        window.draw(door2);
        window.draw(arrow1);
        window.draw(arrow2);

        grid.draw_path(window);
        grid.draw(window);
        window.display();
    }


    return 0;
}
