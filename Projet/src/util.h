#ifndef UTIL_H_
#define UTIL_H_

#include <cstdlib>
#include <ctime>
#include <vector>
#include <GL/glut.h>

using namespace std;

int randomParPas(int a, int b,int pas);

/**
 * Cette fonction permet de creer un vecteur représentant les coordonnées rapidement.
 * retorn Vector<GLfloat> de taille 3
 */
vector<GLfloat> setCoordonnes(GLfloat x,GLfloat z,GLfloat y);

#endif /* UTIL_H_ */
