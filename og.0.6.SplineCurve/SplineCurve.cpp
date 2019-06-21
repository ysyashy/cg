#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

/* Set initial size of the display window. */
const GLsizei winWidth = 600, winHeight = 600;

/* Set size of world-coordinate clipping window. */
const GLfloat xwcMin = -50, xwcMax = 50;
const GLfloat ywcMin = -50, ywcMax = 50;

struct Vec3 {
	GLfloat x, y, z;
};

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void binomialCoefficients(GLint n, GLint *C) {
	for (GLint k = 0; k <= n; k++) {
		/* Compute n!/(k!(n-k)!) . */
		C[k] = 1;
		for (GLint j = n; j >= k + 1; j--)
			C[k] *= j;
		for (GLint j = n - k; j >= 2; j--)
			C[k] /= j;
	}
}

void computeBezPt(GLfloat u, Vec3 *bezPt, GLint nCtrlPts, Vec3 *ctrlPts, GLint *C) {
	GLint k, n = nCtrlPts - 1;
	GLfloat bezBlendFcn;

	bezPt->x = bezPt->y = bezPt->z = 0;
	/* compute blending functions and blend control points. */
	for (k = 0; k < nCtrlPts; k++) {
		bezBlendFcn = C[k] * pow(u, k) * pow(1 - u, n - k);
		bezPt->x += ctrlPts[k].x * bezBlendFcn;
		bezPt->y += ctrlPts[k].y * bezBlendFcn;
		bezPt->z += ctrlPts[k].z * bezBlendFcn;
	}
}

void bezier(Vec3 *ctrlPoints, GLint nCtrlPts, GLint nBezCurvePts) {
	Vec3 bezCurvePt;
	GLfloat u;
	GLint *C, k;

	/* Allocate space for binonial coefficients */
	C = new GLint[nCtrlPts];

	binomialCoefficients(nCtrlPts - 1, C);
	for (k = 0; k <= nBezCurvePts; k++) {
		u = GLfloat(k) / GLfloat(nBezCurvePts);
		computeBezPt(u, &bezCurvePt, nCtrlPts, ctrlPoints, C);

		glBegin(GL_POINTS);
		glVertex2f(bezCurvePt.x, bezCurvePt.y);
		glEnd();
	}
}

void displayFunc() {
	/**
	 * Set example number of control points and number of
	 * curve positions to be plotted along the Bezier curve.
	 */
	GLint nBezCurvePts = 1000;
	Vec3 ctrlPoints[] = {
		{-40, -40, 0}, {-10, 40, 0},
		{10, -40, 0}, {40, 40, 0} };
	int ctrlPts = sizeof(ctrlPoints)/sizeof(Vec3);

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	glPointSize(10);

	glBegin(GL_POINTS);
	for (int i = 0; i < ctrlPts; i++) {
		glVertex2f(ctrlPoints[i].x, ctrlPoints[i].y);
	}
	glEnd();

	
	glPointSize(4);
	glColor3f(1.0, 0.0, 0.0);
	bezier(ctrlPoints, ctrlPts, nBezCurvePts);
	glFlush();
}

void winReshapeFunc(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newHeight, newWidth);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("spline curve");

	init();
	glutDisplayFunc(displayFunc);
	glutReshapeFunc(winReshapeFunc);

	glutMainLoop();

	return 0;
}
