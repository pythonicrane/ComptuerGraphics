#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>

#define RAMPSIZE 16
#define RAMP1START 32
#define RAMP2START 48

static float rotAngle = 0.;

void init(void)
{
    int i;
    for(i = 0; i < 4; i++)
    {
        GLfloat shade;
        shade = (GLfloat)i/(GLfloat)RAMPSIZE;
        //把一些颜色加载到颜色映射表中
        glutSetColor(RAMP1START + (GLint)i, 0., shade, 0.);
        glutSetColor(RAMP2START + (GLint)i, 0., 0., shade);
    }

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    //用颜色的索引号设置颜色
    glIndexi(RAMP1START);

    glPushMatrix();
    glRotatef(-rotAngle, 0.0, 0.0, 0.1);
    glBegin(GL_LINES);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.5, -0.5);
    glEnd();
    glPopMatrix();

    glIndexi(RAMP2START);
    glPushMatrix();
    glRotatef(rotAngle, 0.0, 0.0, 0.1);
    glBegin(GL_LINES);
        glVertex2f(0.5, 0.5);
        glVertex2f(-0.5, -0.5);
    glEnd();
    glPopMatrix();

    glFlush();
}


void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
       gluOrtho2D (-1.0, 1.0,
          -1.0*(GLfloat)h/(GLfloat)w, 1.0*(GLfloat)h/(GLfloat)w);
    else
       gluOrtho2D (-1.0*(GLfloat)w/(GLfloat)h,
          1.0*(GLfloat)w/(GLfloat)h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'r':
      case 'R':
         rotAngle += 20.;
         if (rotAngle >= 360.) rotAngle = 0.;
         glutPostRedisplay();
         break;
      case 27:  /*  Escape Key */
         exit(0);
         break;
      default:
         break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_INDEX);
    glutInitWindowSize (200, 200);
    glutCreateWindow (argv[0]);
    init();
    glutReshapeFunc (reshape);
    glutKeyboardFunc (keyboard);
    glutDisplayFunc (display);
    glutMainLoop();
    return 0;
}