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

  void updateFmod();

  void ambiance();

  void ERRCHECK(FMOD_RESULT);

 private:
  	FMOD_RESULT Initialisation();
    FMOD::System     *system;
    FMOD::Sound      *sound;
    FMOD::Channel    *channel;
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;
    FMOD_VECTOR forward, up, vel, listenerpos, lastpos;

};

#endif /* SONS_H_ */
