#include <glut.h>

#define NUM_COLOURS     8
#define ALPHA           0.0

enum { black, red, green, blue, yellow, magenta, cyan, white };
typedef GLfloat colour_type[3];
colour_type colour[NUM_COLOURS] = { {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0},
                                    {1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {1.0, 1.0, 1.0} };

enum { x, y };
typedef GLdouble vertex_type[2];
int num_vertices = 4;
vertex_type square[] = { {0.5, 0.5}, {-0.5, 0.5}, {-0.5, -0.5}, {0.5, -0.5} };


void Render(vertex_type* image, int num_vertices, int primitive) 
{
    glBegin(primitive);
    for (int i = 0; i < num_vertices; i++)
        glVertex2d(image[i][x], image[i][y]);

    glEnd();
}

void RenderView(void) 
{
    glColor3fv(colour[yellow]);
    Render(square, num_vertices, GL_POLYGON);
    glColor3fv(colour[blue]);
    Render(square, num_vertices, GL_LINE_LOOP);
}

void Display() 
{
    glClear(GL_COLOR_BUFFER_BIT);
    RenderView();
    glFlush();
}

void SetUpGLUT(int argc, char** argv) 
{
    glutInit(&argc, argv);
    glutCreateWindow("Square");
    glutDisplayFunc(Display);
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