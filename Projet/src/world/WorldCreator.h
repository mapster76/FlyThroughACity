#ifndef WORLDCREATOR_H_
#define WORLDCREATOR_H_

#include <osg/Geode>
#include <osgUtil/Optimizer>
#include <osg/Math>
#include <osg/MatrixTransform>
#include <osg/Material>
#include <vector>
#include "world/CustomDrawable.h"
#include "world/Immeuble.h"
#include "world/Sol.h"
#include "util.h"
#include <utility>
#include <map>

#define RAYON_MAX_VILLE 100
#define ESPACE_ENTRE_IMMEUBLE 20
#define COTE_IMMEUBLE 7

using namespace std;

class WorldCreator {
private:


public:
	WorldCreator()
	{
		pRootNode = new osg::Group();
		pNavTrans = new osg::MatrixTransform();
	}

	osg::ref_ptr<osg::Group>  pRootNode;
	osg::ref_ptr<osg::MatrixTransform> pNavTrans;
	map < GLfloat,osg::ref_ptr<osg::Geode> > immeubleParTaille;
	map< vector<GLfloat> , osg::ref_ptr<osg::Geode> > laCarte;

	~WorldCreator()
	{}

	void initialiseWorld();


	osg::ref_ptr<osg::Geode> createImmeubleNode(GLfloat r,GLfloat g,GLfloat b,GLfloat size, GLfloat height);


	vector<GLfloat> setCoordonnes(GLfloat x,GLfloat z,GLfloat y);

	bool noeudImmeubleExiste(GLfloat hauteur);

	bool estUnEmplacementVide(vector<GLfloat> coordonnes);

	void ajouterImmeubleALaCarte(vector<GLfloat> coordonnes);

	void ajouterImmeubleAutourPosition(GLfloat x, GLfloat y);

	void dessinnerUnQuartier(GLfloat xImmeubleQuadrant, GLfloat yImmeubleQuadrant,GLfloat distance);

	void createMap();

	void placeNodeElement(osg::ref_ptr<osg::Node> element,vector<GLfloat> coordonnees);

	void generateSceneGraph();



	void drawWorld(osg::ref_ptr<osg::Group> &rootNode,osg::ref_ptr<osg::MatrixTransform> &navTrans);

};


#endif /* WORLDCREATOR_H_ */
