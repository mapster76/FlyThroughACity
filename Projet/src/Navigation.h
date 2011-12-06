#ifndef NAVIGATION_H_
#define NAVIGATION_H_

#include "nav.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <gadget/Type/Position/PositionUnitConversion.h>

#include <gadget/Type/PositionInterface.h>
#include <gadget/Type/AnalogInterface.h>
#include <gadget/Type/DigitalInterface.h>
#include <osg/Matrix>
#include <osg/Transform>
#include <osg/MatrixTransform>

using namespace std;

class Navigation {
public:
	Navigation();
	virtual ~Navigation();
	void updateNavigation();
	void init(gadget::PositionInterface &wand,gadget::PositionInterface &head,
			gadget::DigitalInterface &button0,gadget::DigitalInterface &button1,gadget::DigitalInterface &button2);
	void ralentirPuisSAreter(long tempsCourant);
	void accelerer(long tempsCourant);
	void seDeplacer();
	void gestionGachette(long tempsCourant);
	void gestionBouton2(long tempsCourant);
	void avancerOuArreter();
	void deccelerer(long tempsCourant);
	void droitDeTourner();
	//float* getVecteurPosition();
	void detectionRotationExcessive(float*);
	void stabiliserCamera(float incrementRadian,float angleHorizon);
	void update(float time_delta);
	osg::Vec3 getTranslation();
	osg::Vec3 getRotation();
	osg::Matrix getCurrentMatrix();

	/**
	* Returns the scale factor for this application.  For this sample, we
	* are handling everything in feet.
	*/
	virtual float getDrawScaleFactor()
	{
	 return gadget::PositionUnitConversion::ConvertToFeet;
	}

private:

   bool estEnTrainDAvancer;
   bool peutTourner;
   long tempsPourArret;
   long tempsPourAcceleration;
   long tempsPourDecceleration;
   long estEnTrainDAccelerer;
   long estEnTrainDeDecelerer;
   bool estStabilise,estInferieur,estSuperieur;
   osg::Vec3 mTranslation;
   osg::Vec3 mRotation;
   osg::Matrix mCurrentMatrix;
   osg::Matrix H;
   osg::Matrix previousT,previousR;

   cluster::UserData< NavData >  mNavigator;

public:
   gadget::PositionInterface  mWand;     // the Wand
   gadget::PositionInterface  mHead;     // the head
   gadget::DigitalInterface   mButton0;
   gadget::DigitalInterface   mButton1;
   gadget::DigitalInterface   mButton2;
};

#endif /* NAVIGATION_H_ */
