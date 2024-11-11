#include "Player.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>


Player::Player(sf::Texture& texture, sf::Vector2i loc, Grid& grd)
    : player(texture), location(loc), grid(grd), bruises(0), score(0), maxRow(0), maxCol(0)
{
}

Player::~Player()
{
    //dtor
}

void Player::draw(sf::RenderWindow& window)
{
    player.setPosition(sf::Vector2f(100.0f + location.x * 20.0f, WindowVerticalOffset + location.y * 20.0f));
    window.draw(player);
}

Grid::Contents Player::move(Direction direction)
{
    sf::Vector2i newLocation(location);
    Grid::Contents cellContents;
    if (location.x == -1 && direction != Right) return Grid::Empty;
    switch (direction)
    {
    case Up:
        if (location.y > 0)
        {
            newLocation.y--;
            cellContents = grid.getCellContents(newLocation.x, newLocation.y);
            switch (cellContents)
            {
            case Grid::Empty:
                location.y--;
                break;
            case Grid::Wall:
                bruises++;
                break;
            case Grid::RubberWall:
                bounce(newLocation);
                break;
            default:
                ;
            }
        }
        break;
    case Down:
        if (newLocation.y < 39)
        {
            newLocation.y++;
            cellContents = grid.getCellContents(newLocation.x, newLocation.y);
            switch (cellContents)
            {
            case Grid::Empty:
                location.y++;
                break;
            case Grid::Wall:
                bruises++;
                break;
            case Grid::RubberWall:
                bounce(newLocation);
                break;
            default:
                ;
            }
        }
        break;
    case Left:
        if (newLocation.x > 0)
        {
            newLocation.x--;
            cellContents = grid.getCellContents(newLocation.x, newLocation.y);
            switch (cellContents)
            {
            case Grid::Empty:
                location.x--;
                break;
            case Grid::Wall:
                bruises++;
                break;
            case Grid::RubberWall:
                bounce(newLocation);
                break;
            default:
                ;
            }
        }
        break;
    case Right:
        if (newLocation.x < 39)
        {
            newLocation.x++;
            cellContents = grid.getCellContents(newLocation.x, newLocation.y);
            switch (cellContents)
            {
            case Grid::Empty:
                location.x++;
                break;
            case Grid::Wall:
                bruises++;
                break;
            case Grid::RubberWall:
                bounce(newLocation);
                break;
            default:
                ;
            }
        }
        break;
            default:
                ;

    }
    if (location.x > maxRow) maxRow = location.x;
    if (location.y > maxCol) maxCol = location.y;
    score = maxRow + maxCol;
    path.push_back(100 * newLocation.x + newLocation.y);
    return cellContents;
}

void Player::bounce(const sf::Vector2i& currentLoc)
{
    sf::Vector2i newLoc;
    bool locationOccupied = true;
    while (locationOccupied)
    {
        newLoc.x = rand() % (currentLoc.x + 1);
        newLoc.y = rand() % (currentLoc.y + 1);
        if (!grid.getCell(newLoc.x, newLoc.y))
            locationOccupied = false;
    }
    location = newLoc;
    path.push_back(100 * newLoc.x + newLoc.y);
}

void Player::print_path() const
{
    for (auto loc : path)
    {
        std::cout << '(' << loc / 100 << ',' << loc % 100 << ')' << std::endl;
    }
}

void Player::draw_path(sf::RenderWindow& window) const
{
    sf::RectangleShape empty(sf::Vector2f(20.0f, 20.0f));
    empty.setFillColor(sf::Color(sf::Color::White));
    sf::RectangleShape wall(sf::Vector2f(20.0f, 20.0f));
    wall.setFillColor(sf::Color(sf::Color::Black));
    sf::RectangleShape rubberwall(sf::Vector2f(20.0f, 20.0f));
    rubberwall.setFillColor(sf::Color(sf::Color::Magenta));
    Grid::Contents contents;

    int x, y;

    for (unsigned i = 0; i < path.size(); i++)
    {
        x = path[i] / 100;
        y = path[i] % 100;
        contents = grid.getCellContents(x,y);
        switch (contents)
        {
            case Grid::Empty:
                empty.setPosition(100.0f + x * 20.0f, WindowVerticalOffset + y * 20.0f);
                window.draw(empty);
                break;
            case Grid::Wall:
                wall.setPosition(100.0f + x * 20.0f, WindowVerticalOffset + y * 20.0f);
                window.draw(wall);
                break;
            case Grid::RubberWall:
                rubberwall.setPosition(100.0f + x * 20.0f, WindowVerticalOffset + y * 20.0f);
                window.draw(rubberwall);
                break;
            default:
                ;
        }
    }
}
