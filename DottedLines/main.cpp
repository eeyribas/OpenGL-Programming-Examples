#include <glut.h>              

#define DrawOneLine(x1, y1, x2, y2) glBegin(GL_LINES); \
glVertex2f((x1), (y1)); glVertex2f((x2), (y2)); glEnd();

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LINE_STIPPLE);

	glLineStipple(1, 0x0101);
	DrawOneLine(50.0, 125.0, 150.0, 125.0);

	glLineStipple(1, 0x00FF);
	DrawOneLine(150.0, 125.0, 250.0, 125.0);

	glLineStipple(1, 0x1C47);
	DrawOneLine(250.0, 125.0, 350.0, 125.0);

	glLineWidth(5.0);
	glLineStipple(1, 0x0101);
	DrawOneLine(50.0, 100.0, 150.0, 100.0);

	glLineStipple(1, 0x00FF);
	DrawOneLine(150.0, 100.0, 250.0, 100.0);

	glLineStipple(1, 0x1C47);
	DrawOneLine(250.0, 100.0, 350.0, 100.0);

	glLineWidth(1.0);
	glLineStipple(1, 0x1C47);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 7; i++)
		glVertex2f(50.0 + ((GLfloat)i * 50.0), 75.0);
	glEnd();

	for (int i = 0; i < 6; i++) {
		DrawOneLine(50.0 + ((GLfloat)i * 50.0), 50.0, 50.0 + ((GLfloat)(i + 1) * 50.0), 50.0);
	}

	glLineStipple(5, 0x1C47);
	DrawOneLine(50.0, 25.0, 350.0, 25.0);

	glDisable(GL_LINE_STIPPLE);
	glFlush();
}

void Init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);                                 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 150);              
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);                 
	
	Init();
	glutDisplayFunc(Display);                       
	glutReshapeFunc(Reshape);

	glutMainLoop();    

	return 0;
}
