#ifndef SOL_H_
#define SOL_H_

#include<iostream>
class Sol : public CustomDrawable {

private:
	GLfloat mSize;
	GLfloat mColor[3];

public:
	Sol(GLfloat size,GLfloat color[])
	{
		mSize=size;
		mColor[0]=color[0];
		mColor[1]=color[1];
		mColor[2]=color[2];
	}

	virtual ~Sol() {
	}

	virtual void drawImplementation(osg::RenderInfo& renderInfo) const {
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
	}


};


#endif /* SOL_H_ */
