#include "Sons.h"

Sons() {}

void Sons::ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

FMOD_RESULT Sons::Initialisation()
{
    result = FMOD::System_Create(&system);
    ERRCHECK(result);
    channel=0;

    //result = system->getVersion(&version);
    //ERRCHECK(result);

/*
    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        getch();
    }
*/

    result = system->setOutput(FMOD_OUTPUTTYPE_ALSA);
    ERRCHECK(result);

    result = system->init(1, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    result = system->createSound("../fmod/Audio/AmbianceVille.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &sound);
    ERRCHECK(result);

    //printf("Press space to pause, Esc to quit\n");

    // Play the sound.

    result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
    ERRCHECK(result);

    return result;

}

void Sons::Ambiance()
{
   // Create a System object and initialize.
  result = Initialisation();

  result = system->createSound("../fmod/Audio/AmbianceVille.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &sound);
    ERRCHECK(result);

    // Play the sound.

    result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
    ERRCHECK(result);

    /*
        Main loop.
    */
    
    do
    {
      /*
        if (kbhit())
        {
            key = getch();

            switch (key)
            {
                case ' ' :
                {
                    bool paused;
                    channel->getPaused(&paused);
                    channel->setPaused(!paused);
                    break;
                }
            }
        }
      */
        system->update();

        if (channel)
        {
            unsigned int ms;
            unsigned int lenms;
            bool         playing;
            bool         paused;

            channel->isPlaying(&playing);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE))
            {
                ERRCHECK(result);
            }

            result = channel->getPaused(&paused);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE))
            {
                ERRCHECK(result);
            }

            result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE))
            {
                ERRCHECK(result);
            }

            result = sound->getLength(&lenms, FMOD_TIMEUNIT_MS);
            if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE))
            {
                ERRCHECK(result);
            }

            printf("Time %02d:%02d:%02d/%02d:%02d:%02d : %s\r", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused ? "Paused " : playing ? "Playing" : "Stopped");
            fflush(stdout);
        }

        Sleep(10);

    } while (key != 27);

    // Shut down

    result = sound->release();
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);
}
