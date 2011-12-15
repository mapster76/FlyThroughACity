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
#include <string>
#include <vector>

using namespace osg;
using namespace std;
class Skybox : public CustomDrawable {
private:
	GLfloat mSize;
	osg::ref_ptr<osg::Image> image;
	//vector< ref_ptr<osg::Image> > vImage;

public:
	Skybox(GLfloat tailleCote,string nomImage);
	virtual ~Skybox();
	virtual void drawImplementation(osg::RenderInfo& renderInfo) const;
};

#endif /* SKYBOX_H_ */
