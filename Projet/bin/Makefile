def: $(shell hostname)

hetre: Environment.o Sons.o main.o 
	g++     -g  -g  -o Town ./Environment.o ./Sons.o ./main.o -L/usr/local/lib64/flagpoll/../../lib64 -L/usr/local/lib -L/usr/lib/flagpoll/../../lib64 -lvrj-3_0 -Wl,-Bdynamic -lSM -lICE -lX11 -lm -lboost_program_options-mt -lgadget-2_0 -ljccl-1_4 -lvpr-2_2 -pthread -luuid -ldl -lboost_signals-mt -lboost_filesystem-mt -lboost_system-mt -lcppdom-1_0_3 -lsonix-1_4 -lvrj_ogl-3_0 -lGLU -lGL -lSM -lICE -lX11 -pthread -lXxf86vm -Wl,-Bdynamic -lSM -lICE -lX11 -lm -pthread -luuid -ldl   -L/usr/local/lib64/flagpoll/../../lib64 -L/usr/lib -L/usr/lib/flagpoll/../../lib64 -ltweek-1_4 -lomniORB4 -lomnithread -lomniDynamic4 -lvpr-2_2 -pthread -luuid -ldl -lboost_signals-mt -lboost_filesystem-mt -lboost_system-mt -lcppdom-1_0_3 -pthread -luuid -ldl -L/lib -L../lib -losg -losgDB -losgGA -losgUtil -lOpenThreads -lfmodex
Environment.o: ../src/Environment.cpp ../src/Environment.h ../src/world/CustomDrawable.h ../src/world/Immeuble.h ../src/world/Sol.h
	g++    -I../src   -I/include -I../fmod -I../src/world -I/usr/local/lib64/flagpoll/../../include/vrjuggler-3.0 -I/usr/include -I/usr/local/lib64/flagpoll/../../include/gadgeteer-2.0 -I/usr/local/lib64/flagpoll/../../include/jccl-1.4 -I/usr/local/lib64/flagpoll/../../include/vpr-2.2 -I/usr/lib/flagpoll/../../include/cppdom-1.0.3 -I/usr/share/flagpoll/../../include/gmtl-0.6.1 -I/usr/local/lib64/flagpoll/../../include/sonix-1.4 -pthread -Wall -DHAVE_CONFIG_H -g  -g -DJUGGLER_DEBUG -g -DJUGGLER_DEBUG -I/usr/local/lib64/flagpoll/../../include/tweek-1.4/tweek/idl -I/usr/local/lib64/flagpoll/../../include/tweek-1.4 -I/usr/include -I/usr/local/lib64/flagpoll/../../include/vpr-2.2 -I/usr/lib/flagpoll/../../include/cppdom-1.0.3 -DTWEEK_HAVE_CXX=1 -D__OSVERSION__=2 -D__linux__ -D__x86_64__ -pthread -g  -g -DJUGGLER_DEBUG -g -DJUGGLER_DEBUG  -o Environment.o -c ../src/Environment.cpp

Sons.o: ../src/Sons.cpp ../src/Sons.h
	g++    -I../src   -I/include -I../fmod -I../src/world -I/usr/local/lib64/flagpoll/../../include/vrjuggler-3.0 -I/usr/include -I/usr/local/lib64/flagpoll/../../include/gadgeteer-2.0 -I/usr/local/lib64/flagpoll/../../include/jccl-1.4 -I/usr/local/lib64/flagpoll/../../include/vpr-2.2 -I/usr/lib/flagpoll/../../include/cppdom-1.0.3 -I/usr/share/flagpoll/../../include/gmtl-0.6.1 -I/usr/local/lib64/flagpoll/../../include/sonix-1.4 -pthread -Wall -DHAVE_CONFIG_H -g  -g -DJUGGLER_DEBUG -g -DJUGGLER_DEBUG -I/usr/local/lib64/flagpoll/../../include/tweek-1.4/tweek/idl -I/usr/local/lib64/flagpoll/../../include/tweek-1.4 -I/usr/include -I/usr/local/lib64/flagpoll/../../include/vpr-2.2 -I/usr/lib/flagpoll/../../include/cppdom-1.0.3 -DTWEEK_HAVE_CXX=1 -D__OSVERSION__=2 -D__linux__ -D__x86_64__ -pthread -g  -g -DJUGGLER_DEBUG -g -DJUGGLER_DEBUG  -o Sons.o -c ../src/Sons.cpp

main.o: ../src/main.cpp ../src/Environment.h ../src/Sons.h
	g++    -I../src   -I/include -I../fmod -I../src/world -I/usr/local/lib64/flagpoll/../../include/vrjuggler-3.0 -I/usr/include -I/usr/local/lib64/flagpoll/../../include/gadgeteer-2.0 -I/usr/local/lib64/flagpoll/../../include/jccl-1.4 -I/usr/local/lib64/flagpoll/../../include/vpr-2.2 -I/usr/lib/flagpoll/../../include/cppdom-1.0.3 -I/usr/share/flagpoll/../../include/gmtl-0.6.1 -I/usr/local/lib64/flagpoll/../../include/sonix-1.4 -pthread -Wall -DHAVE_CONFIG_H -g  -g -DJUGGLER_DEBUG -g -DJUGGLER_DEBUG -I/usr/local/lib64/flagpoll/../../include/tweek-1.4/tweek/idl -I/usr/local/lib64/flagpoll/../../include/tweek-1.4 -I/usr/include -I/usr/local/lib64/flagpoll/../../include/vpr-2.2 -I/usr/lib/flagpoll/../../include/cppdom-1.0.3 -DTWEEK_HAVE_CXX=1 -D__OSVERSION__=2 -D__linux__ -D__x86_64__ -pthread -g  -g -DJUGGLER_DEBUG -g -DJUGGLER_DEBUG  -o main.o -c ../src/main.cpp


	
all: option Town

APP_NAME= Ville

# Basic options.
option:
srcdir=		../src
SRCS=		Environment.cpp Sons.cpp main.cpp 

#DZR_BASE_DIR=	$(shell flagpoll doozer --get-prefix)
#include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.mk
#include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.glapp.mk
#include $(DZR_BASE_DIR)/ext/tweek/dzr.tweek.mk

#EXTRA_INCLUDES+=	-I$(OSGHOME)/include -I../fmod -I../src/world
#EXTRA_LIBS+=		-L$(OSGHOME)/lib -L../lib -losg -losgDB -losgGA -losgUtil -lOpenThreads -lfmodex
# -----------------------------------------------------------------------------
# Application build targets.
# -----------------------------------------------------------------------------
all:
	$(MAKE) $(APP_NAME)

Town: $(OBJS)
	$(LINK) $(LINK_OUT)$@ $(OBJS) $(EXTRA_LIBS) $(LIBS)
