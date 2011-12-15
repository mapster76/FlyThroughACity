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
		delete ambiancePluie;
		delete channelAmbiance;
	}

	if(ambianceNature!=NULL) {
		result = ambianceNature->release();
		ERRCHECK(result);
		delete ambianceNature;
		delete channelAmbiance;
	}

	if(ambianceOrage!=NULL) {
		result = ambianceOrage->release();
		ERRCHECK(result);
		delete ambianceOrage;
		delete channelAmbiance;
	}

	if(ambianceFoule!=NULL) {
		result = ambianceFoule->release();
		ERRCHECK(result);
		delete ambianceFoule;
		delete channelAmbiance;
	}

	if(musique1!=NULL) {
		result = musique1->release();
		ERRCHECK(result);
		delete musique1;
		delete channelAmbiance;
	}

	if(musique2!=NULL) {
		result = musique2->release();
		ERRCHECK(result);
		delete musique2;
		delete channelAmbiance;
	}


	if(sonDeceleration!=NULL) {
		result = sonDeceleration->release();
		ERRCHECK(result);
		delete sonDeceleration;
		delete channelDeceleration;
	}

	if(sonAcceleration!=NULL) {
		result = sonAcceleration->release();
		ERRCHECK(result);
		delete sonAcceleration;
		delete channelAcceleration;
	}

	if(sonVaisseau!=NULL) {
		result = sonVaisseau->release();
		ERRCHECK(result);
		delete sonVaisseau;
		delete channelVaisseau;
	}

	if(sonCollision!=NULL) {
		result = sonCollision->release();
		ERRCHECK(result);
		delete sonCollision;
		delete channelCollision;
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

    //  AMBIANCE ORAGE
    result = system->createSound("../fmod/Audio/Ambiance2.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &ambianceOrage);
    ERRCHECK(result);
    result = ambianceOrage->setMode(FMOD_LOOP_NORMAL);

    //  AMBIANCE FOULE
    result = system->createSound("../fmod/Audio/Ambiance3.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &ambianceFoule);
    ERRCHECK(result);
    result = ambianceFoule->setMode(FMOD_LOOP_NORMAL);


    //  AMBIANCE NATURE
    result = system->createSound("../fmod/Audio/Ambiance1.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &ambianceNature);
    ERRCHECK(result);
    result = ambianceNature->setMode(FMOD_LOOP_NORMAL);


    //  MUSIQUE 1 
    result = system->createSound("../fmod/Audio/Ambiance5.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &musique1);
    ERRCHECK(result);
    result = musique1->setMode(FMOD_LOOP_NORMAL);


    //  MUSIQUE 2
    result = system->createSound("../fmod/Audio/rainandrumble.wav", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &musique2);
    ERRCHECK(result);
    result = musique2->setMode(FMOD_LOOP_NORMAL);


    // VAISSEAU
   result = system->createSound("../fmod/Audio/BruitVaisseauAlArret.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &sonVaisseau);
    ERRCHECK(result);
    result = sonVaisseau->setMode(FMOD_LOOP_NORMAL);

    // DECELERATION
   result = system->createSound("../fmod/Audio/BruitArretVaisseau.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &sonDeceleration);
    ERRCHECK(result);
    result = sonDeceleration->setMode(FMOD_LOOP_OFF);

    // ACCELERATION
   result = system->createSound("../fmod/Audio/Acceleration.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &sonAcceleration);
	ERRCHECK(result);
	result = sonAcceleration->setMode(FMOD_LOOP_OFF);

    // COLLISION
   result = system->createSound("../fmod/Audio/Collision3.mp3", FMOD_SOFTWARE | FMOD_3D | FMOD_CREATESTREAM , 0, &sonCollision);
    ERRCHECK(result);
    result = sonCollision->setMode(FMOD_LOOP_OFF);

    //Initialisation de l'iterateur
    vAmbianceSonore.push_back("20");
    vAmbianceSonore.push_back("21");
    itAmbianceSonore = vAmbianceSonore.begin();

    return result;


}


void Sons::jouerSonVaisseau()
{
	bool currentlyPlaying=false,paused=false;
	bool decellerationPlaying=false;
	channelVaisseau->isPlaying(&currentlyPlaying);
	channelDeceleration->isPlaying(&decellerationPlaying);
	if(!currentlyPlaying && !decellerationPlaying) {
		result = system->playSound(FMOD_CHANNEL_FREE, sonVaisseau, false, &channelVaisseau);
		ERRCHECK(result);
		result = channelVaisseau->setPaused(false);
		ERRCHECK(result);
	}
	channelVaisseau->getPaused(&paused);
	if(paused && !decellerationPlaying) {
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
	if(!currentlyPlaying && !decelerationAlreadyPlayed) {

		decelerationAlreadyPlayed=true;
		result = system->playSound(FMOD_CHANNEL_FREE, sonDeceleration, false, &channelDeceleration);
		ERRCHECK(result);
		result = channelDeceleration->setPaused(false);
		ERRCHECK(result);
	}
	channelDeceleration->getPaused(&paused);
	if(paused  && !decelerationAlreadyPlayed) {
		decelerationAlreadyPlayed=true;
		result = channelDeceleration->setPaused(false);
	}
}

void Sons::pauseSonDeceleration()
{
	bool playing,pause;
	decelerationAlreadyPlayed=false;
	channelDeceleration->getPaused(&pause);
	channelDeceleration->isPlaying(&playing);
	if(playing && !pause) {
		channelDeceleration->setPosition(0,FMOD_TIMEUNIT_MS);
		channelDeceleration->setPaused(true);
	}
}

void Sons::jouerSonAcceleration()
{
	bool currentlyPlaying=false,paused=false;
	channelAcceleration->isPlaying(&currentlyPlaying);
	if(!currentlyPlaying && !accelerationAlreadyPlayed) {
		accelerationAlreadyPlayed=true;
		result = system->playSound(FMOD_CHANNEL_FREE, sonAcceleration, false, &channelAcceleration);
		ERRCHECK(result);
		result = channelAcceleration->setPaused(false);
		ERRCHECK(result);
	}
	channelAcceleration->getPaused(&paused);
	if(paused && !accelerationAlreadyPlayed) {
		accelerationAlreadyPlayed=true;
		result = channelAcceleration->setPaused(false);
	}
}

void Sons::pauseSonAcceleration()
{
	bool playing,pause;
	channelAcceleration->getPaused(&pause);
	accelerationAlreadyPlayed=false;
	channelAcceleration->isPlaying(&playing);
	if(playing && !pause) {
		channelAcceleration->setPosition(0,FMOD_TIMEUNIT_MS);
		channelAcceleration->setPaused(true);
	}
}

void Sons::jouerSonCollision()
{
	bool currentlyPlaying=false,paused=false;
	channelCollision->isPlaying(&currentlyPlaying);
	if(!currentlyPlaying && !collisionAlreadyPlayed) {
		cout << "collision " <<endl;
		collisionAlreadyPlayed=true;
		result = system->playSound(FMOD_CHANNEL_FREE, sonCollision, false, &channelCollision);
		ERRCHECK(result);
		channelCollision->setLoopCount(0);
		result = channelCollision->setPaused(false);
		ERRCHECK(result);
	}
	channelCollision->getPaused(&paused);
	if(paused) {
		result = channelCollision->setPaused(false);
	}
}

void Sons::pauseSonCollision()
{
	bool playing,pause;
	collisionAlreadyPlayed=false;
	channelCollision->getPaused(&pause);
	channelCollision->isPlaying(&playing);
	if(playing && !pause) {
		channelCollision->setPaused(true);
	}
}

void Sons::jouerAmbiancePluie()
{
	FMOD_VECTOR position= {20.0f, 0.0f, 0.0f};
	FMOD_VECTOR velocity= {0.0f, 0.0f, 0.0f};
	result = system->playSound(FMOD_CHANNEL_FREE, ambiancePluie, false, &channelAmbiance);
	ERRCHECK(result);

	result = channelAmbiance->set3DAttributes(&position, &velocity);
	ERRCHECK(result);
	result = channelAmbiance->setPaused(false);
	ERRCHECK(result);
}


void Sons::jouerAmbianceOrage()
{
	FMOD_VECTOR position= {20.0f, 0.0f, 0.0f};
	FMOD_VECTOR velocity= {0.0f, 0.0f, 0.0f};
	result = system->playSound(FMOD_CHANNEL_FREE, ambianceOrage, false, &channelAmbiance);
	ERRCHECK(result);

	result = channelAmbiance->set3DAttributes(&position, &velocity);
	ERRCHECK(result);
	result = channelAmbiance->setPaused(false);
	ERRCHECK(result);
}

void Sons::jouerAmbianceFoule()
{
	FMOD_VECTOR position= {20.0f, 0.0f, 0.0f};
	FMOD_VECTOR velocity= {0.0f, 0.0f, 0.0f};
	result = system->playSound(FMOD_CHANNEL_FREE, ambianceFoule, false, &channelAmbiance);
	ERRCHECK(result);

	result = channelAmbiance->set3DAttributes(&position, &velocity);
	ERRCHECK(result);
	result = channelAmbiance->setPaused(false);
	ERRCHECK(result);
}


void Sons::jouerAmbianceNature()
{
	FMOD_VECTOR position= {20.0f, 0.0f, 0.0f};
	FMOD_VECTOR velocity= {0.0f, 0.0f, 0.0f};
	result = system->playSound(FMOD_CHANNEL_FREE, ambianceNature, false, &channelAmbiance);
	ERRCHECK(result);

	result = channelAmbiance->set3DAttributes(&position, &velocity);
	ERRCHECK(result);
	result = channelAmbiance->setPaused(false);
	ERRCHECK(result);
}

void Sons::jouerMusique1()
{
	FMOD_VECTOR position= {20.0f, 0.0f, 0.0f};
	FMOD_VECTOR velocity= {0.0f, 0.0f, 0.0f};
	result = system->playSound(FMOD_CHANNEL_FREE, musique1, false, &channelAmbiance);
	ERRCHECK(result);

	result = channelAmbiance->set3DAttributes(&position, &velocity);
	ERRCHECK(result);
	result = channelAmbiance->setPaused(false);
	ERRCHECK(result);
}

void Sons::jouerMusique2()
{
	FMOD_VECTOR position= {20.0f, 0.0f, 0.0f};
	FMOD_VECTOR velocity= {0.0f, 0.0f, 0.0f};
	result = system->playSound(FMOD_CHANNEL_FREE, musique2, false, &channelAmbiance);
	ERRCHECK(result);

	result = channelAmbiance->set3DAttributes(&position, &velocity);
	ERRCHECK(result);
	result = channelAmbiance->setPaused(false);
	ERRCHECK(result);
}

void Sons::changerAmbianceSonore(string itAmbianceSonore)
{
  std::cout << "itAmbianceSonore   " << itAmbianceSonore << std::endl;
  if(itAmbianceSonore == "20")
    jouerAmbianceNature();
  else
    jouerMusique2();

}



void Sons::gestionBouton1(gadget::DigitalInterface mButton) {

	if(mButton->getData() == gadget::Digital::TOGGLE_ON) {
		itAmbianceSonore++;
		if(itAmbianceSonore == vAmbianceSonore.end()) {
			itAmbianceSonore=vAmbianceSonore.begin();
		}
		changerAmbianceSonore(*itAmbianceSonore);


		/*
		pNavTrans->removeChild(noeudSkybox);
		noeudSkybox->removeDrawable(skybox);
		cout << *itEmplacementImage << endl;
		skybox=new Skybox(RAYON_MAX_VILLE*5,*itEmplacementImage);
		noeudSkybox->addDrawable(skybox);
		pNavTrans->addChild(noeudSkybox);
		*/

	 }
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
