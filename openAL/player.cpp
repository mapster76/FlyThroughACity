#include <stdlib.h>
#include <stdio.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

// Buffers to hold sound data.
ALuint Buffer;

// Sources are points of emitting sound.
ALuint Source;

/*
 * These are 3D cartesian vector coordinates. A structure or class would be
 * a more flexible of handling these, but for the sake of simplicity we will
 * just leave it as is.
 */

// Position of the source sound.
ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };

// Velocity of the source sound.
ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };


// Position of the Listener.
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

// Velocity of the Listener.
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

// Orientation of the Listener. (first 3 elements are "at", second 3 are "up")
// Also note that these should be units of '1'.
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

int main(int argc, char *argv[])
{

	// Variables to load into.
	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;	
	// Load wav data into a buffer.
	alGenBuffers(1, &Buffer);

	if(alGetError() != AL_NO_ERROR)
	{
	    printf("Error loading data.");
		return 0;
	}

	//Loading wave file
	alutLoadWAVFile((ALbyte*)"wavdata/FancyPants.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffer, format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	// Bind the buffer with the source.
	alGenSources(1, &Source);

	if(alGetError() != AL_NO_ERROR)
	{
	    printf("Error loading data.");
		return 0;
	}
	
	
	alSourcei (Source, AL_BUFFER,   Buffer   );
	alSourcef (Source, AL_PITCH,    1.0      );
	alSourcef (Source, AL_GAIN,     1.0      );

	//Mise en place de la position de la source
	alSourcefv(Source, AL_POSITION, SourcePos);
	alSourcefv(Source, AL_VELOCITY, SourceVel);
	alSourcei (Source, AL_LOOPING,  loop     );

	//Mise en place de la position 
	alListenerfv(AL_POSITION,    ListenerPos);
	alListenerfv(AL_VELOCITY,    ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
	// Do another error check and return.
	if(alGetError() != AL_NO_ERROR)
	{
	    printf("Error loading data.");
		return 0;
	}

	alSourcePlay(Source);

	return 0;
	
}
