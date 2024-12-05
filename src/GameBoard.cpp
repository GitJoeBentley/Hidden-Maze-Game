#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "GameBoard.h"
#include "Constants.h"
#include "Message.h"
using namespace std;
using namespace sf;

sf::Font GameBoard::titleFont;
sf::Font GameBoard::statusFont;
sf::Font GameBoard::defaultFont;
sf::Font GameBoard::winFont;

GameBoard::GameBoard(sf::RenderWindow& wind, Sounds& sound, std::string& name_)
    : window(wind),
      sounds(sound),
      name(name_),
      grid(),
      border(sf::Vector2f(GameWindowSize, GameWindowSize)),
      door1(CellSize),door2(CellSize),
      displayMaze(false),
      popUp(sf::Vector2f(GameWindowSize/3.0, GameWindowSize/6.0))
{
    border.setOutlineThickness(CellWidth);
    borderTexture.loadFromFile(BorderImageFile);
    border.setTexture(&borderTexture);
    border.setOutlineColor(sf::Color(sf::Color::Red));
    border.setPosition(WindowHorizontalOffset, WindowVerticalOffset);
    door1.setFillColor(sf::Color(0,0,0));
    door1.setPosition(WindowHorizontalOffset - CellWidth, WindowVerticalOffset + 0 * CellWidth);
    door2.setFillColor(sf::Color(sf::Color::Blue));
    door2.setPosition(WindowHorizontalOffset + 40 * CellWidth, WindowVerticalOffset + 39 * CellWidth);

    arrowTexture.loadFromFile(ArrowImageFile);
    arrow1.setTexture(arrowTexture);
    arrow2.setTexture(arrowTexture);
    arrow1.setPosition(WindowHorizontalOffset - 2 * CellWidth, WindowVerticalOffset + 0 * CellWidth);
    arrow2.setPosition(WindowHorizontalOffset + 41 * CellWidth, WindowVerticalOffset + 39 * CellWidth);

    titleFont.loadFromFile(TitleFontFile);
    statusFont.loadFromFile(StatusFontFile);
    defaultFont.loadFromFile(DefaultFontFile);
    winFont.loadFromFile(WinFontFile);

    titleText.setFont(titleFont);
    statusText.setFont(statusFont);
    defaultText.setFont(defaultFont);
    winText.setFont(winFont);

    titleText.setCharacterSize(36);
    titleText.setPosition(WindowHorizontalOffset, CellWidth);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setString(name + string("'s Hidden Maze Game"));

    statusText.setCharacterSize(24);
    statusText.setPosition(800.0f, 25.0f);
    statusText.setFillColor(sf::Color::Yellow);
    statusText.setString(string(" \n\nBruises 0") + "\nScore  0");

    defaultText.setStyle(sf::Text::Bold);

    popUp.setOutlineColor(sf::Color::Yellow);
    popUp.setOutlineThickness(10.0f);
    popUp.setPosition(WindowHorizontalOffset + 275.f, WindowVerticalOffset + 320.f);
    popUp.setFillColor(sf::Color(sf::Color::Black));
}

void GameBoard::draw_and_display(Player& player, int countdown, GameStatus status)
{
    window.clear();

    window.draw(border);
    window.draw(door2);
    window.draw(arrow2);
    statusText.setString(string("Time ") + std::to_string(countdown) + "\nBruises " + std::to_string(player.getBruises()) + "\nScore " + std::to_string(player.getScore()));
    window.draw(statusText);
    window.draw(titleText);
    if (player.getPath().size() > 1) player.draw_path(window);
    if (displayMaze)
    {
        grid.draw_path(window);
        grid.draw(window);
    }
    else border.setTexture(&borderTexture);;

    switch (status)
    {
    case Active:
        break;
    case Loss:
    case Win:
        sounds.getWinSound().play();
        winlose(status);
        break;
    case NotStarted:

        start();
        break;
    default:
        ;
    }
    player.draw(window);
    window.display();
}

void GameBoard::start()
{
    unsigned fontsize = 24;
    defaultText.setCharacterSize(fontsize);
    std::string text = "Press the Right Arrow key to start";

    Message msg(text,
                sf::Vector2f(0.67f * text.length()*fontsize, 2.1f * fontsize),
                sf::Vector2f(0.23 * GameSize.x, 0.4f * GameSize.y),
                sf::Vector2f(0.31f * GameSize.x, 0.41f * GameSize.y),
                defaultFont,
                fontsize);
    msg.draw(window);
    window.draw(door1);
    window.draw(arrow1);
}

void GameBoard::winlose(GameStatus status)
{
    if (status == Win)
    {
        auto fontsize = 64;
        string text = "Yeah!!!   You win";
        Message msg(text,
                    sf::Vector2f(0.60f * text.length()*fontsize, 1.5f * fontsize),
                    sf::Vector2f(0.17f * GameSize.x, 0.5f * GameSize.y),
                    sf::Vector2f(0.21f * GameSize.x, 0.512f * GameSize.y),
                    winFont,
                    fontsize);
        msg.draw(window);
    }
    else
    {
        auto fontsize = 64;
        string text = "Too bad, you lose";
        defaultText.setCharacterSize(fontsize);
        Message msg(text,
                    sf::Vector2f(0.60f * text.length()*fontsize, 1.5f * fontsize),
                    sf::Vector2f(0.18f * GameSize.x, 0.5f * GameSize.y),
                    sf::Vector2f(0.28f * GameSize.x, 0.512f * GameSize.y),
                    defaultFont,
                    fontsize);
        msg.draw(window);
    }
    window.display();
    sf::sleep(sf::Time(sf::seconds(5.0f)));
}

Grid::Contents GameBoard::jump(Player& player)
{
    unsigned fontsize = 24;
    defaultText.setCharacterSize(fontsize);
    std::string text = "Press an arrow key to indicate\n     the direction of the jump\n or Escape to cancel the jump";
    Message msg(text,
                sf::Vector2f(500.0f, 180.0f),
                sf::Vector2f(0.245 * GameSize.x, 0.35 * GameSize.y),
                sf::Vector2f(0.33f * GameSize.x, 0.39f * GameSize.y),
                defaultFont,
                fontsize);
    sf::Event event;

    while (window.isOpen())
    {
        // Check all the window's events that were triggered
        // since the last iteration of the main loop.
        while (window.pollEvent(event))
        {
            if      (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return Grid::OutOfBounds;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) return jump(player, Up);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) return  jump(player, Down);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) return jump(player, Left);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) return jump(player, Right);
            else break;
        }

        msg.draw(window);
        window.display();
    }
    return Grid::OutOfBounds;
}

Grid::Contents GameBoard::jump(Player& player, Direction direction)
{
    sf::Vector2i location = player.getLocation();
    if ((location.y < 2 && direction == Up) ||
            (location.x < 2 && direction == Left) ||
            (location.y > 38 && direction == Down) ||
            (location.x > 38 && direction == Right))
        return Grid::OutOfBounds;
    sf::Vector2i newLocation(location);
    switch (direction)
    {
    case Up:
        newLocation.y-=2;
        break;
    case Down:
        newLocation.y+=2;
        break;
    case Left:
        newLocation.x-=2;
        break;
    case Right:
        newLocation.x+=2;
    default:
        ;
    }
    return player.processMove(newLocation);
}

void GameBoard::flash(Player& player)
{
    Clock clock;
    int elapsedTime;
    toggleDisplayMaze();
    while (window.isOpen())
    {
        elapsedTime = clock.getElapsedTime().asMilliseconds();
        if (elapsedTime > 750.0f) break;
        draw_and_display(player, 0, Active);
    }
    toggleDisplayMaze();
}
