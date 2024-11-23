#include "Sounds.h"
#include <string>
using namespace std;

Sounds::Sounds()
{
    rubberBuffer.loadFromFile(RubberSoundFile);
    rubberSound.setBuffer(rubberBuffer);
    rubberSound.setVolume(40.0f);

    stepBuffer.loadFromFile(StepSoundFile);
    stepSound.setBuffer(stepBuffer);
    stepSound.setVolume(40.0f);

    hitWallBuffer.loadFromFile(HitWallSoundFile);
    hitWallSound.setBuffer(hitWallBuffer);
    hitWallSound.setVolume(40.0f);

    booBuffer.loadFromFile(BooSoundFile);
    booSound.setBuffer(booBuffer);
    booSound.setVolume(35.0f);

    winBuffer.loadFromFile(WinSoundFile);
    winSound.setBuffer(winBuffer);
    winSound.setVolume(35.0f);

    bellBuffer.loadFromFile(BellSoundFile);
    bellSound.setBuffer(bellBuffer);
    bellSound.setVolume(20.0f);

    explosionBuffer.loadFromFile(ExplosionSoundFile);
    explosionSound.setBuffer(explosionBuffer);
    explosionSound.setVolume(40.0f);

    fartBuffer.loadFromFile(FartSoundFile);
    fartSound.setBuffer(fartBuffer);
    fartSound.setVolume(20.0f);

    lightBuffer.loadFromFile(LightSoundFile);
    lightSound.setBuffer(lightBuffer);
    lightSound.setVolume(20.0f);
}
