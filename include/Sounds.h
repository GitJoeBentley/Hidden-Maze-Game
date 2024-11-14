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

protected:

private:
    sf::SoundBuffer rubberBuffer;
    sf::Sound rubberSound;

    sf::SoundBuffer stepBuffer;
    sf::Sound stepSound;

    sf::SoundBuffer hitWallBuffer;
    sf::Sound hitWallSound;
};

#endif // SOUNDS_H
