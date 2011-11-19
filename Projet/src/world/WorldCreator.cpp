
#include <WorldCreator.h>

void WorldCreator::initialiseWorld() {
	osg::MatrixTransform* mModelSol = new osg::MatrixTransform();
	osg::ref_ptr<osg::Geode> noeudSol (new osg::Geode);
	GLfloat color[3]={0.5,0.5,0.5};
	osg::ref_ptr<CustomDrawable> sol(new Sol(40,color));
	noeudSol->addDrawable((osg::Drawable*)sol.get());

	pRootNode->addChild(pNavTrans);
	pNavTrans->addChild(mModelSol);
	mModelSol->addChild(noeudSol.get());
}


void WorldCreator::drawWorld(osg::ref_ptr<osg::Group> &rootNode,osg::ref_ptr<osg::MatrixTransform> &navTrans) {
	initialiseWorld();

	createMap();
	generateSceneGraph();

	rootNode=pRootNode;
	navTrans=pNavTrans;
}

osg::ref_ptr<osg::Geode> WorldCreator::createImmeubleNode(GLfloat r,GLfloat g,GLfloat b,GLfloat size, GLfloat height) {
	osg::ref_ptr<osg::Geode> geodeNode (new osg::Geode);
	GLfloat color[3]={r,g,b};
	osg::ref_ptr<Immeuble> unImmeuble(new Immeuble(size,height,color));
	osg::ref_ptr<CustomDrawable> shape=unImmeuble;
	geodeNode->addDrawable((osg::Drawable*)shape.get());
	immeubleParTaille[unImmeuble->getHeight()]=geodeNode;
	return geodeNode;
}

vector<GLfloat> WorldCreator::setCoordonnes(GLfloat x,GLfloat z,GLfloat y) {
	vector<GLfloat> coordonnes;
	coordonnes.resize(3);
	coordonnes[0]=x;
	coordonnes[1]=z;
	coordonnes[2]=y;
	return coordonnes;
}

bool WorldCreator::noeudImmeubleExiste(GLfloat hauteur) {
	return immeubleParTaille.find(hauteur)!=immeubleParTaille.end();
}

bool WorldCreator::estUnEmplacementVide(vector<GLfloat> coordonnes) {
	return laCarte.find(coordonnes)==laCarte.end();
}

void WorldCreator::ajouterImmeubleALaCarte(vector<GLfloat> coordonnes) {
	GLfloat hauteur=randomParPas(10,100,5);
	if(!noeudImmeubleExiste(hauteur)) {
		createImmeubleNode(0,0,1,COTE_IMMEUBLE,hauteur);
	}
	laCarte[coordonnes]=immeubleParTaille[hauteur];
}

void WorldCreator::ajouterImmeubleAutourPosition(GLfloat x, GLfloat y) {
	vector< vector<GLfloat> > lesCoordoonnesAVerifier;
	vector<GLfloat> coordonnes;
	int distance=ESPACE_ENTRE_IMMEUBLE+COTE_IMMEUBLE;

	coordonnes=setCoordonnes(x+distance,0.0,y-distance);
	lesCoordoonnesAVerifier.push_back(coordonnes);
	coordonnes=setCoordonnes(x+distance,0.0,0);
	lesCoordoonnesAVerifier.push_back(coordonnes);
	coordonnes=setCoordonnes(x+distance,0.0,y+distance);
	lesCoordoonnesAVerifier.push_back(coordonnes);
	coordonnes=setCoordonnes(0,0.0,y+distance);
	lesCoordoonnesAVerifier.push_back(coordonnes);
	coordonnes=setCoordonnes(x-distance,0.0,y+distance);
	lesCoordoonnesAVerifier.push_back(coordonnes);
	coordonnes=setCoordonnes(x-distance,0.0,0);
	lesCoordoonnesAVerifier.push_back(coordonnes);
	coordonnes=setCoordonnes(x-distance,0.0,y-distance);
	lesCoordoonnesAVerifier.push_back(coordonnes);
	coordonnes=setCoordonnes(0,0.0,y-distance);
	lesCoordoonnesAVerifier.push_back(coordonnes);

	for(vector< vector<GLfloat> >::iterator uneCoordonee=lesCoordoonnesAVerifier.begin();
			uneCoordonee != lesCoordoonnesAVerifier.end();uneCoordonee++) {
		if(estUnEmplacementVide(*uneCoordonee)) {
			ajouterImmeubleALaCarte(*uneCoordonee);
		}
	}

}

void WorldCreator::createMap() {
	vector<GLfloat> coordonnes;
	coordonnes.resize(3);
	/*coordonnes[0]=0.0;
	coordonnes[1]=0.0;
	coordonnes[2]=0.0;
	osg::ref_ptr<osg::Geode> immeuble=createImmeubleNode(0,0,1,COTE_IMMEUBLE,60);
	laCarte[coordonnes]=immeuble;
	coordonnes[0]=-10.0;
	laCarte[coordonnes]=immeuble;
	coordonnes[2]=-10.0;
	immeuble=createImmeubleNode(0,0,1,COTE_IMMEUBLE,90);
	laCarte[coordonnes]=immeuble;
	coordonnes[0]=10.0;
	laCarte[coordonnes]=immeuble;*/

	int x=10, y=10;
	int distance=ESPACE_ENTRE_IMMEUBLE+COTE_IMMEUBLE;
	while(x<=RAYON_MAX_VILLE) {
		while(y<=RAYON_MAX_VILLE) {
			ajouterImmeubleAutourPosition(x,y);
			y+=distance;
		}
		x+=distance;
	}

}

void WorldCreator::placeNodeElement(osg::ref_ptr<osg::Node> element,vector<GLfloat> coordonnees) {
	osg::ref_ptr<osg::MatrixTransform> mModel = new osg::MatrixTransform();
	mModel->preMult( osg::Matrix::translate(coordonnees[0], coordonnees[1], coordonnees[2]));
	pNavTrans->addChild(mModel);
	mModel->addChild(element.get());
}

void WorldCreator::generateSceneGraph() {
	for (map< vector<GLfloat> , osg::ref_ptr<osg::Geode> >::iterator unImmeuble = laCarte.begin(); unImmeuble != laCarte.end(); ++unImmeuble) {
		placeNodeElement(unImmeuble->second,unImmeuble->first);
	}
}
