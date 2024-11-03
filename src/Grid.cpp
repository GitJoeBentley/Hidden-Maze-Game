#include "Grid.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;


Grid::Grid(int level) : numWalls(0), step(nullptr)
{
    for (int r = 0; r < 40; r++)
        for (int c = 0; c < 40; c++)
            cell[r][c] = nullptr;

    std::ostringstream sout;
    sout << level;
    std::string filename = std::string("grid") + sout.str() + ".txt";
    std::ifstream fin(filename);
    std::string line;
    for (int row=0; row < 40; row++)
    {
        getline(fin, line);
        line.resize(40, ' ');
        for (int col = 0; col < 40; col++)
        {
            if (line[col] == '1')
            {
                cell[row][col] = new sf::RectangleShape(sf::Vector2f(20.0f, 20.0f));
                cell[row][col]->setPosition(sf::Vector2f(100.0f + row * 20.0f, WindowVerticalOffset + col * 20.0f));
                cell[row][col]->setFillColor(sf::Color(20,0,20));
                numWalls++;
            }
        }
    }
    fin.close();
    // Add random walls


    int counter = 0;

    do {
        int row = rand() % 40;
        int col = rand() % 40;
        if (!(cell[row][col])) {
            cell[row][col] = new sf::RectangleShape(sf::Vector2f(20.0f, 20.0f));
            cell[row][col]->setPosition(sf::Vector2f(100.0f + row * 20.0f, WindowVerticalOffset + col * 20.0f));
            cell[row][col]->setFillColor(sf::Color(30, 0, 30));
            numWalls++;
            counter++;
        }
    } while (counter < 100 * level);


    // Add rubber walls
    counter = 0;
    do
    {
        int row = rand() % 40;
        int col = rand() % 40;
        if (!(cell[row][col]))
        {
            cell[row][col] = new sf::RectangleShape(sf::Vector2f(20.0f, 20.0f));
            cell[row][col]->setPosition(sf::Vector2f(100.0f + row * 20.0f, WindowVerticalOffset + col * 20.0f));
            cell[row][col]->setFillColor(sf::Color(240, 140,190));
            numWalls++;
            counter++;
        }
    }
    while (counter < 10 * level);
}

Grid::~Grid()
{
    //dtor
}

void Grid::draw(sf::RenderWindow& window)
{
    for (int r = 0; r < 40; r++)
    {
        for (int c = 0; c < 40; c++)
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
    while (!(x == 39 and y == 39))
    {
        move = rand() % 6;
        switch (move)
        {
        case 0:
            if (x < 39 && last_move != 4)
            {
                x++;
                update_path(x, y);
            }
            else move = last_move;
            break;
        case 1:
            if (x < 38 && last_move != 4)
            {
                x++;
                update_path(x, y);
                x++;
                update_path(x, y);
            }
            else move = last_move;
            break;
        case 2:
            if (y < 39 && last_move != 5)
            {
                y++;
                update_path(x, y);
            }
            else move = last_move;
            break;
        case 3:
            if (y < 38 && last_move != 5)
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
        step[i].setRadius(5.0f);
        step[i].setPosition(sf::Vector2f(100.0f + x * 20.0f, WindowVerticalOffset + y * 20.0f));
        step[i].setFillColor(sf::Color(230, 0, 30));
        //delete cell[y][x];
        //cell[y][x] = nullptr;
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
            //cout << "*** Deleting cell (" << x << ',' << y << ')' << endl;
            delete cell[x][y];
            cell[x][y] = nullptr;
        }
        path.push_back(newLoc);
    }
}
