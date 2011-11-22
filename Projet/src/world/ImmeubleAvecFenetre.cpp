#include <ImmeubleAvecFenetre.h>


ImmeubleAvecFenetre::ImmeubleAvecFenetre(int nombreEtages) {
	   rezDeChausse = osgDB::readNodeFile(REZ_DE_CHAUSSE);
	   etage = osgDB::readNodeFile(ETAGE);
	   toit = osgDB::readNodeFile(TOIT);
	   mNombreEtages=nombreEtages;
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

osg::ref_ptr<osg::Group> ImmeubleAvecFenetre::construireUnImmeuble() {
	osg::ref_ptr<osg::Group>  rootNode;
	osg::ref_ptr<osg::MatrixTransform> navTrans;
	rootNode = new osg::Group();
	navTrans = new osg::MatrixTransform();
	rootNode->addChild(navTrans);


	placeNodeElement(rezDeChausse,setCoordonnes(0,0,0),navTrans);
	for(int i=1;i<mNombreEtages;i++)
		placeNodeElement(etage,setCoordonnes(0,i*4,0),navTrans);
	placeNodeElement(toit,setCoordonnes(0,mNombreEtages*4,0),navTrans);
	return rootNode;
}
