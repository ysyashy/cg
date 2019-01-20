#include <GL/glut.h>

void init() {
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 200, 0, 150);
}

void lineSegment() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.4f, 0.2f);

	glBegin(GL_LINES);
	glVertex2i(180, 15);
	glVertex2i(10, 145);
	glEnd();

	glFlush();
}

int main4(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("An Example OpenGL Program");

	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();
	return 0;
}