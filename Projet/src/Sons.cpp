#include "Sons.h"
#include <unistd.h>

Sons::Sons() {
	result = Initialisation();
}


Sons::~Sons() {
	printf("destroy");
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

    result = system->createSound("../fmod/Audio/rainandrumble.wav", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &sound);
    ERRCHECK(result);

    result = sound->setMode(FMOD_LOOP_NORMAL);

    return result;

}

void Sons::ambiance()
{
	//FMOD_VECTOR position(20.0f, 0.0f, 0.0f);
	//FMOD_VECTOR velocity(0.0f, 0.0f, 0.0f);
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	ERRCHECK(result);


}



void Sons::updateFmod()
{
    // ==========================================================================================
    // UPDATE THE LISTENER
    // ==========================================================================================

   /* listenerpos = camera.getPosition();

    // ********* NOTE ******* READ NEXT COMMENT!!!!!
    // velocity = how far we moved last FRAME (m/f), then time compensate it to SECONDS (m/s).
    velocity.setX( (listenerPos.getX()-lastPos.getX()) / INTERFACE_UPDATETIME );
    velocity.setY( (listenerPos.getY()-lastPos.getY()) / INTERFACE_UPDATETIME );
    velocity.setZ( (listenerPos.getZ()-lastPos.getZ()) / INTERFACE_UPDATETIME );

    FMOD_VECTOR forward = camera.getForward();
    FMOD_VECTOR up      = camera.getUp();

    //Update listener attributes
    result = system.set3DListenerAttributes(0, listenerPos, velocity, forward, up);
    ERRCHECK(result);

    //Update FMOD Ex system
    system.update();

    //Store pos for next time
    lastPos.release();
    lastPos = listenerPos;*/
}
