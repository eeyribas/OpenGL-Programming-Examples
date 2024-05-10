#include <stdlib.h>           
#include <math.h>
#include <glut.h>

void Settings(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glShadeModel(GL_FLAT);
	glPolygonMode(GL_FRONT, GL_FILL);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);

	double cel = 0;
	for (int i = 0; i < 360; i++) {
		cel = 2 * 3.14 * i / 360;
		glVertex2f(cos(cel) * 0.5, sin(cel) * 0.5);
	}

	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Circle");

	Settings();
	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}