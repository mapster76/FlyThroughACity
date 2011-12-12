#ifndef IMMEUBLEAVECFENETRE_H_
#define IMMEUBLEAVECFENETRE_H_
#include <osg/Geode>
#include <osgUtil/Optimizer>
#include <osg/Math>
#include <osg/MatrixTransform>
#include <vector>
#include <iostream>
#include <util.h>
#include <string>
#include <osgDB/ReadFile>
#include <unistd.h>
#include <gmtl/Math.h>
#include <Sol.h>
#include <osg/Light>
#include <osg/ComputeBoundsVisitor>
#include <osg/LightSource>
#include <osg/StateSet>
#include <osg/CullFace>

#define REZ_DE_CHAUSSE std::string("../model/rdc.osg")
#define ETAGE std::string("../model/etageSimple.osg")
#define TOIT std::string("../model/toitSimple.osg")
#define TROTOIR std::string("../model/trotoir.osg")
#define ROUTE std::string("../model/route.obj")

using namespace std;

class ImmeubleAvecFenetre {
private:

	int mNombreEtages;
public:
	static osg::ref_ptr<osg::Node>  rezDeChausse,etage,toit,trotoir,route;
	osg::ref_ptr<osg::Group> mImmeuble;
	osg::ref_ptr<osg::Group> mRoute;
	osg::ref_ptr<osg::Group> mEnsemble;

	ImmeubleAvecFenetre() {}

	ImmeubleAvecFenetre(int nombreEtages);

	~ImmeubleAvecFenetre() {}

	osg::ref_ptr<osg::Group> getNode();

	void placeNodeElement(osg::ref_ptr<osg::Node> element,vector<GLfloat> coordonnees,osg::ref_ptr<osg::Group> noeudAAjouter);

	void construireUnImmeuble();

	int getNombreEtage();

	osg::BoundingBox getBoundingBox();

	int getTaille();

};

#endif /* IMMEUBLEAVECFENETRE_H_ */
