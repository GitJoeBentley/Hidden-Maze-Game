#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Grid.h"
#include "Player.h"
#include "Sounds.h"
#include "HighScores.h"
#include "Constants.h"
#include "Message.h"
#include "Types.h"

class GameBoard
{
public:
    static sf::Font titleFont;
    static sf::Font statusFont;
    static sf::Font defaultFont;
    static sf::Font winFont;

    GameBoard(sf::RenderWindow& wind, Sounds& sounds, std::string& name);
    void draw_and_display(Player& player, int countdown, GameStatus& status);
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

    void flash(Player& player, GameStatus& status);
    Grid::Contents jump(Player& player);
    Grid::Contents jump(Player& player, Direction direction);
    void winlose(GameStatus& status);
    void start();
    bool playAgain(Player& player, int countdown);

private:
    sf::RenderWindow& window;
    Sounds& sounds;
    std::string& name;
    Grid grid;
    //Player player(const sf::Texture& playerTexture, sf::Vector2i loc(-1,0));
    sf::RectangleShape border;
    sf::RectangleShape door1;
    sf::RectangleShape door2;
    sf::Texture arrowTexture;
    sf::Texture borderTexture;
    sf::Sprite arrow1;
    sf::Sprite arrow2;
    sf::Text titleText;
    sf::Text statusText;
    sf::Text defaultText;
    sf::Text winText;
    bool displayMaze;
    //sf::RectangleShape popUp;
    Message* message = nullptr;
};

#endif // GAMEBOARD_H
