#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "SFML/graphics.hpp"
#include "GameBoard.h"
#include "Constants.h"
using namespace std;
using namespace sf;

sf::Font GameBoard::titleFont;
sf::Font GameBoard::statusFont;
sf::Font GameBoard::defaultFont;

GameBoard::GameBoard(sf::RenderWindow& wind, Sounds& sound, std::string& name_)
    : window(wind),
      sounds(sound),
      name(name_),
      grid(),
      border(sf::Vector2f(GameWindowSize, GameWindowSize)),
      door1(CellSize),door2(CellSize),
      displayMaze(false)
{
    border.setFillColor(sf::Color(sf::Color::Blue));
    border.setOutlineThickness(CellWidth);
    //border.setOutlineColor(sf::Color(250, 150, 100));
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

    titleText.setFont(titleFont);
    statusText.setFont(statusFont);
    defaultText.setFont(defaultFont);

    titleText.setCharacterSize(36);
    titleText.setPosition(WindowHorizontalOffset, CellWidth);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setString(name + string("'s Hidden Maze Game"));

    statusText.setCharacterSize(24);
    statusText.setPosition(800.0f, 25.0f);
    statusText.setFillColor(sf::Color::Yellow);
    statusText.setString(string(" \n\nBruises 0") + "\nScore 0");

    defaultText.setStyle(sf::Text::Bold);

}

GameBoard::~GameBoard()
{
    //dtor
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
        border.setFillColor(sf::Color(sf::Color::Cyan));
        grid.draw_path(window);
        grid.draw(window);
    }
    else border.setFillColor(sf::Color(sf::Color::Blue));

    switch (status)
    {
    case Active:
        break;
    case Loss:
        statusText.setFillColor(sf::Color::Red);
        defaultText.setCharacterSize(64);
        defaultText.setPosition(340.0f, 460.0f);
        defaultText.setFillColor(sf::Color::Red);
        defaultText.setString(string("Game Over"));
        window.draw(defaultText);
        sounds.getBooSound().play();
        player.draw(window);
        window.display();
        sf::sleep(sf::Time(sf::seconds(4.0f)));
        break;
    case Win:
        statusText.setFillColor(sf::Color::Green);
        defaultText.setCharacterSize(64);
        defaultText.setPosition(340.0f, 460.0f);
        defaultText.setFillColor(sf::Color::Green);
        defaultText.setString(string("Game Over"));
        window.draw(defaultText);
        sounds.getWinSound().play();
        player.draw(window);
        window.display();
        sf::sleep(sf::Time(sf::seconds(4.0f)));
        break;
    case NotStarted:
        statusText.setFillColor(sf::Color::Green);
        defaultText.setCharacterSize(48);
        defaultText.setPosition(125.0f, 300.0f);
        defaultText.setFillColor(sf::Color::White);
        defaultText.setString(string("Press the Right Arrow key to start"));
        window.draw(defaultText);
        window.draw(door1);
        window.draw(arrow1);
        break;
    default:
        ;
    }
    player.draw(window);
    window.display();
}

void GameBoard::flash(Player& player)
{
    Clock clock;
    float elapsedTime;
    toggleDisplayMaze();
    while (window.isOpen())
    {
        elapsedTime = clock.getElapsedTime().asMilliseconds();
        if (elapsedTime > 800.0f) break;
        draw_and_display(player, 0, Active);
    }
    toggleDisplayMaze();
}
