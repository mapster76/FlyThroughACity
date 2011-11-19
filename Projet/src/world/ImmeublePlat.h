#ifndef IMMEUBLE_H_
#define IMMEUBLE_H_

#include <osg/Geode>
#include "CustomDrawable.h"

#define RAYON_MAX_VILLE 100
#define ESPACE_ENTRE_IMMEUBLE 40
#define COTE_IMMEUBLE 8

class ImmeublePlat : public CustomDrawable {

private:
	GLfloat mLength;
	GLfloat mDepth;
	GLfloat mHeight;
	GLfloat mColor[3];

public:
	ImmeublePlat(GLfloat size,GLfloat height,GLfloat color[]);

	ImmeublePlat(GLfloat length,GLfloat depth,GLfloat height,GLfloat color[]);

	GLfloat getHeight();

	virtual ~ImmeublePlat() ;

	virtual void drawImplementation(osg::RenderInfo& renderInfo) const;


};


#endif /* IMMEUBLE_H_ */
