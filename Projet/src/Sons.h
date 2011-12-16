#ifndef SONS_H_
#define SONS_H_

#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>
//#include <wincompat.h>
#include <stdio.h>
#include <iostream>
#include <gadget/Type/DigitalInterface.h>
#include <vector>
#include <string>

using namespace std;

/**
 * Cette classe n'est pas parfaite et demanderai quelques améliorations elle à été implémenté de façon
 * à avoir quelquechose de fonctionnelle il faudrait très certainement la revoir dans son ensemble
 */
class Sons {

public:

	/**
	 * Initialise et charge tous les sons qui seront utilisé dans le programme
	 */
	Sons();

	/**
	 * destructeur de son nottament pour libérer tous les pointeurs qui ont été initialise
	 */
	virtual ~Sons();

	/**
	 * différente méthode pour jouer les ambiances chaque ambiances est associé à une channel qui nous
	 * permet de controler la lecture ou la pause de celle-ci
	 */
	void jouerAmbiancePluie();
	void jouerAmbianceNature();
	void jouerAmbianceFoule();
	void jouerAmbianceOrage();
	void jouerMusique1();
	void jouerMusique2();
	/**
	 * Différentes méthodes pour mettre en pause les ambiances
	 */
	void pauseAmbiancePluie();
	void pauseAmbianceOrage();
	void pauseAmbianceFoule();
	void pauseAmbianceNature();
	void pauseMusique1();
	void pauseMusique2();

	/**
	 * methode appelée par gestionBouton1 qui permet de changer d'ambiance sonore répertorié dans un
	 * vecteur contenant des string que l'on itére. ATTENTION : on avait utilisé un vector avec les sons
	 * dans un premier temps mais cela ne fonctionnait pas bizarrement les sons pointé par les références
	 * dans le vecteur étaient vide
	 */
	void changerAmbianceSonore(string itAmbianceSonore);

	/**
	 * Différentes méthode pour jouer les bruitages
	 * Chacunes des méthodes à ses particularité en fonction de ce que l'on désire faire avec les bruitages
	 * nottament joué en loop ... Comme les sons se jouent tous en loop et que par un mystere que l'on ne
	 * comprend pas on ne peut pas spécifier à chaque channel la façon dont les sons seront joué.
	 * On a utilisé des variables booléenes qui nous permettent de mettre en pause le son à la fin d'une
	 * première lecture.
	 */
	void jouerSonVaisseau();
	void jouerSonDeceleration();
	void jouerSonAcceleration();
	void jouerSonGrandeVitesse();
	void jouerSonCollision();

	/**
	 * Les méthodes qui suivent permettent de mettre en pause les différents bruitages
	 */
	void pauseSonVaisseau();
	void pauseSonDeceleration();
	void pauseSonAcceleration();
	void pauseSonGrandeVitesse();
	void pauseSonCollision();

	/**
	 * gestion du bouton 1 qui permet de changer l'environnement sonore
	 */
	void gestionBouton1(gadget::DigitalInterface mButton);

	/**
	 * Méthodes de vérification d'érreurs
	 */
	void ERRCHECK(FMOD_RESULT);

private:
	vector<string>::iterator itAmbianceSonore;
	vector<string> vAmbianceSonore;
	FMOD::System     *system;
	FMOD::Sound      *ambianceGenerale, *ambiancePluie, *ambianceOrage, *ambianceNature, *ambianceFoule, *musique1, *musique2, *sonVaisseau, *sonDeceleration, *sonCollision, *sonAcceleration, *sonGrandeVitesse;
	FMOD::Channel    *channelDeceleration,*channelAmbiance,*channelCollision,*channelVaisseau,*channelAcceleration, *channelGrandeVitesse, *channelPluie, *channelOrage, *channelFoule, *channelNature, *channelMusique1, *channelMusique2;
	FMOD_RESULT       result;
	int               key;
	bool 			  collisionAlreadyPlayed,decelerationAlreadyPlayed,accelerationAlreadyPlayed;
	unsigned int      version;
	FMOD_VECTOR forward, up, velocity, listenerPos, lastPos;

};

#endif /* SONS_H_ */
