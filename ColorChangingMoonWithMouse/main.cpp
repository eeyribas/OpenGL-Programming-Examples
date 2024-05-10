#include <glut.h>

GLfloat diffuse_material[4] = { 0.5, 0.5, 0.5, 1.0 };

void Init(void)
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_material);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
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
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat)height / (GLfloat)weight, 1.5 * (GLfloat)height /
                (GLfloat)weight, -10.0, 10.0);
    else
        glOrtho(-1.5 * (GLfloat)weight / (GLfloat)height, 1.5 * (GLfloat)weight / (GLfloat)height, 
                -1.5, 1.5, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Mouse(int button, int state, int x, int y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                diffuse_material[0] += 0.1;
                if (diffuse_material[0] > 1.0)
                    diffuse_material[0] = 0.0;

                glColor4fv(diffuse_material);
                glutPostRedisplay();
            }
            break;
        case GLUT_MIDDLE_BUTTON:
            if (state == GLUT_DOWN) {
                diffuse_material[1] += 0.1;
                if (diffuse_material[1] > 1.0)
                    diffuse_material[1] = 0.0;

                glColor4fv(diffuse_material);
                glutPostRedisplay();
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN) {
                diffuse_material[2] += 0.1;
                if (diffuse_material[2] > 1.0)
                    diffuse_material[2] = 0.0;

                glColor4fv(diffuse_material);
                glutPostRedisplay();
            }
            break;
        default:
            break;
    }
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
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    Init();
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutMouseFunc(Mouse);
    glutKeyboardFunc(Keyboard);

    glutMainLoop();

    return 0;
}