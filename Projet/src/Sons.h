#ifndef SONS_H_
#define SONS_H_

#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>
//#include <wincompat.h>
#include <stdio.h>
#include <iostream>
#include <gadget/Type/DigitalInterface.h>
#include <vector>
#include <string>

using namespace std;


class Sons
{

public:

  Sons();
  virtual ~Sons();

  //void updateFmod(float*,float*,float*,float*,float);

  void jouerAmbiancePluie();
  void jouerAmbianceNature();
  void jouerAmbianceFoule();
  void jouerAmbianceOrage();
  void jouerMusique1();
  void jouerMusique2();
  void changerAmbianceSonore(string itAmbianceSonore);
  void jouerSonVaisseau();
  void jouerSonDeceleration();
  void jouerSonAcceleration();
  void jouerSonCollision();
  void pauseSonVaisseau();
  void pauseSonDeceleration();
  void pauseSonAcceleration();
  void pauseSonCollision();

  void gestionBouton1(gadget::DigitalInterface mButton);
  vector<string>::iterator itAmbianceSonore;
  vector<string> vAmbianceSonore;

  void ERRCHECK(FMOD_RESULT);

 private:
  	FMOD_RESULT Initialisation();
    FMOD::System     *system;
    FMOD::Sound      *ambiancePluie, *ambianceOrage, *ambianceNature, *ambianceFoule, *musique1, *musique2, *sonVaisseau, *sonDeceleration, *sonCollision, *sonAcceleration;
    FMOD::Channel    *channelDeceleration,*channelAmbiance,*channelCollision,*channelVaisseau,*channelAcceleration;
    FMOD_RESULT       result;
    int               key;
    bool 			  collisionAlreadyPlayed,decelerationAlreadyPlayed,accelerationAlreadyPlayed;
    unsigned int      version;
    FMOD_VECTOR forward, up, velocity, listenerPos, lastPos;

};

#endif /* SONS_H_ */
