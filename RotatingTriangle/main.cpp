#include <glut.h>

float a = 0;

void Settings(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glShadeModel(GL_FLAT);
}

void Calculation(void)
{
	a = a + 0.5;
	glutPostRedisplay();
}

void Reshape(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width <= height)
		gluOrtho2D(-2.0, 2.0, -2.0 * (float)height / (float)width, 2.0 * (float)height / (float)width);
	else
		gluOrtho2D(-2.0 * (float)width / (float)height, 2.0 * (float)width / (float)height, -2.0, 2.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Triangle(void)
{
	glColor3f(0.0, 1.0, 1.0);
	glRotatef(a, 0.0, 0.0, -1.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(-1.2, -1.2);
	glVertex2f(1.2, -1.2);
	glVertex2f(0.0, 1.2);
	glEnd();
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	Triangle();
	Calculation();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Display");

	Settings();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}