#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Grid.h"
#include "Player.h"
#include "Sounds.h"
#include "Constants.h"
#include "Types.h"

class GameBoard
{
public:
    //GameBoard(std::string name, int level, sf::Texture& arrowTexture);
    GameBoard(std::string name, int level, Sounds& sounds);
    virtual ~GameBoard();
    void draw_and_display(Player& player, int countdown, GameStatus status);
    sf::RenderWindow& getWindow()
    {
        return window;
    }
    sf::RectangleShape& getBorder()
    {
        return border;
    }
    void toggleDisplayMaze()
    {
        displayMaze = !displayMaze;
    }
    Grid& getGrid()
    {
        return grid;
    }
    void flash(Player& player);

    static sf::Font titleFont;
    static sf::Font statusFont;
    static sf::Font defaultFont;

private:
    std::string name;
    int level;
    Sounds& sounds;
    sf::RenderWindow window;
    Grid grid;
    //Player player(const sf::Texture& playerTexture, sf::Vector2i loc(-1,0));
    sf::RectangleShape border;
    sf::RectangleShape door1;
    sf::RectangleShape door2;
    sf::Texture arrowTexture;
    sf::Sprite arrow1;
    sf::Sprite arrow2;
    sf::Text titleText;
    sf::Text statusText;
    sf::Text defaultText;
    bool displayMaze;
};

#endif // GAMEBOARD_H
