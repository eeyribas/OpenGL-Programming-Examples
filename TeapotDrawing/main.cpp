#include <glut.h>
#include <stdio.h>

#define NUM_COLOURS     8
#define ALPHA           0.0

enum { x, y, z };
int width = 500;
int height = 500;
int x_position = 50;
int y_position = 70;

enum { x_left, x_right, y_bottom, y_top, z_near, z_far };
GLdouble world[] = { -1.0,1.0,-1.0,1.0,0.1,100 };
GLdouble eye[] = { 2.0,2.0,2.0 };
GLdouble centre[] = { 0.0,0.0,0.0 };
GLdouble up[] = { 0.0,1.0,0.0 };

enum { red, green, blue, yellow, magenta, cyan, white, black, colours };
typedef GLfloat colour_type[3];
colour_type colour[NUM_COLOURS] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0, 0.0},
                                    {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, {0.0, 0.0, 0.0} };

enum { teapot, models };
GLdouble t[][3] = { {0.1, 0.0, 0.0} };

void RenderView(void) 
{
    glColor3fv(colour[red]);
    glTranslated(t[teapot][x], t[teapot][y], t[teapot][z]);
    glutWireTeapot(0.5);
}

void Display(void) 
{
    glClear(GL_COLOR_BUFFER_BIT);
    RenderView();
    glFlush();
}

void ReshapeWindow(int weight, int height) 
{
    glViewport(0, 0, (GLsizei)weight, (GLsizei)height);
    glOrtho(world[x_left], world[x_right], world[y_bottom], world[y_top], world[z_near], world[z_far]);
    gluLookAt(eye[x], eye[y], eye[z], centre[x], centre[y], centre[z], up[x], up[y], up[z]);
}

void Keyboard(unsigned char key, int x_mouse, int y_mouse) 
{
    switch (key) {
        case 27: 
            exit(0);
        default:
            printf("key=%c mouse at [%d][%d]\n", key, x_mouse, y_mouse);
    }

    glutPostRedisplay();
}

void SpecialKeys(int key, int x_mouse, int y_mouse) 
{
    for (int i = 0; i <= z; i++) 
        t[teapot][i] = 0.0;

    switch (key) {
        case GLUT_KEY_PAGE_UP: 
            t[teapot][z] = 0.1; 
            break;
        case GLUT_KEY_PAGE_DOWN: 
            t[teapot][z] = -0.1; 
            break;
        case GLUT_KEY_RIGHT: 
            t[teapot][x] = 0.1; 
            break;
        case GLUT_KEY_LEFT: 
            t[teapot][x] = -0.1; 
            break;
        case GLUT_KEY_UP: 
            t[teapot][y] = 0.1; 
            break;
        case GLUT_KEY_DOWN: 
            t[teapot][y] = -0.1; 
            break;
    }

    glutPostRedisplay();
}

void Mouse(int button, int state, int x_mouse, int y_mouse) 
{
    glutPostRedisplay();
}

void SetUpGLUT(int argc, char** argv) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(x_position, y_position);
    glutCreateWindow("Single Buffered 3D Teapot");

    glutDisplayFunc(Display);
    glutReshapeFunc(ReshapeWindow);
    glutSpecialFunc(SpecialKeys);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(Mouse);
}

void InitialiseGL(void) 
{
    glClearColor(1, 1, 1, ALPHA);
}

int main(int argc, char** argv) 
{
    SetUpGLUT(argc, argv);
    InitialiseGL();

    glutMainLoop();

    return 0;
}