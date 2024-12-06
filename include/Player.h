#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics.hpp"
#include "Types.h"
#include "Grid.h"
#include <vector>
#include <string>

class Player : public sf::RectangleShape
{
    public:
        Player(const std::string& name, Grid& grid);
        void draw(sf::RenderWindow& window);
        Grid::Contents move(Direction);
        int getBruises() const { return bruises; }
        int getScore() const { return score; }
        sf::Vector2i getLocation() const { return location; }
        void bounce();
        const std::vector<int>& getPath() const { return path; }
        void print_path() const;
        void draw_path(sf::RenderWindow& window) const;
        bool locationIsInThePath(int x, int y);
        int getCol() const { return location.x; }
        sf::Sprite& getPlayer() { return player; }
        void incrementBruises() { bruises++; }
        void decrementScore() { score--; }
        void bomb();
        void light();
        Grid::Contents processMove(const sf::Vector2i& newLocation);

    protected:

    private:
        std::string name;
        sf::Vector2i location;
        Grid& grid;
        sf::Texture playerTexture;
        sf::Sprite player;
        int bruises;
        int score;
        int maxRow;
        int maxCol;
        std::vector<int> path;

        void updateScore();

};

#endif // PLAYER_H
