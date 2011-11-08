all: Town

APP_NAME= Town

# Basic options.
srcdir=		../src
SRCS=		Environment.cpp main.cpp world/CustomDrawable.h

DZR_BASE_DIR=	$(shell flagpoll doozer --get-prefix)
include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.mk
include $(DZR_BASE_DIR)/ext/vrjuggler/dzr.vrjuggler.glapp.mk
include $(DZR_BASE_DIR)/ext/tweek/dzr.tweek.mk

EXTRA_INCLUDES+=	-I$(OSGHOME)/include
EXTRA_LIBS+=		-L$(OSGHOME)/lib -losg -losgDB -losgGA -losgUtil -lOpenThreads -lopenal -lalut
# -----------------------------------------------------------------------------
# Application build targets.
# -----------------------------------------------------------------------------
all:
	$(MAKE) $(APP_NAME)

Town: $(OBJS)
	$(LINK) $(LINK_OUT)$@ $(OBJS) $(EXTRA_LIBS) $(LIBS)
