#include <glut.h>
#include <math.h>
#include <stdio.h>

static GLint fog_mode;

static void Init(void)
{
    GLfloat position[] = {0.5, 0.5, 3.0, 0.0};
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    {
        GLfloat mat[3] = {0.1745, 0.01175, 0.01175};
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
        mat[0] = 0.61424; 
        mat[1] = 0.04136; 
        mat[2] = 0.04136;

        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
        mat[0] = 0.727811; 
        mat[1] = 0.626959; 
        mat[2] = 0.626959;

        glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
        glMaterialf(GL_FRONT, GL_SHININESS, 0.6 * 128.0);
    }

    glEnable(GL_FOG);
    {
        GLfloat fog_color[4] = {0.5, 0.5, 0.5, 1.0};
        fog_mode = GL_EXP;
        glFogi(GL_FOG_MODE, fog_mode);
        glFogfv(GL_FOG_COLOR, fog_color);
        glFogf(GL_FOG_DENSITY, 0.35);
        glHint(GL_FOG_HINT, GL_DONT_CARE);
        glFogf(GL_FOG_START, 1.0);
        glFogf(GL_FOG_END, 5.0);
    }

    glClearColor(0.5, 0.5, 0.5, 1.0);
}

static void RenderSphere(GLfloat x, GLfloat y, GLfloat z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidSphere(0.4, 16, 16);
    glPopMatrix();
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    RenderSphere(-2., -0.5, -1.0);
    RenderSphere(-1., -0.5, -2.0);
    RenderSphere(0., -0.5, -3.0);
    RenderSphere(1., -0.5, -4.0);
    RenderSphere(2., -0.5, -5.0);
    glFlush();
}

void Reshape(int weight, int height)
{
    glViewport(0, 0, (GLsizei)weight, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (weight <= height)
        glOrtho(-2.5, 2.5, -2.5 * (GLfloat)height / (GLfloat)weight, 2.5 * (GLfloat)height / (GLfloat)weight, -10.0, 10.0);
    else
        glOrtho(-2.5 * (GLfloat)weight / (GLfloat)height, 2.5 * (GLfloat)weight / (GLfloat)height, -2.5, 2.5, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'f':
        case 'F':
            if (fog_mode == GL_EXP) {
                fog_mode = GL_EXP2;
                printf("Fog mode is GL_EXP2\n");
            } else if (fog_mode == GL_EXP2) {
                fog_mode = GL_LINEAR;
                printf("Fog mode is GL_LINEAR\n");
            } else if (fog_mode == GL_LINEAR) {
                fog_mode = GL_EXP;
                printf("Fog mode is GL_EXP\n");
            }

            glFogi(GL_FOG_MODE, fog_mode);
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow(argv[0]);

    Init();
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutDisplayFunc(Display);

    glutMainLoop();

    return 0;
}