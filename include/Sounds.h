#ifndef SOUNDS_H
#define SOUNDS_H
#include <SFML/Audio.hpp>
#include "Constants.h"


class Sounds
{
public:
    enum SoundName{Empty, Bounce, Wall, Bell, Light, Bomb, Fart, Win, Loss, NumberOfSounds};
    Sounds();
    ~Sounds();
    void play(SoundName);
    void playmusic();
    void stopmusic();
private:
    sf::SoundBuffer* buffer;
    sf::Sound* sound;
    sf::Music music;
};

#endif // SOUNDS_H
