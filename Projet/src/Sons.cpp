#include "Sons.h"
#include <unistd.h>

Sons::Sons() {
	result = Initialisation();
}


Sons::~Sons() {
	if(sound!=NULL) {
		result = sound->release();
		ERRCHECK(result);

	}
	if(system!=NULL) {
		result = system->close();
		ERRCHECK(result);
		result = system->release();
		ERRCHECK(result);
	}
}

void Sons::ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
    }
}

FMOD_RESULT Sons::Initialisation()
{
    result = FMOD::System_Create(&system);
    ERRCHECK(result);
    channel=0;

    result = system->setOutput(FMOD_OUTPUTTYPE_ALSA);
    ERRCHECK(result);

    result = system->init(1, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    result = system->createSound("../fmod/Audio/AmbianceVille.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &sound);
    ERRCHECK(result);

    return result;

}

void Sons::ambiance()
{
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	 ERRCHECK(result);
}
