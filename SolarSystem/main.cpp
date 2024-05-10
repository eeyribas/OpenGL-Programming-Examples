#include <glut.h>

static int year = 0, day = 0;

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glutWireSphere(1.0, 20, 16);
	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
	glTranslatef(2.0, 0.0, 0.0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
	glutWireSphere(0.2, 10, 8);
	glPopMatrix();
	glutSwapBuffers();
}

void Init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void Reshape(int weight, int height)
{
	glViewport(0, 0, (GLsizei)weight, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)weight / (GLfloat)height, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 'd':
			day = (day + 10) % 360;
			glutPostRedisplay();   
			break;
		case 'D':
			day = (day - 10) % 360;
			glutPostRedisplay();   
			break;
		case 'y':
			year = (year + 5) % 360;
			glutPostRedisplay();   
			break;
		case 'Y':
			year = (year - 5) % 360;
			glutPostRedisplay();   
			break;
		default:
			break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

	glutMainLoop();

	return 0;
}