#ifndef CUSTOMDRAWABLE_H_
#define CUSTOMDRAWABLE_H_

#include <osg/Geode>
#include <osg/PositionAttitudeTransform>
#include <osgUtil/Optimizer>
#include <osg/Math>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osg/Material>
class CustomDrawable: public osg::Drawable
{
   public:

      CustomDrawable()
      {
      }

      CustomDrawable (const CustomDrawable& pg,
                      const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY)
      { }

      virtual osg::Object* cloneType() const { return new CustomDrawable(); }

      virtual osg::Object* clone(const osg::CopyOp& copyop) const
      { return new CustomDrawable (*this, copyop); }

      virtual void drawImplementation (osg::RenderInfo& renderInfo) const
      {

      }


};



#endif /* CUSTOMDRAWABLE_H_ */
