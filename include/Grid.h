#ifndef GRID_H
#define GRID_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "Constants.h"


class Grid
{
    public:
        Grid(int level);
        virtual ~Grid();
        void draw(sf::RenderWindow&);
        void generate_path();
        void print_path() const;
        void draw_path(sf::RenderWindow&);

    protected:

    private:
        int numWalls;
        sf::CircleShape* step;
        std::vector<int> path;
        sf::RectangleShape* cell[40][40];

        void update_path(int x, int y);
};

#endif // GRID_H
