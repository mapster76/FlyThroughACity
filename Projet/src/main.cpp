#include <cstdlib>
#include <Environment.h>
//#include <Sons.h>

// --- Lib Stuff --- //
#include <vrj/Kernel/Kernel.h>

#include <stdio.h>
#include <string>

int main(int argc, char* argv[])
{

   vrj::Kernel* kernel = vrj::Kernel::instance();  // Get the kernel
   Environment* application = new Environment(kernel, argc, argv); // Instantiate an instance of the app
   //Sons* ambiance = new Sons();

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

   // Load any config files specified on the command line
   for ( int i = 1; i < argc; ++i )
   {
      kernel->loadConfigFile(argv[i]);
   }

   kernel->start();
   kernel->setApplication(application);

   kernel->waitForKernelStop();
   
   delete application;
   return 0;
}
