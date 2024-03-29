/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998-2010 by Iowa State University
 *
 * Original Authors:
 *   Allen Bierbaum, Christopher Just,
 *   Patrick Hartling, Kevin Meinert,
 *   Carolina Cruz-Neira, Albert Baker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#include <OsgNavGrab.h>

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


OsgNavGrab::OsgNavGrab(vrj::Kernel* kern, int& argc, char** argv)
   : vrj::OsgApp(kern)
{
   mFileToLoad = std::string("monkeyLightFur/monkeyLightFur.obj");
   mFileToLoad2 = std::string("zebraBowl/zebraBowl.obj");
   mFileToLoad3= std::string("des/des.obj");
   mFileToLoad4 = std::string("monkeyFur/monkeyFur.obj");
   mFileToLoad5 = std::string("monkey/monkeyTex.obj");
}

void OsgNavGrab::latePreFrame()
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

void OsgNavGrab::preFrame()
{
   //vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL) << "------- preFrame ------\n" << vprDEBUG_FLUSH;
   
   vpr::Interval cur_time = mWand->getTimeStamp();
   vpr::Interval diff_time(cur_time-mLastPreFrameTime);
   if (mLastPreFrameTime.getBaseVal() >= cur_time.getBaseVal())
   {  diff_time.secf(0.0f); }

   float time_delta = diff_time.secf();

   mLastPreFrameTime = cur_time;

   // Get wand data
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

   // If we are pressing button 2 then rotate in the direction the wand is
   // pointing.
   if ( mButton2->getData() == gadget::Digital::ON )
   {
      gmtl::EulerAngleXYZf euler( 0.0f, gmtl::makeYRot(mWand->getData()), 0.0f );// Only allow Yaw (rot y)
      gmtl::Matrix44f rot_mat = gmtl::makeRot<gmtl::Matrix44f>( euler );
      mNavigator.setRotationalVelocity(rot_mat);
   } // Make sure to reset the rotational velocity when we stop pressing the button.
   else if(mButton2->getData() == gadget::Digital::TOGGLE_OFF)
   {
      mNavigator.setRotationalVelocity(gmtl::Matrix44f());
   }

   // Get the wand matrix in the units of this application.
   const gmtl::Matrix44f wand_mat(mWand->getData(getDrawScaleFactor()));
   updateGrabbing(wand_mat);
   //récupère la position actuelle du wand après un déplacement
   //gmtl::Matrix44f wand_matNavigator(mNavigator.getCurPos());
   //updateGrabbing(wand_matNavigator);

   rotateObjects();
   // Update the navigation using the time delta between
   mNavigator.update(time_delta);

}

void OsgNavGrab::bufferPreDraw()
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT);
}

void OsgNavGrab::initScene()
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


OsgNavGrab::GrabObject* OsgNavGrab::makeGrabbable(osg::Node* model,
                                                        osg::MatrixTransform* modelPos)
{
   return new GrabObject(model, modelPos, modelPos->getMatrix());
}

//Méthode permettant de faire tourner les objets
void OsgNavGrab::rotateObjects() {
   mVarAngle=0.001;
   mVarAngle2=0.01;
   mVarAngle3=0.002;
   mVarAngle4=0.005;
   mVarAngle5=0.006;
//   mModelTrans->preMult( osg::Matrix::rotate( gmtl::Math::deg2Rad( mVarAngle ), 1.0f, 0.0f, 0.0f) );
   mModelTrans->preMult( osg::Matrix::rotate(mVarAngle, 1.0f, 1.0f, 0.0f) );
   mModelTrans2->preMult( osg::Matrix::rotate(mVarAngle2, 1.0f, 0.0f, 0.0f) );
   mModelTrans3->preMult( osg::Matrix::rotate(mVarAngle3, 0.0f, 1.0f, 1.0f) );
   mModelTrans4->preMult( osg::Matrix::rotate(mVarAngle4, 0.0f, 1.0f, 0.0f) );
   mModelTrans5->preMult( osg::Matrix::rotate(mVarAngle5, 0.0f, 0.0f, 1.0f) );
}

void OsgNavGrab::updateGrabbing(const gmtl::Matrix44f& wandMatrix)
{
   // The navigation matrix is w_M_vw, so invert it for use here.
   const osg::Matrix& nav_mat(mNavTrans->getMatrix());
   osg::Matrix vw_M_w;
   nav_mat.inverse(vw_M_w);
   
   // Transform the wand matrix from real world coordinates into virtual world
   // coordinates.
   osg::Matrix osg_wandMatrix(
            wandMatrix[0][0],wandMatrix[0][1],wandMatrix[0][2],wandMatrix[0][3],
            wandMatrix[1][0],wandMatrix[1][1],wandMatrix[1][2],wandMatrix[1][3],
            wandMatrix[2][0],wandMatrix[2][1],wandMatrix[2][2],wandMatrix[2][3],
            wandMatrix[3][0],wandMatrix[3][1],wandMatrix[3][2],wandMatrix[3][3]);
   const osg::Matrix wand_matrix = vw_M_w * osg_wandMatrix;
   
   //On récupère la position du wand que l'on stocke dans wand_point
   const osg::Vec3 wand_point(wandMatrix[0][3],wandMatrix[1][3],wandMatrix[2][3]);
   
   const osg::Matrix wand_matrix_rowmajor(wandMatrix.mData);
   
   // Only perform the intersection testing when we are not already grabbing
   // an object.
   if ( mGrabbedObj == NULL )
   {
      GrabObject* intersect_obj(NULL);
      // Find the first object--if any--in mObjects with which the wand
      // intersects.
      for ( std::vector<GrabObject*>::iterator o = mObjects.begin();
            o != mObjects.end();
            ++o )
      {
		 //on récupère la boundingbox de la matrice de transformation MatrixTransform
         const osg::BoundingSphere& bbox = (*o)->xformCore->getBound();
         if ( bbox.contains(wand_point) )
         {
            intersect_obj = *o;
            break;
         }
      }

      // If the intersected object changed since the last frame, we need to
      // update things.
      if ( intersect_obj != mIntersectedObj )
      {
         mIntersectedObj = intersect_obj;
      }
   }

   // Enable grabbing only when no other object is currently grabbed, when
   // the wand button is intersecting an object, and when button 1 is pressed.
   if ( mIntersectedObj != NULL && mGrabbedObj == NULL &&
        mButton1->getData() == gadget::Digital::ON )
   {
      mGrabbedObj = mIntersectedObj;
      mGrabbedObj->xformStart.set(mGrabbedObj->xformCore->getMatrix());  // save start matrix
      mGrabbedObj->xformSaved.invert(wand_matrix_rowmajor); // save inverted wand matrix
   }
   // We cannot be grabbing anything unless button 1 is pressed.
   else if ( mButton1->getData() != gadget::Digital::ON )
   {
      mGrabbedObj = NULL;
   }

   // If mGrabbedObj is non-NULL, then we are grabbing the object pointed at
   // by mGrabbedObj.
   if ( mGrabbedObj != NULL )
   {
      osg::Matrix new_xform;
      new_xform.set(mGrabbedObj->xformStart);
      
      //new_xform.set(wandMatrix.mData);
      new_xform.postMult(mGrabbedObj->xformSaved);
      
      new_xform.postMult(wand_matrix_rowmajor);
      
      mGrabbedObj->xformCore->setMatrix(new_xform);
   }
}

void DrawQuad()
{
  glBegin(GL_QUADS);
         glNormal3f (0, 1, 0);

	 glTexCoord2f(0,0);
         glVertex3f (-30,0, 0);

	 glTexCoord2f(1, 0);
         glVertex3f (30,0,0);

	 glTexCoord2f(1,1);
         glVertex3f ( 30,0,30);

	 glTexCoord2f(0, 1);
	 glVertex3f(-30,0,30);

 glEnd();


}

class CustomDrawable: public osg::Drawable
{
   private:

   public:

      CustomDrawable()
      {
      }

      CustomDrawable (const CustomDrawable& pg,
                      const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY)
      { }

      virtual osg::Object* cloneType() const { return new CustomDrawable(); }

      virtual osg::Object* clone(const osg::CopyOp& copyop) const
      { return new CustomDrawable (*this, copyop); }

      virtual void drawImplementation (osg::RenderInfo& renderInfo) const
      {
		osg::ref_ptr<osg::Image> image (osgDB::readImageFile("wood.png"));
		osg::ref_ptr<osg::Texture2D> texture (new osg::Texture2D(image.get()));

		osg::ref_ptr<osg::StateSet> texSS (new osg::StateSet);
		texSS->setTextureAttributeAndModes (0,   // unit
											  texture.get(),
											  osg::StateAttribute::ON);
		DrawQuad();
		 renderInfo.getState()->apply();
      }
};

void OsgNavGrab::myInit()
{
   mVarAngle=0;
   mVarAngle2=0;
   mVarAngle3=0;
   mVarAngle4=0;
   mVarAngle5=0;
   //
   //          /-- mNoNav
   // mRootNode
   //         \-- mNavTrans -- mModelTrans -- --- mModel
   //					    \-- mModelTrans2 /
   //					    \-- mModelTrans3 /
   //					    \-- mModelTrans4 /
   //					    \-- mModelTrans5 /
   //The top level nodes of the tree
   mRootNode = new osg::Group();
   mNoNav    = new osg::Group();
   mNavTrans = new osg::MatrixTransform();


   mNavigator.init();

   mRootNode->addChild( mNoNav );
   mRootNode->addChild( mNavTrans );

   //Load the model
   std::cout << "Attempting to load file: " << mFileToLoad << "... ";
   mModel = osgDB::readNodeFile(mFileToLoad);
   mModel2 = osgDB::readNodeFile(mFileToLoad2);
   mModel3 = osgDB::readNodeFile(mFileToLoad3);
   mModel4 = osgDB::readNodeFile(mFileToLoad4);
   mModel5 = osgDB::readNodeFile(mFileToLoad5);

   std::cout << "done." << std::endl;

   // Transform node for the model
   mModelTrans  = new osg::MatrixTransform();
   mModelTrans2  = new osg::MatrixTransform();
   mModelTrans3  = new osg::MatrixTransform();
   mModelTrans4  = new osg::MatrixTransform();
   mModelTrans5  = new osg::MatrixTransform();
   //This can be used if the model orientation needs to change
   mModelTrans->preMult( osg::Matrix::rotate( gmtl::Math::deg2Rad( -90.0f ), 1.0f, 0.0f, 0.0f) );

   mModelTrans2->preMult( osg::Matrix::rotate( gmtl::Math::deg2Rad( -90.0f ), 1.0f, 0.0f, 0.0f) );
   mModelTrans2->preMult( osg::Matrix::translate(20.0f, 50.0f, 0.0f) );

   mModelTrans3->preMult( osg::Matrix::rotate( gmtl::Math::deg2Rad( -90.0f ), 1.0f, 0.0f, 0.0f) );
   mModelTrans3->preMult( osg::Matrix::translate(-10.0f, 30.0f, 0.0f) );

   mModelTrans4->preMult( osg::Matrix::rotate( gmtl::Math::deg2Rad( -90.0f ), 1.0f, 0.0f, 0.0f) );
   mModelTrans4->preMult( osg::Matrix::translate(50.0f, 0.0f, 20.0f) );

   mModelTrans5->preMult( osg::Matrix::rotate( gmtl::Math::deg2Rad( -90.0f ), 1.0f, 0.0f, 0.0f) );
   mModelTrans5->preMult( osg::Matrix::translate(-20.0f, -10.0f, 20.0f) );
   if(NULL == mModel)
   {
      std::cout << "ERROR: Could not load file: " << mFileToLoad << std::endl;
   }
   else
   {
      // Add model to the transform
      mModelTrans->addChild(mModel); 
      mModelTrans2->addChild(mModel2);
      mModelTrans3->addChild(mModel3);
      mModelTrans4->addChild(mModel4);
      mModelTrans5->addChild(mModel5);
   }
   mObjects.push_back(makeGrabbable(mModel, mModelTrans));
   mObjects.push_back(makeGrabbable(mModel2, mModelTrans2));
   mObjects.push_back(makeGrabbable(mModel3, mModelTrans3));
   mObjects.push_back(makeGrabbable(mModel4, mModelTrans4));
   mObjects.push_back(makeGrabbable(mModel5, mModelTrans5));
   
   // Add the transform to the tree
   mNavTrans->addChild( mModelTrans );
   mNavTrans->addChild( mModelTrans2 );
   mNavTrans->addChild( mModelTrans3 );
   mNavTrans->addChild( mModelTrans4 );
   mNavTrans->addChild( mModelTrans5 );

   osg::ref_ptr<osg::Geode> glObject (new osg::Geode);


   // Finally, add an instance of our wonderful 'CustomDrawable' to the
   // scene graph.
   osg::ref_ptr<CustomDrawable> drawable (new CustomDrawable);
   glObject->addDrawable (drawable.get());
   mRootNode->addChild(glObject);
//   InitialisationSonore();


   // run optimization over the scene graph
   // NOTE: Using the optimizer may cause problems with textures not showing
   // up on all walls.
//   osgUtil::Optimizer optimizer;
//   optimizer.optimize(mRootNode);
}
