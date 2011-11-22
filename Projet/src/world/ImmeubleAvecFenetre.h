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


#define REZ_DE_CHAUSSE std::string("../model/rdc.obj")
#define ETAGE std::string("../model/etage.obj")
#define TOIT std::string("../model/toit.obj")

using namespace std;

class ImmeubleAvecFenetre {
private:
	osg::ref_ptr<osg::Node>  rezDeChausse,etage,toit;
	int mNombreEtages;
public:
	ImmeubleAvecFenetre(int nombreEtages);

	~ImmeubleAvecFenetre() {}


	void placeNodeElement(osg::ref_ptr<osg::Node> element,vector<GLfloat> coordonnees,osg::ref_ptr<osg::MatrixTransform> pNavTrans);

	osg::ref_ptr<osg::Group> construireUnImmeuble();

	int getNombreEtage();
};

#endif /* IMMEUBLEAVECFENETRE_H_ */
