/* Athabasca University
   Comp390 - Introduction to Computer Graphics
   TME 3: Lighting and Surface Textures
   Program 3: Loaded Texture

   @author: Jonathan Kalmar
   @ID: 3455526
   @date: December 23rd, 2019
*/

#include "windows.h"
#include "gl/glut.h"
#include "math.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// image
//GLubyte* image;

GLubyte* l_texture;

BITMAPFILEHEADER fileheader;

BITMAPINFOHEADER infoheader;

RGBTRIPLE rgb;

GLuint texName;


void makeImage(void) {

	int i, j = 0;

	FILE* l_file;



	string fn = "side.bmp";

	const char* filename = fn.c_str();



	// open image file, return if error

	fopen_s(&l_file, filename, "rb");

	if (l_file == NULL) return;



	// read file header and header info

	fread(&fileheader, sizeof(fileheader), 1, l_file);

	fseek(l_file, sizeof(fileheader), SEEK_SET);

	fread(&infoheader, sizeof(infoheader), 1, l_file);



	// allocate space for the image file

	l_texture = (GLubyte*)malloc(infoheader.biWidth * infoheader.biHeight * 4);

	memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);



	// read da data

	j = 0;

	for (i = 0; i < infoheader.biWidth * infoheader.biHeight; i++)

	{

		fread(&rgb, sizeof(rgb), 1, l_file);



		l_texture[j + 0] = (GLubyte)rgb.rgbtRed; // Red component

		l_texture[j + 1] = (GLubyte)rgb.rgbtGreen; // Green component

		l_texture[j + 2] = (GLubyte)rgb.rgbtBlue; // Blue component

		l_texture[j + 3] = (GLubyte)255; // Alpha value

		j += 4; // Go to the next position

	}

	fclose(l_file); // Closes the file stream

}


//display list
GLuint HouseList;

// vertex array
typedef GLfloat vertex3[3];

//First 8 vertexes are for our cube, the next 5 vertexes are for the pyramid, the next 4 are for the grass, the last 4 are for the ground
vertex3 pt[21] = { {0,0,0}, {0,1,0}, {1,0,0}, {1,1,0}, {0,0,1}, {0,1,1}, {1,0,1}, {1,1,1}, {-0.2, 1.0, -0.2}, {-0.2, 1.0, 1.2}, {1.2, 1.0, 1.2},
			{1.2, 1.0,-0.2}, {0.5,1.5,0.5}, {-1.0, 0.0, -0.5}, {-1.0, 0.0, 2.5}, {2.0,0.0,2.5}, {2.0,0.0,-0.5}, {-8.0,-0.1,-8.0}, {8.0, -0.1,-8.0}, {8.0,-0.1,8.0}, {-8.0,-0.1,8.0} };


//initialize
void initialize() {

	//enable depth test
	glEnable(GL_DEPTH_TEST);

	// set background color
	glClearColor(0.4, 0.4, 1.0, 1.0);

	//load image data into l_texture
	makeImage();

	//texture settings
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texName);

	glBindTexture(GL_TEXTURE_2D, texName);



	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,

		infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,

		l_texture);
	
}

void drawBackground() {
	//enable texture
	glEnable(GL_TEXTURE_2D);

	//create background
	glBegin(GL_QUADS);

	//left side
	glTexCoord2d(0.0, 0.0); glVertex3f(-8.0, -0.1, 8.0);

	glTexCoord2d(0.0, 1.0); glVertex3f(-8.0, 16.0, 8.0);

	glTexCoord2d(1.0, 1.0); glVertex3f(-8.0, 16.0, -8.0);

	glTexCoord2d(1.0, 0.0); glVertex3f(-8.0, -0.1, -8.0);

	//far side
	glTexCoord2d(0.0, 0.0); glVertex3f(-8.0, -0.1, -8.0);

	glTexCoord2d(0.0, 1.0); glVertex3f(-8.0, 16, -8.0);

	glTexCoord2d(1.0, 1.0); glVertex3f(8.0, 16, -8.0);

	glTexCoord2d(1.0, 0.0); glVertex3f(8.0, -0.1, -8.0);

	glEnd();

	//disable texture
	glDisable(GL_TEXTURE_2D);
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
	triangle(8, 9, 12);
	triangle(9, 10, 12);
	triangle(10, 11, 12);
	triangle(11, 8, 12);
}

// render
void render() {
	
	//create list;
	HouseList = glGenLists(1);
	glNewList(HouseList, GL_COMPILE);

	glPushMatrix();
	//center the house around origin
	glTranslatef(-0.5, 0.0, -1.0);

	//create the grass
	glColor3f(0.0, 1.0, 0.0);
	quad(13, 14, 15, 16);

	//create the cube
	glColor3f(1.0, 0.0, 0.0);
	cube();

	//Create the pyramid
	glColor3f(0.0, 0.0, 1.0);
	pyramid();

	glPopMatrix();

	glEndList();

	//create the ground
	glColor3f(0.5, 0.5, 0.5);
	quad(17, 18, 19, 20);

	//create the background
	drawBackground();

	//transformation for the first house. House numbers go from left to right, front row to back row. Starting with the front left house.
	glPushMatrix();
	glTranslatef(-3.5, 0.0, 5.0);
	glScalef(2.0, 1.0, 1.0);

	//render the first house
	glCallList(HouseList);
	glPopMatrix();

	//transformation for the second house
	glPushMatrix();
	glTranslatef(3.5, 0.0, 5.0);
	glScalef(2.0, 1.0, 1.0);

	//render the second house
	glCallList(HouseList);
	glPopMatrix();

	//transformation for the third house
	glPushMatrix();
	glTranslatef(-4.0, 0.0, 0.0);
	glScalef(1.0, 1.0, 1.0);

	//render the third house
	glCallList(HouseList);

	//fourth house
	glTranslatef(4.0, 0.0, 0.0);
	glCallList(HouseList);

	//fifth house
	glTranslatef(4.0, 0.0, 0.0);
	glCallList(HouseList);
	glPopMatrix();

	//transformation for the sixth house
	glPushMatrix();
	glTranslatef(-5.0, 0.0, -5.0);
	glRotatef(45.0, 0.0, 1.0, 0.0);

	//render the sixth house
	glCallList(HouseList);
	glPopMatrix();

	//transformation for the seventh house
	glPushMatrix();
	glTranslatef(0.0, 0.0, -5.0);
	glScalef(1.0, 2.0, 1.0);

	//render the seventh house
	glCallList(HouseList);
	glPopMatrix();

	//transformation for the eighth house
	glPushMatrix();
	glTranslatef(5.0, 0.0, -5.0);
	glRotatef(-45.0, 0.0, 1.0, 0.0);

	//render the eighth house
	glCallList(HouseList);
	glPopMatrix();
}

// display registry
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	//viewing
	//gluLookAt(0.0, 16.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	gluLookAt(4.0,4.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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



	int windowHandle = glutCreateWindow("TME3 Program 3");

	glutSetWindow(windowHandle);



	glutDisplayFunc(display);

	glutReshapeFunc(reshape);



	initialize();



	glutMainLoop();

}