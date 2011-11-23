#include <Environment.h>

#include <osg/Math>
#include <osg/Geode>
#include <osg/Material>
#include <osg/Vec3>
#include <osgUtil/Optimizer>
#include <osgDB/ReadFile>

#include <gmtl/Vec.h>
#include <gmtl/Coord.h>
#include <gmtl/Xforms.h>
#include <gmtl/Math.h>
#include <math.h>
#include <string>

#include "world/CustomDrawable.h"
#include "world/ImmeublePlat.h"
#include "world/Sol.h"


Environment::Environment(vrj::Kernel* kern, int& argc, char** argv)
   : vrj::OsgApp(kern)
{
	mWorld=new WorldCreator();
	estEnTrainDAvancer = false;
	tempsPourArret = 0;
	tempsPourAcceleration=0;
	tempsPourDecceleration=0;
	peutTourner = false;
	estEnTrainDAccelerer=false;
	estEnTrainDeDecelerer=false;
}

void Environment::latePreFrame()
{
   gmtl::Matrix44f world_transform;
   gmtl::invertFull(world_transform, mNavigator.getCurPos());
   // Update the scene graph
   osg::Matrix osg_current_matrix;
   osg_current_matrix.set(world_transform.getData());
   mNavTrans->setMatrix(osg_current_matrix);
   // Finish updating the scene graph.
   vrj::OsgApp::latePreFrame();
}

void augmenterVitesse(float &vitesseAAccelerer) {

	vitesseAAccelerer*=1.05;
}

void Environment::accelerer(long tempsCourant) { 
	int seuilMaximal = 40;
	if(estEnTrainDAvancer) {
		if(!estEnTrainDAccelerer) {
			estEnTrainDAccelerer=true;
			estEnTrainDeDecelerer=false;
		}
		if(tempsPourAcceleration==0)
			tempsPourAcceleration=tempsCourant;

		gmtl::Vec3f direction; // Choix de la vitesse


		gmtl::Vec3f Zdir = mNavigator.getVelocity();
		float* vitesse=Zdir.getData();
		if(tempsCourant-tempsPourAcceleration>20000) {

			if(sqrt(vitesse[0]*vitesse[0]+vitesse[1]*vitesse[1]+vitesse[2]*vitesse[2])<seuilMaximal) {
				cout << "Acceleration "<< endl;
			  augmenterVitesse(vitesse[0]);
			  augmenterVitesse(vitesse[1]);
			  augmenterVitesse(vitesse[2]);
			  cout << "0 " << vitesse[0] << " 1 " << vitesse[1] << " 2 " << vitesse[2] << endl;
			  Zdir.set(vitesse);
			  mNavigator.setVelocity(Zdir);

			}
			tempsPourAcceleration=0;
		}

	}

}



void ralentir(float &vitesseARalentir) {

	if(vitesseARalentir>=-1 && vitesseARalentir<=1) {
	  vitesseARalentir=0;
	} else {
	  if(vitesseARalentir<-1) {
		  vitesseARalentir+=1;
	  }
	  if(vitesseARalentir>1) {
		  vitesseARalentir-=1;
	  }
	}
}

void Environment::deccelerer(long tempsCourant) {
	int seuilMinimal = 10;
		if(estEnTrainDAvancer && estEnTrainDeDecelerer) {

			if(tempsPourDecceleration==0)
				tempsPourDecceleration=tempsCourant;


			gmtl::Vec3f Zdir = mNavigator.getVelocity();
			float* vitesse=Zdir.getData();
			if(tempsCourant-tempsPourDecceleration>40000) {

				if(sqrt(vitesse[0]*vitesse[0]+vitesse[1]*vitesse[1]+vitesse[2]*vitesse[2])>seuilMinimal) {
				  cout << "decellere" << endl;
				  ralentir(vitesse[0]);
				  ralentir(vitesse[1]);
				  ralentir(vitesse[2]);
				  cout << "0 " << vitesse[0] << " 1 " << vitesse[1] << " 2 " << vitesse[2] << endl;
				  Zdir.set(vitesse);
				  mNavigator.setVelocity(Zdir);

				} else {
					cout << "fin Deceleration" << endl;
					estEnTrainDeDecelerer=false;
				}
				tempsPourDecceleration=0;
			}

		}
}


void Environment::ralentirPuisSAreter(long tempsCourant)
{
	if(!estEnTrainDAvancer) {
		if(tempsPourArret==0)
			tempsPourArret=tempsCourant;


		gmtl::Vec3f direction;

		gmtl::Vec3f Zdir = mNavigator.getVelocity();
		float* vitesse=Zdir.getData();
		if(tempsCourant-tempsPourArret>200000) {

			ralentir(vitesse[0]);
			ralentir(vitesse[1]);
			ralentir(vitesse[2]);
		  Zdir.set(vitesse);
		  mNavigator.setVelocity(Zdir);
		  tempsPourArret=tempsCourant;
		}
		if(vitesse[0]==0 && vitesse[1]==0 && vitesse[2]==0)
			tempsPourArret=0;

	}
}

void Environment::droitDeTourner() {
  if(!estEnTrainDAvancer && !peutTourner)
      peutTourner = true;
}

void Environment::seDeplacer()
{
	if(estEnTrainDAvancer && !estEnTrainDAccelerer && !estEnTrainDeDecelerer) {
		gmtl::Matrix44f wandMatrix = mWand->getData(getDrawScaleFactor());

		gmtl::Vec3f direction; // Choix de la vitesse
		gmtl::Vec3f Zdir = gmtl::Vec3f(0.0f, 0.0f, -10.0f);
		gmtl::xform(direction, wandMatrix, Zdir);

		mNavigator.setVelocity(direction);
	}
	if(peutTourner) {
		float vitesseRotationX=gmtl::makeXRot(mWand->getData());
		float vitesseRotationY=gmtl::makeYRot(mWand->getData());
		float vitesseRotationZ=gmtl::makeZRot(mWand->getData());
		gmtl::EulerAngleXYZf euler(vitesseRotationX,vitesseRotationY,vitesseRotationZ);
		gmtl::Matrix44f rot_mat = gmtl::makeRot<gmtl::Matrix44f>( euler );
		mNavigator.setRotationalVelocity(rot_mat);
	}

}

void Environment::avancerOuArreter(){

  if(!estEnTrainDAvancer) {
	  droitDeTourner();
      estEnTrainDAvancer = true;
  } else {
      estEnTrainDAvancer = false;
  }
}


void Environment::gestionBouton2(long tempsCourant)
{
  if (mButton2->getData() == gadget::Digital::TOGGLE_ON){
	  avancerOuArreter();
  }
  seDeplacer();
  ralentirPuisSAreter(tempsCourant);
}

void Environment::gestionGachette(long tempsCourant) {

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


void Environment::preFrame()
{
   
   vpr::Interval cur_time = mWand->getTimeStamp();
   vpr::Interval diff_time(cur_time-mLastPreFrameTime);

   if (mLastPreFrameTime.getBaseVal() >= cur_time.getBaseVal())
   {  diff_time.secf(0.0f); }

   float time_delta = diff_time.secf();
   mLastPreFrameTime = cur_time;

   // Get wand data

   gestionGachette(cur_time.getBaseVal());

   gestionBouton2(cur_time.getBaseVal());

   // Get the wand matrix in the units of this application.
   const gmtl::Matrix44f wand_mat(mWand->getData(getDrawScaleFactor()));
   // Update the navigation using the time delta between
   mNavigator.update(time_delta);


}

void Environment::bufferPreDraw()
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT);
}

void Environment::initScene()
{
   // Initialize devices
   const std::string wand("VJWand");
   const std::string vjhead("VJHead");
   const std::string but0("VJButton0");
   const std::string but1("VJButton1");
   const std::string but2("VJButton2");
   const std::string but3("VJButton3");
   const std::string but4("VJButton4");
   const std::string but5("VJButton5");

   mWand.init(wand);
   mHead.init(vjhead);
   mButton0.init(but0);
   mButton1.init(but1);
   mButton2.init(but2);
   mButton3.init(but3);
   mButton4.init(but4);
   mButton5.init(but5);

   myInit();

}

void Environment::myInit()
{
	mWorld->drawWorld(mRootNode,mNavTrans);
	mNavigator.init();


}
