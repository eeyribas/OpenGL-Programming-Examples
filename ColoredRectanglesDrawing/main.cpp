#include <glut.h>
#include <stdio.h>

#define BUFFER_SIZE		512

void Init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	glDepthRange(0.0, 1.0);
}

void DrawRectangles(GLenum mode)
{
	if (mode == GL_SELECT)
		glLoadName(1);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3i(2, 0, 0);
	glVertex3i(2, 6, 0);
	glVertex3i(6, 6, 0);
	glVertex3i(6, 0, 0);
	glEnd();

	if (mode == GL_SELECT)
		glLoadName(2);
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 1.0);
	glVertex3i(3, 2, -1);
	glVertex3i(3, 8, -1);
	glVertex3i(8, 8, -1);
	glVertex3i(8, 2, -1);
	glEnd();

	if (mode == GL_SELECT)
		glLoadName(3);
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3i(0, 2, -2);
	glVertex3i(0, 7, -2);
	glVertex3i(5, 7, -2);
	glVertex3i(5, 2, -2);
	glEnd();
}

void ProcessHits(GLint hits, GLuint buffer[])
{
	printf("hits = %d\n", hits);
	GLuint *ptr = (GLuint*)buffer;
	GLuint names;
	for (int i = 0; i < hits; i++) {
		names = *ptr;
		printf("Number of names for hit = %d\n", names); 
		ptr++;
		printf("z1 is %g;", (float)*ptr / 0x7fffffff); 
		ptr++;
		printf("	z2 is %g\n", (float)*ptr / 0x7fffffff); 
		ptr++;
		printf("   the name is ");

		for (int j = 0; j < names; j++)
			printf("%d ", *ptr); ptr++;
		printf("\n");
	}
}

void PickRectangles(int button, int state, int x, int y)
{
	GLuint select_buffer[BUFFER_SIZE];
	GLint viewport[4];
	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
		return;

	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(BUFFER_SIZE, select_buffer);
	(void)glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y), 5.0, 5.0, viewport);
	glOrtho(0.0, 8.0, 0.0, 8.0, -0.5, 2.5);
	DrawRectangles(GL_SELECT);
	glPopMatrix();
	glFlush();

	GLint hits = glRenderMode(GL_RENDER);
	ProcessHits(hits, select_buffer);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawRectangles(GL_RENDER);
	glFlush();
}

void Reshape(int weight, int height)
{
	glViewport(0, 0, (GLsizei)weight, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 8.0, 0.0, 8.0, -0.5, 2.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(0);
			break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(200, 200);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	Init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutMouseFunc(PickRectangles);
	glutKeyboardFunc(Keyboard);

	glutMainLoop();

	return 0;
}