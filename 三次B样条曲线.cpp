#include <math.h>
#include <gl/glut.h>
#include <iostream>
using namespace std;

#define NUM_POINTS 6
#define NUM_SEGMENTS (NUM_POINTS-3)

struct Point2
{
    double x;
    double y;

    Point2() { ; }
    Point2(int px, int py) { x = px; y = py; }
    void SetPoint2(int px, int py) { x = px; y = py; }
};

/*全局变量*/
Point2 vec[NUM_POINTS];
bool mouseLeftDown = false;

/*绘制B样条曲线*/
void Bspline(int n)
{
    float f1, f2, f3, f4;
    float deltaT = 1.0 / n;
    float T;

    glBegin(GL_LINE_STRIP);
    for (int num = 0; num < NUM_SEGMENTS; num++)
    {
        for (int i = 0; i <= n; i++) {

            T = i * deltaT;

            f1 = (-T*T*T + 3*T*T - 3*T + 1) / 6.0;
            f2 =(3*T*T*T - 6*T*T + 4) / 6.0;
            f3 = (-3*T*T*T +3*T*T + 3*T + 1) / 6.0;
            f4 = (T*T*T) / 6.0;

            glVertex2f( f1*vec[num].x + f2*vec[num+1].x + f3*vec[num+2].x + f4*vec[num+3].x,
                f1*vec[num].y + f2*vec[num+1].y + f3*vec[num+2].y + f4*vec[num+3].y);
        }
    }

    glEnd();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glLineWidth(1.5f);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_STRIP);
    for(int i = 0;i < NUM_POINTS; i++)
    {
        glVertex2f(vec[i].x, vec[i].y);
    }
    glEnd();

    glPointSize(10.0f);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    for(int i = 0;i < NUM_POINTS; i++)
    {
        glVertex2f(vec[i].x, vec[i].y);
    }
    glEnd();

    Bspline(20);

    glFlush();
    glutSwapBuffers();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);

    vec[0].SetPoint2(200, 400);
    vec[1].SetPoint2(100, 300);
    vec[2].SetPoint2(200, 200);
    vec[3].SetPoint2(250, 300);
    vec[4].SetPoint2(400, 200);
    vec[5].SetPoint2(400, 400);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLsizei)w, (GLsizei)h, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseLeftDown = true;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        mouseLeftDown = false;
    }
}

double distance(int x1, int y1, int x2, int y2)
{
    return sqrt((x1-x2) * (x1 -x2) + (y1-y2) * (y1-y2));
}

void motion(int x, int y)
{
    if (mouseLeftDown)
    {
        for (int i = 0; i < NUM_POINTS; i++)
        {
            if (distance(vec[i].x, vec[i].y, x, y) < 20)
            {
                vec[i].SetPoint2(x, y);
            }
        }
    }

    glutPostRedisplay();
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition (200, 200);
    glutCreateWindow("B-Spline Curve");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();

    return 0;

}