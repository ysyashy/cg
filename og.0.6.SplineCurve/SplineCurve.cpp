#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "vec3.hpp"

/* Set initial size of the display window. */
const GLsizei winWidth = 600, winHeight = 600;

/* Set size of world-coordinate clipping window. */
const GLfloat xwcMin = -50, xwcMax = 50;
const GLfloat ywcMin = -50, ywcMax = 50;

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

GLfloat hermite_son(GLfloat p1, GLfloat p2, GLfloat d1, GLfloat d2, GLfloat u) {
	GLfloat u2 = u * u;
	GLfloat u3 = u2 * u;

	GLfloat h0 = 2 * u3 - 3 * u2 + 1;
	GLfloat h1 = -2 * u3 + 3 * u2;
	GLfloat h2 = u3 - 2 * u2 + u;
	GLfloat h3 = u3 - u2;
	return p1 * h0 + p2 * h1 + d1 * h2 + d2 * h3;
}

void hermite(Vec3 points[], GLfloat derivative[], GLint len) {
	const int simples = 100;
	Vec3 p;

	for (GLuint i = 0; i < len - 1; i++) {
		glBegin(GL_POINTS);
		GLfloat deriv1 = derivative[i];
		GLfloat deriv2 = derivative[i + 1];
		GLfloat dt = 1.0f / simples;
		for (GLfloat t = 0; t < 1.0f; t += dt) {
			p.x = hermite_son(points[i].x, points[i + 1].x, deriv1, deriv2, t);
			p.y = hermite_son(points[i].y, points[i + 1].y, deriv1, deriv2, t);
			// p.z = hermite_son(points[i].z, points[i + 1].z, derivative[i].z, derivative[i + 1].z, t);
			glVertex2f(p.x * 40, p.y * 40);
		}
		glEnd();
	}
}

void cardinal(Vec3 points[], GLuint len, bool isLoop) {
	glBegin(GL_POINTS);
	GLfloat s = 0.5f * (1 - 0);
	int k = 0;
	int loop = len;
	if (!isLoop) { 
		k = 1; 
		loop -= 2;
	}
	for (; k < loop; k++) {
		Vec3 &p0 = points[(k - 1 + len) % len];
		Vec3 &p1 = points[(k + len) % len];
		Vec3 &p2 = points[(k + 1 + len) % len];
		Vec3 &p3 = points[(k + 2 + len) % len];
		const GLfloat step = 1.0f / 50;
		for (GLfloat u = 0; u < 1.0f; u += step) {
			GLfloat u_2 = u * u, u_3 = u_2 * u;
			GLfloat car_0 = -s * u_3 + 2 * s*u_2 - s * u,
				car_1 = (2 - s)*u_3 + (s - 3)*u_2 + 1,
				car_2 = (s - 2)*u_3 + (3 - 2 * s)*u_2 + s * u,
				car_3 = s * u_3 - s * u_2;
			GLfloat x = p0.x * car_0 + p1.x * car_1 + p2.x * car_2 + p3.x * car_3;
			GLfloat y = p0.y * car_0 + p1.y * car_1 + p2.y * car_2 + p3.y * car_3;
			glVertex2f(x * 4, y * 4);
		}
	}
	glEnd();
}

//GLfloat Cox_deBoor(int k, int d, int u, GLfloat arr[]) {
//	return 0.0f;
//}

inline GLfloat square(GLfloat x) { return x * x; }
inline GLfloat cube(GLfloat x) { return x * x * x; }

GLfloat B_0_3(GLfloat u) {
	if (0 <= u && u < 1) {
		return 0.5f * u * u;
	} else if (1 <= u && u < 2) {
		return 0.5f * u * (2 - u) + 0.5f * (u - 1) * (3 - u);
	} else {
		return 0.5f * square(3 - u);
	}
}

GLfloat B_1_3(GLfloat u) {
	if (1 <= u && u < 2) {
		return 0.5f * square(u - 1);
	} else if (2 <= u && u < 3) {
		return 0.5f * (u - 1) * (3 - u) + 0.5f * (u - 2) * (4 - u);
	} else {
		return 0.5f * square(4 - u);
	}
}

GLfloat B_2_3(GLfloat u) {
	if (2 <= u && u < 3) {
		return 0.5f * square(u - 2);
	} else if (3 <= u && u < 4) {
		return 0.5f * (u - 2) * (4 - u) + 0.5f * (u - 3) * (5 - u);
	} else {
		0.5f * square(5 - u);
	}
}
GLfloat B_3_3(GLfloat u)
{
	if (3 <= u && u < 4) {
		return 0.5f * square(u - 3);
	} else if (4 <= u && u < 5) {
		return 0.5f * (u - 3) * (5 - u) + 0.5f * (u - 4) * (6 - u);
	} else {
		return 0.5f * square(6 - u);
	}
}

GLfloat PU(int k, GLfloat u)
{
	if (k == 0) { return B_0_3(u); }
	else if (k == 1) { return B_1_3(u); }
	else if (k == 2) { return B_2_3(u); }
	else { return B_3_3(u); }
}
void BSpline() {
	// k, d
	// u_arr
	// P(u) = p(k) * B-k,d (u)
	Vec3 cp[] = {
		{0, 0, 0},
		{1, 2, 0},
		{2, -1, 0},
		{3, 0, 0}
	};
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < 4; i++) {
		glVertex2f(cp[i].x * 10, cp[i].y * 10);
	}
	glColor3f(0.0, 0.0, 0.0);
	
	for (GLfloat u = 0; u < 4; u += 0.1f) {
		Vec3 pu = { 0,0,0 };
		for (int k = 0; k < 4; k++) {
			GLfloat bkd = PU(k, u);
			pu.x += cp[k].x * bkd;
			pu.y += cp[k].y * bkd;
		}
		// draw (pu.x, pu.y)
		glVertex2f(pu.x * 10, pu.y * 10);
	}
	glEnd();
}

void displayFunc() {
	/**
	 * Set example number of control points and number of
	 * curve positions to be plotted along the Bezier curve.
	 */
	/*GLint nBezCurvePts = 1000;
	Vec3 ctrlPoints[] = {
		{-40, -40, 0}, {-10, 40, 0},
		{10, -40, 0}, {40, 40, 0} };
	int ctrlPts = sizeof(ctrlPoints)/sizeof(Vec3);*/

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(2);

	BSpline();

	/*glBegin(GL_POINTS);
	for (int i = 0; i < ctrlPts; i++) {
		glVertex2f(ctrlPoints[i].x, ctrlPoints[i].y);
	}
	glEnd();*/

	//Vec3 points[] = {
	//	{0, 1, 0 }, {1, 0, 0}
	//};
	//GLfloat derivative[] = {1, 2};
	//glPointSize(1);
	//glColor3f(0, 0, 0);
	//glBegin(GL_LINES);
	//// y-axis
	//glVertex2f(0, -100);
	//glVertex2f(0, 100);
	//// x-axis
	//glVertex2f(-100, 0);
	//glVertex2f(100, 0);
	//glEnd();
	//glPointSize(2);
	//glColor3f(1.0, 0.0, 0.0);
	// hermite(points, derivative, 2);
	// bezier(ctrlPoints, ctrlPts, nBezCurvePts);
	/*Vec3 cardinal_points[] = {
		{0, 0, 0 }, {3, 6, 0}, {6, 6, 0}, {10, 0, 0}
	};
	cardinal(cardinal_points, 4, true);*/
	glFlush();
}

void winReshapeFunc(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newHeight, newWidth);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main1(int argc, char *argv[]) {
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
