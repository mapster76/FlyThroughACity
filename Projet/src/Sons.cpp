#include "Sons.h"
#include <unistd.h>

Sons::Sons() {
	result = Initialisation();
}


Sons::~Sons() {
	printf("destroy");
	if(ambiance1!=NULL) {
		result = ambiance1->release();
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

    /**
     * Initialisation
     */
    result = system->init(1, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    /**
     * Initialiastion du positionnement 3D
     */
    result = system->set3DSettings(1.0f, 1.0f, 1.0f);
    ERRCHECK(result);

    result = system->createSound("../fmod/Audio/rainandrumble.wav", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &ambiance1);
    ERRCHECK(result);
    result = ambiance1->setMode(FMOD_LOOP_NORMAL);

   result = system->createSound("../fmod/Audio/fx15.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &sound1);
    ERRCHECK(result);
    result = sound1->setMode(FMOD_LOOP_OFF);

   result = system->createSound("../fmod/Audio/fx8.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &sound2);
    ERRCHECK(result);
    result = sound2->setMode(FMOD_LOOP_OFF);

   result = system->createSound("../fmod/Audio/fx11.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &sound3);
    ERRCHECK(result);
    result = sound3->setMode(FMOD_LOOP_OFF);

    return result;

}

void Sons::fxSound(FMOD::Sound *sound)
{

	FMOD_VECTOR position= {0.0f, 0.0f, 0.0f};
	FMOD_VECTOR velocity= {0.0f, 0.0f, 0.0f};
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	ERRCHECK(result);

	result = channel->set3DAttributes(&position, &velocity);
	ERRCHECK(result);
	result = channel->setPaused(false);
	ERRCHECK(result);

}

void Sons::ambiance()
{
	FMOD_VECTOR position= {20.0f, 0.0f, 0.0f};
	FMOD_VECTOR velocity= {0.0f, 0.0f, 0.0f};
	result = system->playSound(FMOD_CHANNEL_FREE, ambiance1, false, &channel);
	ERRCHECK(result);

	result = channel->set3DAttributes(&position, &velocity);
	ERRCHECK(result);
	result = channel->setPaused(false);
	ERRCHECK(result);


}



/*void Sons::updateFmod(float* positionEspace, float* upCamera, float *eye, float *center. float updateTime)
{
    // ==========================================================================================
    // UPDATE THE LISTENER
    // ==========================================================================================


    // ********* NOTE ******* READ NEXT COMMENT!!!!!
    // velocity = how far we moved last FRAME (m/f), then time compensate it to SECONDS (m/s).
    velocity.x( (positionEspace[0]-lastPos.x()) / updateTime);
    velocity.y( (positionEspace[1]-lastPos.y()) / updateTime);
    velocity.z( (positionEspace[2]-lastPos.z()) / updateTime);

    FMOD_VECTOR forward = camera.getForward();
    FMOD_VECTOR up;
    up.x(upCamera[0],upCamera[1],upCamera[2]);

    //Update listener attributes
    result = system.set3DListenerAttributes(0, listenerPos, velocity, forward, up);
    ERRCHECK(result);

    //Update FMOD Ex system
    system->update();

    //Store pos for next time
    lastPos.release();
    lastPos = listenerPos;
}*/
