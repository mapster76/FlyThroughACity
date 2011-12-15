#include "Skybox.h"

Skybox::Skybox(GLfloat tailleCote,string nomImage) {
	mSize =tailleCote;
	image=osgDB::readImageFile(nomImage);
}

void Skybox::drawImplementation(osg::RenderInfo& renderInfo) const{
	int positionCote=mSize/2;

	Vec3Array* boxVertices = new osg::Vec3Array;
	boxVertices->push_back(Vec3f(-positionCote,-positionCote,-positionCote)); //back bottom left 0
	boxVertices->push_back(Vec3f(positionCote,-positionCote,-positionCote)); //back bottom right 1
	boxVertices->push_back(Vec3f(positionCote,positionCote,-positionCote)); //back up right 2
	boxVertices->push_back(Vec3f(-positionCote,positionCote,-positionCote)); //back up left 3
	boxVertices->push_back(Vec3f(-positionCote,-positionCote,positionCote)); //front bottom left 4
	boxVertices->push_back(Vec3f(positionCote,-positionCote,positionCote)); //front bottom right 5
	boxVertices->push_back(Vec3f(positionCote,positionCote,positionCote)); //front up right 6
	boxVertices->push_back(Vec3f(-positionCote,positionCote,positionCote)); //front up left 7

	osg::ref_ptr<osg::Texture2D> texture (new osg::Texture2D(image.get()));
	//osg::ref_ptr<osg::Texture2D> texture (new osg::Texture2D(osgDB::readImageFile("../Skybox/skybox6.jpg")));
	//changerSkybox();
	
	osg::ref_ptr<osg::StateSet> texSS (new osg::StateSet);
	texture->setInternalFormat(GL_RGBA);
	texture->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
	texture->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);
	texSS->setTextureAttributeAndModes (0,   // unit
                                          texture.get(),
                                          osg::StateAttribute::ON);
	texSS->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

	renderInfo.getState()->apply(texSS.get());
	boxVertices->at(0)._v;
	glBegin(GL_QUADS);
		glTexCoord2f(1.0/4.0, 1.01/3.0);glVertex3fv(boxVertices->at(0)._v);
		glTexCoord2f(2.0/4.0, 1.01/3.0);glVertex3fv(boxVertices->at(1)._v);
		glTexCoord2f(2.0/4.0, 1.99/3.0);glVertex3fv(boxVertices->at(2)._v);
		glTexCoord2f(1.0/4.0, 1.99/3.0);glVertex3fv(boxVertices->at(3)._v);

		glTexCoord2f(1.0/4.0, 1.01/3.0);glVertex3fv(boxVertices->at(0)._v);
		glTexCoord2f(0, 1.01/3.0);glVertex3fv(boxVertices->at(4)._v);
		glTexCoord2f(0, 1.99/3.0);glVertex3fv(boxVertices->at(7)._v);
		glTexCoord2f(1.0/4.0, 1.99/3.0);glVertex3fv(boxVertices->at(3)._v);

		glTexCoord2f(1, 1.01/3.0);glVertex3fv(boxVertices->at(4)._v);
		glTexCoord2f(3.0/4.0, 1.01/3.0);glVertex3fv(boxVertices->at(5)._v);
		glTexCoord2f(3.0/4.0, 1.99/3.0);glVertex3fv(boxVertices->at(6)._v);
		glTexCoord2f(1, 1.99/3.0);glVertex3fv(boxVertices->at(7)._v);

		glTexCoord2f(2.0/4.0, 1.01/3.0);glVertex3fv(boxVertices->at(1)._v);
		glTexCoord2f(3.0/4.0, 1.01/3.0);glVertex3fv(boxVertices->at(5)._v);
		glTexCoord2f(3.0/4.0, 1.99/3.0);glVertex3fv(boxVertices->at(6)._v);
		glTexCoord2f(2.0/4.0, 1.99/3.0);glVertex3fv(boxVertices->at(2)._v);

		glTexCoord2f(1.01/4.0, 0);glVertex3fv(boxVertices->at(0)._v);
		glTexCoord2f(1.99/4.0, 0);glVertex3fv(boxVertices->at(1)._v);
		glTexCoord2f(1.99/4.0, 1.0/3.0);glVertex3fv(boxVertices->at(5)._v);
		glTexCoord2f(1.01/4.0, 1.0/3.0);glVertex3fv(boxVertices->at(4)._v);

		glTexCoord2f(1.99/4.0, 2.0/3.0);glVertex3fv(boxVertices->at(2)._v);
		glTexCoord2f(1.01/4.0, 2.0/3.0);glVertex3fv(boxVertices->at(3)._v);
		glTexCoord2f(1.01/4.0, 1);glVertex3fv(boxVertices->at(7)._v);
		glTexCoord2f(1.99/4.0, 1);glVertex3fv(boxVertices->at(6)._v);
	glEnd();

	renderInfo.getState()->apply();
}

Skybox::~Skybox() {
}
