#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <string>

const float CellWidth = 20.0f;

const sf::Vector2u GameSize(1000, 1024);
const sf::Vector2f MidWindow(GameSize.x / 2.0f, GameSize.y / 2.0f);
const sf::Vector2f CellSize(CellWidth, CellWidth);

const int NumRows = 40;
const int NumCols = NumRows;
const float GameWindowSize = NumRows * CellWidth;
const float WindowHorizontalOffset = 100.0f;
const float WindowVerticalOffset = 150.0f;

const std::vector<std::string> FontNames = {"arial","courier","komikap","kristan","showcard"};

const std::string ResourcePath = "resources/";
const std::string BorderImageFile = ResourcePath + "bricks.jpg";
const std::string PlayerImageFile = ResourcePath + "player.jpg";
const std::string ArrowImageFile = ResourcePath + "arrow.jpg";

const std::string MusicStartFile = ResourcePath + "BlueSuedeShoes.ogg";

const std::string RubberSoundFile = ResourcePath + "bounce.wav";
const std::string StepSoundFile = ResourcePath + "step.wav";
const std::string HitWallSoundFile = ResourcePath + "slam.wav";
const std::string LossSoundFile = ResourcePath + "loss.wav";
const std::string WinSoundFile = ResourcePath + "win.wav";
//const std::string BellSoundFile = ResourcePath + "bell.wav";
const std::string BombSoundFile = ResourcePath + "explosion.wav";
const std::string FartSoundFile = ResourcePath + "fart.wav";
const std::string LightSoundFile = ResourcePath + "light.wav";

const std::string WelcomeFile = ResourcePath + "welcome.txt";

#endif
