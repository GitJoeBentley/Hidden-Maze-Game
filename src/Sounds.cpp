#include "Sounds.h"
#include <string>
using namespace std;

Sounds::Sounds() : buffer(new sf::SoundBuffer[NumberOfSounds]), sound(new sf::Sound[NumberOfSounds])
{
    string soundfile[NumberOfSounds] = {StepSoundFile, RubberSoundFile, HitWallSoundFile, BellSoundFile, LightSoundFile,
                                        BombSoundFile, FartSoundFile, WinSoundFile, LoseSoundFile
                                       };
    for (int i = 0; i < NumberOfSounds; i++)
    {
        buffer[i].loadFromFile(soundfile[i]);
        sound[i].setBuffer(buffer[i]);
        sound[i].setVolume(40);
    }
    // Music

    music.openFromFile(MusicStartFile);
    music.setVolume(20);
}

Sounds::~Sounds()
{
    delete [] sound;
    delete [] buffer;
    sound = nullptr;
    buffer = nullptr;
}

void Sounds::play(SoundName name)
{
    sound[name].play();
}

void Sounds::playmusic()
{
    music.play();
}

void Sounds::stopmusic()
{
    if (music.getStatus() == sf::SoundSource::Playing) music.stop();
}
