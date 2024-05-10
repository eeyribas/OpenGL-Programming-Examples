#include <glut.h>

void Init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
}

void Triangle(void)
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(5.0, 5.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(25.0, 5.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(5.0, 25.0);
	glEnd();
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	Triangle();
	glFlush();
}

void Reshape(int weight, int height)
{
	glViewport(0, 0, (GLsizei)weight, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (weight <= height)
		gluOrtho2D(0.0, 30.0, 0.0, 30.0 * (GLfloat)height / (GLfloat)weight);
	else
		gluOrtho2D(0.0, 30.0 * (GLfloat)weight / (GLfloat)height, 0.0, 30.0);

	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);

	glutMainLoop();

	return 0;
}