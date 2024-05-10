#include <glut.h>

void Settings(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glShadeModel(GL_FLAT);
}

void DottedLine(void)
{
	glColor3f(0.0, 0.0, 1.0);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xff);
	glBegin(GL_LINES);
	glVertex2f(0.5, 0.4);
	glVertex2f(-0.5, 0.4);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

void Coordinate(void)
{
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, -1.0);
	glVertex2f(0.0, 1.0);
	glVertex2f(1.0, 0.0);
	glVertex2f(-1.0, 0.0);
	glEnd();
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	Coordinate();
	DottedLine();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Coordinate And Dotted Line");

	Settings();
	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}