#include "Navigation.h"

Navigation::Navigation() {
	estEnTrainDAvancer = false;
	tempsPourArret = 0;
	tempsPourAcceleration=0;
	tempsPourDecceleration=0;
	peutTourner = false;
	estEnTrainDAccelerer=false;
	estEnTrainDeDecelerer=false;
	arretEnDouceur=false;
	correctionEnCours=false;
	inverserDirection=false;
	mCompteurCollisions=0;
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
		}
		if(vitesse[0]==0 && vitesse[1]==0 && vitesse[2]==0) {
			tempsPourArret=0;
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

}

static float calculerWAvecY(float y) {
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
		//printQuaternion(rotationActuelle);
		if(!correctionEnCours) {
			horizon.set(0,rotationActuelle.y(),0,calculerWAvecY(rotationActuelle.y()));
			correctionEnCours=true;
		}
		//printQuaternion(horizon);
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
		/*adapte.slerp(0.000000001,rotationActuelle,horizon);
		matriceCorrection.makeRotate(adapte);*/
	} else {
		//cout << "fin correction" << endl;
		if(correctionEnCours) {
			correctionEnCours=false;
		}
	}
	/*if(rotationActuelle.w()>=0) {
		qw=0.5;
	} else {
		qw=-0.5;
	}*/
	/*qw=rotationActuelle.w();
	if(rotationActuelle.z()>limiteHorizon) {
		qz=-increment;
	}
	if( rotationActuelle.z()<-limiteHorizon) {
		qz=+increment;
	}
	if( rotationActuelle.x()>limiteHorizon) {
		qx=-increment;
	}
	if( rotationActuelle.x()<-limiteHorizon) {
		qx=+increment;
	}
	if(rotationActuelle.z()>limiteHorizon || rotationActuelle.z()<-limiteHorizon || rotationActuelle.x()>limiteHorizon || rotationActuelle.x()<-limiteHorizon) {
		adapte.set(qx,0,qz,qw);
		matriceCorrection.makeRotate(adapte);
	}*/
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
  if(!estEnTrainDAvancer && !estEnTrainDAccelerer && !estEnTrainDeDecelerer)
    mSons1.jouerSonVaisseau();
  //if(estEnTrainDAccelerer || estEnTrainDeDecelerer)
  //mSons1.pauseSon();

  /*
  if(estEnTrainDAvancer)
    cout << "Avancer " << endl;
  if(estEnTrainDeDecelerer)
    cout << "  Deceleration  " << endl;
  if(estEnTrainDAccelerer)
    cout << "  Acceleration  " << endl;
  */

  //cout << "Avancer " << estEnTrainDAvancer << "  Decelerer  " << estEnTrainDeDecelerer << "  Accelerer  " << estEnTrainDAccelerer << endl;

}



/*
void Navigation::jouerSonImmeuble()
{

  const gmtl::Matrix44f wandMatrix(mWand->getData(getDrawScaleFactor()));
  //On récupère la position du wand que l'on stocke dans wand_point
  osg::Vec3f wand_point(wandMatrix[0][3],wandMatrix[1][3],wandMatrix[2][3]);
  wand_point = wand_point * mWorld.pNavTrans.get()->getMatrix();
  int vitesseMinimale = 50, altitudeMaximale = 20;

  gmtl::Vec3f Zdir = mNavigator->getVelocity();
  float* vitesse=Zdir.getData();
  
  //Si vitesse suffisamment grande ET altitude assez  basse
  if(sqrt(vitesse[0]*vitesse[0]+vitesse[1]*vitesse[1]+vitesse[2]*vitesse[2])>vitesseMinimale && wand_point[2]<altitudeMaximale) {

    mSons1.jouerEffetDoppler();
  }
}
*/

static void normalisationPI(float &angle) {
	if(angle<0.f) {
		angle+=osg::PI*2.f;
	}
	if(angle>osg::PI*2.f) {
		angle-=osg::PI*2.f;
	}
}

static void radToDeg(float &angle) {
	angle=(angle*180)/(gmtl::Math::PI);
}

static void convertirQuat(osg::Quat quat) {
	float angle = gmtl::Math::aCos(quat.w()) * 2.f;
	normalisationPI(angle);
	radToDeg(angle);
	float x,y,z;
	/* Normalisation de l'axe de rotation */
	float norm = sqrt(quat.x() * quat.x() + quat.y() * quat.y() + quat.z() * quat.z());
	if (norm > 0.0005)
	{
	    x = quat.x()/norm;
	    y = quat.y()/norm;
	    z = quat.z()/norm;
	}
	cout << x << ", "<< y << ", "<< z << ", " << angle <<endl;
}


static void printMatrice(osg::Matrix vw_M_w) {
	cout << vw_M_w.ptr()[0] << " "<< vw_M_w.ptr()[1] << " "<<vw_M_w.ptr()[2] << " "<<vw_M_w.ptr()[3] << endl;
	cout << vw_M_w.ptr()[4] << " "<<vw_M_w.ptr()[5] << " "<<vw_M_w.ptr()[6] <<" "<< vw_M_w.ptr()[7] << endl;
	cout << vw_M_w.ptr()[8] << " "<<vw_M_w.ptr()[9] << " "<<vw_M_w.ptr()[10] << " "<<vw_M_w.ptr()[11] << endl;
	cout << vw_M_w.ptr()[12] << " "<<vw_M_w.ptr()[13] << " "<<vw_M_w.ptr()[14] << " "<<vw_M_w.ptr()[15] << endl;
}

void Navigation::update(float time_delta) {
	//if(estEnTrainDAvancer) {
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

		//printQuaternion(rotationActuelle);
		//calculerW(rotationActuelle);
		//convertirQuat(rotationActuelle);
		//l'application des multiplications de matrices se fait à l'envers dans openscenegraph ...

		osg::Quat rotationActuelle=mCurrentMatrix.getRotate();
		//printQuaternion(rotationActuelle);
		if(abs(rotationWandAxeZ)<0.2 && abs(rotationWandAxeX)<0.2) {

			R.makeIdentity();
			if(rotationActuelle.y()>0.97) {
				stabiliserCamera(0.08,+0.00005,rotationActuelle,H);
			} else {
				if(rotationActuelle.y()>0.8) {
					stabiliserCamera(0.05,0.0005,rotationActuelle,H);
				} else {
					stabiliserCamera(0.005,0.001,rotationActuelle,H);
				}
			}
		}
		mCurrentMatrix = mCurrentMatrix  * H * R * T;
		collisions();

		jouerSonVaisseau();
	//}



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
				/*cout << wandPoint.x() <<", " << wandPoint.y() <<", " << wandPoint.z() << endl;
				cout << "min "<< boundingBox->second.xMin() << ", " << boundingBox->second.yMin() << ", " << boundingBox->second.zMin() << endl;
				cout << "max "<< boundingBox->second.xMax() << ", " << boundingBox->second.yMax() << ", " << boundingBox->second.zMax() << endl;
				cout << "collisions" << endl;*/
				arretBrutal();
				mSons1.jouerSonCollision();
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
      arretEnDouceur=true;
      mSons1.jouerSonDeceleration();
  }
}


void Navigation::gestionBouton2(long tempsCourant)
{

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
