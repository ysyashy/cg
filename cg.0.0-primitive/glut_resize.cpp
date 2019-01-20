#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <algorithm>

const double TWO_PI = 6.2831835;

GLsizei winWidth = 400, winHeight = 400;
GLuint regHex;

struct Vec2 {
	GLint x, y;
	Vec2() : x(0), y(0){}
	Vec2(int px, int py) : x(px), y(py) {}
};

void createList() {
	Vec2 hexVertex;
	Vec2 circCtr(winWidth / 2, winHeight / 2);
	glClearColor(1, 1, 1, 0);

	glDeleteLists(regHex, 1);
	regHex = glGenLists(1);

	const GLfloat radius = 0.4f * std::min(winWidth, winHeight);

	glNewList(regHex, GL_COMPILE);
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	for (GLint k = 0; k < 6; k++) {
		GLdouble theta = TWO_PI * k / 6.0;
		hexVertex.x = circCtr.x + radius * cos(theta);
		hexVertex.y = circCtr.y + radius * sin(theta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();
}

void regHexagon() {
	glClear(GL_COLOR_BUFFER_BIT);
	glCallList(regHex);
	glFlush();
}

void winReshapeFunc(int newWidth, int newHeight) {
	winWidth = newWidth;
	winHeight = newHeight;
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, winWidth, winHeight);
	glLoadIdentity();
	gluOrtho2D(0, winWidth, 0, winHeight);
	glClear(GL_COLOR_BUFFER_BIT);
	createList();
}

int main1(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Reshape-Function & Display-List Example");

	// createList();
	glutDisplayFunc(regHexagon);
	glutReshapeFunc(winReshapeFunc);
	glutMainLoop();

	return 0;
}