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
  void pauseAmbiancePluie();
  void pauseAmbianceOrage();
  void pauseAmbianceFoule();
  void pauseAmbianceNature();
  void pauseMusique1();
  void pauseMusique2();
  void changerAmbianceSonore(string itAmbianceSonore);
  void jouerSonVaisseau();
  void jouerSonDeceleration();
  void jouerSonAcceleration();
  void jouerSonGrandeVitesse();
  void jouerSonCollision();
  void pauseSonVaisseau();
  void pauseSonDeceleration();
  void pauseSonAcceleration();
  void pauseSonGrandeVitesse();
  void pauseSonCollision();

  void gestionBouton1(gadget::DigitalInterface mButton);
  

  void ERRCHECK(FMOD_RESULT);

 private:
  vector<string>::iterator itAmbianceSonore;
  vector<string> vAmbianceSonore;
  	FMOD_RESULT Initialisation();
    FMOD::System     *system;
    FMOD::Sound      *ambianceGenerale, *ambiancePluie, *ambianceOrage, *ambianceNature, *ambianceFoule, *musique1, *musique2, *sonVaisseau, *sonDeceleration, *sonCollision, *sonAcceleration, *sonGrandeVitesse;
    FMOD::Channel    *channelDeceleration,*channelAmbiance,*channelCollision,*channelVaisseau,*channelAcceleration, *channelGrandeVitesse, *channelPluie, *channelOrage, *channelFoule, *channelNature, *channelMusique1, *channelMusique2;
    FMOD_RESULT       result;
    int               key;
    bool 			  collisionAlreadyPlayed,decelerationAlreadyPlayed,accelerationAlreadyPlayed;
    unsigned int      version;
    FMOD_VECTOR forward, up, velocity, listenerPos, lastPos;

};

#endif /* SONS_H_ */
