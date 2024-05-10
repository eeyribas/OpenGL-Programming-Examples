#include <glut.h>
#include <stdio.h>

void Init(void)
{
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSolidSphere(1.0, 20, 16);
	glFlush();
}

void Reshape(int weight, int height)
{
	glViewport(0, 0, (GLsizei)weight, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (weight <= height)
		glOrtho(-1.5, 1.5, -1.5 * (GLfloat)height / (GLfloat)weight, 1.5 * 
				(GLfloat)height / (GLfloat)weight, -10.0, 10.0);
	else
		glOrtho(-1.5 * (GLfloat)weight / (GLfloat)height, 1.5 * (GLfloat)weight / 
				(GLfloat)height, -1.5, 1.5, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);

	glutMainLoop();

	return 0;
}