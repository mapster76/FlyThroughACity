#include<util.h>



int randomParPas(int a, int b,int pas){
	static bool seedInitialiser=false;
	if(!seedInitialiser) {
		srand(10000);
		seedInitialiser=true;
	}
	int nombreAleatoire=rand()%(b-a) +a;
	int quotient=nombreAleatoire/pas;
	int resultat=pas*quotient;
	int reste=nombreAleatoire%pas;
	if(reste > pas/2)
		resultat+=pas;
    return resultat;
}


vector<GLfloat> setCoordonnes(GLfloat x,GLfloat z,GLfloat y) {
	vector<GLfloat> coordonnes;
	coordonnes.resize(3);
	coordonnes[0]=x;
	coordonnes[1]=z;
	coordonnes[2]=y;
	return coordonnes;
}
