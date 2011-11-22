#ifndef SONS_H_
#define SONS_H_

#include <fmod.hpp>
#include <fmod_errors.h>
#include <wincompat.h>
#include <stdio.h>


class Sons
{

public:

  Sons();
  virtual ~Sons();

  FMOD_RESULT Initialisation();

  void Ambiance();

  void ERRCHECK(FMOD_RESULT);

 private:

    FMOD::System     *system;
    FMOD::Sound      *sound;
    FMOD::Channel    *channel = 0;
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;

};

#endif /* SONS_H_ */
