#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Constants.h"
#include "Message.h"
using namespace std;
using namespace sf;

sf::Font Game::titleFont;
sf::Font Game::statusFont;
sf::Font Game::defaultFont;
sf::Font Game::winFont;

Game::Game(sf::RenderWindow& wind, const std::string& name_)
    : window(wind),
      //sounds(),
      border(sf::Vector2f(GameWindowSize, GameWindowSize)),
      door1(CellSize),door2(CellSize),
      displayMaze(false)
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
    titleText.setString(name_ + string("'s Hidden Maze Game"));

    statusText.setCharacterSize(24);
    statusText.setPosition(800.0f, 25.0f);
    statusText.setFillColor(sf::Color::Yellow);
    statusText.setString(string(" \n\nBruises 0") + "\nScore  0");

    defaultText.setStyle(sf::Text::Bold);
    refresh(name_);
}

void Game::refresh(const string& name_)
{
    if (grid) delete grid;
    if (player) delete player;
    grid = new Grid();
    player = new Player(name_, *grid);
}

void Game::draw_and_display()
{
    window.clear();
    window.draw(border);
    window.draw(door2);
    window.draw(arrow2);
    statusText.setString(string("Time ") + std::to_string(countdown()) + "\nBruises " + std::to_string(player->getBruises()) + "\nScore " + std::to_string(player->getScore()));
    window.draw(statusText);
    window.draw(titleText);
    if (player->getPath().size() > 1) player->draw_path(window);
    if (displayMaze)
    {
        grid->draw_path(window);
        grid->draw(window);
    }
    else border.setTexture(&borderTexture);

    player->draw(window);
    window.display();
}

bool Game::playAgain()
{
    unsigned fontsize = 32;
    defaultText.setCharacterSize(fontsize);
    std::string text = "Play Again? (Y/N)";
    if (message)
    {
        delete message;
        message = nullptr;
    }
    message = new Message(text,
                          sf::Vector2f(0.67f * text.length()*fontsize, 2.1f * fontsize),
                          sf::Vector2f(0.30f * GameSize.x, 0.4f * GameSize.y),
                          sf::Vector2f(0.36f * GameSize.x, 0.41f * GameSize.y),
                          defaultFont,
                          fontsize);
    sf::Event event;
    statusText.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        window.clear();
        while (window.pollEvent(event))
        {
            if      (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return false;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) return true;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) return false;
            else break;
        }
        window.draw(border);
        window.draw(door2);
        window.draw(arrow2);
        statusText.setString(string("Time ") + std::to_string(countdown()) + "\nBruises " + std::to_string(getBruises()) + "\nScore " + std::to_string(getScore()));
        window.draw(statusText);
        window.draw(titleText);
        player->draw(window);
        player->draw_path(window);
        message->draw(window);
        window.display();
    }

    delete message;
    message = nullptr;
    return false;
}

void Game::start()
{
    unsigned fontsize = 24;
    defaultText.setCharacterSize(fontsize);
    std::string text = "Press the Right Arrow key to start";

    message = new Message(text,
                          sf::Vector2f(0.67f * text.length()*fontsize, 2.1f * fontsize),
                          sf::Vector2f(0.23 * GameSize.x, 0.4f * GameSize.y),
                          sf::Vector2f(0.31f * GameSize.x, 0.41f * GameSize.y),
                          defaultFont,
                          fontsize);
    message->draw(window);
    window.draw(door1);
    window.draw(arrow1);
}

void Game::winlose()
{
    if (message)
    {
        delete message;
        message = nullptr;
    }
    if (status == Win)
    {
        auto fontsize = 64;
        string text = "Yeah!!!   You win";

        message = new Message(text,
                              sf::Vector2f(0.60f * text.length()*fontsize, 1.5f * fontsize),
                              sf::Vector2f(0.17f * GameSize.x, 0.5f * GameSize.y),
                              sf::Vector2f(0.21f * GameSize.x, 0.512f * GameSize.y),
                              winFont,
                              fontsize);
        message->draw(window);
    }
    else
    {
        auto fontsize = 64;
        string text = "Too bad, you lose";
        defaultText.setCharacterSize(fontsize);
        message = new Message(text,
                              sf::Vector2f(0.60f * text.length()*fontsize, 1.5f * fontsize),
                              sf::Vector2f(0.18f * GameSize.x, 0.5f * GameSize.y),
                              sf::Vector2f(0.28f * GameSize.x, 0.51f * GameSize.y),
                              defaultFont,
                              fontsize);
        message->draw(window);
    }
    window.display();
    sf::sleep(sf::Time(sf::seconds(4.0f)));

    delete message;
    message = nullptr;
}

Grid::Contents Game::jump()
{
    unsigned fontsize = 24;
    defaultText.setCharacterSize(fontsize);
    std::string text = "Press an arrow key to indicate\n     the direction of the jump\n or Escape to cancel the jump";
    message = new Message(text,
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
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) return jump(Up);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) return  jump(Down);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) return jump(Left);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) return jump(Right);
            else break;
        }

        message->draw(window);
        window.display();
    }
    return Grid::OutOfBounds;
}

Grid::Contents Game::jump(Direction direction)
{
    sf::Vector2i location = player->getLocation();
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
    if (message)
    {
        delete message;
        message = nullptr;
    }
    player->setJumped();
    player->decrementCountdown(3);
    return player->processMove(newLocation);
}

bool Game::flash()
{
    if (!player->flashed())
    {
        Clock clock;
        int elapsedTime;
        toggleDisplayMaze();
        while (window.isOpen())
        {
            elapsedTime = clock.getElapsedTime().asMilliseconds();
            if (elapsedTime > 1000.0f) break;
            draw_and_display();
        }
        toggleDisplayMaze();
        if (status == Active)
        {
            player->setFlashed();
            player->incrementBruises();
            grid->AddARandomWall("rubber");
            grid->AddARandomWall();
            player->decrementCountdown(3);
            bounce();
        }
        return true;
    }
    return false;
}
