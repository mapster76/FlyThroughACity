#ifndef _OSG_NAVIGATER_H
#define _OSG_NAVIGATER_H

#include <gmtl/EulerAngle.h>
#include <gmtl/EulerAngleOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Quat.h>
#include <gmtl/QuatOps.h>
#include <osg/MatrixTransform>
#include <vpr/IO/SerializableObject.h>
#include <vpr/IO/ObjectReader.h>
#include <vpr/IO/ObjectWriter.h>
#include <plugins/ApplicationDataManager/UserData.h>

using namespace gmtl;
/** Class to wrap the navigation matrix to share across cluster.
 */
class NavData : public vpr::SerializableObject
{
public:


	virtual void readObject(vpr::ObjectReader* reader) {
		float velocity[3];
		float rotation[3];
		for ( unsigned n=0;n<3;n++ ) {
			velocity[n] = reader->readFloat();
		}
		for ( unsigned n=0;n<3;n++ ) {
			rotation[n] = reader->readFloat();
		}

		mRotation.set(rotation);
		mVelocity.set(velocity);
	}

	virtual void writeObject(vpr::ObjectWriter* writer) {
		const float* velocity = mVelocity.getData();
		const float* rotation = mRotation.getData();
		for ( int n=0;n<3;n++ ) {
			writer->writeFloat(velocity[n]);
		}
		for ( int n=0;n<3;n++ ) {
			writer->writeFloat(rotation[n]);
		}
	}

	void setVelocity(Vec3f velocity) {
	   mVelocity=velocity;
	}

	Vec3f getVelocity() {
	   return mVelocity;
	}

	void setRotation(Vec3f rotation) {
	   mRotation=rotation;
	}

	Vec3f getRotation() {
	   return mRotation;
	}

public:
   Vec3f mRotation;
   Vec3f mVelocity;
};



//   void update(float delta)
  // {
      // Don't update if not active or we have a very large delta
    //  if(delta > 2.0 || !mActive)
      //{
        // std::cout << "Delta big or not active, returning.\n";
        // return;
      //}
      /*if(!mNavData.isLocal())
      {
         std::cout << "Data is NOT local, returning.\n";
         return;
	 }*/
      // Clamp delta
//      if (delta > 1.0)
//      {  delta = 1.0f; }

      // ---------- ROTATION ----------- //
      // Scale the rotation velocity (slerp) to get a time based change
     /* gmtl::Quatf qrot = gmtl::make<gmtl::Quatf>(mRotVelocity);
      gmtl::Quatf scaled_qrot, src_rot;   // scaled rotation and Identity rotation
      gmtl::Matrix44f delta_rot;          // The delta rotation to use

      // Only compute if we don't have identity rotation
      if (!gmtl::isEqual(gmtl::MAT_IDENTITY44F, mRotVelocity, 0.001f))
      {
         gmtl::slerp(scaled_qrot, delta, src_rot, qrot);
         gmtl::set(delta_rot, scaled_qrot);
      }

      if(mMode == WALK)
      {
         gmtl::EulerAngleXYZf euler( 0.0f, gmtl::makeYRot(delta_rot), 0.0f );// Only allow Yaw (rot y)
         delta_rot = gmtl::makeRot<gmtl::Matrix44f>( euler );
      }
      gmtl::postMult(mNavData->mCurPos, delta_rot);*/

      // ------- TRANSLATION ---- //
      /*gmtl::Vec3f trans_delta;
      if(mMode == WALK)
      {
         mVelocity[1] = 0.0f;
      }
      trans_delta =  mVelocity * delta;*/

      // Post multiply the delta translation
      /*gmtl::Matrix44f trans_matrix = gmtl::makeTrans<gmtl::Matrix44f>(trans_delta);
      gmtl::postMult(mNavData->mCurPos, trans_matrix);*/
  // }

  /* gmtl::Matrix44f getCurPos()
   {
      if(!mActive)
      {
         return gmtl::Matrix44f();
      }
      else
      {
         return mNavData->mCurPos;
      }
   }

   void setCurPos(const gmtl::Matrix44f& pos)
   {
      if(mActive)
      {
         mNavData->mCurPos = pos;
      }
   }*/

#endif /* _OSG_NAVIGATE_H */
