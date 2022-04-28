/* Athabasca University
   Comp390 - Introduction to Computer Graphics
   TME1 Program 1: Anti-Aliasing

   @author: Jonathan Kalmar
   @ID: 3455526
   @date: December 18th, 2019

*/

#include <GL/glut.h>

GLuint HouseList;

// initialize
void initialize() {

	// set background color
	glClearColor(1.0, 1.0, 1.0, 0.0);

	//create list
	HouseList = glGenLists(1);
	glNewList(HouseList, GL_COMPILE);

	//create the square
	glBegin(GL_POLYGON);
	glVertex2f(-1.0, -1.0);
	glVertex2f(1.0,-1.0);
	glVertex2f(1.0, 1.0);
	glVertex2f(-1.0, 1.0);
	glEnd();

	//Create the triangle
	glBegin(GL_POLYGON);
	glVertex2f(-1.4, 1.0);
	glVertex2f(1.4, 1.0);
	glVertex2f(0.0, 1.6);
	glEnd();

	glEndList();
}

// render
void render() {

	// set colour to black
	glColor3f(0.0, 0.0, 0.0);

	// wire frame
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//save the current matrix and create the transformation matrix for the first house	
	glPushMatrix();	
	glRotatef(25.0, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 5.0, 0.0);
	glScalef(2.5, 2.5, 0.0);
	
	//render the first house and reset the transformation matrix
	glCallList(HouseList);
	glPopMatrix();
	
	//enable anti-aliasing
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
	//transformation for the second house
	glRotatef(25.0, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -5.0, 0.0);
	glScalef(2.5, 2.5, 0.0);
	
	//render the second house
	glCallList(HouseList);
}

// display registry
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// viewing
	gluLookAt(0.0, 0.0, 16.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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
void main(int argc, char** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	int windowHandle = glutCreateWindow("TME1 Program 1");
	glutSetWindow(windowHandle);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	initialize();

	glutMainLoop();
}