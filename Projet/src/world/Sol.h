#ifndef SOL_H_
#define SOL_H_

#include<iostream>
#include<CustomDrawable.h>


class Sol : public CustomDrawable {

private:
	GLfloat mSize;
	GLfloat mColor[3];


public:
	static osg::ref_ptr<osg::Image> image;

	Sol(GLfloat size,GLfloat color[])
	{
		mSize=size;
		mColor[0]=color[0];
		mColor[1]=color[1];
		mColor[2]=color[2];
	}

	virtual ~Sol() {
	}

	virtual void drawImplementation(osg::RenderInfo& renderInfo) const;


};


#endif /* SOL_H_ */
