/* Athabasca University
   Comp390 - Introduction to Computer Graphics
   TME 3: Lighting and Surface Textures
   Program 1: Lighting elements and surface materials

   @author: Jonathan Kalmar
   @ID: 3455526
   @date: December 22nd, 2019
*/

#include "gl/glut.h"

// lights

GLfloat light_position0[] = { 0.0, 0.0, 10.0, 0.0 }; //behind viewer

GLfloat light_position1[] = { 10.0, 10.0, 10.0, 0.0 };	//top right

GLfloat light_position2[] = { -10.0, 10.0, 10.0, 0.0 };	//top left


GLfloat black_light[] = { 0.0, 0.0, 0.0, 1.0 }; //turn light off

GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat green_light[] = { 0.2, 1.0, 0.2, 1.0 };

GLfloat red_light[] = { 1.0, 0.4, 0.4, 1.0 };

GLfloat blue_light[] = { 0.2, 0.2, 1.0, 1.0 };

GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };



// Material Properties

// gold

GLfloat gold_ambient[] = { 0.24725, 0.1995, 0.0745, 1.0 };

GLfloat gold_diffuse[] = { 0.75164, 0.60648, 0.22658, 1.0 };

GLfloat gold_specular[] = { 0.628281, 0.555802, 0.366065, 1.0 };

GLfloat gold_shininess[] = { 51.2 };



// silver

GLfloat silver_ambient[] = { 0.19225, 0.19225, 0.19225, 1.0 };

GLfloat silver_diffuse[] = { 0.50754, 0.50754, 0.50754, 1.0 };

GLfloat silver_specular[] = { 0.508273, 0.508273, 0.508273, 1.0 };

GLfloat silver_shininess[] = { 51.2 };



// copper

GLfloat copper_ambient[] = { 0.2295, 0.08825, 0.0275, 1.0 };

GLfloat copper_diffuse[] = { 0.5508, 0.2118, 0.066, 1.0 };

GLfloat copper_specular[] = { 0.580594, 0.223257, 0.0695701, 1.0 };

GLfloat copper_shininess[] = { 51.2 };


void lightMenu(GLenum light, GLint colourOption) {
	GLfloat DiffuseColour[4];//current diffuse lighting
	glGetLightfv(light, GL_DIFFUSE, DiffuseColour);

	GLfloat SpecularColour[4];//current specular lighting
	glGetLightfv(light, GL_SPECULAR, SpecularColour);
	
	switch (colourOption) {
	case 1://off
		glDisable(light);
		break;
	case 2://white
		glEnable(light);
		glLightfv(light, GL_AMBIENT, white_light);	//change the ambient lighting colour
		if (DiffuseColour[0] != 0.0 || DiffuseColour[1] != 0.0 || DiffuseColour[2] != 0.0) //if diffuse lighting is currently enabled
			glLightfv(light, GL_DIFFUSE, white_light);	//change the diffuse lighting colour
		if (SpecularColour[0] != 0.0 || SpecularColour[1] != 0.0 || SpecularColour[2] != 0.0) //if specular lighting is currently enabled
			glLightfv(light, GL_SPECULAR, white_light);	//change the specular lighting colour
		break;
	case 3://red
		glEnable(light);
		glLightfv(light, GL_AMBIENT, red_light);
		if (DiffuseColour[0] != 0.0 || DiffuseColour[1] != 0.0 || DiffuseColour[2] != 0.0) glLightfv(light, GL_DIFFUSE, red_light);
		if (SpecularColour[0] != 0.0 || SpecularColour[1] != 0.0 || SpecularColour[2] != 0.0) glLightfv(light, GL_SPECULAR, red_light);
		break;
	case 4://blue
		glEnable(light);
		glLightfv(light, GL_AMBIENT, blue_light);
		if (DiffuseColour[0] != 0.0 || DiffuseColour[1] != 0.0 || DiffuseColour[2] != 0.0) glLightfv(light, GL_DIFFUSE, blue_light);
		if (SpecularColour[0] != 0.0 || SpecularColour[1] != 0.0 || SpecularColour[2] != 0.0) glLightfv(light, GL_SPECULAR, blue_light);
		break;
	case 5://green
		glEnable(light);
		glLightfv(light, GL_AMBIENT, green_light);
		if (DiffuseColour[0] != 0.0 || DiffuseColour[1] != 0.0 || DiffuseColour[2] != 0.0) glLightfv(GL_LIGHT0, GL_DIFFUSE, green_light);
		if (SpecularColour[0] != 0.0 || SpecularColour[1] != 0.0 || SpecularColour[2] != 0.0) glLightfv(GL_LIGHT0, GL_SPECULAR, green_light);
		break;
	}
	glutPostRedisplay();
}

//main menu
void mainMenu(GLint selectedOption) {
	switch (selectedOption) {
	case 1:
		break;
	}
}

//light 0 menu
void light0Menu(GLint colourOption) {
	
	lightMenu(GL_LIGHT0, colourOption);

}

//light 1 menu
void light1Menu(GLint colourOption) {
	
	lightMenu(GL_LIGHT1, colourOption);

}

//light 2 menu
void light2Menu(GLint colourOption) {
	
	lightMenu(GL_LIGHT2, colourOption);

}

//cube material menu
void materialMenu(GLint materialOption) {
	switch (materialOption) {
	case 1:
		glMaterialfv(GL_FRONT, GL_AMBIENT, gold_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, gold_specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, gold_diffuse);
		glMaterialfv(GL_FRONT, GL_SHININESS, gold_shininess);
		break;
	case 2:
		glMaterialfv(GL_FRONT, GL_AMBIENT, silver_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, silver_specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, silver_diffuse);
		glMaterialfv(GL_FRONT, GL_SHININESS, silver_shininess);
		break;
	case 3:
		glMaterialfv(GL_FRONT, GL_AMBIENT, copper_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, copper_specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, copper_diffuse);
		glMaterialfv(GL_FRONT, GL_SHININESS, copper_shininess);
		break;
	}
	glutPostRedisplay();
}

//light element menu
void lightElementMenu(GLint lightElementOption) {

	//get current light colours
	GLfloat Light0Colour[4];
	glGetLightfv(GL_LIGHT0, GL_AMBIENT, Light0Colour);

	GLfloat Light1Colour[4];
	glGetLightfv(GL_LIGHT1, GL_AMBIENT, Light1Colour);

	GLfloat Light2Colour[4];
	glGetLightfv(GL_LIGHT2, GL_AMBIENT, Light2Colour);

	switch (lightElementOption) {
	case 1:	//disable specular and diffuse lighting
		glLightfv(GL_LIGHT0, GL_DIFFUSE, black_light);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, black_light);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, black_light);
		glLightfv(GL_LIGHT0, GL_SPECULAR, black_light);
		glLightfv(GL_LIGHT1, GL_SPECULAR, black_light);
		glLightfv(GL_LIGHT2, GL_SPECULAR, black_light);
		break;
	case 2:	//enable diffuse lighting, disable specular lighting
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0Colour);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, Light1Colour);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, Light2Colour);
		glLightfv(GL_LIGHT0, GL_SPECULAR, black_light);
		glLightfv(GL_LIGHT1, GL_SPECULAR, black_light);
		glLightfv(GL_LIGHT2, GL_SPECULAR, black_light);
		break;
	case 3:	//enable specular and diffuse lighting
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0Colour);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, Light1Colour);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, Light2Colour);
		glLightfv(GL_LIGHT0, GL_SPECULAR, Light0Colour);
		glLightfv(GL_LIGHT1, GL_SPECULAR, Light1Colour);
		glLightfv(GL_LIGHT2, GL_SPECULAR, Light2Colour);
		break;
	}
	glutPostRedisplay();
}

// initialize
void initialize() {

	// set background color
	glClearColor(0.5, 0.7, 0.5, 0.0);

	// enable depth test
	glEnable(GL_DEPTH_TEST);

	// enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	// intial light settings - all 3 lights are white with ambient, diffuse, and specular lighting enabled

	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);

	glLightfv(GL_LIGHT0, GL_AMBIENT, white_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

	glLightfv(GL_LIGHT1, GL_AMBIENT, white_light);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);

	glLightfv(GL_LIGHT2, GL_AMBIENT, white_light);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT2, GL_SPECULAR, white_light);

	//sphere is gold initially
	glMaterialfv(GL_FRONT, GL_SPECULAR, gold_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, gold_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, gold_shininess);

	//create menus and submenus
	GLint Light1 = glutCreateMenu(light0Menu);
	glutAddMenuEntry("Off", 1);
	glutAddMenuEntry("White light", 2);
	glutAddMenuEntry("Red light", 3);
	glutAddMenuEntry("Blue light", 4);
	glutAddMenuEntry("Green light", 5);
	GLint Light2 = glutCreateMenu(light1Menu);
	glutAddMenuEntry("Off", 1);
	glutAddMenuEntry("White light", 2);
	glutAddMenuEntry("Red light", 3);
	glutAddMenuEntry("Blue light", 4);
	glutAddMenuEntry("Green light", 5);
	GLint Light3 = glutCreateMenu(light2Menu);
	glutAddMenuEntry("Off", 1);
	glutAddMenuEntry("White light", 2);
	glutAddMenuEntry("Red light", 3);
	glutAddMenuEntry("Blue light", 4);
	glutAddMenuEntry("Green light", 5);
	GLint Materials = glutCreateMenu(materialMenu);
	glutAddMenuEntry("Gold", 1);
	glutAddMenuEntry("Silver", 2);
	glutAddMenuEntry("Copper", 3);
	GLint LightElements = glutCreateMenu(lightElementMenu);
	glutAddMenuEntry("Ambient only", 1);
	glutAddMenuEntry("Ambient and diffuse", 2);
	glutAddMenuEntry("Ambient, diffuse, and specular", 3);
	glutCreateMenu(mainMenu);
	glutAddSubMenu("Light 1", Light1);
	glutAddSubMenu("Light 2", Light2);
	glutAddSubMenu("Light 3", Light3);
	glutAddSubMenu("Material Properties", Materials);
	glutAddSubMenu("Light Elements", LightElements);
	glutAddMenuEntry("Quit", 1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

}


// render sphere
void render() {

	glPushMatrix();

	glutSolidSphere(1.0, 64, 10);

	glPopMatrix();

}


// display registry
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();



	gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);



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
	int windowHandle = glutCreateWindow("TME3 Program 1");
	glutSetWindow(windowHandle);
	glutDisplayFunc(display);
	
	initialize();

	glutReshapeFunc(reshape);

	glutMainLoop();

}