#include <GL/glut.h>
#include <cmath>
#include <iostream>

namespace curve {

struct Vec2 {
	GLint x, y;
	Vec2() : x(0), y(0){}
	Vec2(GLint px, GLint py) : x(px), y(py) {}
	Vec2 &operator=(const Vec2 &o) {
		this->x = o.x;
		this->y = o.y;
		return *this;
	}
};

enum class CurveType : int {
	Limacon = 1,
	Cardioid,
	ThreeLeaf,
	FourLeaf,
	Spiral
};

GLsizei winWidth = 600, winHeight = 500;

void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 200, 0, 150);
}

void lineSegment(Vec2 p1, Vec2 p2) {
	glBegin(GL_LINES);
	glVertex2i(p1.x, p1.y);
	glVertex2i(p2.x, p2.y);
	glEnd();
}

void drawCurve(CurveType type) {
	const GLdouble twoPi = 6.283185;
	const GLint a = 175, b = 60;
	const GLint x0 = 200, y0 = 250;

	Vec2 curvePos[2];
	glColor3f(0, 0, 0);
	curvePos[0].x = x0;
	curvePos[0].y = y0;

	switch (type) {
	case curve::CurveType::Limacon:
		curvePos[0].x += a + b;
		break;
	case curve::CurveType::Cardioid:
		curvePos[0].x += a + a;
		break;
	case curve::CurveType::ThreeLeaf:
		curvePos[0].x += a;
		break;
	case curve::CurveType::FourLeaf:
		curvePos[0].x += a;
		break;
	case curve::CurveType::Spiral:
	default:
		break;
	}

	const GLfloat dtheta = 1.0f / a;
	GLfloat theta = dtheta;
	GLfloat r;
	while (theta < twoPi) {
		switch (type) {
		case curve::CurveType::Limacon:
			r = a * cos(theta) + b;
			break;
		case curve::CurveType::Cardioid:
			r = a * (1 + cos(theta));
			break;
		case curve::CurveType::ThreeLeaf:
			r = a * cos(3 * theta);
			break;
		case curve::CurveType::FourLeaf:
			r = a * cos(2 * theta);
			break;
		case curve::CurveType::Spiral:
			r = (a / 4.0f) * theta;
			break;
		default:
			break;
		}
		curvePos[1].x = x0 + r * cos(theta);
		curvePos[1].y = y0 + r * sin(theta);
		lineSegment(curvePos[0], curvePos[1]);

		curvePos[0] = curvePos[1];
		theta += dtheta;
	}
}

void displayFunc() {
	std::cout << "Please enter a number.\n"
		<< "1.limacon, 2.cardioid, 3.threeLeaf, 4.fourLeaf, 5.spiral.\n";
	int id = 2;
	// std::cin >> id;
	switch (id) {
	case 1:
		drawCurve(CurveType::Limacon);	break;
	case 2:
		drawCurve(CurveType::Cardioid);	break;
	case 3:
		drawCurve(CurveType::ThreeLeaf);	break;
	case 4:
		drawCurve(CurveType::FourLeaf);	break;
	case 5:
		drawCurve(CurveType::Spiral);	break;
	default:
		break;
	}
	glFlush();
}

void winReshapeFunc(GLint w, GLint h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glClear(GL_COLOR_BUFFER_BIT);
}

}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(curve::winWidth, curve::winHeight);
	glutCreateWindow("Draw Curve");

	curve::init();
	glutDisplayFunc(curve::displayFunc);
	glutReshapeFunc(curve::winReshapeFunc);

	glutMainLoop();
	return 0;
}