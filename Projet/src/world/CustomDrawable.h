#ifndef CUSTOMDRAWABLE_H_
#define CUSTOMDRAWABLE_H_

class CustomDrawable: public osg::Drawable
{
   private:
		void (*mRender)();
   public:

      CustomDrawable(void (*render)())
      {
    	  mRender=render;
      }

      CustomDrawable (const CustomDrawable& pg,
                      const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY)
      { }

      virtual osg::Object* cloneType() const { return new CustomDrawable(mRender); }

      virtual osg::Object* clone(const osg::CopyOp& copyop) const
      { return new CustomDrawable (*this, copyop); }

      virtual void drawImplementation (osg::RenderInfo& renderInfo) const
      {
		/*osg::ref_ptr<osg::Image> image (osgDB::readImageFile("wood.png"));
		osg::ref_ptr<osg::Texture2D> texture (new osg::Texture2D(image.get()));

		osg::ref_ptr<osg::StateSet> texSS (new osg::StateSet);
		texSS->setTextureAttributeAndModes (0,   // unit
											  texture.get(),
											  osg::StateAttribute::ON);*/
		mRender();
      }


};



#endif /* CUSTOMDRAWABLE_H_ */
