#ifndef UTIL_H_
#define UTIL_H_

#include <cstdlib>
#include <ctime>
#include <vector>
#include <GL/glut.h>
#include <vpr/IO/SerializableObject.h>
#include <vpr/IO/ObjectReader.h>
#include <vpr/IO/ObjectWriter.h>
#include <plugins/ApplicationDataManager/UserData.h>


using namespace std;

class Random : public vpr::SerializableObject {
public :
  int mNombreAleatoire;

  virtual void readObject(vpr::ObjectReader* reader) {
    int nombreAleatoire;
    nombreAleatoire = reader->readUint32();
    mNombreAleatoire=nombreAleatoire;
  }

  virtual void writeObject(vpr::ObjectWriter* writer) {
    const int nombreAleatoire = mNombreAleatoire;
    writer->writeUint32(nombreAleatoire);
  }

  int getNombreAleatoire() {
    return mNombreAleatoire;
  }

  void setNombreAleatoire(int nombreAleatoire) {
    mNombreAleatoire=nombreAleatoire;
  }
};

class RandomGenerator {
 public:
  cluster::UserData< Random >  mRandom;
  RandomGenerator() {
    vpr::GUID new_guid("d6be4359-e8cf-41fc-a72b-a5b4f3f29aa2");
    mRandom.init(new_guid);
  }

  ~RandomGenerator() {}

  void randomParPas(int a, int b,int pas){
    static bool seedInitialiser=false;
    if(!seedInitialiser) {
      srand(time(NULL));
      seedInitialiser=true;
    }
    int nombreAleatoire=rand()%(b-a) +a;
    int quotient=nombreAleatoire/pas;
    int resultat=pas*quotient;
    int reste=nombreAleatoire%pas;
    if(reste > pas/2)
      resultat+=pas;
    mRandom->setNombreAleatoire(resultat);
  }
  
  unsigned int getRandom(){
    return mRandom->getNombreAleatoire();
  }
};

/**
 * Cette fonction permet de creer un vecteur représentant les coordonnées rapidement.
 * retorn Vector<GLfloat> de taille 3
 */
vector<GLfloat> setCoordonnes(GLfloat x,GLfloat z,GLfloat y);

#endif /* UTIL_H_ */
