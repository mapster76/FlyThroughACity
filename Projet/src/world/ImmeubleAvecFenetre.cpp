#include <ImmeubleAvecFenetre.h>

osg::ref_ptr<osg::Node> ImmeubleAvecFenetre::rezDeChausse = osgDB::readNodeFile(REZ_DE_CHAUSSE);
osg::ref_ptr<osg::Node> ImmeubleAvecFenetre::etage = osgDB::readNodeFile(ETAGE);
osg::ref_ptr<osg::Node> ImmeubleAvecFenetre::toit = osgDB::readNodeFile(TOIT);
osg::ref_ptr<osg::Node> ImmeubleAvecFenetre::trotoir = osgDB::readNodeFile(TROTOIR);
osg::ref_ptr<osg::Node> ImmeubleAvecFenetre::route = osgDB::readNodeFile(ROUTE);

ImmeubleAvecFenetre::ImmeubleAvecFenetre(int nombreEtages) {
	   mNombreEtages=nombreEtages;
/*	   osg::ref_ptr<osg::StateSet> etageStateSet (etage->getOrCreateStateSet());
	   //Its shader objects
	   	osg::ref_ptr<osg::Program> goochShader (new osg::Program);
	   	 osg::ref_ptr<osg::Shader> capsulevertexShader(
	         osg::Shader::readShaderFile (osg::Shader::VERTEX, "../shaders/nuanceurSommets.glsl"));

	   	 osg::ref_ptr<osg::Shader> capsulefragShader(
	         osg::Shader::readShaderFile (osg::Shader::FRAGMENT, "../shaders/nuanceurFragments.glsl"));

	   	//Binding the box shaders to its program
	   	goochShader->addShader(capsulevertexShader.get());
	   	goochShader->addShader(capsulefragShader.get());

	   	etageStateSet->setAttribute(goochShader);*/



}

int ImmeubleAvecFenetre::getNombreEtage() {
	return mNombreEtages;
}


void ImmeubleAvecFenetre::placeNodeElement(osg::ref_ptr<osg::Node> element,vector<GLfloat> coordonnees,osg::ref_ptr<osg::MatrixTransform> navTrans) {
	osg::ref_ptr<osg::MatrixTransform> mModel = new osg::MatrixTransform();

	mModel->preMult( osg::Matrix::translate(coordonnees[0], coordonnees[1], coordonnees[2]));
	mModel->preMult( osg::Matrix::rotate( gmtl::Math::deg2Rad( -90.0f ), 1.0f, 0.0f, 0.0f) );

	navTrans->addChild(mModel);
	mModel->addChild(element.get());
}

void creerLeSol(vector<GLfloat> coordonnees,osg::ref_ptr<osg::MatrixTransform> navTrans) {
	/*osg::ref_ptr<osg::Geode> noeudSol (new osg::Geode);
	GLfloat color[3]={0.2,0.2,0.2};
	osg::ref_ptr<CustomDrawable> sol(new Sol(13,color));
	noeudSol->addDrawable((osg::Drawable*)sol.get());*/
	osg::ref_ptr<osg::MatrixTransform> mModel = new osg::MatrixTransform();

	mModel->preMult( osg::Matrix::translate(coordonnees[0], coordonnees[1], coordonnees[2]));
	mModel->preMult( osg::Matrix::rotate( gmtl::Math::deg2Rad( -90.0f), 1.0f, 0.0f, 0.0f) );

	navTrans->addChild(mModel);
	mModel->addChild(ImmeubleAvecFenetre::route.get());
}

osg::ref_ptr<osg::Group> ImmeubleAvecFenetre::construireUnImmeuble() {
	osg::ref_ptr<osg::Group>  rootNode;
	osg::ref_ptr<osg::MatrixTransform> navTrans;
	rootNode = new osg::Group();
	navTrans = new osg::MatrixTransform();
	rootNode->addChild(navTrans);

	creerLeSol(setCoordonnes(0,0,0),navTrans);
	//placeNodeElement(route,setCoordonnes(0,0,0),navTrans);
	placeNodeElement(trotoir,setCoordonnes(0,0,0),navTrans);
	placeNodeElement(rezDeChausse,setCoordonnes(0,0,0),navTrans);
	for(int i=1;i<mNombreEtages;i++)
		placeNodeElement(etage,setCoordonnes(0,i*4,0),navTrans);
	placeNodeElement(toit,setCoordonnes(0,mNombreEtages*4,0),navTrans);
	return rootNode;
}
