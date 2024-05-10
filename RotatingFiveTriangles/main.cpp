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

void Triangle(void) 
{
	glColor3f(0.0, 1.0, 1.0);
	glRotatef(a, 0.0, 0.0, -1.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.2, -0.2);
	glVertex2f(0.2, -0.2);
	glVertex2f(0.0, 0.2);
	glEnd();
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();   	         
	glViewport(0, 0, 400, 400);
	Triangle();	
	Calculation();

	glLoadIdentity();                 
	glViewport(200, 200, 200, 200);
	Triangle();
	Calculation();

	glLoadIdentity();                
	glViewport(0, 200, 200, 200);
	Triangle();
	Calculation();

	glLoadIdentity();                
	glViewport(0, 0, 200, 200);
	Triangle();
	Calculation();

	glLoadIdentity();                
	glViewport(200, 0, 200, 200);
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
	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}
