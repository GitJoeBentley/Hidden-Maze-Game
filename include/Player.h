#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics.hpp"
#include "Types.h"
#include "Grid.h"
#include <vector>

class Player : public sf::RectangleShape
{
    public:
        Player(Grid& grid);
        void draw(sf::RenderWindow& window);
        Grid::Contents move(Direction);
        unsigned getBruises() const { return bruises; }
        unsigned getScore() const { return score; }
        sf::Vector2i getLocation() { return location; }
        void bounce(const sf::Vector2i& location);
        const std::vector<int>& getPath() const { return path; }
        void print_path() const;
        void draw_path(sf::RenderWindow& window) const;
        bool locationIsInThePath(int x, int y);
        int getCol() const { return location.x; }
        sf::Sprite& getPlayer() { return player; }
        void incrementBruises() { bruises++; }
        void decrementScore() { score--; }
        void explodeBomb();
        void light();

    protected:

    private:
        sf::Vector2i location;
        Grid& grid;
        sf::Texture playerTexture;
        sf::Sprite player;
        int bruises;
        int score;
        int maxRow;
        int maxCol;
        std::vector<int> path;
};

#endif // PLAYER_H
