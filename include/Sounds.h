#ifndef SOUNDS_H
#define SOUNDS_H
#include <SFML/Audio.hpp>
#include "Constants.h"


class Sounds
{
public:
    enum SoundName{Step, Rubber, Wall, Bell, Light, Bomb, Fart, Win, Lose, NumberOfSounds};
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
