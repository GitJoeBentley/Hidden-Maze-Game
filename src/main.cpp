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
#include "Player.h"
#include "Constants.h"
#include "Types.h"
using namespace std;


int main()
{
    srand(static_cast<unsigned>(time(0)));
    int level = 1;
    string name = "Joe";

    bool displayMaze = false;
    sf::RenderWindow window(sf::VideoMode(1000, 1024), "", sf::Style::Close);
    window.setTitle(sf::String(name + "'s Hidden Maze Game"));

    Grid grid(level);

    // Create player
    sf::Texture playerTexture;
    playerTexture.loadFromFile(PlayerImageFile);
    Player player(playerTexture, sf::Vector2i(-1,0), grid);

    sf::RectangleShape border(sf::Vector2f(GameWindowSize, GameWindowSize));
    border.setFillColor(sf::Color(sf::Color::Blue));
    border.setOutlineThickness(20);
    border.setOutlineColor(sf::Color(250, 150, 100));
    border.setPosition(100.0f, WindowVerticalOffset);

    sf::RectangleShape door1(sf::Vector2f(20.0f, 20.0f));
    door1.setFillColor(sf::Color(0,0,0));
    door1.setPosition(100.0f - 20.0f, WindowVerticalOffset + 0 * 20.0f);
    sf::RectangleShape door2(sf::Vector2f(20.0f, 20.0f));
    door2.setFillColor(sf::Color(sf::Color::Blue));
    door2.setPosition(100.0f + 40 * 20.0f, WindowVerticalOffset + 39 * 20.0f);

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
    courierfont.loadFromFile("c:/temp/cour.ttf");

    sf::Text titleText(name + "'s Hidden Maze Game", font, 36);
    titleText.setFillColor(sf::Color(255,200,210));
    titleText.setPosition(WindowHorizontalOffset,20.0f);

    sf::Text levelText(string("Level ") + std::to_string(level), courierfont, 18);
    sf::Text bruisesText("Bruises " + std::to_string(player.getBruises()),courierfont, 18);
    sf::Text scoreText("Score " + std::to_string(player.getScore()), courierfont, 18);
    levelText.setFillColor(sf::Color(190,250,250));
    bruisesText.setFillColor(sf::Color(200,250,250));
    scoreText.setFillColor(sf::Color(210,250,250));
    levelText.setPosition(800.0f,25.0f);
    bruisesText.setPosition(800.0f,50.0f);
    scoreText.setPosition(800.0f,75.0f);

    //////////// Sound effects /////////////
    sf::SoundBuffer rubberBuffer;
    rubberBuffer.loadFromFile(rubberSoundFile);
    sf::Sound rubberSound;
    rubberSound.setBuffer(rubberBuffer);

    sf::SoundBuffer stepBuffer;
    stepBuffer.loadFromFile(stepSoundFile);
    sf::Sound stepSound;
    stepSound.setBuffer(stepBuffer);

    sf::SoundBuffer hitWallBuffer;
    hitWallBuffer.loadFromFile(hitWallSoundFile);
    sf::Sound hitWallSound;
    hitWallSound.setBuffer(hitWallBuffer);

    Grid::Contents cellContents;

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
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F4)) rubberSound.play();
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F5)) stepSound.play();
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F6)) hitWallSound.play();

            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F3))
            {
                if (displayMaze)
                {
                    displayMaze = !displayMaze;
                    border.setFillColor(sf::Color(sf::Color::Blue));
                }
                else
                {
                    displayMaze = !displayMaze;
                    border.setFillColor(sf::Color(sf::Color::Cyan));
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                cellContents = player.move(Up);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                cellContents = player.move(Down);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                cellContents = player.move(Left);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                cellContents = player.move(Right);
            else break;
            //player.print_path();
            if (cellContents == Grid::Empty) stepSound.play();
            if (cellContents == Grid::Wall) hitWallSound.play();
            if (cellContents == Grid::RubberWall) rubberSound.play();
        }
        window.clear();
        window.draw(border);
        if (player.getCol() == -1)
        {
            window.draw(door1);
            window.draw(arrow1);
        }

        window.draw(door2);
        window.draw(arrow2);
        bruisesText.setString("Bruises " + std::to_string(player.getBruises()));
        scoreText.setString("Score " + std::to_string(player.getScore()));
        window.draw(levelText);
        window.draw(bruisesText);
        window.draw(scoreText);
        window.draw(titleText);
        //player.draw(window);

        if (displayMaze)
        {
            grid.draw_path(window);
            grid.draw(window);
        }
        if (player.getPath().size() > 1) player.draw_path(window);
        player.draw(window);
        window.display();
    }


    return 0;
}
