#ifndef WORLDCREATOR_H_
#define WORLDCREATOR_H_

#include <ImmeubleAvecFenetre.h>
#include <osg/Geode>
#include <osg/PositionAttitudeTransform>
#include <osgUtil/Optimizer>
#include <osg/Math>
#include <osg/MatrixTransform>
#include <osg/Material>
#include <vector>
#include "world/CustomDrawable.h"
#include <gadget/Type/DigitalInterface.h>
#include <osg/ShapeDrawable>
#include "world/ImmeublePlat.h"
#include "world/Sol.h"
#include "util.h"
#include <utility>
#include <string>
#include <map>
#include "Skybox.h"
#include<osg/Light>
#include<osg/LightSource>

#define RAYON_MAX_VILLE 500
#define ESPACE_ENTRE_IMMEUBLE 26
using namespace std;

class WorldCreator {

private:


protected:
public:
	osg::ref_ptr<osg::Group>  pRootNode;
	osg::ref_ptr<osg::MatrixTransform> pNavTrans;
	map < GLfloat,ImmeubleAvecFenetre > immeubleParTaille;
	map < vector<GLfloat> , ImmeubleAvecFenetre > laCarte;
	map < GLfloat ,  osg::Geode* > laCarteBox;
	map < vector<GLfloat> , osg::BoundingBox > lesBoundingBoxes;
	osg::ref_ptr<Skybox> skybox;
	vector<string> vEmplacementImage;
	vector<string>::iterator itEmplacementImage;
	osg::ref_ptr<osg::Geode> noeudSkybox;
	/**
	 * Cette fonction initialise le graphe de scene et ajoute le sol.
	 */
	void initialiseWorld();

	// Accesseur 
	map < vector<GLfloat> , ImmeubleAvecFenetre > getCarte();

	/**
	 * Cette fonction cree un nouvel immeuble et l'ajoute a la map qui repertorie les immeubles par taille.
	 * return un pointeur intelligent vers un noeud de type Geode permettant de dessiner des fonction opengl
	 */
	osg::ref_ptr<osg::Geode> createImmeublePlatNode(GLfloat r,GLfloat g,GLfloat b,osg::Vec3f coordonnees,GLfloat size, GLfloat height);
	/**
	 * Cette fonction verifie si l'immeuble avec la hauteur donnée est déjà présent dans la map immeubleParTaille
	 */
	bool noeudImmeubleExiste(GLfloat hauteur);

	/**
	 * Cette fonction verifie si un immeuble n'a pas déjà été tracé à l'emplacement donné
	 */
	bool estUnEmplacementVide(vector<GLfloat> coordonnes);

	/**
	 * cette fonction ajoute un immeuble a la map laCarte sauf si l'immeuble est déjà présent à l'emplacement donné elle n'ajoute rien
	 * De plus elle génére un immeuble d'une hauteur différente. Si la hauteur de l'immeuble généré aléatoirement n'existe pas il va l'ajouter au graphe de scene par l'appel de la fonction creatImmeubleNode
	 */
	void ajouterImmeubleALaCarte(vector<GLfloat> coordonnes);

	/**
	 * ajoute des immeuble tout autour de la position de l'immeuble courant si un immeuble est déjà présent à cette position il n'en ajoutera pas
	 */
	void ajouterImmeubleAutourPosition(GLfloat x, GLfloat y);

	/**
	 * dessine tout un quartier
	 */
	void dessinnerUnQuartier(GLfloat xImmeuble, GLfloat yImmeuble,GLfloat distance);

	/**
	 * fonction qui cree la carte et place tout les immeuble dessus
	 */
	void createMap();

	/**
	 * Ajoute un element au graphe de scene le noeud peut etre de type geode ou autre
	 */
	void placeNodeElement(osg::ref_ptr<osg::Node> element,vector<GLfloat> coordonnees);

	/**
	 * Genere le graphe de scene a partir de ce qui est contenu dans la carte
	 */
	void generateSceneGraph();

	/**
	 * Ajoute des lumieres à la scenes
	 */
	void illuminateScene();

	osg::ref_ptr<osg::Node> createImmeubleAvecFenetreNode(GLfloat nombreEtage);

	WorldCreator()
	{
		pRootNode = new osg::Group();
		pNavTrans = new osg::MatrixTransform();
	}

	void gestionBouton3(gadget::DigitalInterface mButton);

	~WorldCreator()
	{}

	void drawWorld(osg::ref_ptr<osg::Group> &rootNode,osg::ref_ptr<osg::MatrixTransform> &navTrans);

	void updateBoundingBox();

};


#endif /* WORLDCREATOR_H_ */
