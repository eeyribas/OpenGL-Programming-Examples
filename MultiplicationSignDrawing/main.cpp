#include <glut.h>
#include <stdio.h>

static float rotation_angle = 0.;

void Init(void)
{
    GLfloat values[2];

    glGetFloatv(GL_LINE_WIDTH_GRANULARITY, values);
    printf("GL_LINE_WIDTH_GRANULARITY value is %3.1f\n", values[0]);

    glGetFloatv(GL_LINE_WIDTH_RANGE, values);
    printf("GL_LINE_WIDTH_RANGE values are %3.1f %3.1f\n", values[0], values[1]);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glLineWidth(1.5);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glRotatef(-rotation_angle, 0.0, 0.0, 0.1);
    glBegin(GL_LINES);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();

    glPopMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glRotatef(rotation_angle, 0.0, 0.0, 0.1);
    glBegin(GL_LINES);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.5, -0.5);
    glEnd();

    glPopMatrix();
    glFlush();
}

void Reshape(int weight, int height)
{
    glViewport(0, 0, weight, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (weight <= height)
        gluOrtho2D(-1.0, 1.0, -1.0 * (GLfloat)height / (GLfloat)weight, 1.0 * (GLfloat)height / (GLfloat)weight);
    else
        gluOrtho2D(-1.0 * (GLfloat)weight / (GLfloat)height, 1.0 * (GLfloat)weight / (GLfloat)height, -1.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'r':
        case 'R':
            rotation_angle += 20.;
            if (rotation_angle >= 360.) 
                rotation_angle = 0.;
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