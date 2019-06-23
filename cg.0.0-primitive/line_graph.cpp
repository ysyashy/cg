#include <GL/glut.h>
#include <iostream>
#include <algorithm>
#include <numeric>

namespace chart {

GLsizei win_Width = 600, win_Height = 500;
GLint xRaster = 35, yRaster = 150;

struct Vec2 {
	GLint x, y;
	Vec2() : x(0), y(0) {}
	Vec2(GLint px, GLint py) : x(px), y(py) {}
	Vec2 &operator=(const Vec2 &o) {
		this->x = o.x;
		this->y = o.y;
		return *this;
	}
};

GLubyte label[36] = {
	'J', 'a', 'n',  'F', 'e', 'b', 'M', 'a', 'r',
	'A', 'p', 'r',  'M', 'a', 'y', 'J', 'u', 'n',
	'J', 'u', 'l',  'A', 'u', 'g', 'S', 'e', 'p',
	'O', 'c', 't',  'N', 'o', 'v', 'D', 'e', 'c'
};

GLint data[] = {
	420, 342, 324, 310, 262, 185,
	190, 196, 217, 240, 312, 438
};

void init() {
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 600, 0, 500);
}

void lineGraph() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < sizeof(data) / sizeof(GLint); i++) {
		glVertex2i(30 + i * 50, data[i]);
	}
	glEnd();

	glColor3f(1.0f, 0, 0);
	for (int i = 0; i < 12; i++) {
		glRasterPos2i(xRaster + i * 50, data[i]);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '*');
	}

	glColor3f(0, 0, 0);
	xRaster = 20;
	for (int month = 0; month < 12; month++) {
		glRasterPos2d(xRaster, yRaster);
		for (int i = 3 * month; i < 3 * month + 3; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[i]);
		}
		xRaster += 50;
	}
	glFlush();
}

void barChart() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	for (int i = 0; i < 12; i++) {
		glRecti(20 + i * 50, 165, 40 + i * 50, data[i]);
	}
	glColor3f(0, 0, 0);
	xRaster = 20;
	for (int m = 0; m < 12; m++) {
		glRasterPos2i(xRaster, yRaster);
		for (int i = 3 * m; i < 3 * m + 3; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[i]);
			xRaster += 50;
		}
	}
	glFlush();
}

void pieChart() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);

	Vec2 vCircle(win_Width / 2, win_Height / 2);
	GLint radius = std::min(win_Width, win_Height) / 4;

	// draw a circle
	int simple = 360;
	glBegin(GL_POINTS);
	while (simple > 0) {
		glVertex2f(vCircle.x + radius * cos(simple)
			, vCircle.y + radius * sin(simple));
		simple--;
	}
	glEnd();

	GLfloat values[] = {
		10.0f, 7.0f, 13.0f, 5.0f, 13.0f, 14.0f,
		3.0f, 16.0f, 5.0f, 17.0f, 8.0f
	};
	GLfloat sum = std::accumulate(std::begin(values), std::end(values), 0);

	GLfloat sliceAngle, previousSliceAngle = 0.0f;
	const GLfloat twoPi = 6.28f;
	Vec2 vPie;
	for (int i = 0; i < 12; i++) {
		sliceAngle = twoPi * values[i] / sum + previousSliceAngle;
		vPie.x = vCircle.x + radius * cos(sliceAngle);
		vPie.y = vCircle.y + radius * sin(sliceAngle);
		glBegin(GL_LINES);
		glVertex2i(vCircle.x, vCircle.y);
		glVertex2i(vPie.x, vPie.y);
		glEnd();
		previousSliceAngle = sliceAngle;
	}

	glFlush();
}

void winReshapeFunc(GLint newWidth, GLint newHeight) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, newWidth, 0, newHeight);
	glClear(GL_COLOR_BUFFER_BIT);
}

}


int main6(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(chart::win_Width, chart::win_Height);
	glutCreateWindow("Line Chart Data Plot");

	chart::init();
	// glutDisplayFunc(lineGraph);
	// glutDisplayFunc(chart::barChart);
	glutDisplayFunc(chart::pieChart);
	glutReshapeFunc(chart::winReshapeFunc);
	glutMainLoop();

	return 0;
}
