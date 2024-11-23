#include "Player.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <algorithm>
using namespace std;

Player::Player(Grid& grd)
    : location(sf::Vector2i(-1,0)), grid(grd), bruises(0), score(0), maxRow(0), maxCol(-1)
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
    sf::Vector2i newLocation(location);
    Grid::Contents cellContents;
    if (location.x == -1 && direction != Right) return Grid::Empty;
    switch (direction)
    {
    case Up:
        if (newLocation.y > 0)
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
        if (newLocation.x == 39 && newLocation.y == 39)
        {
            // It's a win
            newLocation.x++;
            score++;
            location.x++;
            path.push_back(100 * newLocation.x + newLocation.y);
            return Grid::Win;
        }
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

void Player::explodeBomb()
{
    for (int x = location.x - 1; x <= location.x + 1; x++)
    {
        if (x < 0 || x >= 40) continue;
        for (int y = location.y - 1; y <= location.y + 1; y++)
        {
            if (y < 0 || y >= 40 || (x == location.x && y == location.y)) continue;
            //cout << "*** " << x << ',' << y << endl;
            grid.clearCell(x,y);
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

