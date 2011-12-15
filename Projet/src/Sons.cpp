#include "Sons.h"
#include <unistd.h>

using namespace std;

Sons::Sons() {
	result = Initialisation();
}


Sons::~Sons() {
  //printf("destroy");
	if(ambiancePluie!=NULL) {
		result = ambiancePluie->release();
		ERRCHECK(result);
	}

	if(sonDeceleration!=NULL) {
		result = sonDeceleration->release();
		ERRCHECK(result);
	}

	if(sonVaisseau!=NULL) {
		result = sonVaisseau->release();
		ERRCHECK(result);
	}

	if(sonCollision!=NULL) {
		result = sonVaisseau->release();
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
    //channel = 0;

    result = system->setOutput(FMOD_OUTPUTTYPE_ALSA);
    ERRCHECK(result);

    /**
     * Initialisation
     */
    result = system->init(10, FMOD_INIT_NORMAL, 0);
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

    // VAISSEAU
   result = system->createSound("../fmod/Audio/BruitVaisseauAlArret.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &sonVaisseau);
    ERRCHECK(result);
    result = sonVaisseau->setMode(FMOD_LOOP_NORMAL);

    // DECELERATION
   result = system->createSound("../fmod/Audio/BruitArretVaisseau.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &sonDeceleration);
    ERRCHECK(result);
    result = sonDeceleration->setMode(FMOD_LOOP_OFF);

    // COLLISION
   result = system->createSound("../fmod/Audio/Collision3.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &sonCollision);
    ERRCHECK(result);
    result = sonCollision->setMode(FMOD_LOOP_OFF);

    return result;

}


void Sons::jouerSonVaisseau()
{
	bool currentlyPlaying=false,paused=false;
	channelVaisseau->isPlaying(&currentlyPlaying);
	if(!currentlyPlaying) {
		result = system->playSound(FMOD_CHANNEL_FREE, sonVaisseau, false, &channelVaisseau);
		ERRCHECK(result);
		result = channelVaisseau->setPaused(false);
		ERRCHECK(result);
	}
	channelVaisseau->getPaused(&paused);
	if(paused) {
		result = channelVaisseau->setPaused(false);
	}
}

void Sons::pauseSonVaisseau()
{
	bool playing,pause;
	channelVaisseau->getPaused(&pause);
	channelVaisseau->isPlaying(&playing);
	if(playing && !pause) {
		channelVaisseau->setPaused(true);
	}
}

void Sons::jouerSonDeceleration()
{
	bool currentlyPlaying=false,paused=false;
	channelDeceleration->isPlaying(&currentlyPlaying);
	if(!currentlyPlaying) {
		result = system->playSound(FMOD_CHANNEL_FREE, sonDeceleration, false, &channelDeceleration);
		ERRCHECK(result);
		result = channelDeceleration->setPaused(false);
		ERRCHECK(result);
	}
	channelDeceleration->getPaused(&paused);
	if(paused) {
		result = channelDeceleration->setPaused(false);
	}
}

void Sons::pauseSonDeceleration()
{
	bool playing,pause;
	channelDeceleration->getPaused(&pause);
	channelDeceleration->isPlaying(&playing);
	if(playing && !pause) {
		channelDeceleration->setPaused(true);
	}
}

void Sons::jouerSonCollision()
{
	bool currentlyPlaying=false,paused=false;
	channelVaisseau->isPlaying(&currentlyPlaying);
	if(!currentlyPlaying) {
		result = system->playSound(FMOD_CHANNEL_FREE, sonVaisseau, false, &channelVaisseau);
		ERRCHECK(result);
		result = channelVaisseau->setPaused(false);
		ERRCHECK(result);
	}
	channelVaisseau->getPaused(&paused);
	if(paused) {
		result = channelVaisseau->setPaused(false);
	}
}

void Sons::jouerAmbiancePluie()
{
	cout << "son ambiance Pluie" << endl;
	FMOD_VECTOR position= {20.0f, 0.0f, 0.0f};
	FMOD_VECTOR velocity= {0.0f, 0.0f, 0.0f};
	result = system->playSound(FMOD_CHANNEL_FREE, ambiancePluie, false, &channelAmbiance);
	ERRCHECK(result);

	result = channelAmbiance->set3DAttributes(&position, &velocity);
	ERRCHECK(result);
	result = channelAmbiance->setPaused(false);
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
