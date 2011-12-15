#include "Navigation.h"

Navigation::Navigation() {
	estEnTrainDAvancer = false;
	tempsPourArret = 0;
	tempsPourAcceleration=0;
	tempsPourDecceleration=0;
	peutTourner = false;
	estEnTrainDAccelerer=false;
	estEnTrainDeDecelerer=false;
	estEnTrainDeSArreter=false;
	arretEnDouceur=false;
	mCurrentMatrix.makeIdentity();

}

Navigation::~Navigation() {
}

void Navigation::init(WorldCreator world,gadget::PositionInterface &wand,gadget::PositionInterface &head,
				gadget::DigitalInterface &button0,gadget::DigitalInterface &button1,gadget::DigitalInterface &button2) {
	vpr::GUID new_guid("d6be4359-e8cf-41fc-a72b-a5b4f3f29aa2");
	mNavigator.init(new_guid);
	mWand=wand;
	mHead=head;
	mButton0=button0;
	mButton1=button1;
	mButton2=button2;
	mWorld=world;
	mWorld.updateBoundingBox();
}


void Navigation::detectionRotationExcessive(float* vitesseRotation) {

  float angleX = gmtl::Math::PI/2;
  float angleY = gmtl::Math::PI/2;

  if(abs(vitesseRotation[0]) > angleX){
    vitesseRotation[0] = 0;
    vitesseRotation[1] = 0;
    vitesseRotation[2] = 0;
  }

  if(abs(vitesseRotation[1]) > angleY){
    vitesseRotation[0] = 0;
    vitesseRotation[1] = 0;
    vitesseRotation[2] = 0;
  }

}



void augmenterVitesse(float &vitesseAAccelerer) {

	vitesseAAccelerer*=1.05;
}

void Navigation::accelerer(long tempsCourant) {
  int seuilMaximal = 80;
  if(estEnTrainDAvancer) {
    if(!estEnTrainDAccelerer) {
      estEnTrainDAccelerer=true;
      estEnTrainDeDecelerer=false;
    }
    if(tempsPourAcceleration==0)
      tempsPourAcceleration=tempsCourant;

    gmtl::Vec3f direction; // Choix de la vitesse


    gmtl::Vec3f Zdir = mNavigator->getVelocity();
    float* vitesse=Zdir.getData();
    if(tempsCourant-tempsPourAcceleration>20000) {

      if(sqrt(vitesse[0]*vitesse[0]+vitesse[1]*vitesse[1]+vitesse[2]*vitesse[2])<seuilMaximal) {
	augmenterVitesse(vitesse[0]);
	augmenterVitesse(vitesse[1]);
	augmenterVitesse(vitesse[2]);
	Zdir.set(vitesse);
	mNavigator->setVelocity(Zdir);

      }
      tempsPourAcceleration=0;
    }

  }

}



void facteurRalentissement(float &vitesseARalentir) {
	vitesseARalentir*=0.95;
}

void Navigation::ralentir(long tempsCourant) {
  int seuilMinimal = 10;
  if(estEnTrainDAvancer && estEnTrainDeDecelerer) {
    if(tempsPourDecceleration==0)
      tempsPourDecceleration=tempsCourant;

    gmtl::Vec3f Zdir = mNavigator->getVelocity();
    float* vitesse=Zdir.getData();
    if(tempsCourant-tempsPourDecceleration>40000) {

      if(sqrt(vitesse[0]*vitesse[0]+vitesse[1]*vitesse[1]+vitesse[2]*vitesse[2])>seuilMinimal) {
	facteurRalentissement(vitesse[0]);
	facteurRalentissement(vitesse[1]);
	facteurRalentissement(vitesse[2]);
	Zdir.set(vitesse);
	mNavigator->setVelocity(Zdir);

      } else {
	estEnTrainDeDecelerer=false;
      }
      tempsPourDecceleration=0;
    }

  }
}

void Navigation::arretBrutal() {
	estEnTrainDAvancer=false;
	arretEnDouceur=false;
	estEnTrainDeSArreter=false;
	estEnTrainDAccelerer=false;
	estEnTrainDeDecelerer=false;
}

void Navigation::ralentirPuisSAreter(long tempsCourant)
{
  if(!estEnTrainDAvancer && arretEnDouceur) {
    if(tempsPourArret==0)
      tempsPourArret=tempsCourant;
    gmtl::Vec3f direction;
    gmtl::Vec3f Zdir = mNavigator->getVelocity();
    float* vitesse=Zdir.getData();
    if(tempsCourant-tempsPourArret>40000) {
      facteurRalentissement(vitesse[0]);
      facteurRalentissement(vitesse[1]);
      facteurRalentissement(vitesse[2]);
      Zdir.set(vitesse);
      mNavigator->setVelocity(Zdir);
      tempsPourArret=tempsCourant;
      estEnTrainDeSArreter=true;
    } else {
      estEnTrainDeSArreter=false;
    }
    if(vitesse[0]==0 && vitesse[1]==0 && vitesse[2]==0) {
      tempsPourArret=0;
      // estEnTrainDeSArreter=false;
    }

  }
  if(!estEnTrainDAvancer && !arretEnDouceur) {
    gmtl::Vec3f Zdir = mNavigator->getVelocity();
    float* vitesse=Zdir.getData();
    vitesse[0]=0;
    vitesse[1]=0;
    vitesse[2]=0;
    mNavigator->setVelocity(Zdir);
  }

}

void Navigation::droitDeTourner() {
  if(!estEnTrainDAvancer && !peutTourner)
      peutTourner = true;
}

void Navigation::seDeplacer()
{
  if(estEnTrainDAvancer && !estEnTrainDAccelerer && !estEnTrainDeDecelerer) {
    gmtl::Matrix44f wandMatrix = mWand->getData(getDrawScaleFactor());
    gmtl::Vec3f direction; // Choix de la vitesse
    gmtl::Vec3f Zdir = gmtl::Vec3f(0.0f, 0.0f, -10.0f);
    gmtl::xform(direction, wandMatrix, Zdir);
    mNavigator->setVelocity(direction);
  }
  if(peutTourner) {
    float rotationWandAxeX=gmtl::makeXRot(mWand->getData(getDrawScaleFactor()));
    float rotationWandAxeZ=gmtl::makeZRot(mWand->getData(getDrawScaleFactor()));
    gmtl::Vec3f rotationXYZ(rotationWandAxeX,rotationWandAxeZ ,0);
    if(rotationWandAxeX>=0.2)
      rotationWandAxeX-=0.2;
    if(rotationWandAxeX<=-0.2)
      rotationWandAxeX+=0.2;
    if(rotationWandAxeZ>=0.2)
      rotationWandAxeZ-=0.2;
    if(rotationWandAxeZ<=-0.2)
      rotationWandAxeZ+=0.2;
    mNavigator->setRotation(rotationXYZ);
  }
}static float calculerWAvecY(float y) {
	float angle=gmtl::Math::aSin(y);
	float w=cos(angle);
	cout <<"angle correction" <<  w << endl;
	return w;
}

static void printQuaternion(osg::Quat quat) {
	cout << quat.x() << ", " << quat.y() << ", " << quat.z() << ", " << quat.w() << endl;
}

void Navigation::stabiliserCamera(float limiteHorizon,float increment,osg::Quat rotationActuelle,osg::Matrix &matriceCorrection) {
  double qx=0,qz=0,qw=0;
  osg::Quat adapte;
  static osg::Quat horizon;
  if(rotationActuelle.z()>limiteHorizon || rotationActuelle.z()<-limiteHorizon || rotationActuelle.x()>limiteHorizon || rotationActuelle.x()<-limiteHorizon) {
    qw=rotationActuelle.w();
    if(abs(rotationActuelle.z())>limiteHorizon) {
      if(rotationActuelle.z()>limiteHorizon) {
	qz=-increment;
      }
      if( rotationActuelle.z()<-limiteHorizon) {
	qz=+increment;
      }
    }
    if(abs(rotationActuelle.x())>limiteHorizon) {
      if( rotationActuelle.x()>limiteHorizon) {
	qx=-increment;
      }
      if( rotationActuelle.x()<-limiteHorizon) {
	qx=+increment;
      }
    }
    adapte.set(qx,0,qz,qw);
    matriceCorrection.makeRotate(adapte);
  } 
}


void Navigation::stabiliserCameraInverse(float limiteHorizon,float increment,osg::Quat rotationActuelle,osg::Matrix &matriceCorrection) {
  double qx=0,qz=0,qw=0;
  osg::Quat adapte;

  if( rotationActuelle.x()>limiteHorizon) {
    qx=-increment;
    qw=rotationActuelle.w();
  }
  if( rotationActuelle.x()<-limiteHorizon) {
    qx=+increment;
    qw=rotationActuelle.w();
  }
  if(rotationActuelle.z()>limiteHorizon) {
    qz=-increment;
    qw=rotationActuelle.w();
  }
  if( rotationActuelle.z()<-limiteHorizon) {
    qz=+increment;
    qw=rotationActuelle.w();
  }
  if(rotationActuelle.z()>limiteHorizon || rotationActuelle.z()<-limiteHorizon || rotationActuelle.x()>limiteHorizon || rotationActuelle.x()<-limiteHorizon) {
    adapte.set(qx,0,qz,qw);
    matriceCorrection.makeRotate(adapte);
  }
}


void Navigation::jouerSonVaisseau()
{
  if(estEnTrainDAvancer) {
    mSons1.pauseSonCollision();
    //if(estEnTrainDeSArreter) {
      mSons1.pauseSonVaisseau();
      // }
    if(!estEnTrainDeSArreter) { 
      mSons1.pauseSonDeceleration();
    }
    if(!estEnTrainDAccelerer) {
      cout << "deceleration" << endl;
      mSons1.pauseSonGrandeVitesse();
      mSons1.pauseSonAcceleration();
      mSons1.jouerSonVaisseau();
    } else {
      cout << "acceleration" << endl;
      mSons1.jouerSonAcceleration();
      mSons1.jouerSonGrandeVitesse();
    }

  } else {
    if(estEnTrainDeSArreter) {
      mSons1.jouerSonDeceleration();
      mSons1.pauseSonVaisseau();
    }
    /* else {
      //mSons1.jouerSonVaisseau();
      }*/
  }
}

void Navigation::update(float time_delta) {
  osg::Matrix T;
  float rotationWandAxeZ=gmtl::makeZRot(mWand->getData(getDrawScaleFactor()));
  float rotationWandAxeX=gmtl::makeXRot(mWand->getData(getDrawScaleFactor()));
  gmtl::Vec3f translation =  mNavigator->getVelocity() * time_delta;
  mTranslation.set(translation.mData[0],translation.mData[1],translation.mData[2]);

  gmtl::Vec3f rotation =mNavigator->getRotation();
  mRotation.set(rotation.mData[0],rotation.mData[1],rotation.mData[2]);
  //Translation
  T.makeTranslate(-mTranslation);
  //Rotation
  osg::Matrix R;
  R.makeIdentity();
  osg::Vec3 x(1,0,0);
  osg::Vec3 y(0,1,0);
  osg::Vec3 z(0,0,1);
  R.makeRotate(-mRotation.x()/100,x,-mRotation.y()/100,y,-mRotation.z()/100,z);
  //Correction de l'angle de la caméra
  osg::Matrix H;
  H.makeIdentity();

  osg::Matrix K;
  K.makeIdentity();
  
  osg::Quat rotationActuelle=mCurrentMatrix.getRotate();
  if(abs(rotationWandAxeZ)<0.2 && abs(rotationWandAxeX)<0.2) {

    R.makeIdentity();
    if(rotationActuelle.y()>0.97) {
      stabiliserCamera(0.15,+0.00005,rotationActuelle,H);
    } else {
      if(rotationActuelle.y()>0.8) {
	stabiliserCamera(0.05,0.0005,rotationActuelle,H);
      } else {
	stabiliserCamera(0.005,0.001,rotationActuelle,H);
      }
    }
  }
  //l'application des multiplications de matrices se fait à l'envers dans openscenegraph ...
  mCurrentMatrix = mCurrentMatrix  * H * R * T;
  collisions();

  jouerSonVaisseau();
}

void Navigation::rebond(osg::BoundingBox immeuble,osg::Vec3f positionCourante) {
	for(int i=0;i<8;i++) {
		if(positionCourante.z() <= immeuble.corner(i).z()+0.5 && positionCourante.z() >= immeuble.corner(i).z()-0.5) {

		}
	}

}

void Navigation::collisions() {
  gmtl::Matrix44f wand_matrix(mWand->getData(getDrawScaleFactor()));
  const osg::Matrix& matNav(mCurrentMatrix);
  osg::Matrix matNavInverse;
  matNavInverse=matNavInverse.inverse(matNav);

  osg::Matrix wandMatrix=matNavInverse;
  float decalageWandX,decalageWandY,decalageWandZ;
  float positionX,positionY,positionZ;
  decalageWandX=0;
  decalageWandY=wand_matrix[1][3];
  decalageWandZ=0;
  positionX=matNavInverse.ptr()[12];
  positionY=matNavInverse.ptr()[13];
  positionZ=matNavInverse.ptr()[14];

  wandMatrix.makeTranslate(positionX+decalageWandX,positionY+decalageWandY,positionZ+decalageWandZ);
  osg::Vec3f wandPoint(wandMatrix.getTrans());
  osg::BoundingBox wandBbox;
  wandBbox.set(wandPoint[0]-0.2,wandPoint[1]-0.2,wandPoint[2]-0.2,wandPoint[0]+0.2,wandPoint[1]+0.2,wandPoint[2]+0.2);
  for (map< vector<GLfloat> , osg::BoundingBox >::iterator boundingBox = mWorld.lesBoundingBoxes.begin(); boundingBox != mWorld.lesBoundingBoxes.end(); ++boundingBox) {
    if(boundingBox->second.intersects(wandBbox)) {
      arretBrutal();
      mSons1.jouerSonCollision();
      mSons1.jouerSonDeceleration();
      mSons1.pauseSonAcceleration();
      mSons1.pauseSonVaisseau();
      break;
    }
  }
}

osg::Vec3 Navigation::getTranslation() {
	return mTranslation;
}

osg::Vec3 Navigation::getRotation() {
	return mRotation;
}

osg::Matrix Navigation::getCurrentMatrix() {
	return mCurrentMatrix;
}

void Navigation::avancerOuArreter() {
  if(!estEnTrainDAvancer) {
	  droitDeTourner();
      estEnTrainDAvancer = true;
  } else {
      estEnTrainDAvancer = false;
      estEnTrainDAccelerer=false;
      estEnTrainDeDecelerer=false;
      arretEnDouceur=true;
  }
}


void Navigation::gestionBouton2(long tempsCourant) {

  if (mButton2->getData() == gadget::Digital::TOGGLE_ON){
    avancerOuArreter();
  }
  seDeplacer();
  ralentirPuisSAreter(tempsCourant);

}

void Navigation::gestionGachette(long tempsCourant) {

   if ( mButton0->getData() == gadget::Digital::ON )
   {
	 accelerer(tempsCourant);
   }

   if ( mButton0->getData() == gadget::Digital::OFF)
   {
     if(estEnTrainDAccelerer && !estEnTrainDeDecelerer) {
		 estEnTrainDAccelerer=false;
		 estEnTrainDeDecelerer=true;
      }
     ralentir(tempsCourant);
   }
}
