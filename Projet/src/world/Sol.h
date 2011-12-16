#ifndef SOL_H_
#define SOL_H_

#include<iostream>
#include<CustomDrawable.h>

/**
 * Classe permettant de dessiner le sol et appliqué une texture
 * Elle n'est plus utilisé car elle ralenti le programme de manière
 * dramatique à la place on charge un objet Sol déjà texturé grâce à l'UV mapping
 * dans Blender c'est beaucoup plus efficace.
 * Pour avoir les textures il vaux mieux exporter en .obj
 */
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
