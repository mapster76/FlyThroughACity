
#include <WorldCreator.h>


void WorldCreator::initialiseWorld() {
	osg::MatrixTransform* mModelSol = new osg::MatrixTransform();
	osg::ref_ptr<osg::Geode> noeudSol (new osg::Geode);
	GLfloat color[3]={0.2,0.2,0.2};
	osg::ref_ptr<CustomDrawable> sol(new Sol(RAYON_MAX_VILLE*2,color));
	noeudSol->addDrawable((osg::Drawable*)sol.get());

	pRootNode->addChild(pNavTrans);
	pNavTrans->addChild(mModelSol);
	mModelSol->addChild(noeudSol.get());
}


void WorldCreator::drawWorld(osg::ref_ptr<osg::Group> &rootNode,osg::ref_ptr<osg::MatrixTransform> &navTrans) {
	initialiseWorld();

	createMap();
	generateSceneGraph();
	illuminateScene();

	rootNode=pRootNode;
	navTrans=pNavTrans;
}

osg::ref_ptr<osg::Geode> WorldCreator::createImmeublePlatNode(GLfloat r,GLfloat g,GLfloat b,GLfloat size, GLfloat height) {
	osg::ref_ptr<osg::Geode> geodeNode (new osg::Geode);
	GLfloat color[3]={r,g,b};
	osg::ref_ptr<ImmeublePlat> unImmeuble(new ImmeublePlat(size,height,color));
	osg::ref_ptr<CustomDrawable> shape=unImmeuble;
	geodeNode->addDrawable((osg::Drawable*)shape.get());
	immeubleParTaille[unImmeuble->getHeight()]=geodeNode;
	return geodeNode;
}

osg::ref_ptr<osg::Node> WorldCreator::createImmeubleAvecFenetreNode(GLfloat nombreEtage) {
	osg::ref_ptr<osg::Node> resultNode;
	ImmeubleAvecFenetre unImmeuble(nombreEtage);
	resultNode=unImmeuble.construireUnImmeuble();
	immeubleParTaille[unImmeuble.getNombreEtage()]=resultNode;
	return resultNode;
}

bool WorldCreator::noeudImmeubleExiste(GLfloat hauteur) {
	return immeubleParTaille.find(hauteur)!=immeubleParTaille.end();
}

bool WorldCreator::estUnEmplacementVide(vector<GLfloat> coordonnes) {
	return laCarte.find(coordonnes)==laCarte.end();
}

void WorldCreator::ajouterImmeubleALaCarte(vector<GLfloat> coordonnes) {
	//Generation d'un nombre d'étage entre 1 et 10 pseudo-aleatoirement
	GLfloat nombreEtage=randomParPas(3,20,1);
	if(!noeudImmeubleExiste(nombreEtage)) {
		createImmeubleAvecFenetreNode(nombreEtage);
		//createImmeublePlatNode(0,0,1,COTE_IMMEUBLE,nombreEtage*10);
	}
	laCarte[coordonnes]=immeubleParTaille[nombreEtage];
}

void WorldCreator::ajouterImmeubleAutourPosition(GLfloat x, GLfloat y) {
	vector< vector<GLfloat> > lesCoordoonnesAVerifier;
	vector<GLfloat> coordonnes;
	int distance=ESPACE_ENTRE_IMMEUBLE;

	coordonnes=setCoordonnes(x+distance,0.0,y-distance);
	lesCoordoonnesAVerifier.push_back(coordonnes);
	coordonnes=setCoordonnes(x+distance,0.0,y);
	lesCoordoonnesAVerifier.push_back(coordonnes);
	coordonnes=setCoordonnes(x+distance,0.0,y+distance);
	lesCoordoonnesAVerifier.push_back(coordonnes);
	coordonnes=setCoordonnes(x,0.0,y+distance);
	lesCoordoonnesAVerifier.push_back(coordonnes);
	coordonnes=setCoordonnes(x-distance,0.0,y+distance);
	lesCoordoonnesAVerifier.push_back(coordonnes);
	coordonnes=setCoordonnes(x-distance,0.0,y);
	lesCoordoonnesAVerifier.push_back(coordonnes);
	coordonnes=setCoordonnes(x-distance,0.0,y-distance);
	lesCoordoonnesAVerifier.push_back(coordonnes);
	coordonnes=setCoordonnes(x,0.0,y-distance);
	lesCoordoonnesAVerifier.push_back(coordonnes);

	for(vector< vector<GLfloat> >::iterator uneCoordonee=lesCoordoonnesAVerifier.begin();
			uneCoordonee != lesCoordoonnesAVerifier.end();uneCoordonee++) {
		if(estUnEmplacementVide(*uneCoordonee)) {
			ajouterImmeubleALaCarte(*uneCoordonee);
		}
	}

}

void WorldCreator::dessinnerUnQuartier(GLfloat xImmeuble, GLfloat yImmeuble,GLfloat distance) {
	int x=xImmeuble, y=yImmeuble;
	while(x<=RAYON_MAX_VILLE) {
		while(y<=RAYON_MAX_VILLE) {
			ajouterImmeubleAutourPosition(x,y);
			ajouterImmeubleAutourPosition(-x,y);
			ajouterImmeubleAutourPosition(-x,-y);
			ajouterImmeubleAutourPosition(x,-y);
			y+=distance;
		}
		y=yImmeuble;
		x+=distance;
	}
}
void WorldCreator::createMap() {
	vector<GLfloat> coordonnes;
	coordonnes.resize(3);
	int x=ESPACE_ENTRE_IMMEUBLE/2, y=ESPACE_ENTRE_IMMEUBLE/2;
	dessinnerUnQuartier(x,y,ESPACE_ENTRE_IMMEUBLE);
	/*ImmeubleAvecFenetre unImmeubleAvecFenetre;
	osg::ref_ptr<osg::Node>  rezDeChausse;
	placeNodeElement(unImmeubleAvecFenetre.construireUnImmeuble(),setCoordonnes(0,0,0));*/
}

void WorldCreator::placeNodeElement(osg::ref_ptr<osg::Node> element,vector<GLfloat> coordonnees) {
	osg::ref_ptr<osg::MatrixTransform> mModel = new osg::MatrixTransform();
	mModel->preMult( osg::Matrix::translate(coordonnees[0], coordonnees[1], coordonnees[2]));
	pNavTrans->addChild(mModel);
	mModel->addChild(element.get());
}

void WorldCreator::generateSceneGraph() {
	for (map< vector<GLfloat> , osg::ref_ptr<osg::Node> >::iterator unImmeuble = laCarte.begin(); unImmeuble != laCarte.end(); ++unImmeuble) {
		placeNodeElement(unImmeuble->second,unImmeuble->first);
	}
}

void WorldCreator::illuminateScene() {
	osg::ref_ptr<osg::PositionAttitudeTransform> position(new osg::PositionAttitudeTransform());
	osg::ref_ptr<osg::Group> lightGroup (new osg::Group);
	osg::ref_ptr<osg::StateSet> lightSS (pRootNode->getOrCreateStateSet());

	osg::ref_ptr<osg::LightSource> lightSource1 = new osg::LightSource;
	osg::Vec4f lightPosition(osg::Vec4f(0.0,0.0,200.0,0.0f));
	osg::ref_ptr<osg::Light> myLight = new osg::Light;
	myLight->setLightNum(1);
	myLight->setPosition(lightPosition);
	//myLight->setDirection(osg::Vec3(0.0f,0.0f,-1.0f));
	myLight->setAmbient(osg::Vec4(0.6f,0.6f,0.6f,1.0f));
	myLight->setDiffuse(osg::Vec4(.8f,.8f,.8f,1.0f));
	//myLight->setConstantAttenuation(1.0f);
	lightSource1->setLight(myLight.get());

	lightSource1->setLocalStateSetModes(osg::StateAttribute::ON);
	lightSource1->setStateSetModes(*lightSS,osg::StateAttribute::ON);
	lightGroup->addChild(lightSource1.get());

	/*osg::ref_ptr<osg::LightSource> lightSource2 = new osg::LightSource;
	osg::Vec4f lightPosition2 (osg::Vec4f(0.0,200.0,0.0,1.0f));
	osg::ref_ptr<osg::Light> myLight2 = new osg::Light;
	myLight2->setLightNum(1);
	myLight2->setPosition(lightPosition2);
	myLight2->setDirection(osg::Vec3(0.0f,-1.0f,0.0f));
	myLight2->setAmbient(osg::Vec4(0.2f,0.2f,0.2f,1.0f));
	myLight2->setDiffuse(osg::Vec4(.8f,.8f,.8f,1.0f));
	//myLight2->setConstantAttenuation(1.0f);
	lightSource2->setLight(myLight2.get());

	lightSource2->setLocalStateSetModes(osg::StateAttribute::ON);
	lightSource2->setStateSetModes(*lightSS,osg::StateAttribute::ON);
	lightGroup->addChild(lightSource2.get());

	osg::ref_ptr<osg::LightSource> lightSource3 = new osg::LightSource;
	osg::Vec4f lightPosition3(osg::Vec4f(200.0,0.0,0.0,1.0f));
	osg::ref_ptr<osg::Light> myLight3 = new osg::Light;
	myLight3->setLightNum(2);
	myLight3->setPosition(lightPosition3);
	myLight3->setDirection(osg::Vec3(-5.0f,0.0f,0.0f));
	myLight3->setAmbient(osg::Vec4(0.2f,0.2f,0.2f,1.0f));
	myLight3->setDiffuse(osg::Vec4(.8f,.8f,.8f,1.0f));
	//myLight3->setConstantAttenuation(1.0f);
	lightSource3->setLight(myLight3.get());

	lightSource3->setLocalStateSetModes(osg::StateAttribute::ON);
	lightSource3->setStateSetModes(*lightSS,osg::StateAttribute::ON);
	lightGroup->addChild(lightSource3.get());

	osg::ref_ptr<osg::LightSource> lightSource4 = new osg::LightSource;
	osg::Vec4f lightPosition4(osg::Vec4f(-200.0,0.0,0.0,0.0f));
	osg::ref_ptr<osg::Light> myLight4 = new osg::Light;
	myLight4->setLightNum(3);
	myLight4->setPosition(lightPosition4);
	myLight4->setDirection(osg::Vec3(5.0f,0.0f,0.0f));
	myLight4->setAmbient(osg::Vec4(0.2f,0.2f,0.2f,1.0f));
	myLight4->setDiffuse(osg::Vec4(.8f,.8f,.8f,1.0f));
	//myLight4->setConstantAttenuation(1.0f);
	lightSource4->setLight(myLight4.get());

	lightSource4->setLocalStateSetModes(osg::StateAttribute::ON);
	lightSource4->setStateSetModes(*lightSS,osg::StateAttribute::ON);
	lightGroup->addChild(lightSource4.get());


	osg::ref_ptr<osg::LightSource> lightSource5 = new osg::LightSource;
	osg::Vec4f lightPosition5(osg::Vec4f(0.0,0.0,-200.0,0.0f));
	osg::ref_ptr<osg::Light> myLight5 = new osg::Light;
	myLight5->setLightNum(4);
	myLight5->setPosition(lightPosition5);
	//myLight5->setDirection(osg::Vec3(0.0f,0.0f,1.0f));
	myLight5->setAmbient(osg::Vec4(0.2f,0.2f,0.2f,1.0f));
	myLight5->setDiffuse(osg::Vec4(.8f,.8f,.8f,1.0f));
	//myLight5->setConstantAttenuation(1.0f);
	lightSource5->setLight(myLight5.get());

	lightSource5->setLocalStateSetModes(osg::StateAttribute::ON);
	lightSource5->setStateSetModes(*lightSS,osg::StateAttribute::ON);
	lightGroup->addChild(lightSource5.get());*/

	position->addChild(lightGroup.get());
	pRootNode->addChild(position.get());
}
