#include<Sol.h>

osg::ref_ptr<osg::Image> Sol::image=osgDB::readImageFile("../tex/route.jpg");

void Sol::drawImplementation(osg::RenderInfo& renderInfo) const{
	//osg::ref_ptr<osg::Image> image (osgDB::readImageFile("../tex/route.jpg"));
	osg::ref_ptr<osg::Texture2D> texture (new osg::Texture2D(image.get()));

	osg::ref_ptr<osg::StateSet> texSS (new osg::StateSet);
	texSS->setTextureAttributeAndModes (0,   // unit
                                          texture.get(),
                                          osg::StateAttribute::ON);
	texSS->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

	renderInfo.getState()->apply(texSS.get());


	glColor3fv(mColor);
	glBegin(GL_QUADS);
		glNormal3f (0, 1, 0);

		glTexCoord2f(0,0);
		glVertex3f (-mSize,0, -mSize);

		glTexCoord2f(1, 0);
		glVertex3f (mSize,0,-mSize);

		glTexCoord2f(1,1);
		glVertex3f ( mSize,0,mSize);

		glTexCoord2f(0, 1);
		glVertex3f(-mSize,0,mSize);

	glEnd();

	//reinitiailiste l'etat pour ne pas appliquer la texture par la suite
	renderInfo.getState()->apply();

}
