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

const std::string ResourcePath = "resources/";
const std::string BorderImageFile = ResourcePath + "bricks.jpg";
const std::string PlayerImageFile = ResourcePath + "player.jpg";
const std::string ArrowImageFile = ResourcePath + "arrow.jpg";
const std::string MusicStartFile = ResourcePath + "BlueSuedeShoes.ogg";
const std::string RubberSoundFile = ResourcePath + "boing.wav";
const std::string StepSoundFile = ResourcePath + "step.wav";
const std::string HitWallSoundFile = ResourcePath + "slam.wav";
const std::string BooSoundFile = ResourcePath + "boo.wav";
const std::string WinSoundFile = ResourcePath + "win.wav";
const std::string BellSoundFile = ResourcePath + "bell.wav";
const std::string ExplosionSoundFile = ResourcePath + "explosion.wav";
const std::string FartSoundFile = ResourcePath + "fart.wav";
const std::string LightSoundFile = ResourcePath + "light.wav";
const std::string TitleFontFile = ResourcePath + "ITCKRIST.TTF";
const std::string StatusFontFile = ResourcePath + "courbd.ttf";
const std::string DefaultFontFile = ResourcePath + "arial.ttf";
const std::string WinFontFile = ResourcePath + "SHOWG.TTF";
const std::string WelcomeFile = ResourcePath + "welcome.txt";

#endif
