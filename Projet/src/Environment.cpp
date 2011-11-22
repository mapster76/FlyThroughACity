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

#include <string>

#include "world/CustomDrawable.h"
#include "world/ImmeublePlat.h"
#include "world/Sol.h"


Environment::Environment(vrj::Kernel* kern, int& argc, char** argv)
   : vrj::OsgApp(kern)
{
	mWorld=new WorldCreator();
	estEnTrainDAvancer=false;
	tempsPourArret=0;
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


void Environment::mettreVitesseInitiale()
{

    gmtl::Matrix44f wandMatrix = mWand->getData(getDrawScaleFactor());

    gmtl::Vec3f direction; // Choix de la vitesse
    gmtl::Vec3f Zdir = gmtl::Vec3f(0.0f, 0.0f, -10.0f);
    gmtl::xform(direction, wandMatrix, Zdir);
    //mNavigator.setVelocity(gmtl::Vec3f(0.2, 0.0, 0.0));
    mNavigator.setVelocity(direction);

}

void Environment::avancerOuArreter(){
    if(estEnTrainDAvancer)
      estEnTrainDAvancer = false;
    else
      estEnTrainDAvancer = true;
}


void Environment::gestionBouton2(long tempsCourant)
{
  if (mButton2->getData() == gadget::Digital::TOGGLE_ON){
	  if(!estEnTrainDAvancer) {
	       estEnTrainDAvancer = true;
	       mettreVitesseInitiale();
	  } else {
	       estEnTrainDAvancer = false;
	  }

  }
  ralentirPuisSAreter(tempsCourant);
}

void Environment::gestionGachette()
{

  gmtl::Matrix44f wandMatrix = mWand->getData(getDrawScaleFactor());

   if ( mButton0->getData() == gadget::Digital::ON )
   {
      gmtl::Vec3f direction;
      gmtl::Vec3f Zdir = gmtl::Vec3f(0.0f, 0.0f, -10.0f);
      gmtl::xform(direction, wandMatrix, Zdir);
      mNavigator.setVelocity(direction);
   }  // Make sure to reset the velocity when we stop pressing the button.

   else if ( mButton0->getData() == gadget::Digital::TOGGLE_OFF)
   {
      mNavigator.setVelocity(gmtl::Vec3f(0.0, 0.0, 0.0));
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

   gestionGachette();

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
