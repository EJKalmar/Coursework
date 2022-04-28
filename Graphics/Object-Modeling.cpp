/* Athabasca University
   Comp390 - Introduction to Computer Graphics
   TME 2: 3D graphics
   Program 1: Object Modeling

   @author: Jonathan Kalmar
   @ID: 3455526
   @date: December 21st, 2019
*/

#include "GL/glut.h"

//display list
GLuint HouseList;

// vertex array
typedef GLfloat vertex3[3];

//First 8 vertexes are for our cube, the next 5 vertexes are for the pyramid, the last 4 are for the grass
vertex3 pt[17] = { {0,0,0}, {0,1,0}, {1,0,0}, {1,1,0}, {0,0,1}, {0,1,1}, {1,0,1}, {1,1,1}, {-0.2, 1.0, -0.2}, {-0.2, 1.0, 1.2}, {1.2, 1.0, 1.2},
																			{1.2, 1.0,-0.2}, {0.5,1.5,0.5}, {-1.0, 0.0, -0.5}, {-1.0, 0.0, 2.5}, {2.0,0.0,2.5}, {2.0,0.0,-0.5} };

// initialize
void initialize() {

	// set background color
	glClearColor(1.0, 1.0, 1.0, 0.0);

}

//render quad
void quad(GLint n1, GLint n2, GLint n3, GLint n4) {
	glBegin(GL_POLYGON);
	glVertex3fv(pt[n1]);
	glVertex3fv(pt[n2]);
	glVertex3fv(pt[n3]);
	glVertex3fv(pt[n4]);
	glEnd();
}

//render triangle
void triangle(GLint n1, GLint n2, GLint n3) {
	glBegin(GL_POLYGON);
	glVertex3fv(pt[n1]);
	glVertex3fv(pt[n2]);
	glVertex3fv(pt[n3]);
	glEnd();
}

//render cube
void cube() {
	quad(6, 2, 3, 7);
	quad(5, 1, 0, 4);
	quad(7, 3, 1, 5);
	quad(4, 0, 2, 6);
	quad(2, 0, 1, 3);
	quad(7, 5, 4, 6);
}

//render pyramid
void pyramid() {
	triangle(8,9,12);
	triangle(9, 10, 12);
	triangle(10, 11, 12);
	triangle(11, 8, 12);
}

// render
void render() {

	//create list;
	HouseList = glGenLists(1);
	glNewList(HouseList, GL_COMPILE_AND_EXECUTE);
	
	//wire frame
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	//create the grass
	glColor3f(0.0, 1.0, 0.0);
	quad(13, 14, 15, 16);
	
	//create the cube
	glColor3f(1.0, 0.0, 0.0);
	cube();
	
	//Create the pyramid
	glColor3f(0.0, 0.0, 1.0);
	pyramid();
	
	glEndList();
}



// display registry
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// viewing
	//gluLookAt(1.5, 1.5, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(0.0, 16.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	gluLookAt(2.5, 2.5, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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

	int windowHandle = glutCreateWindow("TME2 Program 1");

	glutSetWindow(windowHandle);

	glutDisplayFunc(display);

	glutReshapeFunc(reshape);

	initialize();

	glutMainLoop();

}