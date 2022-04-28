/* Athabasca University
   Comp390 - Introduction to Computer Graphics
   TME 3: Lighting and Surface Textures
   Program 2: Calculate specular reflection

   @author: Jonathan Kalmar
   @ID: 3455526
   @date: December 23rd, 2019
*/

#include <iostream>
#include <math.h>
#include "gl/glut.h"
#include "vector3.h"

using namespace std;

// viewer
vector3 viewer(0.0, 0.0, 80.0);

// square
vector3 wallNormal(0.0, 0.0, 1.0);

// colors
vector3 grey(0.75, 0.75, 0.75);
vector3 lightRed(0.75, 0.1, 0.1);

// lighting position
vector3 lightPosition(10, 10, 10);

// lighting elements
float ambient_coef = 0.3;
float diffuse_coef = 0.7;
float specular_coef = 0.5;
float shininess = 32.0;

// initialize
void initialize() {

	// set background color
	glClearColor(0.5, 0.7, 0.5, 0.0);

}



// calculate local color
// local color is intensity * base color
vector3 localColor(vector3 intersect, vector3 baseColor, vector3 normal) {

	// calculate light vector
	vector3 origin = lightPosition.subtract(intersect);
	vector3 unitVec = origin.normalize();

	// calculate dot product L*N
	float dotProd = unitVec.dot(normal);

	//calculate the view vector
	vector3 origin1 = viewer.subtract(intersect);
	vector3 viewVec = origin1.normalize();

	//calculate reflection vector
	vector3 ReflVec(2.0 * dotProd * normal.x - unitVec.x, 2 * dotProd * normal.y - unitVec.y, 2 * dotProd * normal.z - unitVec.z);

	//calculate dot product V*R
	float dotProd1 = viewVec.dot(ReflVec);

	// calculate intensity
	float ambientContr = ambient_coef;
	float diffuseContr = diffuse_coef * dotProd;
	float specularContr = specular_coef * pow(dotProd1, shininess);
	float intensity = ambientContr + diffuseContr + specularContr;

	if (intensity > 1.0) intensity = 1.0;

	float r = intensity * baseColor.x;
	float g = intensity * baseColor.y;
	float b = intensity * baseColor.z;

	return vector3(r, g, b);

}



// render

void render() {

	// render the square

	for (int m = -25; m < 25; m++) {

		for (int n = -25; n < 25; n++) {

			vector3 color = localColor(vector3(m, n, 0), lightRed, wallNormal);

			glColor3f(color.x, color.y, color.z);

			glRecti(m, n, m + 1, n + 1);

		}

	}

}



// display registry

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();



	gluLookAt(0.0, 40.0, 150.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//gluLookAt(viewer.x, viewer.y, viewer.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);



	render();



	glutSwapBuffers();

}



// reshape registry

void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 250.0);

	glMatrixMode(GL_MODELVIEW);

}



// main program

void main(int argc, char** argv)

{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(500, 500);

	glutInitWindowPosition(100, 100);



	int windowHandle = glutCreateWindow("TME3 Program 2");

	glutSetWindow(windowHandle);



	glutDisplayFunc(display);

	glutReshapeFunc(reshape);



	initialize();



	glutMainLoop();

}