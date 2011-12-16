#ifndef IMMEUBLE_H_
#define IMMEUBLE_H_

#include <osg/Geode>
#include "CustomDrawable.h"


#define COTE_IMMEUBLE 8

/**
 * Ancienne classe permettant de dessiner un prisme d'une certaine couleur
 * avec du code OpenGL non utilisé mais je la garde car elle peut etre utile
 * pour débugguer
 */
class ImmeublePlat : public CustomDrawable {

private:
	GLfloat mLength;
	GLfloat mDepth;
	GLfloat mHeight;
	GLfloat mColor[3];

public:
	ImmeublePlat();

	ImmeublePlat(GLfloat size,GLfloat height,GLfloat color[]);

	ImmeublePlat(GLfloat length,GLfloat depth,GLfloat height,GLfloat color[]);

	GLfloat getHeight();

	virtual ~ImmeublePlat() ;

	virtual void drawImplementation(osg::RenderInfo& renderInfo) const;


};


#endif /* IMMEUBLE_H_ */
