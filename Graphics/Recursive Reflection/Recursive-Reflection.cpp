/* Athabasca University
   Comp390 - Introduction to Computer Graphics
   TME4: Ray Tracing
   Program 1: Recursive reflection

   @author: Jonathan Kalmar
   @ID: 3455526
   @date: December 27th, 2019
*/

#include <iostream>
#include <math.h>
#include "gl/glut.h"
#include "plane.h"

using namespace std;

// viewer
vector3 viewer(-40.0, 40.0, 120.0);

// floor
vector3 floorNormal(0.0, 1.0, 0.0);

plane   floorDef(0.0, 4.0, 0.0, 0.0);

vector3 floorLimit1(-75.0, 0, -75.0);

vector3 floorLimit2(-75.0, 0, 75.0);

vector3 floorLimit3(75.0, 0, 75.0);

vector3 floorLimit4(75.0, 0, -75.0);

// wall
vector3 wallNormal(0.0, 0.0, 1.0);

plane   wall(0.0, 0.0, 4.0, 0.0);

vector3 wallLimit1(-25.0, 0.0, 0.0);

vector3 wallLimit2(-25.0, 50.0, 0.0);

vector3 wallLimit3(25.0, 50.0, 0.0);

vector3 wallLimit4(25.0, 0.0, 0.0);

// colors
vector3 grey(0.75, 0.75, 0.75);

vector3 lightRed(0.75, 0.1, 0.1);

// lighting position
vector3 lightPosition(25, 25, 100.0);

// lighting elements
float ambient_coef = 0.3;

float diffuse_coef = 0.7;

float reflect_coef = 0.4;

float local_coef = 0.6;


// initialize

void initialize() {

	// set background color

	glClearColor(0.5, 0.7, 0.5, 0.0);

}


// calculate local color
// local color is intensity * base color
vector3 localColor(vector3 intersect, vector3 baseColor, vector3 normal) {

	// calculate unit vector
	vector3 origin = lightPosition.subtract(intersect);

	vector3 unitVec = origin.normalize();

	// calculate dot product
	float dotProd = unitVec.dot(normal);

	// calculate intensity
	float ambientContr = ambient_coef;

	float diffuseContr = diffuse_coef * dotProd;

	float intensity = ambientContr + diffuseContr;


	if (intensity > 1.0) intensity = 1.0;


	float r = intensity * baseColor.x;

	float g = intensity * baseColor.y;

	float b = intensity * baseColor.z;


	return vector3(r, g, b);

}

bool intersectWall(vector3 origin, vector3 ray) {//determines whether or not the ray intersects the wall
	vector3 intersect = wall.intersect(origin, ray);//find where the ray intersects the wall plane
	if (intersect.x >= wallLimit1.x && intersect.x <= wallLimit3.x && intersect.y >= wallLimit1.y && intersect.y <= wallLimit3.y)//if it is inside the wall, return true
		return true;
	else
		return false;
}

bool intersectFloor(vector3 origin, vector3 ray) {//determine whether or not the ray intersects the floor
	vector3 intersect = floorDef.intersect(origin, ray);//find where the ray intersects the floor plane
	if (intersect.x >= floorLimit1.x && intersect.x <= floorLimit3.x && intersect.z >= floorLimit1.z && intersect.z <= floorLimit3.z && (ray.cross(intersect)).distance(origin) != 0)//if its inside the floor, return true
		return true;
	else
		return false;
}

vector3 rayTracer(vector3 intersect, vector3 incidentRay) {//calculate and return the color at the intersection point
	vector3 localClr(0.0, 0.0, 0.0);
	vector3 reflectiveClr(0.0, 0.0, 0.0);
	vector3 color(0.0, 0.0, 0.0);

	//if the ray does not intersect an object, return no contribution
	if (!intersectFloor(intersect, incidentRay) && !intersectWall(intersect, incidentRay))
		return color;

	// else if the ray hits the wall, return red
	else if (intersectWall(intersect, incidentRay)) {
		color = localColor(incidentRay, lightRed, wallNormal);
	}

	// else if the ray hits the floor, return grey mixed with a reflection component, calculated recursively
	else if (intersectFloor(intersect, incidentRay)) {
		localClr = localColor(incidentRay, grey, floorNormal);
		vector3 reflect = incidentRay.subtract(intersect).reflect(floorNormal);//reflect ray
		reflectiveClr = rayTracer(incidentRay, incidentRay.add(reflect));//calculate the reflective color recursively
		if (reflectiveClr.dot(vector3(1, 1, 1)) == 0.0) color = localClr;//if the reflective component is 0 then the color is the local color
		else color = localClr.scalar(local_coef).add(reflectiveClr.scalar(reflect_coef));//otherwise we mix in the reflective color
	}

	return color;
}

void render() {

	// render the floor
	for (int i = -75; i < 75; i++) {

		for (int j = -75; j < 75; j++) {

			vector3 intersect = vector3(i, 0, j);

			//cast a ray from the camera to the pixel and ray trace to determine its colour
			vector3 mixedColor = rayTracer(viewer, intersect);

			glColor3f(mixedColor.x, mixedColor.y, mixedColor.z);


			// use the small rectangles method

			glBegin(GL_POLYGON);

			glVertex3i(i, 0, j);

			glVertex3i(i + 1, 0, j);

			glVertex3i(i + 1, 0, j + 1);

			glVertex3i(i, 0, j + 1);

			glEnd();

		}

	}



	// render the wall

	for (int m = -25; m < 25; m++) {

		for (int n = 0; n < 50; n++) {
			
			vector3 intersect = vector3(m, n, 0);
			
			//cast a ray from the camera to the pixel and ray trace to determine its colour
			vector3 color = rayTracer(viewer, intersect);
			
			glColor3f(color.x, color.y, color.z);

			glRecti(m, n, m + 1, n + 1);

		}

	}

}



// display registry

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();



	gluLookAt(viewer.x, viewer.y, viewer.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);



	render();



	glutSwapBuffers();

}



// reshape registry

void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 200.0);

	glMatrixMode(GL_MODELVIEW);

}



// main program

void main(int argc, char** argv)

{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(500, 500);

	glutInitWindowPosition(100, 100);



	int windowHandle = glutCreateWindow("TME4 Program 1");

	glutSetWindow(windowHandle);



	glutDisplayFunc(display);

	glutReshapeFunc(reshape);



	initialize();



	glutMainLoop();
}
