#include <ImmeubleAvecFenetre.h>

osg::ref_ptr<osg::Node> ImmeubleAvecFenetre::rezDeChausse = osgDB::readNodeFile(REZ_DE_CHAUSSE);
osg::ref_ptr<osg::Node> ImmeubleAvecFenetre::etage = osgDB::readNodeFile(ETAGE);
osg::ref_ptr<osg::Node> ImmeubleAvecFenetre::toit = osgDB::readNodeFile(TOIT);
osg::ref_ptr<osg::Node> ImmeubleAvecFenetre::trotoir = osgDB::readNodeFile(TROTOIR);
osg::ref_ptr<osg::Node> ImmeubleAvecFenetre::route = osgDB::readNodeFile(ROUTE);
osg::ref_ptr<osg::Node> ImmeubleAvecFenetre::rezDeChausseLow = osgDB::readNodeFile(REZ_DE_CHAUSSE_LOW);
osg::ref_ptr<osg::Node> ImmeubleAvecFenetre::etageLow = osgDB::readNodeFile(ETAGE_LOW);
osg::ref_ptr<osg::Node> ImmeubleAvecFenetre::toitLow = osgDB::readNodeFile(TOIT_LOW);
osg::ref_ptr<osg::Node> ImmeubleAvecFenetre::lampadaire = osgDB::readNodeFile(LAMPADAIRE);

ImmeubleAvecFenetre::ImmeubleAvecFenetre(int nombreEtages) {
	mImmeuble=new osg::Group();
	mImmeubleLow=new osg::Group();
	mEmptyNode=new osg::Group();
	mRoute= new osg::Group();
	mNombreEtages=nombreEtages;
	osg::ref_ptr<osg::StateSet> etageStateSet (etage->getOrCreateStateSet());
	osg::ref_ptr<osg::StateSet> rdcStateSet (rezDeChausse->getOrCreateStateSet());
	osg::ref_ptr<osg::StateSet> toitStateSet (toit->getOrCreateStateSet());
	osg::ref_ptr<osg::StateSet> trotoirStateSet (trotoir->getOrCreateStateSet());
	osg::ref_ptr<osg::StateSet> routeStateSet (route->getOrCreateStateSet());
	osg::ref_ptr<osg::StateSet> etageLowStateSet (etageLow->getOrCreateStateSet());
	osg::ref_ptr<osg::StateSet> rdcLowStateSet (rezDeChausseLow->getOrCreateStateSet());
	osg::ref_ptr<osg::StateSet> toitLowStateSet (toitLow->getOrCreateStateSet());
	osg::ref_ptr<osg::StateSet> lampadaireStateSet (lampadaire->getOrCreateStateSet());

	//Its shader objects
	osg::ref_ptr<osg::Program> shader (new osg::Program);
	osg::ref_ptr<osg::Shader> capsulevertexShader(
	osg::Shader::readShaderFile (osg::Shader::VERTEX, "../shaders/nuanceurSommets.glsl"));

	osg::ref_ptr<osg::Shader> capsulefragShader(
			osg::Shader::readShaderFile (osg::Shader::FRAGMENT, "../shaders/nuanceurFragments.glsl"));

	shader->addShader(capsulevertexShader.get());
	shader->addShader(capsulefragShader.get());
	osg::ref_ptr<osg::Program> shader2 (new osg::Program);
	osg::ref_ptr<osg::Shader> texturevertexShader(
			osg::Shader::readShaderFile (osg::Shader::VERTEX, "../shaders/nuanceurSommetsTexture.glsl"));

	osg::ref_ptr<osg::Shader> texturefragShader(
			osg::Shader::readShaderFile (osg::Shader::FRAGMENT, "../shaders/nuanceurFragmentsTexture.glsl"));
	//Binding the box shaders to its program
	shader2->addShader(texturevertexShader.get());
	shader2->addShader(texturefragShader.get());

	etageStateSet->setAttribute(shader);
	rdcStateSet->setAttribute(shader);
	toitStateSet->setAttribute(shader);
	trotoirStateSet->setAttribute(shader);
	lampadaireStateSet->setAttribute(shader);
	etageLowStateSet->setAttribute(shader2);
	rdcLowStateSet->setAttribute(shader2);
	toitLowStateSet->setAttribute(shader2);
	routeStateSet->setAttribute(shader2);

}

int ImmeubleAvecFenetre::getNombreEtage() {
	return mNombreEtages;
}

void ImmeubleAvecFenetre::placeNodeLampadaire(osg::ref_ptr<osg::Node> element,vector<GLfloat> coordonnees,osg::ref_ptr<osg::Group> noeudAAjouter,float rotationY) {
	osg::ref_ptr<osg::MatrixTransform> mModel = new osg::MatrixTransform();

	mModel->preMult( osg::Matrix::translate(coordonnees[0], coordonnees[1], coordonnees[2]));
	mModel->preMult( osg::Matrix::rotate( gmtl::Math::deg2Rad( -90.0f ), 1.0f, 0.0f, 0.0f) );
	mModel->preMult( osg::Matrix::rotate( gmtl::Math::deg2Rad( rotationY ), 0.0f, 0.0f, 1.0f) );
	noeudAAjouter->addChild(mModel);
	mModel->addChild(element.get());
}

void ImmeubleAvecFenetre::placeNodeElement(osg::ref_ptr<osg::Node> element,vector<GLfloat> coordonnees,osg::ref_ptr<osg::Group> noeudAAjouter) {
	osg::ref_ptr<osg::MatrixTransform> mModel = new osg::MatrixTransform();

	mModel->preMult( osg::Matrix::translate(coordonnees[0], coordonnees[1], coordonnees[2]));
	mModel->preMult( osg::Matrix::rotate( gmtl::Math::deg2Rad( -90.0f ), 1.0f, 0.0f, 0.0f) );

	noeudAAjouter->addChild(mModel);
	mModel->addChild(element.get());
}

void creerLeSol(vector<GLfloat> coordonnees,osg::ref_ptr<osg::Group> noeudAAjouter) {
	osg::ref_ptr<osg::MatrixTransform> mModel = new osg::MatrixTransform();

	mModel->preMult( osg::Matrix::translate(coordonnees[0], coordonnees[1], coordonnees[2]));
	mModel->preMult( osg::Matrix::rotate( gmtl::Math::deg2Rad( -90.0f), 1.0f, 0.0f, 0.0f) );

	noeudAAjouter->addChild(mModel);
	mModel->addChild(ImmeubleAvecFenetre::route.get());
}

void ImmeubleAvecFenetre::construireUnImmeuble() {
	/**
	 * Noeud avec tous un maximun de détails dont les lampadaires
	 */
	osg::ref_ptr<osg::Group>  rootNode;
	osg::ref_ptr<osg::MatrixTransform> navTrans;
	rootNode = new osg::Group();
	navTrans = new osg::MatrixTransform();

	rootNode->addChild(navTrans);
	navTrans->addChild(mImmeuble);
	osg::ref_ptr<osg::Group> lampadaires=new osg::Group();

	navTrans->addChild(mRoute);
	navTrans->addChild(lampadaires);

	creerLeSol(setCoordonnes(0,0,0),mRoute);
	placeNodeElement(trotoir,setCoordonnes(0,0,0),mRoute);
	placeNodeLampadaire(lampadaire,setCoordonnes(7,0,4),lampadaires,-90);
	placeNodeLampadaire(lampadaire,setCoordonnes(7,0,-4),lampadaires,-90);
	placeNodeLampadaire(lampadaire,setCoordonnes(-7,0,4),lampadaires,90);
	placeNodeLampadaire(lampadaire,setCoordonnes(-7,0,-4),lampadaires,90);
	placeNodeLampadaire(lampadaire,setCoordonnes(4,0,-7),lampadaires,0);
	placeNodeLampadaire(lampadaire,setCoordonnes(-4,0,-7),lampadaires,0);
	placeNodeLampadaire(lampadaire,setCoordonnes(4,0,7),lampadaires,180);
	placeNodeLampadaire(lampadaire,setCoordonnes(-4,0,7),lampadaires,180);
	placeNodeElement(rezDeChausse,setCoordonnes(0,0,0),mImmeuble);
	for(int i=1;i<mNombreEtages;i++)
		placeNodeElement(etage,setCoordonnes(0,i*4,0),mImmeuble);
	placeNodeElement(toit,setCoordonnes(0,mNombreEtages*4,0),mImmeuble);
	//Permet de rendre invisible l'interieur d'un batiment
	osg::StateSet* immeubleStateSet=mImmeuble->getOrCreateStateSet();
	osg::CullFace* cf = new osg::CullFace(osg::CullFace::BACK);
	immeubleStateSet->setAttributeAndModes(cf, osg::StateAttribute::ON);
	mEnsemble=rootNode;

	/*
	 * Noeud qui n'affiche pas les lampadaire
	 */
	osg::ref_ptr<osg::Group>  rootNodeSansLamp;
	osg::ref_ptr<osg::MatrixTransform> navTransSansLamp;
	osg::ref_ptr<osg::Group> immeubleSansLamp;
	rootNodeSansLamp = new osg::Group();
	immeubleSansLamp = new osg::Group();
	navTransSansLamp = new osg::MatrixTransform();

	rootNodeSansLamp->addChild(navTransSansLamp);
	navTransSansLamp->addChild(immeubleSansLamp);
	navTransSansLamp->addChild(mRoute);

	placeNodeElement(rezDeChausse,setCoordonnes(0,0,0),immeubleSansLamp);
	for(int i=1;i<mNombreEtages;i++)
		placeNodeElement(etage,setCoordonnes(0,i*4,0),immeubleSansLamp);
	placeNodeElement(toit,setCoordonnes(0,mNombreEtages*4,0),immeubleSansLamp);
	//Permet de rendre invisible l'interieur d'un batiment
	osg::StateSet* immeubleStateSetSansLamp=immeubleSansLamp->getOrCreateStateSet();
	immeubleStateSetSansLamp->setAttributeAndModes(cf, osg::StateAttribute::ON);


	mEnsembleSansLamp=rootNodeSansLamp;

	/*
	 * Immeuble avec très peu de polygones afficher un peu plus loin
	 */
	osg::ref_ptr<osg::Group>  rootNodeLow;
	osg::ref_ptr<osg::MatrixTransform> navTransLow;
	rootNodeLow = new osg::Group();
	navTransLow = new osg::MatrixTransform();

	rootNodeLow->addChild(navTransLow);
	navTransLow->addChild(mImmeubleLow);
	navTransLow->addChild(mRoute);

	placeNodeElement(rezDeChausseLow,setCoordonnes(0,0,0),mImmeubleLow);
	for(int i=1;i<mNombreEtages;i++)
		placeNodeElement(etageLow,setCoordonnes(0,i*4,0),mImmeubleLow);
	placeNodeElement(toitLow,setCoordonnes(0,mNombreEtages*4,0),mImmeubleLow);
	//Permet de rendre invisible l'interieur d'un batiment
	osg::StateSet* immeubleStateSetLow=mImmeubleLow->getOrCreateStateSet();
	immeubleStateSetLow->setAttributeAndModes(cf, osg::StateAttribute::ON);

	mEnsembleLow=rootNodeLow;

	lodEnsemble = new LOD();
	lodEnsemble->addChild( mEmptyNode.get(), 300.0f, FLT_MAX);
	lodEnsemble->addChild( mEnsembleLow.get(), 100.0f, 300);
	lodEnsemble->addChild( mEnsembleSansLamp.get(), 50.0f, 100.0f );
	lodEnsemble->addChild( mEnsemble.get(), 0.0f, 50.0f );
}

int ImmeubleAvecFenetre::getTaille() {
	return (mNombreEtages+1)*4;
}

osg::BoundingBox ImmeubleAvecFenetre::getBoundingBox() {
	osg::ComputeBoundsVisitor cbv;
	mImmeuble->accept(cbv);
	osg::BoundingBox bb( cbv.getBoundingBox() );
	osg::Vec3f max=bb._max;
	max.set(bb._max.x(),bb._max.y()+2,bb._max.z());
	bb.set(bb._min,max);
	return bb;
}

osg::ref_ptr<osg::LOD> ImmeubleAvecFenetre::getNode() {
	return lodEnsemble;
}
