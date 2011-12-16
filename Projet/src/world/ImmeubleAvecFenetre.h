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
#define LAMPADAIRE std::string("../model/lampadaireCarre.osg")
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
	osg::ref_ptr<osg::Group> mImmeuble,mImmeubleLow;
	osg::ref_ptr<osg::Group> mRoute;
	osg::ref_ptr<osg::Group> mEnsemble,mEnsembleLow,mEnsembleSansLamp,mEmptyNode;
	ref_ptr<LOD> lodEnsemble;

	/**
	 * permet de placer un noeud dans le graphe de scene de l'immeuble
	 */
	void placeNodeElement(osg::ref_ptr<osg::Node> element,vector<GLfloat> coordonnees,osg::ref_ptr<osg::Group> noeudAAjouter);

	/**
	 * Permet de placer des lampadaires
	 */
	void placeNodeLampadaire(osg::ref_ptr<osg::Node> element,vector<GLfloat> coordonnees,osg::ref_ptr<osg::Group> noeudAAjouter,float rotationY);

public:
	static osg::ref_ptr<osg::Node>  rezDeChausse,etage,toit,trotoir,route,lampadaire,rezDeChausseLow,etageLow,toitLow;

	/**
	 * Constructeur par défaut pour qu'il puisse etre mis dans un vector
	 */
	ImmeubleAvecFenetre() {}

	/**
	 * Constructeur normal qui permet d'initialiser l'immeuble dont les shaders
	 * et spécifié sont nombre d'étage
	 */
	ImmeubleAvecFenetre(int nombreEtages);

	/**
	 * destructeur rien à faire
	 */
	~ImmeubleAvecFenetre() {}

	/**
	 * Permet de retourner le noeud représentant l'immeuble
	 */
	osg::ref_ptr<osg::LOD> getNode();

	/**
	 * permet de construire l'immeuble
	 */
	void construireUnImmeuble();

	/**
	 * retourne le nombre de l'étage donné à l'immeuble
	 */
	int getNombreEtage();

	/**
	 * retourne la BoundingBox associé à l'immeuble
	 */
	osg::BoundingBox getBoundingBox();

	/**
	 * retourne la taille estimée de la BoundingBox
	 */
	int getTaille();

};

#endif /* IMMEUBLEAVECFENETRE_H_ */
