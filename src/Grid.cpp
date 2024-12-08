#include "Grid.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;


Grid::Grid() : numWalls(0), step(nullptr)
{
    for (int r = 0; r < NumRows; r++)
        for (int c = 0; c < NumCols; c++)
            cell[r][c] = nullptr;

    // Straight-line walls
    int y = rand() % NumRows / 3 + NumRows / 3;
    for (int x = 0; x < NumCols; x++)
    {
        cell[x][y] = new sf::RectangleShape(CellSize);
        cell[x][y]->setPosition(sf::Vector2f(WindowHorizontalOffset + x * CellWidth, WindowVerticalOffset + y * CellWidth));
        cell[x][y]->setFillColor(sf::Color(sf::Color::Black));
        numWalls++;
    }
    int x = rand() % NumCols / 3 + NumCols / 3;
    for (int y = 0; y < NumRows; y++)
    {
        cell[x][y] = new sf::RectangleShape(CellSize);
        cell[x][y]->setPosition(sf::Vector2f(WindowHorizontalOffset + x * CellWidth, WindowVerticalOffset + y * CellWidth));
        cell[x][y]->setFillColor(sf::Color(sf::Color::Black));
        numWalls++;
    }

    // Add random walls
    int counter = 0;

    do
    {
        AddARandomWall();
        counter++;
    }
    while (counter < 250);

    // Add rubber walls
    counter = 0;
    do
    {
        AddARandomWall("rubber");
        counter++;
    }
    while (counter < 25);

    generate_path();
}

void Grid::AddARandomWall(const std::string& type)
{
    int row, col;
    // Make sure location is empty and not in the path
    do
    {
        row = rand() % NumRows;
        col = rand() % NumCols;
    }
    while (locationIsInThePath(col, row) && !(cell[row][col]));

    cell[row][col] = new sf::RectangleShape(CellSize);
    cell[row][col]->setPosition(sf::Vector2f(WindowHorizontalOffset + row * CellWidth, WindowVerticalOffset + col * CellWidth));
    if (type == "solid")
    {
        cell[row][col]->setFillColor(sf::Color(sf::Color::Black));
        numWalls++;
    }
    else
    {
        cell[row][col]->setFillColor(sf::Color(sf::Color::Magenta));
        numWalls++;
    }
}

Grid::~Grid()
{
    for (int r = 0; r < NumRows; r++)
        for (int c = 0; c < NumCols; c++)
            if (cell[r][c])
            {
                delete cell[r][c];
                cell[r][c] = nullptr;
            }
    delete [] step;
}

void Grid::draw(sf::RenderWindow& window)
{
    for (int r = 0; r < NumRows; r++)
    {
        for (int c = 0; c < NumCols; c++)
        {
            if (cell[r][c])
            {
                window.draw(*(cell[r][c]));
            }
        }
    }
}

void Grid::generate_path()
{
    update_path(0,0);
    int move, last_move = -1;
    int x = 0, y = 0;
    while (!(x == NumRows-1 and y == NumRows-1))
    {
        move = rand() % 6;
        switch (move)
        {
        case 0:
            if (x < NumRows-1 && last_move != 4)
            {
                x++;
                update_path(x, y);
            }
            else move = last_move;
            break;
        case 1:
            if (x < NumRows-2 && last_move != 4)
            {
                x++;
                update_path(x, y);
                x++;
                update_path(x, y);
            }
            else move = last_move;
            break;
        case 2:
            if (y < NumRows-1 && last_move != 5)
            {
                y++;
                update_path(x, y);
            }
            else move = last_move;
            break;
        case 3:
            if (y < NumRows-2 && last_move != 5)
            {
                y++;
                update_path(x, y);
                y++;
                update_path(x, y);
            }
            else move = last_move;

            break;
        case 4:
            if (x > 0 && last_move != 0 && last_move != 1)
            {
                x--;
                update_path(x, y);
            }
            else move = last_move;

            break;
        case 5:
            if (y > 0 && last_move != 2 && last_move != 3)
            {
                y--;
                update_path(x, y);
            }
            else move = last_move;

            break;
        default:
            ;
        }
        last_move = move;
    }
    sort(path.begin(), path.end());
    std::vector<int>::iterator it = std::unique(path.begin(), path.end());
    path.resize(std::distance(path.begin(), it));
    step = new sf::CircleShape[path.size()];

    for (unsigned i = 0; i < path.size(); i++)
    {
        x = path[i] / 100;
        y = path[i] % 100;
        step[i].setRadius(4.0f);
        step[i].setPosition(sf::Vector2f(WindowHorizontalOffset + x * CellWidth, WindowVerticalOffset + y * CellWidth));
        step[i].setOrigin(-CellWidth / 2.0f, -CellWidth / 2.0f);
        step[i].setFillColor(sf::Color(sf::Color::Red));
    }
}

void Grid::clearCell(int x, int y)
{
    if (cell[x][y])
    {
        delete cell[x][y];
        cell[x][y] = nullptr;
    }
}


void Grid::print_path() const
{
    for (auto loc : path)
    {
        cout << '(' << loc / 100 << ',' << loc % 100 << ')' << endl;
    }
}

void Grid::draw_path(sf::RenderWindow& window)
{
    for (unsigned i = 0; i < path.size(); i++)
    {
        window.draw(step[i]);
    }
}

void Grid::update_path(int x, int y)
{
    int newLoc = 100 * x + y;
    if (find(path.begin(), path.end(), newLoc) == path.end())
    {
        if (cell[x][y])
        {
            clearCell(x,y);
        }
        path.push_back(newLoc);
    }
}

bool Grid::locationIsInThePath(int x, int y) const
{
    return find(path.begin(), path.end(), 100 * x + y) != path.end();;
}


Grid::Contents Grid::getCellContents(int row, int col) const
{
    if (row == NumRows and col == NumCols-1) return Win;
    sf::RectangleShape* ptrCell = getCell(row, col);
    if (ptrCell)
    {
        if (ptrCell->getFillColor() == sf::Color::Magenta) return RubberWall;
        else return Wall;
    }
    return Empty;
}
