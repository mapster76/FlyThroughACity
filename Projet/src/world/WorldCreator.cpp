
#include <WorldCreator.h>


void WorldCreator::initialiseWorld() {
	pRootNode->addChild(pNavTrans);
	vEmplacementImage.push_back("../Skybox/skybox1.jpg");
	vEmplacementImage.push_back("../Skybox/skybox2.jpg");
	vEmplacementImage.push_back("../Skybox/skybox3.jpg");
	vEmplacementImage.push_back("../Skybox/skybox5.jpg");
	vEmplacementImage.push_back("../Skybox/skybox6.jpg");
	vEmplacementImage.push_back("../Skybox/skybox11.jpg");
	itEmplacementImage=vEmplacementImage.begin();
	skybox=new Skybox(RAYON_MAX_VILLE*5,*itEmplacementImage);
	noeudSkybox=new osg::Geode();
	noeudSkybox->addDrawable(skybox);
	pNavTrans->addChild(noeudSkybox);
}

void WorldCreator::gestionBouton3(gadget::DigitalInterface mButton) {
	if(mButton->getData() == gadget::Digital::TOGGLE_ON) {
		itEmplacementImage++;
		if(itEmplacementImage== vEmplacementImage.end()) {
			itEmplacementImage=vEmplacementImage.begin();
		}
		pNavTrans->removeChild(noeudSkybox);
		noeudSkybox->removeDrawable(skybox);
		cout << *itEmplacementImage << endl;
		skybox=new Skybox(RAYON_MAX_VILLE*5,*itEmplacementImage);
		noeudSkybox->addDrawable(skybox);
		pNavTrans->addChild(noeudSkybox);

		//skybox->changerSkybox();
	}
}


void WorldCreator::drawWorld(osg::ref_ptr<osg::Group> &rootNode,osg::ref_ptr<osg::MatrixTransform> &navTrans) {
	initialiseWorld();illuminateScene();
	createMap();
	generateSceneGraph();
	rootNode=pRootNode;
	navTrans=pNavTrans;
}

osg::ref_ptr<osg::Geode> WorldCreator::createImmeublePlatNode(GLfloat r,GLfloat g,GLfloat b,osg::Vec3f coordonnees,GLfloat size, GLfloat height) {
	osg::ref_ptr<osg::Geode> geodeNode (new osg::Geode);
	GLfloat color[3]={r,g,b};
	osg::ref_ptr<ImmeublePlat> unImmeuble(new ImmeublePlat(size,height,color));
	osg::ref_ptr<CustomDrawable> shape=unImmeuble;
	geodeNode->addDrawable((osg::Drawable*)shape.get());
	laCarteBox[unImmeuble->getHeight()]=geodeNode;
	osg::ref_ptr<osg::MatrixTransform> mModel = new osg::MatrixTransform();
	mModel->preMult( osg::Matrix::translate(coordonnees[0], coordonnees[1], coordonnees[2]));
	pNavTrans->addChild(mModel);
	mModel->addChild(geodeNode.get());
	return geodeNode;
}

osg::ref_ptr<osg::Node> WorldCreator::createImmeubleAvecFenetreNode(GLfloat nombreEtage) {
	osg::ref_ptr<osg::Node> resultNode;
	ImmeubleAvecFenetre unImmeuble(nombreEtage);
	unImmeuble.construireUnImmeuble();
	immeubleParTaille[unImmeuble.getNombreEtage()]=unImmeuble;
	return resultNode;
}

bool WorldCreator::noeudImmeubleExiste(GLfloat hauteur) {
	return immeubleParTaille.find(hauteur)!=immeubleParTaille.end();
}

bool WorldCreator::estUnEmplacementVide(vector<GLfloat> coordonnes) {
	return laCarte.find(coordonnes)==laCarte.end();
}

void WorldCreator::updateBoundingBox() {
	for (map< vector<GLfloat> , ImmeubleAvecFenetre >::iterator unImmeuble = laCarte.begin(); unImmeuble != laCarte.end(); ++unImmeuble) {
		osg::BoundingBox bbox;
		ImmeubleAvecFenetre lImmeuble=unImmeuble->second;
		vector<GLfloat> coordonnes=unImmeuble->first;
		osg::Vec3f position(coordonnes[0],0,coordonnes[2]);
		bbox=lImmeuble.getBoundingBox();
		osg::BoundingBox nouvelBox(bbox._min+position,bbox._max+position);
		lesBoundingBoxes[coordonnes]=nouvelBox;
	}
	Vec3f limiteMinSol(-RAYON_MAX_VILLE*5.f,-1,-RAYON_MAX_VILLE*5.f);
	Vec3f limiteMaxSol(RAYON_MAX_VILLE*5.f,1,RAYON_MAX_VILLE*5.f);
	osg::BoundingBox sol(limiteMinSol,limiteMaxSol);
	vector<GLfloat> centre;
	centre.push_back(0);
	centre.push_back(0);
	centre.push_back(0);
	lesBoundingBoxes[centre]=sol;

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
	for (map< vector<GLfloat> , ImmeubleAvecFenetre >::iterator unImmeuble = laCarte.begin(); unImmeuble != laCarte.end(); ++unImmeuble) {
		placeNodeElement(unImmeuble->second.getNode(),unImmeuble->first);
	}
}

map < vector<GLfloat> , ImmeubleAvecFenetre > WorldCreator::getCarte() {

  return laCarte;

}

void WorldCreator::illuminateScene() {
	/*osg::ref_ptr<osg::MatrixTransform> mModel = new osg::MatrixTransform();

	mModel->preMult( osg::Matrix::translate(0, 0, 0));*/
	pRootNode->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OVERRIDE || osg::StateAttribute::OFF);
	pNavTrans->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::ON);
	osg::ref_ptr<osg::Group> lightGroup (new osg::Group);
	osg::ref_ptr<osg::StateSet> lightSS (pNavTrans->getOrCreateStateSet());

	osg::ref_ptr<osg::LightSource> lightSource1 = new osg::LightSource;
	osg::Vec4f lightPosition(osg::Vec4f(0.0,RAYON_MAX_VILLE*5,RAYON_MAX_VILLE*5,1.0));
	osg::Vec3f lightDirection(osg::Vec3f(0.0,0.0,1.0));
	osg::ref_ptr<osg::Light> myLight = new osg::Light;
	myLight->setLightNum(1);

	myLight->setPosition(lightPosition);
	myLight->setDirection(lightDirection);
	myLight->setAmbient(osg::Vec4(.3f,.3f,.3f,1.0f));
	myLight->setDiffuse(osg::Vec4(.5f,.5f,.5f,1.0f));
	myLight->setSpecular(osg::Vec4(.7f,.7f,.7f,1.0f));
	lightSource1->setLight(myLight.get());
	//pRootNode->getOrCreateStateSet()->setMode(GL_LIGHT1, osg::StateAttribute::ON);
	lightSource1->setLocalStateSetModes(osg::StateAttribute::ON);
	lightSource1->setStateSetModes(*lightSS,osg::StateAttribute::ON);
	lightGroup->addChild(lightSource1.get());

	//Light markers: small spheres
	/*osg::ref_ptr<osg::Geode> lightMarkerGeode (new osg::Geode);
	lightMarkerGeode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3f(0.0f,1.0f,0.0f),0.5f)));*/

	/*osg::ref_ptr<osg::LightSource> lightSource2 = new osg::LightSource;
	osg::Vec4f lightPosition2(osg::Vec4f(0.0,0.0,1.0,0.0f));
	osg::ref_ptr<osg::Light> myLight2 = new osg::Light;
	myLight2->setLightNum(2);
	myLight2->setPosition(lightPosition);
	myLight2->setAmbient(osg::Vec4(.4f,.4f,.4f,1.0f));
	myLight2->setDiffuse(osg::Vec4(.5f,.5f,.5f,1.0f));
	myLight2->setSpecular(osg::Vec4(.3f,.3f,.3f,1.0f));
	lightSource2->setLight(myLight2.get());

	lightSource2->setLocalStateSetModes(osg::StateAttribute::ON);
	lightSource2->setStateSetModes(*lightSS,osg::StateAttribute::ON);
	lightGroup->addChild(lightSource2.get());*/
	//mModel->addChild(lightGroup.get());
	//pNavTrans->addChild(lightMarkerGeode);
	pNavTrans->addChild(lightGroup);
}
