#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics.hpp"
#include "Types.h"
#include "Grid.h"
#include <vector>

class Player : public sf::RectangleShape

{
    public:
        Player(sf::Texture& texture, sf::Vector2i loc, Grid& grid);
        virtual ~Player();
        void draw(sf::RenderWindow& window);
        Grid::Contents move(Direction);
        unsigned getBruises() const { return bruises; }
        unsigned getScore() const { return score; }
        void bounce(const sf::Vector2i& location);
        const std::vector<int>& getPath() const { return path; }
        void print_path() const;
        void draw_path(sf::RenderWindow& window) const;
        int getCol() const { return location.x; }

    protected:

    private:
        sf::Sprite player;
        sf::Vector2i location;
        Grid& grid;
        unsigned bruises;
        unsigned score;
        int maxRow;
        int maxCol;
        std::vector<int> path;
};

#endif // PLAYER_H
