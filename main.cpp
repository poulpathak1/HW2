/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <math.h>

#if __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0,1,4,1};
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1(){

	int rotation = 0;
	double x = 1;
	double y = 0;

	for(int i = 0; i < 10; i++){

		glPushMatrix(); 
		glTranslatef(x, y, 0);  // set up teapot in the scene 
		glRotatef(rotation, 0, 0, 1); // rotation based on the degree
		glutSolidTeapot(0.2); // drawing teapot
		glPopMatrix();

		rotation = rotation + 36;

		y = sin((rotation * 3.14159265)/180); // position of y value in the imaginary circle
		x = cos((rotation * 3.14159265)/180); // position of x value in the imaginary circle	
	}

}


void problem2() {

	double offset = 0.05;

	double x = -2;
	double y = 0.05;
	double z = 0;
	double scale = 0.2;

	for (int i=0; i<16; i++){ 

		scale = scale + 0.06;
		x = x + 0.28;
		y = scale/2; 
		z = z - 0.035;

		glPushMatrix();
		glTranslatef(x, y, z); 
		glutSolidCube(scale);  
		glPopMatrix();
	
	}

}
void problem3() {
    // TODO: Your code here!


	double scale = 0.15;
	double x = 0;
	double y = 1;

	for (int i = 1; i <= 6; i++)
	{
		for (int j = 0; j < i; j++)
		{
			glPushMatrix(); 
			glTranslatef(x, y, 0.5); 
			glutSolidTeapot(scale);	 // creating a teapot
			glPopMatrix();	

			x = x + 0.8; // next teapot on this row

		}
		
		x = i * -0.4; // placing first teapot on additional row
		y = y - 0.3;  // placing next row 
		
	}
	



}

void problem4() {
    // TODO: Your code here!


	//this is an image of a person created using open GL!

	//Creating head
	glPushMatrix(); 
	glTranslatef(0, 1, 0); 
	glScalef(1, 1.5, 1);
	glutSolidSphere(0.25, 16, 16);
	glPopMatrix();

	//creating body
	glPushMatrix(); 
	glTranslatef(0, 0.2, 0); 
	glScalef(1, 1.5, 1);
	glutSolidSphere(0.45, 6, 6);
	glPopMatrix();

	//creating right hand
	glPushMatrix(); 
	glTranslatef(0.4, 1, 0); 
	glScalef(0.1, 1, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	//creating left hand
	glPushMatrix(); 
	glTranslatef(-0.4, 1, 0); 
	glScalef(0.1, 1, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	//creating left leg
	glPushMatrix(); 
	glTranslatef(-0.2, -0.5, 0); 
	glScalef(0.1, 2, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	//creating right leg
	glPushMatrix(); 
	glTranslatef(0.2, -0.5, 0); 
	glScalef(0.1, 2, 0.1);
	glutSolidCube(1);
	glPopMatrix();

}

void display() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
		glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(1,0,0); // x axis
		glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,1,0); // y axis
		glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,windowWidth,windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot,0,1,0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0])*.1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1,(y-lastPos[1])*.1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key-'0';
    if (key == 'q' || key == 'Q' || key == 27){
        exit(0);
    }
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
