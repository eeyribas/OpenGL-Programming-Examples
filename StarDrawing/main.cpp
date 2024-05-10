#include <glut.h>
#include <stdio.h>

#define NUM_COLOURS     8
#define ALPHA           0.0
enum { black, red, green, blue, yellow, magenta, cyan, white };

GLdouble x_left = 0.0;
GLdouble x_right = 4.0;
GLdouble y_bottom = 0.0;
GLdouble y_top = 4.0;

typedef GLfloat colour_type[3];
colour_type colour[NUM_COLOURS] = { {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
                                    {1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {1.0, 1.0, 1.0} };

enum { x, y };
typedef GLdouble vertex_type[2];
int star_size = 10;
vertex_type star[] = { {0.8, 0.1}, {1.95, 1.1}, {3.2, 0.4}, {2.6, 1.9}, {3.5, 2.9}, {2.2, 2.7},
                       {1.6, 3.8}, {1.30, 2.6}, {0.1, 2.3}, {1.1, 1.6} };

void Render(vertex_type* image, int num_vertices, GLenum mode) 
{
    glBegin(mode);
    for (int i = 0; i < num_vertices; i++)
        glVertex2d(image[i][x], image[i][y]);

    glEnd();
}

void RenderView(void) 
{
    glColor3fv(colour[blue]);
    Render(star, star_size, GL_LINE_LOOP);
}

void Display(void) 
{
    glClear(GL_COLOR_BUFFER_BIT);
    RenderView();
    glFlush();
}

void Keyboard(unsigned char key, int x_mouse, int y_mouse) 
{
    switch (key) {
        case 27:
            exit(0);
        case 'm':
            printf("[%d][%d]\n", x_mouse, y_mouse);
            break;
        default:
            printf("%s%c\n", "key=", key);
    }
}

void SetUpGLUT(int argc, char** argv) 
{
    glutInit(&argc, argv);
    glutCreateWindow("Star");
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
}

void InitialiseGL(void) 
{
    glClearColor(1, 1, 1, ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(x_left, x_right, y_bottom, y_top);
}

int main(int argc, char** argv) 
{
    SetUpGLUT(argc, argv);
    InitialiseGL();

    glutMainLoop();

    return 0;
}