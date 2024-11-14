#include "Sounds.h"
#include <string>
using namespace std;

Sounds::Sounds()
{
    rubberBuffer.loadFromFile(rubberSoundFile);
    rubberSound.setBuffer(rubberBuffer);
    rubberSound.setVolume(40.0f);

    stepBuffer.loadFromFile(stepSoundFile);
    stepSound.setBuffer(stepBuffer);
    stepSound.setVolume(40.0f);

    hitWallBuffer.loadFromFile(hitWallSoundFile);
    hitWallSound.setBuffer(hitWallBuffer);
    hitWallSound.setVolume(40.0f);


}
