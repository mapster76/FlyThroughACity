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

#endif /* _OSG_NAVIGATE_H */
