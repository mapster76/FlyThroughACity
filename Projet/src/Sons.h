#ifndef SONS_H_
#define SONS_H_

#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>
//#include <wincompat.h>
#include <stdio.h>


class Sons
{

public:

  Sons();
  virtual ~Sons();

  //void updateFmod(float*,float*,float*,float*,float);

  void ambiance();
  void fxSound(FMOD::Sound *);

  void ERRCHECK(FMOD_RESULT);

 private:
  	FMOD_RESULT Initialisation();
    FMOD::System     *system;
    FMOD::Sound      *ambiance1, *sound1, *sound2, *sound3;
    FMOD::Channel    *channel;
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;
    FMOD_VECTOR forward, up, velocity, listenerPos, lastPos;

};

#endif /* SONS_H_ */
