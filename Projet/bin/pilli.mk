# Le nom de l'application
APP = Town

# La liste des fichiers à compiler
#SRC = main.cpp simpleApp.cpp
SRC = ../src/util.cpp ../src/world/Sol.cpp ../src/world/ImmeubleAvecFenetre.cpp ../src/world/ImmeublePlat.cpp ../src/world/Skybox.cpp ../src/world/WorldCreator.cpp ../src/Navigation.cpp ../src/Environment.cpp ../src/Sons.cpp ../src/main.cpp  
OBJ = $(SRC:.cpp=.o)

# Les options de compilation + r«pertoire des .h
CXXFLAGS += -g -Wall -fexceptions -pthread -Wall -DHAVE_CONFIG_H -DJUGGLER_DEBUG
CXXFLAGS += -I.
CXXFLAGS += -I${VJ_BASE_DIR}/include/vrjuggler-3.0/
CXXFLAGS += -I${VJ_BASE_DIR}/include/gadgeteer-2.0/
CXXFLAGS += -I${VJ_BASE_DIR}/include/jccl-1.4/
CXXFLAGS += -I${VJ_BASE_DIR}/include/vpr-2.2/
CXXFLAGS += -I/usr/include/cppdom-1.0.3/
CXXFLAGS += -I${VJ_BASE_DIR}/include/gmtl-0.6.1/
CXXFLAGS += -I/usr/include/fmodex
CXXFLAGS += -I../src
CXXFLAGS += -I../src/world



# Les options d'édition des liens + répertoires et noms des .so
LDFLAGS += -L$(VJ_BASE_DIR)/lib -lvrj-3_0 -lvrj_ogl-3_0 -lgadget-2_0 -ljccl-1_4 -lvpr-2_2
LDFLAGS += -lfmodex
LDFLAGS += -losg -losgDB -losgUtil -lOpenThreads
LDFLAGS += -lGLU -lGL -lm
# ( pour linker avec ${HOME}/plib/libplibssg.so et ${HOME}/plib/libplibnet.so
#   on ajoutera "-L${HOME}/plib -lplibssg  -lplibnet" )
$(APP) : $(OBJ)
	$(CXX) $(LDFLAGS) -o $(APP) $(OBJ)

include Dep.mk



clean:
	-\rm ../src/*.o ../src/world/*.o $(APP)


dep:
	 g++ -MM -MG $(SRC) >Dep.mk
