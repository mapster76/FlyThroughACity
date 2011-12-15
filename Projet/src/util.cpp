#include<util.h>

vector<GLfloat> setCoordonnes(GLfloat x,GLfloat z,GLfloat y) {
	vector<GLfloat> coordonnes;
	coordonnes.resize(3);
	coordonnes[0]=x;
	coordonnes[1]=z;
	coordonnes[2]=y;
	return coordonnes;
}


