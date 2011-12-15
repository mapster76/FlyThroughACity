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
	mCurrentMatrix=mCurrentMatrix.identity();
}

void Environment::latePreFrame()
{
	//on applique la matrice de transformation calculée dans navigation
	mNavTrans->setMatrix(mNavigation.getCurrentMatrix());
	vrj::OsgApp::latePreFrame();
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

   mNavigation.gestionGachette(cur_time.getBaseVal());

   mNavigation.gestionBouton2(cur_time.getBaseVal());

   mWorld->gestionBouton1(mButton1);
   mSons.gestionBouton1(mButton1);

   // Get the wand matrix in the units of this application.
   const gmtl::Matrix44f wand_mat(mWand->getData(getDrawScaleFactor()));
   
   // Gestion des collisions
   //collisions(wand_mat);
   // Update the navigation using the time delta between
   mNavigation.update(time_delta);

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

	mNavigation.init(*mWorld,mWand,mHead,mButton0,mButton1,mButton2);

	mSons.jouerAmbiancePluie();

}


