# Le nom de l'application
APP = Town

# La liste des fichiers � compiler
#SRC = main.cpp simpleApp.cpp
SRC = ../src/util.cpp ../src/world/Sol.cpp ../src/world/ImmeubleAvecFenetre.cpp ../src/world/ImmeublePlat.cpp ../src/world/WorldCreator.cpp ../src/Navigation.cpp ../src/Environment.cpp ../src/main.cpp  
OBJ = $(SRC:.cpp=.o)

# Les options de compilation + r�pertoire des .h
CXXFLAGS += -g -Wall -fexceptions -pthread -Wall -DHAVE_CONFIG_H -DJUGGLER_DEBUG
CXXFLAGS += -I.
CXXFLAGS += -I${VJ_BASE_DIR}/include/vrjuggler-2.2/
CXXFLAGS += -I${VJ_BASE_DIR}/include/gadgeteer-1.2/
CXXFLAGS += -I${VJ_BASE_DIR}/include/jccl-1.2/
CXXFLAGS += -I${VJ_BASE_DIR}/include/vpr-2.0/
CXXFLAGS += -I${VJ_BASE_DIR}/include/cppdom-0.7.10/
CXXFLAGS += -I${VJ_BASE_DIR}/include/gmtl-0.5.4/
CXXFLAGS += -I${FMODROOT}/inc
CXXFLAGS += -I../src
CXXFLAGS += -I../src/world



# Les options d'�dition des liens + r�pertoires et noms des .so
LDFLAGS += -L$(VJ_BASE_DIR)/lib -lvrj-2_2 -lvrj_ogl-2_2 -lgadget-1_2 -ljccl-1_2 -lvpr-2_0
LDFLAGS += -L$(FMODROOT)/lib -lfmodex
LDFLAGS += -losg -losgDB -losgUtil -lOpenThreads
LDFLAGS += -lGLU -lGL -lm
# ( pour linker avec ${HOME}/plib/libplibssg.so et ${HOME}/plib/libplibnet.so
#   on ajoutera "-L${HOME}/plib -lplibssg  -lplibnet" )

$(APP) : $(OBJ)
	$(CXX) $(LDFLAGS) -o $(APP) $(OBJ)

clean:
	-\rm ../src/*.o $(APP)

include Dep.mk
dep:
	 g++ -MM -MG $(SRC) >Dep.mk
