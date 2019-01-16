/*
	Name: Very 6+1
	Author: Hui Zheng

	Description: C++ Open gl project with keyborad interaction
				 
*/



#include <GL/glut.h>
#include <iostream>
#include <random>
#include <ctime>
using namespace std;

GLfloat pos[] = { -2,4,7,1 }, amb[] = { 0.3,0.3,0.3,1.0 };
GLfloat front_amb_diff[] = { 0.8,0.8,0.1,1.0 };
GLfloat back_amb_diff[] = { 0.8,.8,0.1,1.0 };

GLfloat spe[] = { 0.25,0.25,0.25,1.0 };
GLfloat theta = 0, dt = 0.5, axes[3][3] = { {1,0,0},{0,1,0},{0,0,1} };

int axis = 0;
double zoom = 0;
double x_cord = -5;
double y_cord = 5;
double rotate_hammer = 30;
bool isHit = false;
int num_moved = 0;
int right_num = 0;
int num_egg = 0;

void myinit()
{
	GLfloat mat_specular[] = {0, 0, 0.0, 0.0 };
	GLfloat mat_shininess[] = { 10.0 };
	GLfloat light_position[] = { 0, 1, 1, 0.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}
void draw_star(double x) { //draw a single star
	double i = x;			//there are nine points in the star
		glBegin(GL_POLYGON);
		glColor3f(0.9, 1, 0.1);
		glVertex2f(0.4 + i, 0.6 + i);
		glVertex2f(0.1 + i, 0.6 + i);
		glVertex2f(0.3 + i, 0.4 + i);
		glVertex2f(0.2 + i, 0.1 + i);
		glVertex2f(0.5 + i, 0.3 + i);
		glVertex2f(0.8 + i, 0.1 + i);
		glVertex2f(0.7 + i, 0.4 + i);
		glVertex2f(0.9 + i, 0.6 + i);
		glVertex2f(0.6 + i, 0.6 + i);
		glVertex2f(0.5 + i, 0.9 + i);
		glEnd();
}
void draw_stars() {  //the win effect of star
					//this function will rotate stars
	glColor3f(0, 1, 1);
	if (isHit) {
		glRotated(theta, axes[axis][0], axes[axis][1], axes[axis][2]);
	}	
	else {
		glPushMatrix();
			glRotated(theta, 0, 0, 1);
			glLightfv(GL_LIGHT0, GL_POSITION, pos);
		glPopMatrix();
	}
	draw_star(1);
}

void draw_torus() { // draw the donut(torus)
	glColor3f(0, 1, 1);
	if (isHit){
	    glRotated(theta, 1, 1,1 );
	}
	else {
		glPushMatrix();
		glRotated(theta, 0, 0, 1);
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
		glPopMatrix();
	}
	glutSolidTorus(0.2, 0.6, 18, 38);
}

void draw_voal_sphere() { // draw the 5 golden eggs(aka voal sphere)
	glColor3f(0.9, 0.7, 0.2);
	double x = -8;
	for (int i = 0; i < 5; i++) {
		if (isHit) {
			if(i != num_egg) { // when an egg is hit,the function will skip its index
				glPushMatrix();// so that the broken egg will not be draw again
				glTranslated(x + i * 4, 0, 0);
				glScalef(1.0f, 1.5f, 1.0f);
				glLightfv(GL_LIGHT0, GL_POSITION, pos);
				glutSolidSphere(1, 100, 100);
				glPopMatrix();
			}
		}
		else {
			glPushMatrix();
			glRotated(theta, axes[axis][0], axes[axis][1], axes[axis][2]);
			glTranslated(x + i * 4, 0, 0);
			glScalef(1.0f, 1.5f, 1.0f);
			glutSolidSphere(1, 100, 100);
			glPopMatrix();
		}
	}
		glFlush();
}

void draw_hammer() { //this function draws the hammer
	glColor3f(1, 0, 0);

	glPushMatrix();
	glRotated(rotate_hammer, 0, 0, 1);
	glTranslated(x_cord, y_cord, 1);
	glScalef(4.0f, 2.0f, 0.0f); //
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glRotated(rotate_hammer, 0, 0, 1);
	glTranslated(x_cord  , y_cord-1, 1);
	glScalef(1.0f, 10.0f, 0.0f);
	glutSolidSphere(0.1, 100, 100); //
	glPopMatrix();
}
void display(void)
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw_hammer();
	if (isHit) {
		num_egg = num_moved;
		draw_voal_sphere();
		if (right_num == num_moved) { //if the right egg was hit, it will draw stars
			glPushMatrix();			//else draw donut
			glTranslated(-7+(num_moved*4), 0, 1);
			for (int r = 0; r < 360; r +=30) {
				glPushMatrix();
				glRotated(r, 0, 0, 1);
				glTranslated(-0.1, -0.1, 1);
				draw_stars();
				glPopMatrix();

				glPushMatrix();
				glRotated(r, 0, 0, 1);
				glTranslated(1, -0.5, 1);
				draw_stars();
				glPopMatrix();

			}
			glPopMatrix();
		}
		else {
			glPushMatrix();
			glTranslated(-8 + (num_moved * 4), -1, 1);
			draw_torus();
			glPopMatrix();
		}
	}
	else {
		draw_voal_sphere();
		
	}
	glFlush();
}
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	
	case ' ': //break the egg
		if (!isHit) {
			srand(time(NULL));
			right_num = rand() % 10 % 5;
			isHit = true;
			x_cord = -5 + (num_moved * 3);
			y_cord = 6 + (num_moved * -3);	
			rotate_hammer = 45;	
		}
		break;
	case 'r':  //reset all parameters
		axis = 0;
		num_moved = 0;
	    x_cord = -5;
		y_cord = 5;
		rotate_hammer = 30;
		isHit = false;
		num_moved = 0;
		right_num = 0;
		num_egg = 0;
		break;
	}
	glutPostRedisplay();
}

void special_key(int key,int x,int y) {

	switch (key) {

	case GLUT_KEY_LEFT: // move hammer to the left
		if (!isHit && num_moved != 0) {
			x_cord -= 3.5;
			y_cord += 2;
			num_moved--;
		}
		break;
	case GLUT_KEY_RIGHT: //move hammer to the right
		if (!isHit && num_moved != 4) {
			num_moved++;
			x_cord += 3.5;
			y_cord -= 2;
		}
		break;
	}
	glutPostRedisplay();
}

void myReshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -6, 6,-4,3.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void idle(void) {
	theta = (theta < 360) ? theta + dt : dt;
	glMatrixMode(GL_PROJECTION);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	cout << " ****** Welcome to Very 6+1 *******\n"
		<< "You will see five golden eggs, one of them contains golden stars \n"
		<< "To win this game, you need to make the right guess\n"
		<< "Press LEFT or RIGHT arrow key to move the hammer\n"
		<< "Press SPACE to break the egg\n"
		<< "Press R to reset"
		<< "If you see golden stars pop out,  you win\n"
		<< "If you see a blue donut,that means your guess was wrong\n"
		<< "good luck and have fun\n";



	glutInit(&argc, argv);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(400, 100);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Very 6+1 Hui Zheng");
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1.0, 2, 8);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff);

	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_amb_diff);

	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spe);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,75);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslated(0, 0, -5);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_key);
	glutIdleFunc(idle);
	

	glutMainLoop();
}
