#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Constants.h"
//#include "Message.h"
#include "Msg.h"
using namespace std;

Game::Game(sf::RenderWindow& wind, Fonts& fnts, const std::string& name_)
    : window(wind),
      fonts(fnts),
      sounds(),
      border(sf::Vector2f(GameWindowSize, GameWindowSize)),
      door1(CellSize),door2(CellSize),
      titleText(name_ + "'s Hidden Maze Game", fonts.font("kristan"), 36),
      statusText("Time 60\nBruises 0\nScore 0", fonts.font("courier"), 24 ),
      displayMaze(false)
{
    border.setOutlineThickness(CellWidth);
    borderTexture.loadFromFile(BorderImageFile);
    border.setTexture(&borderTexture);
    border.setOutlineColor(sf::Color(sf::Color::Blue));
    border.setPosition(WindowHorizontalOffset, WindowVerticalOffset);
    door1.setFillColor(sf::Color(0,0,0));
    door1.setPosition(WindowHorizontalOffset - CellWidth, WindowVerticalOffset + 0 * CellWidth);
    door2.setFillColor(sf::Color(sf::Color::Green));
    door2.setPosition(WindowHorizontalOffset + NumRows * CellWidth, WindowVerticalOffset + (NumRows-1) * CellWidth);

    arrowTexture.loadFromFile(ArrowImageFile);
    arrow1.setTexture(arrowTexture);
    arrow2.setTexture(arrowTexture);
    arrow1.setPosition(WindowHorizontalOffset - 2 * CellWidth, WindowVerticalOffset + 0 * CellWidth);
    arrow2.setPosition(WindowHorizontalOffset + (NumRows+1) * CellWidth, WindowVerticalOffset + (NumRows-1) * CellWidth);

    titleText.setPosition(WindowHorizontalOffset, CellWidth);
    titleText.setFillColor(sf::Color::Yellow);

    statusText.setPosition(800.0f, 25.0f);
    statusText.setFillColor(sf::Color::Yellow);

    refresh(name_);

    sounds.playmusic();

    timeBar.setSize(sf::Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(sf::Color::Red);
    timeBar.setPosition((GameSize.x / 2) - timeBarStartWidth / 2, 85);
}

Game::~Game()
{
    delete grid;
    grid = nullptr;
    delete player;
    player = nullptr;
    delete message;
    message = nullptr;
}

// getters
sf::RenderWindow& Game::getWindow()
{
    return window;
}

sf::RectangleShape& Game::getBorder()
{
    return border;
}

Grid* Game::getGrid()
{
    return grid;
}

Player* Game::getPlayer()
{
    return player;
}

int Game::getScore() const
{
    return player->getScore();
}

int Game::getBruises() const
{
    return player->getBruises();
}

Game::GameStatus Game::getStatus() const
{
    return status;
}

Sounds& Game::getSounds()
{
    return sounds;
}

int Game::getCountdown() const
{
    return player -> getCountdown();
}

//setters
void Game::setStatus(Game::GameStatus status_)
{
    status = status_;
}
void Game::toggleDisplayMaze()
{
    displayMaze = !displayMaze;
}

void Game::incrementBruises()
{
    player->incrementBruises();
}
void Game::decrementScore()
{
    player->decrementScore();
}

void Game::refresh(const string& name_)
{
    if (grid) delete grid;
    if (player) delete player;
    grid = new Grid();
    player = new Player(name_, *grid, sounds);
}

void Game::bounce()
{
    sounds.play(Sounds::Bounce);
    player->bounce();
}

void Game::move(Player::Direction direction)
{
    if (status == Game::NotStarted) status = Game::Active;
    Grid::Contents contents = player-> move(direction);

    if (contents == Grid::Win)
    {
        status = Game::Win;
    }
    if (contents == Grid::Loss)
    {
        status = Game::Loss;
    }

    return;
}

bool Game::bomb()
{
    return player -> bomb();
}

bool Game::light()
{
    return player -> light();
}

void Game::draw_and_display()
{
    window.clear();
    window.draw(border);
    window.draw(door2);
    window.draw(arrow2);
    statusText.setString(string("Time ") + std::to_string(getCountdown()) + "\nBruises " + std::to_string(player->getBruises()) + "\nScore " + std::to_string(player->getScore()));
    window.draw(statusText);
    window.draw(titleText);
    timeBar.setSize(sf::Vector2f(timeBarStartWidth * player->getCountdown()/60, timeBarHeight));
    window.draw(timeBar);
    if (player->getPath().size() > 1) player->draw_path(window);

    if (displayMaze)
    {
        grid->draw_path(window);
        grid->draw(window);
    }
    else border.setTexture(&borderTexture);

    player->draw(window);
    if (getStatus() == Game::NotStarted && !displayMaze) start();

    window.display();
}

bool Game::playAgain()
{
    Msg msg(Text(string("Play again?  (Y/N)"), fonts.font("arial"), 64, window, sf::Color::Yellow));

    sf::Event event;
    statusText.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
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
        statusText.setString(string("Time ") + std::to_string(getCountdown()) + "\nBruises " + std::to_string(player->getBruises()) + "\nScore " + std::to_string(player->getScore()));
        window.draw(statusText);
        window.draw(titleText);
        player->draw(window);
        player->draw_path(window);
        msg.draw();
        window.display();
    }

    return false;
}

void Game::start()
{
    Msg msg(Text(string("Press the Right Arrow key to start"), fonts.font("arial"), 24, window, sf::Color::Green));
    msg.draw();
    player->draw(window);
    window.draw(arrow1);
}

Grid::Contents Game::jump()
{
    if (player->jumped())
    {
        sounds.play(Sounds::Fart);
        return Grid::Empty;
    }

    Text text("Press an arrow key to indicate\n     the direction of the jump\n or Escape to cancel the jump", fonts.font("arial"), 24, window, sf::Color::Yellow);
    Msg msg(text);

    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if      (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return Grid::OutOfBounds;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) return jump(Player::Up);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) return  jump(Player::Down);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) return jump(Player::Left);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) return jump(Player::Right);
            else break;
        }
        msg.draw();
        window.display();
    }
    return Grid::OutOfBounds;
}

Grid::Contents Game::jump(Player::Direction direction)
{
    sf::Vector2i location = player->getLocation();
    if ((location.y < 2 && direction == Player::Up) ||
            (location.x < 2 && direction == Player::Left) ||
            (location.y > 38 && direction == Player::Down) ||
            (location.x > 38 && direction == Player::Right))
        return Grid::OutOfBounds;
    sf::Vector2i newLocation(location);
    switch (direction)
    {
    case Player::Up:
        newLocation.y-=2;
        break;
    case Player::Down:
        newLocation.y+=2;
        break;
    case Player::Left:
        newLocation.x-=2;
        break;
    case Player::Right:
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
        sf::Clock clock;
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
    sounds.play(Sounds::Fart);
    return false;
}
