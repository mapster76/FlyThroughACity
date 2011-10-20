/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998-2007 by Iowa State University
 *
 * Original Authors:
 *   Allen Bierbaum, Christopher Just,
 *   Patrick Hartling, Kevin Meinert,
 *   Carolina Cruz-Neira, Albert Baker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

//----------------------------------------
// Test Osg VR Juggler program
//
// main.cpp
//----------------------------------------

#include <cstdlib>
#include <OsgNavGrab.h>

// --- Lib Stuff --- //
#include <vrj/Kernel/Kernel.h>

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
ALfloat ListenerOri[] = { 0.0, 0.0, 1.0,  0.0, 1.0, 0.0 };

void KillALData()
{
	alDeleteBuffers(1, &Buffer);
	alDeleteSources(1, &Source);
	alutExit();
}

int main(int argc, char* argv[])
{

   vrj::Kernel* kernel = vrj::Kernel::instance();  // Get the kernel
   OsgNavGrab* application = new OsgNavGrab(kernel, argc, argv);             // Instantiate an instance of the app

   if ( argc <= 1 )
   {
      // display some usage info (holding the user by the hand stuff)
      //  this will probably go away once the kernel becomes separate
      //  and can load application plugins.
      std::cout<<"\n"<<std::flush;
      std::cout<<"\n"<<std::flush;

      std::cout << "Usage: " << argv[0]
         << " vrjconfigfile[0] vrjconfigfile[1] ... vrjconfigfile[n]\n"
         << std::endl << std::endl;

      std::exit(1);
   }

// Partie OpenAL

	alutInit(NULL, 0);
	alGetError();

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
	alutLoadWAVFile((ALbyte*)"wavdata/FancyPants.wav", &format, &data, &size, 		&freq, &loop);
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

// Fin de la partie OpenAL

   //application->setModelFileName(std::string(argv[1]));

   // Load any config files specified on the command line
   for ( int i = 1; i < argc; ++i )
   {
      kernel->loadConfigFile(argv[i]);
   }

   kernel->start();

   kernel->setApplication(application);
   kernel->waitForKernelStop();
   
   delete application;

	// Do another error check and return.
	if(alGetError() != AL_NO_ERROR)
	{
	    printf("Error loading data.");
		return 0;
	}

	atexit(KillALData);

	char c = ' ';
	
	while(c != 'q')
	{
		alSourcePlay(Source);
		c = getchar();
	}

   return 0;
}
