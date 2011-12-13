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
#include <osg/LOD>
#include <osgUtil/Simplifier>

#define REZ_DE_CHAUSSE std::string("../model/rdcSimple.osg")
#define ETAGE std::string("../model/etageSimple.osg")
#define TOIT std::string("../model/toitSimple.osg")
#define TROTOIR std::string("../model/trotoir.osg")
#define ROUTE std::string("../model/route.obj")
#define REZ_DE_CHAUSSE_LOW std::string("../model/rdcSimpleL2.obj")
#define ETAGE_LOW std::string("../model/etageSimpleL2.obj")
#define TOIT_LOW std::string("../model/toitSimpleL2.obj")

using namespace std;
using namespace osg;
using namespace osgDB;
using namespace osgUtil;
class ImmeubleAvecFenetre {
private:

	int mNombreEtages;
public:
	static osg::ref_ptr<osg::Node>  rezDeChausse,etage,toit,trotoir,route,rezDeChausseLow,etageLow,toitLow;
	osg::ref_ptr<osg::Group> mImmeuble,mImmeubleLow;
	osg::ref_ptr<osg::Group> mRoute;
	osg::ref_ptr<osg::Group> mEnsemble,mEnsembleLow;
	ref_ptr<LOD> lodEnsemble;
	ImmeubleAvecFenetre() {}

	ImmeubleAvecFenetre(int nombreEtages);

	~ImmeubleAvecFenetre() {}

	osg::ref_ptr<osg::LOD> getNode();

	void placeNodeElement(osg::ref_ptr<osg::Node> element,vector<GLfloat> coordonnees,osg::ref_ptr<osg::Group> noeudAAjouter);

	void construireUnImmeuble();

	int getNombreEtage();

	osg::BoundingBox getBoundingBox();

	int getTaille();

};

#endif /* IMMEUBLEAVECFENETRE_H_ */
