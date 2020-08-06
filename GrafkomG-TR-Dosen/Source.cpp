#include <iostream>
#include <GL/freeglut.h>
#include "nfgLoader.h"
#include "tgaLoader.h"

//tweening
float xpos = 0;
float deltax = 1;
//mouse
float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;
//keyboard
float xsca = 1.0f;
float ysca = 1.0f;
float zsca = 1.0f;
float xtra = 0.0f;
float ytra = 0.0f;
float ztra = 0.0f;

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glScalef(xsca, ysca, zsca);
	glTranslatef(xtra, ytra, ztra);
	glTranslatef(0, -1, 0);
	//glBegin(GL_QUADS);
	//glVertex2f(-10.0, -10.0);
	//glVertex2f(-10.0, 10.0);
	//glVertex2f(10.0, 10.0);
	//glVertex2f(10.0, -10.0);
	//glEnd();


	Tga info = Tga("Woman1.tga");
	glEnable(GL_TEXTURE_2D);

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info.GetWidth(), info.GetWidth(),
		0, GL_BGR_EXT, GL_UNSIGNED_BYTE, info.GetPixels().data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//vertex
	float x1 = 0, x2, x3, y1, y2, y3, z1, z2, z3, u1, u2, u3, v1, v2, v3;
	for (int i = 0; i < 718; i++) {

		//kordinatvertex
		x1 = KordinatV[index[i].i1].x; x2 = KordinatV[index[i].i2].x; x3 = KordinatV[index[i].i3].x;
		y1 = KordinatV[index[i].i1].y; y2 = KordinatV[index[i].i2].y; y3 = KordinatV[index[i].i3].y;
		z1 = KordinatV[index[i].i1].z; z2 = KordinatV[index[i].i2].z; z3 = KordinatV[index[i].i3].z;
		//koordinattexture
		u1 = KordinatV[index[i].i1].u; u2 = KordinatV[index[i].i2].u; u3 = KordinatV[index[i].i3].u;
		v1 = KordinatV[index[i].i1].v; v2 = KordinatV[index[i].i2].v; v3 = KordinatV[index[i].i3].v;

		glBegin(GL_POLYGON);
		glTexCoord2f(u1, v1); 
		glVertex3f(x1, y1, z1);

		glTexCoord2f(u2, v2); 
		glVertex3f(x2, y2, z2);

		glTexCoord2f(u3, v3); 
		glVertex3f(x3, y3, z3);
		glEnd();
	}

	glPopMatrix();
	glutSwapBuffers();

}

void myinit(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	GLfloat ambientlight[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuselight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularlight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { -80.0, 0.0, 50.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientlight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuselight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, specularlight);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);


	glPointSize(2.0);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	glOrtho(-5, 5, -5, 5, -5, 5);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2, 2, -2 * (GLfloat)h / (GLfloat)w,
			2 * (GLfloat)h / (GLfloat)w, -2, 2);
	else
		glOrtho(-2 * (GLfloat)w / (GLfloat)h,
			2 * (GLfloat)w / (GLfloat)h, -2, 2, -2, 2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle()
{
	if (!mouseDown)
	{
		xrot += 0.3f;
		yrot += 0.4f;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseDown = true;
		xdiff = x - yrot;
		ydiff = -y + xrot;
	}
	else
		mouseDown = false;
}

void mouseMotion(int x, int y)
{
	if (mouseDown)
	{
		yrot = x - xdiff;
		xrot = y + ydiff;

		glutPostRedisplay();
	}
}

void myKeyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'w'://ZoomIn
	case 'W':
		//glScalef(1.05, 1.05, 1.05);
		xsca += 0.1;
		ysca += 0.1;
		zsca += 0.1;
		break;
	case 's'://ZoomOut
	case 'S':
		xsca += -0.1;
		ysca += -0.1;
		zsca += -0.1;
		break;
	case 'a':
	case 'A': //CameraLeft
		xtra += 0.1;
		break;
	case 'd':
	case 'D': //CameraRight
		xtra -= 0.1;
		break;
	}
	Display();
}

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);

	yrot += 1;

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(250, 80);
	glutCreateWindow("Bimo Adam - 672018274 | Yosefhin R.Y - 672018412");

	myinit();
	load("Woman1.nfg");
	glutDisplayFunc(Display);
	glutTimerFunc(0, timer, 0);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);


	glutMainLoop();
	return 1;
}