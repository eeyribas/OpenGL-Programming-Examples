#include <stdio.h>
#include <stdlib.h>
#include <glut.h>

#define NUM_COLOURS		10
#define ALPHA			0.0
#define NUM_CAMERAS		2

enum { x, y, z };
enum { red, green, blue, yellow, magenta, cyan, brown, pink, white, black };

typedef GLfloat colour_type[3];
colour_type colour[NUM_COLOURS] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0, 0.0},
								    {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {0.4, 0.1, 0.1}, {1.0, 0.8, 0.9},
								    {1.0, 1.0, 1.0}, {0.0, 0.0, 0.0} };

int perspective_projection = GL_TRUE;
GLdouble fovy = 60;
GLdouble aspect = 1.0;

enum { camera_1, camera_2 };
GLdouble eye[NUM_CAMERAS][3] = { {2.0, 2.0, 2.0}, {2.0, 2.0, -2.0} };
GLdouble centre[NUM_CAMERAS][3] = { {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0} };
GLdouble up[NUM_CAMERAS][3] = { {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0} };
int current_camera = camera_1;

GLdouble ra = 0.0;
GLdouble tx = 0.0;


void Axis(double length) 
{
	glPushMatrix();

	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, length);
	glEnd();

	glTranslated(0, 0, length - 0.2);
	glutWireCone(0.04, 0.2, 12, 9);
	glPopMatrix();
}

void RenderAxes(void) 
{
	glPushMatrix();
	glLineWidth(2);
	glColor3fv(colour[red]);
	Axis(1.5);

	glRotated(-90, 1, 0, 0);
	glColor3fv(colour[blue]);
	Axis(1.5);

	glRotated(90, 0, 1, 0);
	glColor3fv(colour[green]);
	Axis(1.5);

	glPopMatrix();
}

void RenderWheel(GLdouble tx, GLdouble ty, GLdouble tz) 
{
	glColor3fv(colour[magenta]);
	glPushMatrix();
	glTranslated(tx, ty, tz);
	glTranslated(0, 0.0125, 0);
	glRotated(ra, 0, 0, 1);
	glutWireTorus(0.025, 0.09, 11, 11);
	glPopMatrix();
}

void RenderBoard(void) 
{
	glColor3fv(colour[pink]);
	glPushMatrix();
	glTranslated(tx, 0, 0);
	glPushMatrix();
	glTranslated(0, 0.1, 0);
	glPushMatrix();
	glScaled(1, 0.05, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	RenderWheel(0.25, 0.0, 0.25);
	RenderWheel(-0.25, 0.0, 0.25);
	RenderWheel(0.25, 0.0, -0.25);
	RenderWheel(-0.25, 0.0, -0.25);

	glPopMatrix();
	glPopMatrix();
}

void SetProjection(void) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (!perspective_projection)
		glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 10.0);
	else
		gluPerspective(fovy, aspect, 0.1, 100.0);
}

void SetCamera(void) 
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye[current_camera][x], eye[current_camera][y], eye[current_camera][z],
			  centre[current_camera][x], centre[current_camera][y], centre[current_camera][z],
			  up[current_camera][x], up[current_camera][y], up[current_camera][z]);
}

void Display(void) 
{
	SetProjection();
	SetCamera();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderAxes();
	RenderBoard();

	glutSwapBuffers();
}

void CycleCameras(void) 
{
	current_camera++;
	if (current_camera == NUM_CAMERAS)
		current_camera = 0;
}

void RollRight(void) 
{
	ra -= 1.0;
	if (ra <= -360)
		ra = 0;

	tx += 0.005;
}

void RollLeft(void) 
{
	ra += 1.5;
	if (ra >= 360)
		ra = 0;

	tx -= 0.005;
}

void ToggleDepth(void) 
{
	static int depth_on = GL_TRUE;

	if (depth_on) {
		glDisable(GL_DEPTH_TEST);
		depth_on = GL_FALSE;
	} else {
		glEnable(GL_DEPTH_TEST);
		depth_on = GL_TRUE;
	}
}

void Keyboard(unsigned char key, int x_mouse, int y_mouse) 
{
	switch (key) {
		case 27: 
			exit(0);
		case 'p': 
			perspective_projection = !perspective_projection;
			break;
		case 'd': 
			ToggleDepth();
			break;
		case 'c': 
			CycleCameras();
			break;
		case 'r': 
			RollRight();
			break;
		case 'l': 
			RollLeft();
			break;
		default: 
			printf("[%d][%d]\n", x_mouse, y_mouse);
	}

	glutPostRedisplay();
}

void Reshape(int weight, int height) 
{
	aspect = (GLdouble)weight / (GLdouble)height;
	glViewport(0, 0, (GLsizei)weight, (GLsizei)height);
}

void SetUpGLUT(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Hierarchical Model");

	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
}

void InitialiseGL(void) 
{
	glClearColor(1, 1, 1, ALPHA);
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) 
{
	SetUpGLUT(argc, argv);
	InitialiseGL();

	glutMainLoop();

	return 0;
}