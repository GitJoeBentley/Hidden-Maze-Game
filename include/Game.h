#ifndef GAME_H
#define GAME_H

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

class Game
{
public:
    static sf::Font titleFont;
    static sf::Font statusFont;
    static sf::Font defaultFont;
    static sf::Font winFont;
    enum GameStatus {NotStarted, Active, Paused, Win, Loss, GameOver};

    Game(sf::RenderWindow& wind, const std::string& name);
    ~Game()
    {
        delete grid;
        grid = nullptr;
        delete player;
        player = nullptr;
        delete message;
        message = nullptr;
    }
    void draw_and_display();
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

    Grid* getGrid()
    {
        return grid;
    }
    Player* getPlayer()
    {
        return player;
    }
    void incrementBruises()
    {
        player->incrementBruises();
    }
    void decrementScore()
    {
        player->decrementScore();
    }

    bool flash();
    Grid::Contents jump();
    Grid::Contents jump(Direction direction);
    void winlose();
    void start();
    bool playAgain();
    void refresh(const std::string& name_);
    void bounce()
    {
        sounds.play(Sounds::Bounce);
        player->bounce();
    }
    int getScore() const
    {
        return player->getScore();
    }
    int getBruises() const
    {
        return player->getBruises();
    }
    void move(Direction direction)
    {
        if (status == Game::NotStarted) status = Game::Active;
        Grid::Contents contents = player-> move(direction);

        if (contents == Grid::Win)
        {
            status = Game::Win;
            winlose();
        }
        if (contents == Grid::Loss)
        {
            status = Game::Loss;
            winlose();
        }

        return;
    }
    bool bomb()
    {
        return player -> bomb();
    }
    bool light()
    {
        return player -> light();
    }
    int countdown() const
    {
        return player -> getCountdown();
    }
    Game::GameStatus getStatus() const
    {
        return status;
    }
    void setStatus(Game::GameStatus status_)
    {
        status = status_;
    }
    Sounds& getSounds()
    {
        return sounds;
    }

private:
    sf::RenderWindow& window;
    GameStatus status = NotStarted;
    Sounds sounds;
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
    Grid* grid = nullptr;
    Message* message = nullptr;
    Player* player = nullptr;
};

#endif // Game_H
