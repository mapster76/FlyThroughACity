#include "Navigation.h"

Navigation::Navigation() {
	estEnTrainDAvancer = false;
	tempsPourArret = 0;
	tempsPourAcceleration=0;
	tempsPourDecceleration=0;
	peutTourner = false;
	estEnTrainDAccelerer=false;
	estEnTrainDeDecelerer=false;
	estStabilise=false;
	previousT.makeIdentity();
	previousR.makeIdentity();
	estInferieur=false;
	estSuperieur=false;
}

Navigation::~Navigation() {
}

void Navigation::init(gadget::PositionInterface &wand,gadget::PositionInterface &head,
				gadget::DigitalInterface &button0,gadget::DigitalInterface &button1,gadget::DigitalInterface &button2) {
	vpr::GUID new_guid("d6be4359-e8cf-41fc-a72b-a5b4f3f29aa2");
	mNavigator.init(new_guid);
	mWand=wand;
	mHead=head;
	mButton0=button0;
	mButton1=button1;
	mButton2=button2;
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
			  //	cout << "Acceleration "<< endl;
			  augmenterVitesse(vitesse[0]);
			  augmenterVitesse(vitesse[1]);
			  augmenterVitesse(vitesse[2]);
			  //cout << "0 " << vitesse[0] << " 1 " << vitesse[1] << " 2 " << vitesse[2] << endl;
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
				  // cout << "decellere" << endl;
				  ralentir(vitesse[0]);
				  ralentir(vitesse[1]);
				  ralentir(vitesse[2]);
				  // cout << "0 " << vitesse[0] << " 1 " << vitesse[1] << " 2 " << vitesse[2] << endl;
				  Zdir.set(vitesse);
				  mNavigator->setVelocity(Zdir);

				} else {
				  //	cout << "fin Deceleration" << endl;
					estEnTrainDeDecelerer=false;
				}
				tempsPourDecceleration=0;
			}

		}
}


void Navigation::ralentirPuisSAreter(long tempsCourant)
{
	if(!estEnTrainDAvancer) {
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
		if(vitesse[0]==0 && vitesse[1]==0 && vitesse[2]==0)
			tempsPourArret=0;

	}
}

void Navigation::droitDeTourner() {
  if(!estEnTrainDAvancer && !peutTourner)
      peutTourner = true;
}

void Navigation::stabiliserCamera(float incrementRadian,float angleHorizon) {
  /*if(angleHorizon>0.05) {
    gmtl::EulerAngleXYZf eulerAngle(0,0,-incrementRadian);
    gmtl::Matrix44f rotMat = gmtl::makeRot<gmtl::Matrix44f>( eulerAngle );
    mNavigator->setCurPos(mNavigator->getCurPos()*rotMat);
    float nouvelAngleHorizon=gmtl::makeZRot(mNavigator->getCurPos());
    if(nouvelAngleHorizon>gmtl::Math::PI/2) {
      nouvelAngleHorizon=gmtl::Math::PI-nouvelAngleHorizon;
    } else {
      if(nouvelAngleHorizon<-gmtl::Math::PI/2) {
	nouvelAngleHorizon=gmtl::Math::PI+nouvelAngleHorizon;
      }
    }
    if(nouvelAngleHorizon<-0.02) {
      gmtl::EulerAngleXYZf eulerAngle(0,0,-nouvelAngleHorizon/2);
      gmtl::Matrix44f rotMat = gmtl::makeRot<gmtl::Matrix44f>( eulerAngle );
      mNavigator->setCurPos(mNavigator->getCurPos()*rotMat);
    }
  } else {
    if(angleHorizon<-0.05) {
      gmtl::EulerAngleXYZf eulerAngle(0,0,incrementRadian);
      gmtl::Matrix44f rotMat = gmtl::makeRot<gmtl::Matrix44f>( eulerAngle );
      mNavigator->setCurPos(mNavigator->getCurPos()*rotMat);
      float nouvelAngleHorizon=gmtl::makeZRot(mNavigator->getCurPos());
      if(nouvelAngleHorizon>gmtl::Math::PI/2) {
	nouvelAngleHorizon=gmtl::Math::PI-nouvelAngleHorizon;
      } else {
	if(nouvelAngleHorizon<-gmtl::Math::PI/2) {
	  nouvelAngleHorizon=gmtl::Math::PI+nouvelAngleHorizon;
	  nouvelAngleHorizon=-nouvelAngleHorizon;
	}
      }
      //	cout << "nouvelAngleHorizon" << nouvelAngleHorizon << endl;
      if(nouvelAngleHorizon>0.02) {
	gmtl::EulerAngleXYZf eulerAngle(0,0,-nouvelAngleHorizon/2);
	gmtl::Matrix44f rotMat = gmtl::makeRot<gmtl::Matrix44f>( eulerAngle );
	mNavigator->setCurPos(mNavigator->getCurPos()*rotMat);
      }
    }
  }*/
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

		float rotationWandAxeX=gmtl::makeXRot(mWand->getData());
		float rotationWandAxeZ=gmtl::makeZRot(mWand->getData());
		//float rotationWandAxeY=gmtl::makeYRot(mWand->getData());


		gmtl::Vec3f rotationXYZ(rotationWandAxeX,rotationWandAxeZ ,0);

		mNavigator->setRotation(rotationXYZ);

	}

}

int signe(int nombre) {
	if(nombre>=0)
		return 1;
	else
		return -1;
}

void Navigation::update(float time_delta) {
	gmtl::Vec3f translation =  mNavigator->getVelocity() * time_delta;
	mTranslation.set(translation.mData[0],translation.mData[1],translation.mData[2]);
	//cout << "translation " << translation << endl;
	gmtl::Vec3f rotation =mNavigator->getRotation();
	mRotation.set(rotation.mData[0],rotation.mData[1],rotation.mData[2]);
	//cout << "rotation " << rotation << endl;

	//Calcul de la matrice position
	//Translation
	osg::Matrix T;
	T.makeTranslate(-mTranslation);
	//Rotation
	osg::Matrix R;
	R.makeIdentity();
	//R1.makeRotate(-mRotation.x(),x,-mRotation.y(),y,-mRotation.z(),z);
	//cout << "angle " << -mRotation.x()/100 << ", " << -mRotation.y()/100 << ", " << -mRotation.z()/100 << endl;
	osg::Matrix H;
	float rotationWandAxeZ=gmtl::makeZRot(mWand->getData());
	H.makeIdentity();
	if(abs(rotationWandAxeZ)<0.1) {
		//cout << "rotation" << endl;
		osg::Quat rotationActuelle=mCurrentMatrix.getRotate();
		gmtl::Matrix44f rotation;
		rotation.set((float*) mCurrentMatrix.ptr());
		osg::Quat adapte;
		//cout << rotationActuelle.x() << "," << rotationActuelle.y() << "," << rotationActuelle.z() << "," << rotationActuelle.w() << endl;
		double x=0,z=0,w=0;
		if(abs(rotationActuelle.z())>0.05 && abs(rotationActuelle.x())>0.05) {
			if(rotationActuelle.z()>0.05 && rotationActuelle.x()>0.05) {
				z=-0.01;
				x=-0.01;
				w=rotationActuelle.w();
			}
			if(rotationActuelle.z()<-0.05 && rotationActuelle.x()>0.05) {
				z=+0.01;
				x=-0.01;
				w=rotationActuelle.w();
			}
			if(rotationActuelle.z()<-0.05 && rotationActuelle.x()<-0.05) {
				z=+0.01;
				x=+0.01;
				w=rotationActuelle.w();
			}
			if(rotationActuelle.z()>0.05 && rotationActuelle.x()<-0.05) {
				z=-0.01;
				x=+0.01;
				w=rotationActuelle.w();
			}
		} else {
			if(rotationActuelle.z()>0.05) {
				cout << "z=-0.01;" << endl;
				z=-0.01;
				w=rotationActuelle.w();
			}
			if( rotationActuelle.z()<-0.05) {
				cout << "z=+0.01;" << endl;
				z=+0.01;
				w=rotationActuelle.w();
			}
			if( rotationActuelle.x()>0.05) {
				cout << "x=-0.01;" << endl;
				x=-0.01;
				w=rotationActuelle.w();
			}
			if( rotationActuelle.x()<-0.05) {
				cout << "x=+0.01;" << endl;
				x=+0.01;
				w=rotationActuelle.w();
			}
		}
		if(rotationActuelle.z()>0.05 || rotationActuelle.z()<-0.05 || rotationActuelle.x()>0.05 || rotationActuelle.x()<-0.05) {
			adapte.set(x,0,z,w);
			H.makeRotate(adapte);
		}

	} else {
		osg::Vec3 x(1,0,0);
		osg::Vec3 y(0,1,0);
		osg::Vec3 z(0,0,1);
		R.makeRotate(-mRotation.x()/100,x,-mRotation.y()/100,y,-mRotation.z()/100,z);
	}
	mCurrentMatrix = mCurrentMatrix * H * R * T;
	//cout << "rotation" << -mNavigation.getRotation().x()/100 << ", " << -mNavigation.getRotation().y()/100 << ", " << -mNavigation.getRotation().z()/100 << endl;
	//l'application des multiplications de matrices se fait à l'envers dans openscenegraph ...

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
