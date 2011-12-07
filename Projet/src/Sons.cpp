#include "Sons.h"
#include <unistd.h>

Sons::Sons() {
	result = Initialisation();
}


Sons::~Sons() {
	printf("destroy");
	if(ambiancePluie!=NULL) {
		result = ambiancePluie->release();
		ERRCHECK(result);
	}

	if(sonDeceleration!=NULL) {
		result = sonDeceleration->release();
		ERRCHECK(result);
	}

	if(sonDemarrage!=NULL) {
		result = sonDemarrage->release();
		ERRCHECK(result);
	}

	if(effetDoppler!=NULL) {
		result = effetDoppler->release();
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

    //  AMBIANCE PLUIE
    result = system->createSound("../fmod/Audio/rainandrumble.wav", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &ambiancePluie);
    ERRCHECK(result);
    result = ambiancePluie->setMode(FMOD_LOOP_NORMAL);

    // DEMARRAGE
   result = system->createSound("../fmod/Audio/fx2.MP3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &sonDemarrage);
    ERRCHECK(result);
    result = sonDemarrage->setMode(FMOD_LOOP_OFF);

    // DECELERATION
   result = system->createSound("../fmod/Audio/fx12.MP3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &sonDeceleration);
    ERRCHECK(result);
    result = sonDeceleration->setMode(FMOD_LOOP_OFF);

   // EFFET DOPPLER
   result = system->createSound("../fmod/Audio/fx18.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &effetDoppler);
    ERRCHECK(result);
    result = effetDoppler->setMode(FMOD_LOOP_OFF);


    return result;

}

void Sons::jouerSonDeceleration()
{

  	FMOD_VECTOR position= {0.0f, 0.0f, 0.0f};
	FMOD_VECTOR velocity= {0.0f, 0.0f, 0.0f};
	result = system->playSound(FMOD_CHANNEL_FREE, sonDeceleration, false, &channel);
	ERRCHECK(result);

	result = channel->set3DAttributes(&position, &velocity);
	ERRCHECK(result);
	result = channel->setPaused(false);
	ERRCHECK(result);
}

void Sons::jouerEffetDoppler()
{

  	FMOD_VECTOR position= {0.0f, 0.0f, 0.0f};
	FMOD_VECTOR velocity= {0.0f, 0.0f, 0.0f};
	result = system->playSound(FMOD_CHANNEL_FREE, effetDoppler, false, &channel);
	ERRCHECK(result);

	result = channel->set3DAttributes(&position, &velocity);
	ERRCHECK(result);
	result = channel->setPaused(false);
	ERRCHECK(result);
}


void Sons::jouerSonDemarrage()
{

  	FMOD_VECTOR position= {0.0f, 0.0f, 0.0f};
	FMOD_VECTOR velocity= {0.0f, 0.0f, 0.0f};
	result = system->playSound(FMOD_CHANNEL_FREE, sonDemarrage, false, &channel);
	ERRCHECK(result);

	result = channel->set3DAttributes(&position, &velocity);
	ERRCHECK(result);
	result = channel->setPaused(false);
	ERRCHECK(result);
}
 

void Sons::jouerAmbiancePluie()
{
	FMOD_VECTOR position= {20.0f, 0.0f, 0.0f};
	FMOD_VECTOR velocity= {0.0f, 0.0f, 0.0f};
	result = system->playSound(FMOD_CHANNEL_FREE, ambiancePluie, false, &channel);
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
