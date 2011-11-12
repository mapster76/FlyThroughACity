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
	osg::ref_ptr<osg::Group>  pRootNode;
	osg::ref_ptr<osg::MatrixTransform> pNavTrans;
	vector< vector<GLfloat> > vElementLocation;
	vector< osg::ref_ptr<osg::Node> > v;
public:
	WorldCreator()
	{
		pRootNode = new osg::Group();
		pNavTrans = new osg::MatrixTransform();
	}


	~WorldCreator()
	{}

	void initialiseWorld() {
		vector<GLfloat> coordonnes;
		coordonnes.resize(3);
		coordonnes[0]=10.0;
		coordonnes[1]=0.0;
		coordonnes[2]=10.0;
		vElementLocation.push_back(coordonnes);
		coordonnes[0]=-10.0;
		vElementLocation.push_back(coordonnes);
		coordonnes[2]=-10.0;
		vElementLocation.push_back(coordonnes);
		coordonnes[0]=10.0;
		vElementLocation.push_back(coordonnes);
	}


	osg::ref_ptr<osg::Geode> createGeodeNode(GLfloat r,GLfloat g,GLfloat b) {
		osg::ref_ptr<osg::Geode> geodeNode (new osg::Geode);
		GLfloat color[3]={r,g,b};
		osg::ref_ptr<CustomDrawable> shape(new Immeuble(5,30,color));
		geodeNode->addDrawable((osg::Drawable*)shape.get());
		return geodeNode;
	}

	void createMap() {
		initialiseWorld();
	}

	void placeNodeElement(osg::ref_ptr<osg::Node> element,vector<GLfloat> coordonnees) {
		osg::ref_ptr<osg::MatrixTransform> mModel = new osg::MatrixTransform();
		mModel->preMult( osg::Matrix::translate(coordonnees[0], coordonnees[1], coordonnees[2]));
		pNavTrans->addChild(mModel);
		mModel->addChild(element.get());
	}

	void generateSceneGraph(osg::ref_ptr<osg::Node> element) {
		for (vector< vector<GLfloat> >::iterator pLocation = vElementLocation.begin(); pLocation != vElementLocation.end(); ++pLocation) {
			placeNodeElement(element,*pLocation);
		}
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

		pRootNode->addChild(pNavTrans);
		pNavTrans->addChild(mModelSol);
		mModelSol->addChild(noeudSol.get());

		createMap();
		generateSceneGraph(noeudImmeuble);

		rootNode=pRootNode;
		navTrans=pNavTrans;
	}

};


#endif /* WORLDCREATOR_H_ */
