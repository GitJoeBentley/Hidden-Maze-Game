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
    for (int i=0;i< 40;i++)
    {
        getline(fin, line);
        line.resize(40, ' ');
        for (int j = 0; j < 40; j++)
        {
            if (line[j] == '1') {
                cell[i][j] = new sf::RectangleShape(sf::Vector2f(20.0f, 20.0f));
                cell[i][j]->setPosition(sf::Vector2f(100.0f + j * 20.0f, 100.0f + i * 20.0f));
                cell[i][j]->setFillColor(sf::Color(20,0,20));
                numWalls++;
            }
        }
    }
    fin.close();
    // Add random walls
    int counter = 0;
    do {
        int x = rand() % 40;
        int y = rand() % 40;
        if (!(cell[x][y])) {
            cell[x][y] = new sf::RectangleShape(sf::Vector2f(20.0f, 20.0f));
            cell[x][y]->setPosition(sf::Vector2f(100.0f + x * 20.0f, 100.0f + y * 20.0f));
            cell[x][y]->setFillColor(sf::Color(30, 0, 30));
            numWalls++;
            counter++;
        }
    } while (counter < 100 * level);
    // Add rubber walls
    counter = 0;
    do {
        int x = rand() % 40;
        int y = rand() % 40;
        if (!(cell[x][y])) {
            cell[x][y] = new sf::RectangleShape(sf::Vector2f(20.0f, 20.0f));
            cell[x][y]->setPosition(sf::Vector2f(100.0f + x * 20.0f, 100.0f + y * 20.0f));
            cell[x][y]->setFillColor(sf::Color(240, 140,190));
            numWalls++;
            counter++;
        }
    } while (counter < 10 * level);
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
    path.push_back(0);
    int loc = 0;
    int move, last_move = -1;
    int x = 0, y = 0;
    while (!(x == 39 and y == 39))
    {
        move = rand() % 6;
        switch (move)
        {
        case 0:
            if (x < 39 && last_move != 4) {
                x++;
                update_path(x, y);
                //path.push_back(100 * x + y);
            }
            break;
        case 1:
            if (x < 38 && last_move != 4) {
                x++;
                update_path(x, y);
                //path.push_back(100 * x + y);
                x++;
                update_path(x, y);
                //path.push_back(100 * x + y);
            }
            break;
        case 2:
            if (y < 39 && last_move != 5) {
                y++;
                update_path(x, y);
                //path.push_back(100* x + y);
            }
            break;
        case 3:
            if (y < 38 && last_move != 5) {
                y++;
                update_path(x, y);
                //path.push_back(100 * x + y);
                y++;
                update_path(x, y);
                //path.push_back(100 * x + y);
            }
            break;
        case 4:
            if (x > 0 && last_move != 0 && last_move != 1) {
                x--;
                update_path(x, y);
                //path.push_back(100 * x + y);
            }
            break;
        case 5:
            if (y > 0 && last_move != 2 && last_move != 3) {
                y--;
                update_path(x, y);
                //path.push_back(100 * x + y);
            }
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
        step[i].setPosition(sf::Vector2f(100.0f + x * 20.0f, 100.0f + y * 20.0f));
        step[i].setFillColor(sf::Color(230, 0, 30));
        delete cell[y][x];
        cell[y][x] = nullptr;
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
    if (find(path.begin(), path.end(), newLoc) == path.end()) {
        path.push_back(newLoc);
        if (cell[y][x]) {
            delete cell[y][x];
            cell[y][x] = nullptr;
        }
    }
}