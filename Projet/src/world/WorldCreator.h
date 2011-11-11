#ifndef WORLDCREATOR_H_
#define WORLDCREATOR_H_

#include <osg/Geode>
#include <osgUtil/Optimizer>
#include <osg/Math>
#include <osg/Material>
#include <vector>
#include "world/CustomDrawable.h"
#include "world/Immeuble.h"
#include "world/Sol.h"

using namespace std;

class WorldCreator {
private:
	osg::ref_ptr<osg::Group>  mRootNode;
	osg::ref_ptr<osg::MatrixTransform> mNavTrans;
	vector< osg::ref_ptr<CustomDrawable> > mElementsOfWorld;
public:
	WorldCreator()
	{
		mRootNode = new osg::Group();
		mNavTrans = new osg::MatrixTransform();
	}


	~WorldCreator()
	{}

	void initialiseWorld() {

	}

	void placeGeodeElement(osg::ref_ptr<osg::Geode> element,GLfloat x,GLfloat y,GLfloat z) {
		osg::ref_ptr<osg::MatrixTransform> mModel = new osg::MatrixTransform();
		mModel->preMult( osg::Matrix::translate(x, y, z) );
		mNavTrans->addChild(mModel);
		mModel->addChild(element.get());
	}

	void drawWorld(osg::ref_ptr<osg::Group> &rootNode,osg::ref_ptr<osg::MatrixTransform> &navTrans) {
		osg::MatrixTransform* mModelSol = new osg::MatrixTransform();
		osg::ref_ptr<osg::Geode> noeudSol (new osg::Geode);
		GLfloat color[3]={0.5,0.5,0.5};
		osg::ref_ptr<CustomDrawable> sol(new Sol(40,color));
		noeudSol->addDrawable((osg::Drawable*)sol.get());
		//mModelSol->preMult( osg::Matrix::translate(0.0f, 0.0f, 0.0f));


		osg::ref_ptr<osg::Geode> noeudImmeuble (new osg::Geode);
		GLfloat color2[3]={0,0,1};
		osg::ref_ptr<CustomDrawable> immeuble(new Immeuble(5,30,color2));
		noeudImmeuble->addDrawable((osg::Drawable*)immeuble.get());

		mRootNode->addChild(mNavTrans);
		mNavTrans->addChild(mModelSol);
		mModelSol->addChild(noeudSol.get());

		placeGeodeElement(noeudImmeuble,10.0f,0,10.0f);

		placeGeodeElement(noeudImmeuble,-10.0f,0,10.0f);

		placeGeodeElement(noeudImmeuble,10.0f,0,-10.0f);

		placeGeodeElement(noeudImmeuble,-10.0f,0,-10.0f);

		rootNode=mRootNode;
		navTrans=mNavTrans;
	}

};


#endif /* WORLDCREATOR_H_ */
