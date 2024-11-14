#include <string>
#include <iostream>
#include "SFML/graphics.hpp"
#include "GameBoard.h"
#include "Constants.h"
using namespace std;
using namespace sf;

sf::Font GameBoard::titleFont;
sf::Font GameBoard::statusFont;

GameBoard::GameBoard(std::string nam, int lev)
    : name(nam),
      level(lev),
      window(sf::VideoMode(GameSize.x, GameSize.y),nam+"'s Hidden Maze Game",sf::Style::Close),
      grid(lev),
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

    titleFont.loadFromFile(titleFontFile);
    statusFont.loadFromFile(statusFontFile);
    titleText.setFont(titleFont);
    titleText.setCharacterSize(36);
    titleText.setPosition(WindowHorizontalOffset, CellWidth);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setString(name + string("'s Hidden Maze Game"));
    statusText.setFont(statusFont);
    statusText.setCharacterSize(24);
    statusText.setPosition(800.0f, 25.0f);
    statusText.setFillColor(sf::Color::Yellow);
    statusText.setString(string("Level ") + to_string(level) + "\nBruises 0" + "\nScore 0");
}

GameBoard::~GameBoard()
{
    //dtor
}

void GameBoard::draw_and_display(Player& player, int countdown)
{
    window.clear();
    window.draw(border);
    if (player.getCol() == -1)
    {
        window.draw(door1);
        window.draw(arrow1);
    }

    window.draw(door2);
    window.draw(arrow2);
    statusText.setString(string("Time ") + std::to_string(countdown) + "\nBruises " + std::to_string(player.getBruises()) + "\nScore " + std::to_string(player.getScore()));
    window.draw(statusText);
    window.draw(titleText);

    if (displayMaze)
    {
        border.setFillColor(sf::Color(sf::Color::Cyan));
        grid.draw_path(window);
        grid.draw(window);
    }
    else border.setFillColor(sf::Color(sf::Color::Blue));

    if (player.getPath().size() > 1) player.draw_path(window);
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
        draw_and_display(player, 0);
    }
    toggleDisplayMaze();
}
