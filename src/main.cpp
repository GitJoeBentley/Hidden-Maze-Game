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
#include "Game.h"
#include "HighScores.h"
#include "Sounds.h"
#include "Types.h"
#include "Message.h"
using namespace std;

std::string welcome(sf::RenderWindow& window, const HighScores& highScores);
std::string getWelcomeText();
char getKey();


int main()
{
    srand(static_cast<unsigned>(time(0)));
    sf::RenderWindow window(sf::VideoMode(GameSize.x, GameSize.y),"Hidden Maze Game",sf::Style::Close);
    window.setFramerateLimit(60);

    Sounds sounds;
    HighScores highScores;
    Grid::Contents cellContents;
    std::string name = welcome(window, highScores);

    Game* game;

    // Music
    sf::Music music;
    music.openFromFile(MusicStartFile);
    music.setVolume(20);

    //GAME CLOCK & TIMER
    sf::Clock clock;
    int timer;
    sf::Event event;
    bool playAgain = true;

    // Game Loop starts here ///////////////////////////
    while (playAgain)
    {
        //status = NotStarted;
        game = new Game(window, sounds, name);
        game -> flash();
        music.play();

        while (game->getWindow().isOpen())
        {
            // Check all the window's events that were triggered
            // since the last iteration of the main loop.
            while (game->getWindow().pollEvent(event))
            {
                if (event.type == sf::Event::Closed) game->getWindow().close();
                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) game->getWindow().close();
                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F3)) game->toggleDisplayMaze();
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                {
                    if (game->flash()) sounds.getBellSound().play();
                    else sounds.getFartSound().play();
                    break;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) game->getWindow().close();
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))   // bomb
                {
                    if (game->bomb()) sounds.getExplosionSound().play();
                    else sounds.getFartSound().play();
                    break;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))   // light
                {
                    if (game->light()) sounds.getLightSound().play();
                    else sounds.getFartSound().play();
                    break;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))   // jump
                {
                    if (game->getPlayer()->jumped()) sounds.getFartSound().play();
                    else cellContents = game->jump();
                    break;
                }

                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    cellContents = game->move(Up);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  cellContents = game->move(Down);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  cellContents = game->move(Left);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    if (game->getStatus() == Game::NotStarted) game->setStatus(Game::Active);
                    cellContents = game->move(Right);
                }
                else break;


                if (cellContents == Grid::Empty)       sounds.getStepSound().play();
                if (cellContents == Grid::Wall)        sounds.getHitWallSound().play();
                if (cellContents == Grid::RubberWall)  sounds.getRubberSound().play();
                if (cellContents == Grid::OutOfBounds) sounds.getFartSound().play();
                if (cellContents == Grid::Win)
                {
                    sounds.getWinSound().play();
                    game->setStatus(Game::Win);
                    game->winlose();
                    break;
                }
                if (cellContents == Grid::Loss)
                {
                    sounds.getBooSound().play();
                    game->setStatus(Game::Loss);
                    game->winlose();
                    break;
                }
            }

            // Increment time clock
            if (game->getStatus() == Game::Active)
            {
                timer = clock.getElapsedTime().asSeconds();
                if (timer > 0)
                {
                    game->getPlayer()->decrementCountdown();
                    clock.restart();
                    if (music.getStatus() == sf::SoundSource::Playing) music.stop();
                }
            }

            game->draw_and_display();
            if (game->getStatus() == Game::Loss || game->getStatus() == Game::Win) break;
        }
        highScores.updateHighScores(Score(name.c_str(),game->getScore(), game->getBruises(), 60 - game->countdown(), time(0)));
        highScores.WriteHighScoresFile();
        playAgain = game->playAgain();
        delete game;
    }
    return 0;
}

std::string welcome(sf::RenderWindow& window, const HighScores& highScores)
{
    std::string text, buffer, name;

    // Text
    text = getWelcomeText();

    sf::Font font;
    sf::Font instructionsFont;
    if (!font.loadFromFile(DefaultFontFile))
    {
        std::cout << "Can't find font " << DefaultFontFile << std::endl;
    }
    if (!instructionsFont.loadFromFile(StatusFontFile))
    {
        std::cout << "Can't find font " << StatusFontFile << std::endl;
    }

    sf::Text instructions;
    instructions.setString(text.c_str());
    instructions.setFont(font);
    instructions.setCharacterSize(18); // in pixels, not points!
    instructions.setFillColor(sf::Color::Cyan);
    instructions.setPosition(90.0f,20.0f);

    // Create High Scores text
    sf::Text highScoresText;
    highScoresText.setFont(instructionsFont);
    highScoresText.setCharacterSize(16); // in pixels, not points!
    highScoresText.setFillColor(sf::Color::Green);
    highScoresText.setPosition(150.0f,600.0f);

    // Write High Scores
    std::ostringstream sout;
    sout << highScores << std::endl;
    highScoresText.setString(sout.str());

    sf::Event evnt;
    char input = ' ';

    while (window.isOpen())
    {
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                input = getKey();
                if ((input >= 'a' && input <= 'z')||(input >= 'A' && input <= 'Z')||input == ' ')
                {
                    name += input;
                }
                if (input == '\b') // backspace
                {
                    name = "";
                    text = getWelcomeText();
                }
                break;
            default:
                ;
            }
        }
        window.clear();
        instructions.setString((text+name+'_').c_str());
        window.draw(instructions);
        window.draw(highScoresText);

        window.display();
        if (isspace(name[0]))
            name = name.substr(1);  // remove leading space from name
        name[0] = toupper(name[0]);

        if (input == '\n')
        {
            window.clear();
            return name;
        }
    }
    return name;
}

std::string getWelcomeText()
{
    std::ifstream fin(WelcomeFile);
    std::string text, buffer;
    if (!fin)
    {
        std::cout << "Cannot open welcome file." << std::endl;
        return "";
    }

    while (getline(fin, buffer))
    {
        text += buffer += '\n';
    }

    text += "\n          Please type your name and press Enter ===> ";

    fin.close();
    return text;
}


// Determine what key is pressed
char getKey()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        return  'a';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        return  'b';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        return  'c';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        return  'd';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        return  'e';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        return  'f';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
        return  'g';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        return  'h';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
        return  'i';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        return  'j';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        return  'k';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        return  'l';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        return  'm';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
        return  'n';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
        return  'o';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        return  'p';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        return  'q';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        return  'r';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        return  's';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
        return  't';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
        return  'u';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
        return  'v';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        return  'w';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        return  'x';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
        return  'y';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        return  'z';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        return  ' ';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        return  '\n';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
        return  '\b';
    return ' ';
}
