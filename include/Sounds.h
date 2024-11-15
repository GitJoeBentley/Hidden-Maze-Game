#ifndef SOUNDS_H
#define SOUNDS_H
#include <SFML/Audio.hpp>
#include "Constants.h"


class Sounds
{
public:
    Sounds();
    sf::Sound& getRubberSound()  { return rubberSound; }
    sf::Sound& getStepSound()    { return stepSound; }
    sf::Sound& getHitWallSound() { return hitWallSound; }
    sf::Sound& getBooSound() { return booSound; }
    sf::Sound& getWinSound() { return winSound; }

protected:

private:
    sf::SoundBuffer rubberBuffer;
    sf::Sound rubberSound;

    sf::SoundBuffer stepBuffer;
    sf::Sound stepSound;

    sf::SoundBuffer hitWallBuffer;
    sf::Sound hitWallSound;

    sf::SoundBuffer booBuffer;
    sf::Sound booSound;

    sf::SoundBuffer winBuffer;
    sf::Sound winSound;
};

#endif // SOUNDS_H
