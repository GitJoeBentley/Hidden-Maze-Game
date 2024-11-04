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
#include "Constants.h"

using std::cout;
using std::endl;
using std::string;


int main()
{
    srand(static_cast<unsigned>(time(0)));
    int level = 90;
    int bruises = 0;
    int score = 0;
    string name = "Joe";

    bool displayMaze = false;
    Grid grid(level);
    sf::RenderWindow window(sf::VideoMode(1000, 1024), "", sf::Style::Close);
    window.setTitle(sf::String("Joe's Hidden Maze Game"));
    float GameWindowSize = 40*20.0f;
    sf::RectangleShape border(sf::Vector2f(GameWindowSize, GameWindowSize));
    border.setFillColor(sf::Color(150, 50, 250));

    // set a 10-pixel wide orange outline
    border.setOutlineThickness(20);
    border.setOutlineColor(sf::Color(250, 150, 100));
    border.setPosition(100.0f, WindowVerticalOffset);

    sf::RectangleShape door1(sf::Vector2f(20.0f, 20.0f));
    door1.setFillColor(sf::Color(0,0,0));
    door1.setPosition(100.0f - 20.0f, WindowVerticalOffset + 0 * 20.0f);
    sf::RectangleShape door2(sf::Vector2f(20.0f, 20.0f));
    door2.setFillColor(sf::Color(0,0,0));
    door2.setPosition(100.0f + 40 * 20.0f, WindowVerticalOffset + 39 * 20.0f);

    //sf::RectangleShape wall(sf::Vector2f(20.0f, 20.0f));
    //wall.setFillColor(sf::Color(20,0,20));

    sf::Texture arrowTexture;
    arrowTexture.loadFromFile("c:/temp/arrow.jpg");
    sf::Sprite arrow1;
    arrow1.setTexture(arrowTexture);
    arrow1.setPosition(100.0f - 40.0f, WindowVerticalOffset + 0 * 20.0f);
    sf::Sprite arrow2;
    arrow2.setTexture(arrowTexture);
    arrow2.setPosition(100.0f + 41 * 20.0f, WindowVerticalOffset + 39 * 20.0f);
    grid.generate_path();
    //grid.print_path();

    // Fonts
    sf::Font font;
    sf::Font courierfont;
    font.loadFromFile("c:/temp/ITCKRIST.TTF");
    courierfont.loadFromFile("c:/temp/courbd.ttf");

    sf::Text titleText("Joe's Hidden Maze Game", font, 36);
    titleText.setFillColor(sf::Color(255,200,210));
    titleText.setPosition(270.0f,20.0f);

    name.resize(23,' ');
    sf::Text scoreText(name + "Bruises " + std::to_string(bruises) + "                   Score " + std::to_string(score), courierfont, 24);
    scoreText.setFillColor(sf::Color(160,250,250));
    scoreText.setPosition(100.0f,90.0f);


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
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F3))
            {
                displayMaze = !displayMaze;
            }
        }
        window.draw(border);
        window.draw(door1);
        window.draw(door2);
        window.draw(arrow1);
        window.draw(arrow2);
        window.draw(scoreText);
        window.draw(titleText);

        if (displayMaze) {
            grid.draw_path(window);
            grid.draw(window);
        }
        window.display();
    }


    return 0;
}
