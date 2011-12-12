#ifndef SKYBOX_H_
#define SKYBOX_H_

#include <osg/Geode>
#include <osgDB/ReadFile>
#include <iostream>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/ShapeDrawable>
#include <osg/StateSet>
#include<CustomDrawable.h>
#include <vector>

using namespace osg;
class Skybox : public CustomDrawable {
public:
	GLfloat mSize;
	static osg::ref_ptr<osg::Image> image;
	Skybox(GLfloat tailleCote);
	virtual ~Skybox();
	virtual void drawImplementation(osg::RenderInfo& renderInfo) const;
};

#endif /* SKYBOX_H_ */
