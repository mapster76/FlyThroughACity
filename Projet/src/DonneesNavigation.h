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
/**
 * Classe permettant de partager les informations de rotations et de vitesse à travers le cluster
 */
class NavData : public vpr::SerializableObject
{
public:
	/*
	 * Méthodes abstraite redéfinie qui permette de sérialisé le vecteur de rotation et de vitesse
	 */

	/**
	 * permet de lire un objet qui a été encapsulé et envoyer à travers le réseau
	 */
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

	/**
	 * Permet d'écrire un objet pour l'envoyé à travers le réseau
	 */
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

	/**
	 * Setter de la vitesse
	 */
	void setVelocity(Vec3f velocity) {
		mVelocity=velocity;
	}

	/**
	 * Accesseur de la vitesse
	 */
	Vec3f getVelocity() {
		return mVelocity;
	}

	/**
	 * Setter de la rotation à affecter
	 */
	void setRotation(Vec3f rotation) {
		mRotation=rotation;
	}

	/**
	 * Accesseur de la rotation
	 */
	Vec3f getRotation() {
		return mRotation;
	}

public:
	Vec3f mRotation;
	Vec3f mVelocity;
};

#endif /* _OSG_NAVIGATE_H */
