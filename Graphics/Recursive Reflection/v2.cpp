/*#include <iostream>

#include <math.h>

#include "gl/glut.h"



#include "plane.h"



using namespace std;

//false
vector3 origin(0.0, 0.0, 0.0);
vector3 falseVect(9999.99, 9999.99, 9999.99);
float falseDist = origin.distance(falseVect);

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

	wall.setP1(wallLimit1);
	wall.setP2(wallLimit2);
	wall.setP3(wallLimit3);
	wall.setP4(wallLimit4);

	floorDef.setP1(floorLimit1);
	floorDef.setP2(floorLimit2);
	floorDef.setP3(floorLimit3);
	floorDef.setP4(floorLimit4);

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
float findMin(float a, float b, float c, float d) {
	if (a <= b && a <= c && a <= d) return a;
	else if (b <= a && b <= c && b <= d) return b;
	else if (c <= a && c <= b && c <= d) return c;
	else return d;
}
float findMax(float a, float b, float c, float d) {
	if (a >= b && a >= c && a >= d) return a;
	else if (b >= a && b >= c && b >= d) return b;
	else if (c >= a && c >= b && c >= d) return c;
	else return d;
}

vector3 intersectRect(vector3 origin, vector3 ray, plane plane) {//determines whether or not a ray intersects a rectangle. Returns -1 if not, returns the distance to the plane otherwise.
	vector3 P1 = plane.getP1();
	vector3 P2 = plane.getP2();
	vector3 P3 = plane.getP3();
	vector3 P4 = plane.getP4();

	float xmin = findMin(P1.x, P2.x, P3.x, P4.x);
	float xmax = findMax(P1.x, P2.x, P3.x, P4.x);
	float ymin = findMin(P1.y, P2.y, P3.y, P4.y);
	float ymax = findMax(P1.y, P2.y, P3.y, P4.y);
	float zmin = findMin(P1.z, P2.z, P3.z, P4.z);
	float zmax = findMax(P1.z, P2.z, P3.z, P4.z);

	vector3 intersect = plane.intersect(origin,ray);
	if (intersect.x >= xmin && intersect.x <= xmax && intersect.y >= ymin && intersect.y <= ymax && intersect.z >= zmin && intersect.z <= zmax)
		return intersect;
	else
		return falseVect;
	//vector3 normal(plane.a, plane.b, plane.c);
	//float d = plane.d;
	//float distance = -(origin.dot(normal) + d) / (unitVec.dot(normal));

}

vector3 rayTracer(vector3 intersect, vector3 incidentRay) {

	vector3 color(0.0, 0.0, 0.0);
	vector3 wallIntersect = intersectRect(intersect, incidentRay, wall);
	vector3 floorIntersect = intersectRect(intersect, incidentRay, floorDef);

	if (wallIntersect.distance(origin)==falseDist && floorIntersect.distance(origin)==falseDist)
		return color;
	else if (wallIntersect.distance(origin) != falseDist) {
		color = localColor(incidentRay, lightRed, wallNormal);
	}
	else  {//if (floorIntersect.distance(origin) != falseDist)
		vector3 reflect = incidentRay.subtract(intersect).reflect(floorNormal);
		vector3 reflectedRay = incidentRay.add(reflect);
		color = localColor(incidentRay, grey, floorNormal);
		color = color.scalar(local_coef).add(rayTracer(incidentRay, reflectedRay).scalar(reflect_coef));
	}
	return color;
}
void render() {

	// render the floor

	for (int i = -75; i < 75; i++) {

		for (int j = -75; j < 75; j++) {

			vector3 intersect = vector3(i, 0, j);

			vector3 incidentRay = intersect.subtract(viewer);

			vector3 color = localColor(intersect, grey, floorNormal);
			vector3 mixedColor = rayTracer(viewer, intersect);
			vector3 reflect = intersect.subtract(viewer).reflect(floorNormal);

			vector3 reflectColor = rayTracer(intersect, intersect.add(reflect));

			//vector3 mixedColor = color.scalar(local_coef).add(reflectColor.scalar(reflect_coef));

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



	// render the wall - non-reflective surface

	for (int m = -25; m < 25; m++) {

		for (int n = 0; n < 50; n++) {
			vector3 intersect = vector3(m, n, 0);
			vector3 color = rayTracer(viewer, intersect);
			//vector3 color = localColor(vector3(m, n, 0), lightRed, wallNormal);
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



	int windowHandle = glutCreateWindow("Athabasca University - Comp390 U11 S2 O2");

	glutSetWindow(windowHandle);



	glutDisplayFunc(display);

	glutReshapeFunc(reshape);



	initialize();



	glutMainLoop();

}*/