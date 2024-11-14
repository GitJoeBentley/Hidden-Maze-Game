#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <string>

const sf::Vector2u GameSize(1000, 1024);
const float CellWidth = 20.0f;
const int NumRows = 40;
const int NumCols = 40;
const  sf::Vector2f CellSize(CellWidth, CellWidth);
const float GameWindowSize = 40 * CellWidth;
const float WindowHorizontalOffset = 100.0f;
const float WindowVerticalOffset = 150.0f;
const std::string PlayerImageFile = "c:/temp/player.jpg";
const std::string ArrowImageFile = "c:/temp/arrow.jpg";
const std::string rubberSoundFile = "c:/temp/boing.wav";
const std::string stepSoundFile = "c:/temp/step.wav";
const std::string hitWallSoundFile = "c:/temp/slam.wav";
const std::string titleFontFile = "c:/temp/ITCKRIST.TTF";
const std::string statusFontFile = "c:/temp/courbd.ttf";

#endif
