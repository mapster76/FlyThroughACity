#ifndef SONS_H_
#define SONS_H_

#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>
//#include <wincompat.h>
#include <stdio.h>
#include <iostream>


class Sons
{

public:

  Sons();
  virtual ~Sons();

  //void updateFmod(float*,float*,float*,float*,float);

  void jouerAmbiancePluie();
  void jouerSonVaisseau();
  void jouerSonDeceleration();
  void jouerSonCollision();
  void pauseSonVaisseau();
  void pauseSonDeceleration();
  void pauseSonCollision();

  void ERRCHECK(FMOD_RESULT);

 private:
  	FMOD_RESULT Initialisation();
    FMOD::System     *system;
    FMOD::Sound      *ambiancePluie, *sonVaisseau, *sonDeceleration, *sonCollision; 
    FMOD::Channel    *channelDeceleration,*channelAmbiance,*channelCollision,*channelVaisseau;
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;
    FMOD_VECTOR forward, up, velocity, listenerPos, lastPos;

};

#endif /* SONS_H_ */
