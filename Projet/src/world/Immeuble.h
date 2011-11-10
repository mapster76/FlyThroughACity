#ifndef IMMEUBLE_H_
#define IMMEUBLE_H_

#include <osg/Geode>
#include "CustomDrawable.h"

class Immeuble : public CustomDrawable {

private:
	GLfloat mSize;
	GLfloat mHeight;
	GLfloat mColor[3];

public:
	Immeuble(GLfloat size,GLfloat height,GLfloat color[])
	{
		mSize=size;
		mHeight=height;
		mColor[0]=color[0];
		mColor[1]=color[1];
		mColor[2]=color[2];
	}

	virtual ~Immeuble() {
		delete mColor;
	}

	virtual void drawImplementation(osg::RenderInfo& renderInfo) const {
		std::cout << "Immeuble" << std::endl;
		std::cout << mColor[0] << " " << mColor[1] << " " << mColor[2] << std::endl;
		glColor3fv(mColor);
		glBegin(GL_QUADS);
			glNormal3f (0, 1, 0);
			glVertex3f (-mSize,mHeight, -mSize);
			glVertex3f (mSize,mHeight,-mSize);
			glVertex3f ( mSize,mHeight,mSize);
			glVertex3f(-mSize,mHeight,mSize);

			glNormal3f (0, 0, -1);
			glVertex3f (-mSize,0, mSize);
			glVertex3f (mSize,0,mSize);
			glVertex3f ( mSize,mHeight,mSize);
			glVertex3f(-mSize,mHeight,mSize);

			glNormal3f (0, 0, -1);
			glVertex3f (-mSize,0, -mSize);
			glVertex3f (mSize,0,-mSize);
			glVertex3f ( mSize,mHeight,-mSize);
			glVertex3f(-mSize,mHeight,-mSize);

			glNormal3f (-1, 0, 0);
			glVertex3f (mSize,0, -mSize);
			glVertex3f (mSize,0,mSize);
			glVertex3f ( mSize,mHeight,mSize);
			glVertex3f(mSize,mHeight,-mSize);

			glNormal3f (1, 0, 0);
			glVertex3f (-mSize,0, -mSize);
			glVertex3f (-mSize,0,mSize);
			glVertex3f (-mSize,mHeight,mSize);
			glVertex3f(-mSize,mHeight,-mSize);
		glEnd();
	}


};


#endif /* IMMEUBLE_H_ */
