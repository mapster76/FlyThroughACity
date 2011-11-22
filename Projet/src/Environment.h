#ifndef _ENVIRONMENT
#define _ENVIRONMENT

#include <vrj/vrjConfig.h>

#include <iostream>
#include <iomanip>
#include <math.h>

#include <vrj/Draw/OGL/GlApp.h>
#include <gadget/Type/Position/PositionUnitConversion.h>

#include <gadget/Type/PositionInterface.h>
#include <gadget/Type/AnalogInterface.h>
#include <gadget/Type/DigitalInterface.h>

//OSG  includes
#include <osg/Matrix>
#include <osg/Transform>
#include <osg/MatrixTransform>
#include <osgUtil/SceneView>

#include <vrj/Draw/OSG/OsgApp.h>
#include "world/WorldCreator.h"
#include "nav.h"

/**
 * Demonstration Open Scene Graph application class
 */
class Environment : public vrj::OsgApp
{
public:
   Environment(vrj::Kernel* kern, int& argc, char** argv);

   virtual ~Environment()
   {
	   delete mWorld;
      /* Do nothing. */ ;
   }

   // Execute any initialization needed before the API is started<BR><BR>
   //
   // This is called once before OGL is initialized
   virtual void initScene();

   void myInit();

   virtual osg::Group* getScene()
   {
      return mRootNode;
   }

   virtual void configSceneView(osgUtil::SceneView* newSceneViewer)
   {
      vrj::OsgApp::configSceneView(newSceneViewer);
      /*newSceneViewer->getLight()->setAmbient(osg::Vec4(0.f,0.0f,0.0f,1.0f));
      newSceneViewer->getLight()->setDiffuse(osg::Vec4(0.0f,0.0f,0.0f,1.0f));
      newSceneViewer->getLight()->setSpecular(osg::Vec4(.0f,.0f,.0f,1.0f));*/
   }

   void updateNavigation();

   void ralentirPuisSAreter(long tempsCourant);
   void seDeplacer();
   void gestionGachette();
   void gestionBouton2(long tempsCourant);
   void avancerOuArreter();

   void bufferPreDraw();

   // ----- Drawing Loop Functions ------
   //
   //  The drawing loop will look similar to this:
   //
   //  while (drawing)
   //  {
   //        preFrame();
   //       <Application Data Syncronization>
   //        latePreFrame();
   //       draw();
   //        intraFrame();     // Drawing is happening while here
   //       sync();
   //        postFrame();      // Drawing is now done
   //
   //       UpdateTrackers();
   //  }
   //------------------------------------

   //: Function called after tracker update but before start of drawing<BR><BR>
   //
   // called once before every frame.
   virtual void preFrame();

   // Function called after ApplicationData syncronization but before draw()
   virtual void latePreFrame();
   
   //: Function called after drawing has been triggered but BEFORE it completes<BR><BR>
   //
   // called once during each frame
   virtual void intraFrame()
   {
      // Put your intra frame computations here.
   }

   //: Function called before updating trackers but after the frame is drawn<BR><BR>
   //
   // called once after every frame
   virtual void postFrame()
   {
      // Put your post frame computations here.
   }

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
   long tempsPourArret;
   gmtl::Matrix44f  mNavMatrix;
   osg::ref_ptr<osg::Group>  mRootNode;
   osg::ref_ptr<osg::MatrixTransform> mNavTrans;
   vpr::Interval mLastPreFrameTime;   /**< Time of the start of the last preframe */
   WorldCreator* mWorld;
   OsgNavigator  mNavigator;

public:
   gadget::PositionInterface  mWand;     // the Wand
   gadget::PositionInterface  mHead;     // the head
   gadget::DigitalInterface   mButton0;
   gadget::DigitalInterface   mButton1;
   gadget::DigitalInterface   mButton2;
   gadget::DigitalInterface   mButton3;
   gadget::DigitalInterface   mButton4;
   gadget::DigitalInterface   mButton5;
};


#endif
