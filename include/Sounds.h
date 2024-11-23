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
    sf::Sound& getBellSound() { return bellSound; }
    sf::Sound& getExplosionSound() { return explosionSound; }
    sf::Sound& getFartSound() { return fartSound; }
    sf::Sound& getLightSound() { return lightSound; }

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

    sf::SoundBuffer bellBuffer;
    sf::Sound bellSound;

    sf::SoundBuffer explosionBuffer;
    sf::Sound explosionSound;

    sf::SoundBuffer fartBuffer;
    sf::Sound fartSound;

    sf::SoundBuffer lightBuffer;
    sf::Sound lightSound;
};

#endif // SOUNDS_H
