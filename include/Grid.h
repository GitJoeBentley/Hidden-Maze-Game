#ifndef GRID_H
#define GRID_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "Constants.h"


class Grid
{
    public:
        enum Contents { Empty, Wall, RubberWall, Win, Loss, OutOfBounds};
        Grid();
        ~Grid();
        void draw(sf::RenderWindow&);
        void generate_path();
        void print_path() const;
        void draw_path(sf::RenderWindow& window);
        sf::RectangleShape* getCell(int row, int col) const { return cell[row][col]; }
        Grid::Contents getCellContents(int row, int col) const;
        std::vector<int>& getPath() { return path; }
        bool locationIsInThePath(int x, int y) const;
        void AddARandomWall(const std::string& = "solid");
        void clearCell(int x, int y);

    private:
        int numWalls;
        sf::CircleShape* step;
        std::vector<int> path;
        sf::RectangleShape* cell[NumRows][NumCols];

        void update_path(int x, int y);
};

#endif // GRID_H
