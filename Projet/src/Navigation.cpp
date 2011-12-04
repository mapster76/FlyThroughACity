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
}

Navigation::~Navigation() {
	delete mNavigator;
}

void Navigation::init(OsgNavigator *navigator,gadget::PositionInterface &wand,gadget::PositionInterface &head,
				gadget::DigitalInterface &button0,gadget::DigitalInterface &button1,gadget::DigitalInterface &button2) {
	mNavigator=navigator;
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
  if(angleHorizon>0.05) {
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
  }
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
		float rotationWandAxeY=gmtl::makeYRot(mWand->getData());

		if(abs(rotationWandAxeY) < gmtl::Math::PI/2) {
			float vitesseRotation[3] = {gmtl::makeXRot(mWand->getData()),gmtl::makeZRot(mWand->getData()),0};
			if(abs(rotationWandAxeX)<0.2) {
				vitesseRotation[0]=0;
			}
			

			if(abs(rotationWandAxeZ)<0.2) {
				float angleHorizon=gmtl::makeZRot(mNavigator->getCurPos());
				float increment=0.02;

				if(angleHorizon>gmtl::Math::PI/2) {
					angleHorizon=gmtl::Math::PI-angleHorizon;

				} else {

					if(angleHorizon<=-gmtl::Math::PI/2) {
						angleHorizon=gmtl::Math::PI+angleHorizon;
						increment=-increment;
					}
				}
				stabiliserCamera(increment,angleHorizon);
				if(abs(angleHorizon)<0.05) {
				  vitesseRotation[1]=rotationWandAxeY; 
				  if(rotationWandAxeY>0.2)
				    vitesseRotation[1]-=0.2;
				  if(rotationWandAxeY<-0.2)
				    vitesseRotation[1]+=0.2;
				} else
				  vitesseRotation[0]=0;
			}else {
			  if(rotationWandAxeX>0.2)
			    vitesseRotation[0]-=0.2;
			  if(rotationWandAxeX<-0.2)
			    vitesseRotation[0]+=0.2;
			  if(rotationWandAxeZ>0.2)
			    vitesseRotation[1]-=0.2;
			  if(rotationWandAxeZ<-0.2)
			    vitesseRotation[1]+=0.2;
			}

			gmtl::EulerAngleXYZf euler(vitesseRotation[0],vitesseRotation[1],vitesseRotation[2]);
			gmtl::Matrix44f rot_mat = gmtl::makeRot<gmtl::Matrix44f>( euler );
			mNavigator->setRotationalVelocity(rot_mat);
		}
	}

}

void Navigation::avancerOuArreter(){

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
