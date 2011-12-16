#ifndef NAVIGATION_H_
#define NAVIGATION_H_

#include "DonneesNavigation.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <gadget/Type/Position/PositionUnitConversion.h>
#include "world/WorldCreator.h"
#include <gadget/Type/PositionInterface.h>
#include <gadget/Type/AnalogInterface.h>
#include <gadget/Type/DigitalInterface.h>
#include <osg/Matrix>
#include <osg/Transform>
#include <osg/MatrixTransform>

#include <Sons.h>

using namespace std;

class Navigation {
public:
	Navigation();
	virtual ~Navigation();
	/**
	 * Méthode permettant l'initialisation de toutes les variables nécéssaire au fonctionnement de la navigation
	 */
	void init(WorldCreator world,gadget::PositionInterface &wand,gadget::PositionInterface &head,gadget::DigitalInterface &button0,gadget::DigitalInterface &button1,gadget::DigitalInterface &button2);

	/**
	 * Méthode appelée lorsque l'on à appuyer sur le bouton 2 pour s'arreter
	 */
	void ralentirPuisSAreter(long tempsCourant);

	/**
	 * Méthode appelée lorsque que l'on appui sur la gachette pour accelerer
	 */
	void accelerer(long tempsCourant);

	/**
	 * Méthode appelé a chaque affichage qui va permettre de se déplacer
	 * et de tourner dans le monde lorsque l'on souhaite en fonction des appui bouton.
	 */
	void seDeplacer();

	/**
	 * Méthode qui appele acceleration lorsque la gachette est appuyé et decceleration si elle
	 * est relachée
	 */ 
	void gestionGachette(long tempsCourant);

	/**
	 * Permet de deplacer ou arreter l'utilisateur dans le monde appele les méthode se déplacer et avancer
	 */
	void gestionBouton2(long tempsCourant);

	/**
	 * permet de mettre des variables booléennes d'état à vrai ou faux
	 */ 
	void avancerOuArreter();

	/**
	 * Méthode appelée pour ralentir après une accéleration 
	 */
	void ralentir(long tempsCourant);

	/**
	 * Méthode appelée pour s'arreter lorsque qu'il y a une collision
	 */
	void arretBrutal();

	/**
	 * Méthode qui donne le droit de tourner (utilisée au premier déplacement)
	 */
	void droitDeTourner();

	/**
	 * Méthode permettant de détecter des collisions avec les murs
	 */
	void collisions();

	/**
	 * Méthode permettant de jouer les effets sonores de vaisseau en fonction de l'état dans lequel on se trouve 
	 */
	void jouerSonVaisseau();

	/**
	 * Méthode permettant de stabiliser la caméra après avoir effectuer une rotation
	 */
	void stabiliserCamera(float limiteHorizon,float increment,osg::Quat rotationActuelle,osg::Matrix &matriceCorrection);

	/**
	 * Méthode appelée à chaque frame qui met à jour la Navigation
	 */
	void update(float time_delta);

	/**
	 * Méthode qui permet de retourner la matrice de navigation courante pour l'appliquée à l'environnement
	 */
	osg::Matrix getCurrentMatrix();

	/**
	 * Returns the scale factor for this application.  For this sample, we
	 * are handling everything in feet.
	 */
	virtual float getDrawScaleFactor()
	{
		return gadget::PositionUnitConversion::ConvertToFeet;
	}

private:

	bool estEnTrainDAvancer;
	bool peutTourner;
	long tempsPourArret;
	long tempsPourAcceleration;
	long tempsPourDecceleration;
	long estEnTrainDAccelerer;
	long estEnTrainDeDecelerer;
	bool estEnTrainDeSArreter;
	bool arretEnDouceur;
	osg::Vec3 mTranslation;
	osg::Vec3 mRotation;
	osg::Matrix mCurrentMatrix;
	WorldCreator mWorld;
	cluster::UserData< NavData >  mNavigator;
	Sons mSons;
	gadget::PositionInterface  mWand;     // the Wand
	gadget::PositionInterface  mHead;     // the head
	gadget::DigitalInterface   mButton0;
	gadget::DigitalInterface   mButton1;
	gadget::DigitalInterface   mButton2;
};

#endif /* NAVIGATION_H_ */
