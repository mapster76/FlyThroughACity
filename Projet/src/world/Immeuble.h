#ifndef IMMEUBLE_H_
#define IMMEUBLE_H_

#include <osg/Geode>
#include "CustomDrawable.h"

class Immeuble : public CustomDrawable {

private:
	GLfloat mLength;
	GLfloat mDepth;
	GLfloat mHeight;
	GLfloat mColor[3];

public:
	Immeuble(GLfloat size,GLfloat height,GLfloat color[]);

	Immeuble(GLfloat length,GLfloat depth,GLfloat height,GLfloat color[]);

	GLfloat getHeight();

	virtual ~Immeuble() ;

	virtual void drawImplementation(osg::RenderInfo& renderInfo) const;


};


#endif /* IMMEUBLE_H_ */
