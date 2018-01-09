#include <windows.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <stdio.h>
#include <math.h>
 GLfloat x_coord[3], y_coord[3];
 int nPoints = 0;
 inline GLfloat x_convert (int x)
 {
 return -8.0+x/499.0*16;
 }
 inline GLfloat y_convert (int y)
 {
 return 8.0 - y/499.0*16;
 }
 void init(){
   glClearColor(1,1,1,0);
 }
 void myReshape(int w,int h)
 {
 glViewport(0,0,(GLsizei)w,(GLsizei)h);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 //gluPerspective(45.0,(GLfloat)w/(GLfloat)h,1.0,50.0);
 if(w<=h)
 glOrtho(-8.0,8.0,-8.0*(GLfloat)h/(GLfloat)w,8.0*(GLfloat)h/(GLfloat)w,-8.0,8.0);
 else
 glOrtho(-8.0*(GLfloat)h/(GLfloat)w,8.0*(GLfloat)h/(GLfloat)w,-8.0,8.0,-8.0,8.0);

 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 }

 void Hermit(int n)  //
 {
   float t, dt, t2, t3, f1, f2, f3, f4;

    dt = 1.0/n;      // t runs from 0 to 1.
    GLfloat PT0_x = x_coord[1] - x_coord[0];
    GLfloat PT0_y = y_coord[1] - y_coord[0];
    GLfloat PT1_x = x_coord[2] - x_coord[1];
 GLfloat PT1_y = y_coord[2] - y_coord[1];
    glBegin(GL_LINE_STRIP);
 for (t = 0.0; t <= 1.0; t += dt) {
        t2 = t * t;
        t3 = t2 * t;       // t3 = t * t * t
        f1 = 2.0*t3 - 3.0*t2 + 1.0;
        f2 = -2.0*t3 + 3.0*t2;
        f3 = t3 - 2.0*t2 + t;
        f4 = t3 - t2;
        glVertex2f( f1*x_coord[0] + f2*x_coord[2] + f3*PT0_x + f4*PT1_x,
                         f1*y_coord[0] + f2*y_coord[2] + f3*PT0_y + f4*PT1_y );
    }
    glEnd();
 }
 void display(){
     glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(0,1,0);                //画两点之间的直线
   glBegin(GL_LINE_STRIP);
   for (int i = 0; i < nPoints; i++)
 glVertex3f (x_coord[i], y_coord[i], 0.0);
   glEnd();

       glColor3f (1.0, 0, 0);            //调用DDA画线算法
    if (nPoints == 3)
 Hermit(20);

 glFlush();

 }
 void handle_mouseclick (int button, int state, int x, int y){
 if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
 if (nPoints == 3) nPoints = 0;

 printf("%d (%d, %d) ==> (%f, %f)\n", nPoints, x, y, x_convert(x), y_convert(y));

 x_coord[nPoints] = x_convert(x);
 y_coord[nPoints] = y_convert(y);
 nPoints++;
 glutPostRedisplay();
 }
 }
int main(int argc, char** argv)
 {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB |GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("hello");
    init ();
    glutDisplayFunc( display );
     glutReshapeFunc(myReshape);
    glutMouseFunc(handle_mouseclick);
    glutMainLoop();
    return 0;
 }