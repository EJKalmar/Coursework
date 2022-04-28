/* Athabasca University
   Comp390 - Introduction to Computer Graphics
   TME1 Program 3: Colouring and Shading

   @author: Jonathan Kalmar
   @ID: 3455526
   @date: December 18th, 2019

*/

#include "GL/glut.h"

// initialize
void initialize() {

	// set background color to white
	glClearColor(1.0, 1.0, 1.0, 0.0);

}

// render
void render() {

	glBegin(GL_QUADS);

	//bottom left, red vertex
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-3.0, -3.0);
	
	//bottom right, yellow vertex
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(-3.0, 3.0);

	//top right, blue vertex
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(3.0, 3.0);

	//top left, green vertex
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(3.0, -3.0);

	glEnd();

}

// display registry
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// viewing
	gluLookAt(0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	render();

	glutSwapBuffers();

}

// reshape registry
void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 40.0);

	glMatrixMode(GL_MODELVIEW);

}

// main program
void main(int argc, char** argv)
{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(500, 500);

	glutInitWindowPosition(100, 100);

	int windowHandle = glutCreateWindow("TME1 Program 3");

	glutSetWindow(windowHandle);

	glutDisplayFunc(display);

	glutReshapeFunc(reshape);

	initialize();

	glutMainLoop();

}