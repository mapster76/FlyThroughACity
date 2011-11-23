all: Town

APP_NAME= Town


# Basic options.
srcdir=		../src
SRCS=		util.cpp world/ImmeubleAvecFenetre.cpp world/ImmeublePlat.cpp world/WorldCreator.cpp Environment.cpp  main.cpp 

DZR_BASE_DIR=	$(shell flagpoll doozer --get-prefix)
include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.mk
include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.glapp.mk
include $(DZR_BASE_DIR)/ext/tweek/dzr.tweek.mk

EXTRA_INCLUDES+=	-I$(OSGHOME)/include -I../fmod -I../src/world
EXTRA_LIBS+=		-L$(OSGHOME)/lib -L../lib -losg -losgDB -losgGA -losgUtil -lOpenThreads -lfmodex
# -----------------------------------------------------------------------------
# Application build targets.
# -----------------------------------------------------------------------------
all:
	$(MAKE) $(APP_NAME)

Town: $(OBJS)
	$(LINK) $(LINK_OUT)$@ $(OBJS) $(EXTRA_LIBS) $(LIBS)
	
clean:
	rm *.o *.d Town world/*.o world/*.d

