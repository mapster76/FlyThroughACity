#include <ImmeubleAvecFenetre.h>


ImmeubleAvecFenetre::ImmeubleAvecFenetre() {
	   rezDeChausse = osgDB::readNodeFile(REZ_DE_CHAUSSE);
	   etage = osgDB::readNodeFile(ETAGE);
	   toit = osgDB::readNodeFile(TOIT);
}

void ImmeubleAvecFenetre::placeNodeElement(osg::ref_ptr<osg::Node> element,vector<GLfloat> coordonnees,osg::ref_ptr<osg::MatrixTransform> navTrans) {
	osg::ref_ptr<osg::MatrixTransform> mModel = new osg::MatrixTransform();

	mModel->preMult( osg::Matrix::translate(coordonnees[0], coordonnees[1], coordonnees[2]));
	mModel->preMult( osg::Matrix::rotate( gmtl::Math::deg2Rad( -90.0f ), 1.0f, 0.0f, 0.0f) );

	navTrans->addChild(mModel);
	mModel->addChild(element.get());
}

osg::ref_ptr<osg::Group> ImmeubleAvecFenetre::construireUnImmeuble() {
	osg::ref_ptr<osg::Group>  rootNode;
	osg::ref_ptr<osg::MatrixTransform> navTrans;
	rootNode = new osg::Group();
	navTrans = new osg::MatrixTransform();
	rootNode->addChild(navTrans);

	//rezDeChausse->setName("rdc");
	placeNodeElement(rezDeChausse,setCoordonnes(0,0,0),navTrans);
	placeNodeElement(etage,setCoordonnes(0,4,0),navTrans);
	placeNodeElement(toit,setCoordonnes(0,8,0),navTrans);
	//std::cout << navTrans->getChild(3) << std::endl;
	return rootNode;
}
