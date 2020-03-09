#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include "../og.0.6.SplineCurve/vec3.hpp"

//Vec3 g_Points[7] = {
//	{ 10,10,0 },
//	{  5,10,2 },
//	{ -5,5,0 },
//	{-10,5,-2},
//	{-4,10,0},
//	{-4,5,2},
//	{-8,1,0}
//};
// float g_Knots[] = { 0.0f,0.0f,0.0f,0.0f,1.0f,2.0f,3.0f,4.0f,4.0f,4.0f,4.0f };

Vec3 g_Points[7] = {
	{ 10,  5, 0 },
	{  8, -5, 0 },
	{  6,  5, 0 },
	{  4, -5, 0 },
	{  2,  5, 0 },
	{  0, -5, 0 },
	{ -2,  5, 0 }
};
// float g_Knots[] = { 0.0f,0.1f,0.2f,0.3f,0.4f,0.5f,0.6f,0.7f,0.8f,0.9f,1.0f };
float g_Knots[] = { 0.0f,1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f,10.f };
unsigned int g_num_cvs = 7;
unsigned int g_degree = 3;
unsigned int g_order = g_degree + 1;
unsigned int g_num_knots = g_num_cvs + g_order;

unsigned int LOD = 500;

float CoDeBoor(float u, int i, int k, const float* Knots)
{
	if (1 == k) {
		return (Knots[i] <= u && u <= Knots[i + 1]) ? 1.0f : 0.0f;
	}
	float Den1 = Knots[i + k - 1] - Knots[i];
	float Den2 = Knots[i + k] - Knots[i + 1];
	float Eq1 = 0, Eq2 = 0;
	if (Den1 > 0) {
		Eq1 = ((u - Knots[i]) / Den1) * CoDeBoor(u, i, k - 1, Knots);
	}
	if (Den2 > 0) {
		Eq2 = (Knots[i + k] - u) / Den2 * CoDeBoor(u, i + 1, k - 1, Knots);
	}
	return Eq1 + Eq2;
}

void GetOutpoint(float t, Vec3& point)
{
	for (unsigned int i = 0; i != g_num_cvs; i++) {
		float Val = CoDeBoor(t, i, g_order, g_Knots);
		if (Val > 0.001f) {
			point += Val * g_Points[i];
		}
	}
}

void OnDraw()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	// clear the previous transform
	glLoadIdentity();
	// set the camera position
	gluLookAt(1, 10, 26,	// eye pos
		0, 5, 0,	// aim point
		0, 1, 0);	// up direction
	glColor3f(1, 1, 0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i != LOD; i++) {
		float t = g_Knots[g_num_knots - 1] * i / (float)(LOD - 1);
		// float t = i / (float)(LOD - 1);

		if (i == LOD - 1) t -= 0.001f;

		Vec3 point = { 0, 0, 0 };
		GetOutpoint(t, point);
		glVertex3fv((float*)&point);
	}
	glEnd();

	glColor3f(1, 0, 0);
	glPointSize(3);
	glBegin(GL_POINTS);
	for (int i = 0; i != g_num_cvs; i++) {
		glVertex2fv((float*)& g_Points[i]);
	}
	glEnd();

	// currently we've been drawing to the back buffer, we need
	// to swap the back buffer with the front one to make the image visible
	glutSwapBuffers();
}

void OnReShape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}
	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// just use a perspective projection
	gluPerspective(45, (float)w / h, 0.1, 100);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OnInit()
{
	glEnable(GL_DEPTH_TEST);
}
void OnExit(){}

void OnKeyPress(unsigned char key, int, int)
{
	switch (key) {
	case '+':
		LOD += 2;
		break;
	case '-':
		LOD -= 2;
		if (LOD < 4) LOD = 4;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Nurbs Curve");

	glutDisplayFunc(OnDraw);
	glutReshapeFunc(OnReShape);
	glutKeyboardFunc(OnKeyPress);

	OnInit();

	// set the function to be called when we exit
	atexit(OnExit);

	glutMainLoop();
	return 0;
}