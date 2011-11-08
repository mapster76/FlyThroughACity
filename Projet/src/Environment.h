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

/**
 * Demonstration Open Scene Graph application class
 */
class Environment : public vrj::OsgApp
{
public:
   Environment(vrj::Kernel* kern, int& argc, char** argv);

   virtual ~Environment()
   {
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

      newSceneViewer->getLight()->setAmbient(osg::Vec4(0.3f,0.3f,0.3f,1.0f));
      newSceneViewer->getLight()->setDiffuse(osg::Vec4(0.9f,0.9f,0.9f,1.0f));
      newSceneViewer->getLight()->setSpecular(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
   }

   void updateNavigation();

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
   gmtl::Matrix44f   mNavMatrix;
   osg::Group*  mRootNode;
   osg::MatrixTransform* mNavTrans;
   vpr::Interval           mLastPreFrameTime;   /**< Time of the start of the last preframe */


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
