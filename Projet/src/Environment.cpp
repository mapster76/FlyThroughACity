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

Environment::Environment(vrj::Kernel* kern, int& argc, char** argv)
   : vrj::OsgApp(kern)
{
}

void Environment::latePreFrame()
{
   gmtl::Matrix44f world_transform;
   // Update the scene graph
   osg::Matrix osg_current_matrix;
   osg_current_matrix.set(world_transform.getData());
   mNavTrans->setMatrix(osg_current_matrix);

   // Finish updating the scene graph.
   vrj::OsgApp::latePreFrame();
}

void Environment::preFrame()
{
   
   vpr::Interval cur_time = mWand->getTimeStamp();
   vpr::Interval diff_time(cur_time-mLastPreFrameTime);

   if (mLastPreFrameTime.getBaseVal() >= cur_time.getBaseVal())
   {  diff_time.secf(0.0f); }

   //float time_delta = diff_time.secf();

   mLastPreFrameTime = cur_time;

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

void drawQuad()
{
	GLfloat size=30;
	glBegin(GL_QUADS);
		glNormal3f (0, 1, 0);

		glTexCoord2f(0,0);
		glVertex3f (-size,0, -size);

		glTexCoord2f(1, 0);
		glVertex3f (size,0,-size);

		glTexCoord2f(1,1);
		glVertex3f ( size,0,size);

		glTexCoord2f(0, 1);
		glVertex3f(-size,0,size);

	glEnd();
}

void drawImmeuble() {
	GLfloat size=5;
	GLfloat height=20;
	glColor3f(0,0,1);
	glBegin(GL_QUADS);
		glNormal3f (0, 1, 0);
		glVertex3f (-size,height, -size);
		glVertex3f (size,height,-size);
		glVertex3f ( size,height,size);
		glVertex3f(-size,height,size);

		glNormal3f (0, 0, -1);
		glVertex3f (-size,0, size);
		glVertex3f (size,0,size);
		glVertex3f ( size,height,size);
		glVertex3f(-size,height,size);

		glNormal3f (0, 0, -1);
		glVertex3f (-size,0, -size);
		glVertex3f (size,0,-size);
		glVertex3f ( size,height,-size);
		glVertex3f(-size,height,-size);

		glNormal3f (-1, 0, 0);
		glVertex3f (size,0, -size);
		glVertex3f (size,0,size);
		glVertex3f ( size,height,size);
		glVertex3f(size,height,-size);

		glNormal3f (1, 0, 0);
		glVertex3f (-size,0, -size);
		glVertex3f (-size,0,size);
		glVertex3f (-size,height,size);
		glVertex3f(-size,height,-size);
	glEnd();
}

void Environment::myInit()
{
   mRootNode = new osg::Group();
   mNavTrans = new osg::MatrixTransform();

   osg::MatrixTransform* mModelSol = new osg::MatrixTransform();
   osg::ref_ptr<osg::Geode> noeudSol (new osg::Geode);
   osg::ref_ptr<CustomDrawable> sol(new CustomDrawable(&drawQuad));
   mModelSol->preMult( osg::Matrix::translate(0.0f, 0.0f, 0.0f) );




   osg::ref_ptr<osg::Geode> noeudImmeuble (new osg::Geode);

   osg::ref_ptr<CustomDrawable> immeuble(new CustomDrawable(&drawImmeuble));
   noeudSol->addDrawable((osg::Drawable*)sol.get());
   noeudImmeuble->addDrawable((osg::Drawable*)immeuble.get());

   mRootNode->addChild(mNavTrans);
   mNavTrans->addChild(mModelSol);
   mModelSol->addChild(noeudSol.get());

   osg::MatrixTransform* mModelImmeuble = new osg::MatrixTransform();
   mModelImmeuble->preMult( osg::Matrix::translate(30.0f, 0.0f, 0.0f) );
   mNavTrans->addChild(mModelImmeuble);
   mModelImmeuble->addChild(noeudImmeuble.get());

   osg::MatrixTransform* mModelImmeuble2 = new osg::MatrixTransform();
   mModelImmeuble2->preMult( osg::Matrix::translate(0.0f, 0.0f, 30.0f) );
   mNavTrans->addChild(mModelImmeuble2);
   mModelImmeuble2->addChild(noeudImmeuble.get());
}
