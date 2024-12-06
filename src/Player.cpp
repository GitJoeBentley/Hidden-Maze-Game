#include "Player.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <algorithm>
using namespace std;


Player::Player(const string& name_, Grid& grid_)
    : name(name_), location(sf::Vector2i(-1,0)), grid(grid_), bruises(0), score(0), maxRow(0), maxCol(-1)
{
    playerTexture.loadFromFile(PlayerImageFile);
    player.setTexture(playerTexture);
}


void Player::draw(sf::RenderWindow& window)
{
    player.setPosition(sf::Vector2f(WindowHorizontalOffset + location.x * CellWidth, WindowVerticalOffset + location.y * CellWidth));
    window.draw(player);
}

Grid::Contents Player::move(Direction direction)
{
    if ((location.y == 0 && direction == Up) ||
            (location.x == 0 && direction == Left) ||
            (location.y == 39 && direction == Down) ||
            (location.x == 39 && location.y != 39 && direction == Right))
        return Grid::OutOfBounds;
    sf::Vector2i newLocation(location);
    if (location.x == -1 && direction != Right) return Grid::Empty;
    switch (direction)
    {
    case Up:
        newLocation.y--;
        break;
    case Down:
        newLocation.y++;
        break;
    case Left:
        newLocation.x--;
        break;
    case Right:
        newLocation.x++;
    default:
        ;
    }

    return processMove(newLocation);
}

Grid::Contents Player::processMove(const sf::Vector2i& newLocation)
{
    Grid::Contents cellContents = grid.getCellContents(newLocation.x, newLocation.y);

    switch (cellContents)
    {
    case Grid::Empty:
        location.x = newLocation.x;
        location.y = newLocation.y;
        break;
    case Grid::Wall:
        bruises++;
        break;
    case Grid::RubberWall:
        bounce();
        break;
    case Grid::Win:
        location.x = newLocation.x;
    default:
        ;
    }
    updateScore();
    path.push_back(100 * newLocation.x + newLocation.y);
    return cellContents;
}

void Player::updateScore()
{
    if (location.x > maxCol)
    {
        maxCol = location.x;
        score += 2;
    }
    else if (location.y > maxRow)
    {
        maxRow = location.y;
        score += 2;
    }
    else
    {
        int temp = 100 * location.x + location.y;
        std::vector<int>::iterator it;
        it = find(path.begin(), path.end(), temp);
        if (it == path.end()) score++;
    }
}

void Player::bounce()
{
    sf::Vector2i newLoc;
    bool locationOccupied = true;
    while (locationOccupied)
    {
        newLoc.x = rand() % (location.x + 1);
        newLoc.y = rand() % (location.y + 1);
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
    sf::RectangleShape empty(CellSize);
    empty.setFillColor(sf::Color(sf::Color::White));
    sf::RectangleShape wall(CellSize);
    wall.setFillColor(sf::Color(sf::Color::Black));
    sf::RectangleShape rubberwall(CellSize);
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
            empty.setPosition(WindowHorizontalOffset + x * CellWidth, WindowVerticalOffset + y * CellWidth);
            window.draw(empty);
            break;
        case Grid::Wall:
            wall.setPosition(WindowHorizontalOffset + x * CellWidth, WindowVerticalOffset + y * CellWidth);
            window.draw(wall);
            break;
        case Grid::RubberWall:
            rubberwall.setPosition(WindowHorizontalOffset + x * CellWidth, WindowVerticalOffset + y * CellWidth);
            window.draw(rubberwall);
            break;
        default:
            ;
        }
    }
}

void Player::bomb()
{
    for (int x = location.x - 1; x <= location.x + 1; x++)
    {
        if (x < 0 || x >= 40) continue;
        for (int y = location.y - 1; y <= location.y + 1; y++)
        {
            if (y < 0 || y >= 40 || (x == location.x && y == location.y)) continue;
            grid.clearCell(x,y);
            path.push_back(100 * x + y);
        }
    }
}

void Player::light()
{
    for (int x = location.x - 1; x <= location.x + 1; x++)
    {
        if (x < 0 || x >= 40) continue;
        for (int y = location.y - 1; y <= location.y + 1; y++)
        {
            if (y < 0 || y >= 40) continue;
            path.push_back(100 * x + y);
        }
    }
}

