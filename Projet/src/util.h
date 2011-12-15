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

class SharedNumber : public vpr::SerializableObject {
public :
  int mNombrePartage;

  virtual void readObject(vpr::ObjectReader* reader) {
    int nombrePartage;
    nombrePartage = reader->readUint32();
    mNombrePartage=nombrePartage;
  }

  virtual void writeObject(vpr::ObjectWriter* writer) {
    const int nombrePartage = mNombrePartage;
    writer->writeUint32(nombrePartage);
  }

  int getNombrePartage() {
    return mNombrePartage;
  }

  void setNombrePartage(int nombrePartage) {
    mNombrePartage=nombrePartage;
  }
};

class RandomGenerator {
 public:
  cluster::UserData< SharedNumber >  mRandom;
  RandomGenerator() {
    vpr::GUID new_guid("d6be4359-e8cf-41fc-a72b-a5b4f3f29aa2");
    mRandom.init(new_guid);
    if(mRandom->getNombrePartage()==0)
      mRandom->setNombrePartage(time(NULL));
  }

  ~RandomGenerator() {}

  int randomParPas(int a, int b,int pas){
    /* static bool seedInitialiser=false;
       if(!seedInitialiser) {*/
      srand(mRandom->getNombrePartage());
      /* seedInitialiser=true;
	 }*/
    int nombreAleatoire=rand()%(b-a) +a;
    int quotient=nombreAleatoire/pas;
    int resultat=pas*quotient;
    int reste=nombreAleatoire%pas;
    if(reste > pas/2)
      resultat+=pas;
    return resultat;
  }
};

/**
 * Cette fonction permet de creer un vecteur représentant les coordonnées rapidement.
 * retorn Vector<GLfloat> de taille 3
 */
vector<GLfloat> setCoordonnes(GLfloat x,GLfloat z,GLfloat y);

#endif /* UTIL_H_ */
