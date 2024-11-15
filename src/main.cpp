#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Grid.h"
#include "Player.h"
#include "Player.h"
#include "GameBoard.h"
#include "Sounds.h"
#include "Types.h"
using namespace std;


int main()
{
    srand(static_cast<unsigned>(time(0)));
    int level = 1;
    string name = "Joe";

    //Grid grid(level);
    Sounds sounds;
    GameBoard game(name, level, sounds);
    Player player(game.getGrid());

    Grid::Contents cellContents;
    game.flash(player);

    //GAME CLOCK & TIMER
    sf::Clock clock;
    int countdown = 60;
    int timer;
    GameStatus status = NotStarted;

    // Run the program as long as the window is open
    while (game.getWindow().isOpen())
    {
        // Check all the window's events that were triggered
        // since the last iteration of the main loop.
        sf::Event event;
        while (game.getWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                game.getWindow().close();
            }
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) game.getWindow().close();
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F3)) game.toggleDisplayMaze();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))    {
                game.flash(player);
                player.decrementScore();
                player.incrementBruises();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    cellContents = player.move(Up);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  cellContents = player.move(Down);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  cellContents = player.move(Left);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if (status == NotStarted) status = Active;
                cellContents = player.move(Right);
            }
            else break;

            if (cellContents == Grid::Empty) sounds.getStepSound().play();
            if (cellContents == Grid::Wall) sounds.getHitWallSound().play();
            if (cellContents == Grid::RubberWall) sounds.getRubberSound().play();
            if (cellContents == Grid::Win) sounds.getWinSound().play();
        }
        timer = clock.getElapsedTime().asSeconds();
        if (timer > 0) {
            countdown--;
            clock.restart();
        }

        // loss
        if (countdown <= 0 or player.getBruises() >= 50) {
            status = Loss;
            game.draw_and_display(player, countdown, Loss);
            break;
        }
        // win
        if (cellContents == Grid::Win)
        {
            status = Win;
            game.draw_and_display(player, countdown, Win);
            break;
        }
        game.draw_and_display(player, countdown, Active);
    }

    return 0;
}
