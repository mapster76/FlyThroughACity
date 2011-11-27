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

  int angleX = 2;
  int angleY = 2;
  int angleZ = 2;

  if(vitesseRotation[0] < -angleX) {
    vitesseRotation[0] = 0;
    vitesseRotation[1] = 0;
    vitesseRotation[2] = 0;
  }
  if(vitesseRotation[0] > angleX){
    vitesseRotation[0] = 0;
    vitesseRotation[1] = 0;
    vitesseRotation[2] = 0;
  }

  if(vitesseRotation[1] < -angleY){
    vitesseRotation[0] = 0;
    vitesseRotation[1] = 0;
    vitesseRotation[2] = 0;
  }
  if(vitesseRotation[1] > angleY){
    vitesseRotation[0] = 0;
    vitesseRotation[1] = 0;
    vitesseRotation[2] = 0;
  }

  if(vitesseRotation[2] < -angleZ){
    vitesseRotation[0] = 0;
    vitesseRotation[1] = 0;
    vitesseRotation[2] = 0;
  }
  if(vitesseRotation[2] > angleZ){
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
				cout << "Acceleration "<< endl;
			  augmenterVitesse(vitesse[0]);
			  augmenterVitesse(vitesse[1]);
			  augmenterVitesse(vitesse[2]);
			  cout << "0 " << vitesse[0] << " 1 " << vitesse[1] << " 2 " << vitesse[2] << endl;
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
				  cout << "decellere" << endl;
				  ralentir(vitesse[0]);
				  ralentir(vitesse[1]);
				  ralentir(vitesse[2]);
				  cout << "0 " << vitesse[0] << " 1 " << vitesse[1] << " 2 " << vitesse[2] << endl;
				  Zdir.set(vitesse);
				  mNavigator->setVelocity(Zdir);

				} else {
					cout << "fin Deceleration" << endl;
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
	if(angleHorizon>0.025) {
		gmtl::EulerAngleXYZf eulerAngle(0,0,-incrementRadian);
		gmtl::Matrix44f rotMat = gmtl::makeRot<gmtl::Matrix44f>( eulerAngle );
		mNavigator->setCurPos(mNavigator->getCurPos()*rotMat);
		cout << " sup .025" << endl;
		float nouvelAngleHorizon=gmtl::makeZRot(mNavigator->getCurPos());
		if(nouvelAngleHorizon>1.7) {
			nouvelAngleHorizon=gmtl::Math::PI-nouvelAngleHorizon;
		}
		if(nouvelAngleHorizon<-1.7) {
			cout << angleHorizon << endl;
			nouvelAngleHorizon=gmtl::Math::PI+nouvelAngleHorizon;
		}
		if(nouvelAngleHorizon<-0.025) {
			cout << "nouvelAngleHorizon" << nouvelAngleHorizon << endl;
			gmtl::EulerAngleXYZf eulerAngle(0,0,-nouvelAngleHorizon);
			gmtl::Matrix44f rotMat = gmtl::makeRot<gmtl::Matrix44f>( eulerAngle );
			mNavigator->setCurPos(mNavigator->getCurPos()*rotMat);
			cout << "c'est la fin" << gmtl::makeZRot(mNavigator->getCurPos()) << endl;
		}
	} else {
		if(angleHorizon<-0.025) {
			gmtl::EulerAngleXYZf eulerAngle(0,0,incrementRadian);
			gmtl::Matrix44f rotMat = gmtl::makeRot<gmtl::Matrix44f>( eulerAngle );
			mNavigator->setCurPos(mNavigator->getCurPos()*rotMat);
			cout << " inf -.025" << endl;
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
		//cout << "Navigation "<< mNavigator->getVelocity().mData[0] <<" " << mNavigator->getVelocity().mData[1] <<" " << mNavigator->getVelocity().mData[2] <<" " << endl;
	}
	if(peutTourner) {

		//float angleRotationX=gmtl::makeXRot(mNavigator->getCurPos());
		float rotationWandAxeX=gmtl::makeXRot(mWand->getData());
		float rotationWandAxeZ=gmtl::makeZRot(mWand->getData());
		float vitesseRotation[3] = {gmtl::makeXRot(mWand->getData()),gmtl::makeZRot(mWand->getData()),0};
		/*if(abs(vitesseRotation[1])>0. && abs(angleRotationX)>0) {
			vitesseRotation[0]*=0.5;
		}*/

		/*if(rotationWandAxeZ!=0) {
			vitesseRotation[2]=-rotationWandAxeX;
		}*/
		if(abs(rotationWandAxeX)<0.2) {
			vitesseRotation[0]=0;
		}
		if(rotationWandAxeX>0.2)
			vitesseRotation[0]-=0.2;
		if(rotationWandAxeX<-0.2)
			vitesseRotation[0]+=0.2;

		//cout << "angle x " << gmtl::makeXRot(mNavigator->getCurPos()) << "angle y " << gmtl::makeYRot(mNavigator->getCurPos()) << "angle horizon " <<  gmtl::makeZRot(mNavigator->getCurPos()) <<endl;
		if(abs(rotationWandAxeZ)<0.2) {
			/*gmtl::Vec3f directionCourante=mNavigator->getVelocity();
			directionCourante.getData()[1]=0;
			mNavigator->setVelocity(directionCourante);
			vitesseRotation[0]-=vitesseRotation[0];*/
			float angleHorizon=gmtl::makeZRot(mNavigator->getCurPos());
			//float angleY=gmtl::makeYRot(mNavigator->getCurPos());
			float increment=0.01;
			/*if((angleY>3.14/2 && (angleY<3.15)) || ((angleY>-3.15) && (angleY<-3.14/2))) {
				angleHorizon=M_PI-angleHorizon;
				increment=-0.01;
			}*/
			//cout << "angle x " << gmtl::makeXRot(mNavigator->getCurPos()) << "angle y " << gmtl::makeYRot(mNavigator->getCurPos()) << "angle horizon " << angleHorizon <<endl;

			if(abs(angleHorizon)<1.5 && abs(angleHorizon)>0) {
				stabiliserCamera(increment,angleHorizon);
			}

			if(angleHorizon>1.7) {
				cout << angleHorizon << endl;
				angleHorizon=gmtl::Math::PI-angleHorizon;
				cout << "angle horizon>1.7 +" << angleHorizon<< endl ;
				stabiliserCamera(increment,angleHorizon);
			}

			if(angleHorizon<-1.7) {
				cout << angleHorizon << endl;
				angleHorizon=gmtl::Math::PI+angleHorizon;
				cout << "angle horizon<-1.7 +" << angleHorizon << endl;
				stabiliserCamera(-increment,angleHorizon);
			}



			/*	if((ancienAngleHorizon>=0 && angleHorizon>=0) || (ancienAngleHorizon<=0 && angleHorizon<=0)) {
					if(angleHorizon>0.04) {
						gmtl::EulerAngleXYZf eulerAngle(0,0,-0.0025);
						gmtl::Matrix44f rotMat = gmtl::makeRot<gmtl::Matrix44f>( eulerAngle );
						mNavigator->setCurPos(mNavigator->getCurPos()*rotMat);
					}
					if(angleHorizon<-0.04) {
						gmtl::EulerAngleXYZf eulerAngle(0,0,0.0025);
						gmtl::Matrix44f rotMat = gmtl::makeRot<gmtl::Matrix44f>( eulerAngle );
						mNavigator->setCurPos(mNavigator->getCurPos()*rotMat);
					}
					if(angleHorizon>1) {
						gmtl::EulerAngleXYZf eulerAngle(0,0,-0.005);
						gmtl::Matrix44f rotMat = gmtl::makeRot<gmtl::Matrix44f>( eulerAngle );
						mNavigator->setCurPos(mNavigator->getCurPos()*rotMat);
					}
					if(angleHorizon<-1) {
						gmtl::EulerAngleXYZf eulerAngle(0,0,0.005);
						gmtl::Matrix44f rotMat = gmtl::makeRot<gmtl::Matrix44f>( eulerAngle );
						mNavigator->setCurPos(mNavigator->getCurPos()*rotMat);
					}

					ancienAngleHorizon=angleHorizon;
				}*/

			vitesseRotation[1]=0;
		}
		if(rotationWandAxeZ>0.2)
			vitesseRotation[1]-=0.2;
		if(rotationWandAxeZ<-0.2)
			vitesseRotation[1]+=0.2;

		//cout << "0 : " << vitesseRotation[0] << "   1 : " << vitesseRotation[1] << "    2 : " << vitesseRotation[2] << endl;
		/*if(!estEnTrainDAvancer)
		  detectionRotationExcessive(vitesseRotation);*/
		//cout << "0 : " << vitesseRotation[0] << "   1 : " << vitesseRotation[1] << "    2 : " << vitesseRotation[2] << endl;

		gmtl::EulerAngleXYZf euler(vitesseRotation[0],vitesseRotation[1],vitesseRotation[2]);
		//cout << euler << endl;
		gmtl::Matrix44f rot_mat = gmtl::makeRot<gmtl::Matrix44f>( euler );

		mNavigator->setRotationalVelocity(rot_mat);



		//cout << "x : " << (gmtl::makeXRot(mNavigator->getCurPos())*360)/(2*M_PI) << "   y : " << (gmtl::makeYRot(mNavigator->getCurPos())*360)/(2*M_PI) << "    z : " << (gmtl::makeZRot(mNavigator->getCurPos())*360)/(2*M_PI) << endl;


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
