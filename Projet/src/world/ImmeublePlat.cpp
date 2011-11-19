#include <ImmeublePlat.h>

ImmeublePlat::ImmeublePlat(GLfloat size,GLfloat height,GLfloat color[])
{
	mLength=size;
	mDepth=size;
	mHeight=height;
	mColor[0]=color[0];
	mColor[1]=color[1];
	mColor[2]=color[2];
}

ImmeublePlat::ImmeublePlat(GLfloat length,GLfloat depth,GLfloat height,GLfloat color[])
{
	mLength=length;
	mDepth=depth;
	mHeight=height;
	mColor[0]=color[0];
	mColor[1]=color[1];
	mColor[2]=color[2];
}

GLfloat ImmeublePlat::getHeight() {
	return mHeight;
}

ImmeublePlat::~ImmeublePlat() {
}

void ImmeublePlat::drawImplementation(osg::RenderInfo& renderInfo) const {
	glColor3fv(mColor);
	glBegin(GL_QUADS);
		glNormal3f (0, 1, 0);
		glVertex3f (-mLength,mHeight, -mDepth);
		glVertex3f (mLength,mHeight,-mDepth);
		glVertex3f (mLength,mHeight,mDepth);
		glVertex3f(-mLength,mHeight,mDepth);

		glNormal3f (0, 0, -1);
		glVertex3f (-mLength,0, mDepth);
		glVertex3f (mLength,0,mDepth);
		glVertex3f ( mLength,mHeight,mDepth);
		glVertex3f(-mLength,mHeight,mDepth);

		glNormal3f (0, 0, -1);
		glVertex3f (-mLength,0, -mDepth);
		glVertex3f (mLength,0,-mDepth);
		glVertex3f (mLength,mHeight,-mDepth);
		glVertex3f(-mLength,mHeight,-mDepth);

		glNormal3f (-1, 0, 0);
		glVertex3f (mLength,0, -mDepth);
		glVertex3f (mLength,0,mDepth);
		glVertex3f (mLength,mHeight,mDepth);
		glVertex3f(mLength,mHeight,-mDepth);

		glNormal3f (1, 0, 0);
		glVertex3f (-mLength,0, -mDepth);
		glVertex3f (-mLength,0,mDepth);
		glVertex3f (-mLength,mHeight,mDepth);
		glVertex3f(-mLength,mHeight,-mDepth);
	glEnd();
}

void dessinnerFacadeFenetre() {

}

void dessinerFenetre() {

}


