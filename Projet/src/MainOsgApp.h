#ifndef _MAIN_OSG_APP
#define _MAIN_OSG_APP

#include <vrj/vrjConfig.h>
#include "DonneesNavigation.h"
#include "Navigation.h"
#include <vrj/Draw/OGL/GlApp.h>
#include <gadget/Type/Position/PositionUnitConversion.h>
#include <gadget/Type/PositionInterface.h>
#include <gadget/Type/AnalogInterface.h>
#include <gadget/Type/DigitalInterface.h>
#include <osg/Matrix>
#include <osg/Transform>
#include <osg/MatrixTransform>
#include <osgUtil/SceneView>
#include <Sons.h>
#include <vrj/Draw/OSG/OsgApp.h>
#include "world/WorldCreator.h"


class MainOsgApp : public vrj::OsgApp
{
public:
   MainOsgApp(vrj::Kernel* kern, int& argc, char** argv);

   virtual ~MainOsgApp()
   {
	   delete mWorld;
   }

   // Execute any initialization needed before the API is started<BR><BR>
   //
   // This is called once before OGL is initialized
   virtual void initScene();

   /**
    * Méthode permettand de faire des appel pour initialiser tous l'environnement
    */
   void myInit();

   /**
    * Méthode qui doit renvoyer le noeud racine du graphe de scène à VRJuggler
    */
   virtual osg::Group* getScene()
   {
      return mRootNode;
   }

   /**
    * Permet de paramaétrer le sceneView (la caméra) qui est ensuite géré par
    * VRJuggler
    */
   virtual void configSceneView(osgUtil::SceneView* newSceneViewer)
   {
      vrj::OsgApp::configSceneView(newSceneViewer);
      //On désactive la LIGHT0 activé par défaut
      newSceneViewer->getLight()->setAmbient(osg::Vec4(0.0f,0.0f,0.0f,1.0f));
      newSceneViewer->getLight()->setDiffuse(osg::Vec4(0.0f,0.0f,0.0f,1.0f));
      newSceneViewer->getLight()->setSpecular(osg::Vec4(.0f,.0f,.0f,1.0f));
   }

   void bufferPreDraw();

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


 private : 
   gmtl::Matrix44f  mNavMatrix;
   osg::ref_ptr<osg::Group>  mRootNode;
   osg::ref_ptr<osg::MatrixTransform> mNavTrans;
   vpr::Interval mLastPreFrameTime;   /**< Time of the start of the last preframe */
   WorldCreator* mWorld;
   Sons mSons;
   //OsgNavigator  mNavigator;
   osg::Matrix mCurrentMatrix;
   Navigation mNavigation;
   double distance;

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
