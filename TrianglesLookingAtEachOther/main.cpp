#include <glut.h>

static int left_first = GL_TRUE;

static void Init(void)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_FLAT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

static void DrawLeftTriangle(void)
{
    glBegin(GL_TRIANGLES);
    glColor4f(1.0, 1.0, 0.0, 0.75);
    glVertex3f(0.1, 0.9, 0.0);
    glVertex3f(0.1, 0.1, 0.0);
    glVertex3f(0.7, 0.5, 0.0);
    glEnd();
}

static void DrawRightTriangle(void)
{
    glBegin(GL_TRIANGLES);
    glColor4f(0.0, 1.0, 1.0, 0.75);
    glVertex3f(0.9, 0.9, 0.0);       
    glVertex3f(0.3, 0.5, 0.0);       
    glVertex3f(0.9, 0.1, 0.0);    
    glEnd();
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (left_first) {
        DrawLeftTriangle();
        DrawRightTriangle();
    } else {
        DrawRightTriangle();
        DrawLeftTriangle();
    }

    glFlush();
}

void Reshape(int weight, int height)
{
    glViewport(0, 0, (GLsizei)weight, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (weight <= height)
        gluOrtho2D(0.0, 1.0, 0.0, 1.0 * (GLfloat)height / (GLfloat)weight);
    else
        gluOrtho2D(0.0, 1.0 * (GLfloat)weight / (GLfloat)height, 0.0, 1.0);
}

void Keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 't':
        case 'T':
            left_first = !left_first;
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(200, 200);
    glutCreateWindow(argv[0]);

    Init();
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutDisplayFunc(Display);

    glutMainLoop();

    return 0;
}