#include <glut.h>
#include <stdio.h>
#include <math.h>

#define PI              3.14159
#define NUM_COLOURS     8
#define ALPHA           0.0
#define MAX_VERTICES    100

GLint width = 350;
GLint height = 350;
GLint initial_x_position = 50;
GLint initial_y_position = 50;

enum { black, red, green, blue, yellow, magenta, cyan, white };
typedef GLfloat colour_type[3];
colour_type colour[NUM_COLOURS] = { {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, 
                                    {1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {1.0, 1.0, 1.0} };

enum { x, y };
typedef GLdouble vertex_type[2];
int num_vertices = 11;
vertex_type ngon[MAX_VERTICES];


void Render(vertex_type* image, int num_vertices, GLenum mode) 
{
    glBegin(mode);
    for (int i = 0; i < num_vertices; i++)
        glVertex2d(image[i][x], image[i][y]);

    glEnd();
}

void ComputeVertices(GLdouble centre_x, GLdouble centre_y, GLdouble radius) 
{
    GLdouble angle;
    if (num_vertices > MAX_VERTICES)
        num_vertices = MAX_VERTICES;

    angle = 2 * PI / num_vertices;
    for (int i = 0; i < num_vertices; i++) {
        ngon[i][x] = radius * cos(angle * i) + centre_x;
        ngon[i][y] = radius * sin(angle * i) + centre_y;
    }
}

void RenderView(void) 
{
    glColor3fv(colour[yellow]);
    Render(ngon, num_vertices, GL_POLYGON);
    glColor3fv(colour[red]);
    Render(ngon, num_vertices, GL_LINE_LOOP);
}

void Display(void) 
{
    glClear(GL_COLOR_BUFFER_BIT);
    RenderView();
    glFlush();
}
void Reshape(int tmp_width, int tmp_height) 
{
    width = tmp_width;
    height = tmp_height;
    if (height < width)
        ComputeVertices(width / 2, height / 2, height / 5);
    else
        ComputeVertices(width / 2, height / 2, width / 5);

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)width, 0.0, (GLdouble)height);
}

void Keyboard(unsigned char key, int x_mouse, int y_mouse) 
{
    switch (key) {
        case 27:
            exit(0);
        case 'm':
            printf("\n[%d][%d]\n", x_mouse, y_mouse);
            break;
        default:
            printf("%s%c\n", "key=", key);
    }
}

void SetUpGLUT(int argc, char** argv) 
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(initial_x_position, initial_y_position);
    glutCreateWindow("Centred N-gon");

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
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