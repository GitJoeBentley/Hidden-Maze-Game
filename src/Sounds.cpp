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

    booBuffer.loadFromFile(booSoundFile);
    booSound.setBuffer(booBuffer);
    booSound.setVolume(35.0f);

    winBuffer.loadFromFile(winSoundFile);
    winSound.setBuffer(winBuffer);
    winSound.setVolume(35.0f);
}
