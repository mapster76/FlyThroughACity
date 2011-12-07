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
	inverserDirection=false;
	mCompteurCollisions=0;
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



void ralentir(float &vitesseARalentir) {
	vitesseARalentir*=0.95;
}

void Navigation::deccelerer(long tempsCourant) {
	int seuilMinimal = 10;
	if(estEnTrainDAvancer && estEnTrainDeDecelerer) {

		if(tempsPourDecceleration==0)
			tempsPourDecceleration=tempsCourant;

		gmtl::Vec3f Zdir = mNavigator->getVelocity();
		float* vitesse=Zdir.getData();
		if(tempsCourant-tempsPourDecceleration>40000) {

			if(sqrt(vitesse[0]*vitesse[0]+vitesse[1]*vitesse[1]+vitesse[2]*vitesse[2])>seuilMinimal) {
			  ralentir(vitesse[0]);
			  ralentir(vitesse[1]);
			  ralentir(vitesse[2]);
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
			ralentir(vitesse[0]);
			ralentir(vitesse[1]);
			ralentir(vitesse[2]);
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
		mNavigator->setRotation(rotationXYZ);
	}

}

void Navigation::stabiliserCamera(float limiteHorizon,float increment,osg::Quat rotationActuelle,osg::Matrix &matriceCorrection) {
	double qx=0,qz=0,qw=0;
	osg::Quat adapte;
	if(rotationActuelle.z()>limiteHorizon) {
		qz=-increment;
		qw=rotationActuelle.w();
	}
	if( rotationActuelle.z()<-limiteHorizon) {
		qz=+increment;
		qw=rotationActuelle.w();

	}
	if( rotationActuelle.x()>limiteHorizon) {
		qx=-increment;
		qw=rotationActuelle.w();
	}
	if( rotationActuelle.x()<-limiteHorizon) {
		qx=+increment;
		qw=rotationActuelle.w();
	}
	if(rotationActuelle.z()>limiteHorizon || rotationActuelle.z()<-limiteHorizon || rotationActuelle.x()>limiteHorizon || rotationActuelle.x()<-limiteHorizon) {
		adapte.set(qx,0,qz,qw);
		matriceCorrection.makeRotate(adapte);
	}
}

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


void Navigation::update(float time_delta) {
	if(estEnTrainDAvancer) {
		osg::Matrix T;

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
		float rotationWandAxeZ=gmtl::makeZRot(mWand->getData(getDrawScaleFactor()));
		float rotationWandAxeX=gmtl::makeXRot(mWand->getData(getDrawScaleFactor()));
		osg::Quat rotationActuelle=mCurrentMatrix.getRotate();

		if(abs(rotationWandAxeZ)<0.2 && abs(rotationWandAxeX)<0.2) {
			R.makeIdentity();
			if(rotationActuelle.y()>0.97) {
				stabiliserCamera(0.15,0.0005,rotationActuelle,H);
			} else {
				if(rotationActuelle.y()>0.8) {
					stabiliserCamera(0.05,0.0005,rotationActuelle,H);
				} else {
					stabiliserCamera(0.005,0.001,rotationActuelle,H);
				}
			}
		}
		collisions();
		//l'application des multiplications de matrices se fait à l'envers dans openscenegraph ...
		mCurrentMatrix = mCurrentMatrix * H * R * T;
		jouerSonImmeuble();
	}



}

void Navigation::collisions() {
	//if(estEnTrainDAvancer) {
	gmtl::Matrix44f wandMatrix(mWand->getData(getDrawScaleFactor()));
	// The navigation matrix is w_M_vw, so invert it for use here.
	/*const osg::Matrix& nav_mat(mWorld.pNavTrans->getMatrix());
	osg::Matrix vw_M_w;
	nav_mat.inverse(vw_M_w);

	// Transform the wand matrix from real world coordinates into virtual world
	// coordinates.
	osg::Matrix osg_wandMatrix(
			wand_matrix[0][0],wand_matrix[0][1],wand_matrix[0][2],wand_matrix[0][3],
			wand_matrix[1][0],wand_matrix[1][1],wand_matrix[1][2],wand_matrix[1][3],
			wand_matrix[2][0],wand_matrix[2][1],wand_matrix[2][2],wand_matrix[2][3],
			wand_matrix[3][0],wand_matrix[3][1],wand_matrix[3][2],wand_matrix[3][3]);
	osg::Matrix wandMatrix= vw_M_w * osg_wandMatrix;*/
		//On récupère la position du wand que l'on stocke dans wand_point
		const osg::Vec3f wandPoint(wandMatrix[0][3],wandMatrix[1][3],wandMatrix[2][3]);
		osg::BoundingBox wandBbox;
		wandBbox.set(wandPoint[0]-0.5,wandPoint[1]-0.5,wandPoint[2]-0.5,wandPoint[0]+0.5,wandPoint[1]+0.5,wandPoint[2]+0.5);
		mWorld.updateBoundingBox();

		for (map< vector<GLfloat> , osg::BoundingBox >::iterator boundingBox = mWorld.lesBoundingBoxes.begin(); boundingBox != mWorld.lesBoundingBoxes.end(); ++boundingBox) {
			if(boundingBox->second.intersects(wandBbox)) {
				mCompteurCollisions++;
				cout << "collisions" << endl;
				if(mCompteurCollisions>5) {

					arretBrutal();
					mCompteurCollisions=0;
				}
			}
		}
	//}
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
     deccelerer(tempsCourant);
   }
}
