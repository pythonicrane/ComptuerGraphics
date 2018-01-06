/**
*计算机图形学第三版第12章P294计算机动画例子
*@author ZhaoHeln 2018年1月6日 20:07:10
*/
#include<gl/glut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;

GLsizei winWidth = 500, winHeight = 500;
const double TWO_PI = 6.2831853;
GLuint regHex;
static GLfloat rotTheta = 0.0;



//顶点对象
class scrPt
{
public:
	GLint x;
	GLint y;
};


static void init()
{
	scrPt hexVertex;
	GLdouble hexTheta;
	GLint k;

	glClearColor(1.0, 1.0, 1.0, 0.0);
	regHex = glGenLists(1);
	glNewList(regHex, GL_COMPILE);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 6; k++)
	{
		hexTheta = TWO_PI*k / 6;
		hexVertex.x = 150 + 100 * cos(hexTheta);
		hexVertex.y = 150 + 100 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();
}

void displayHex()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(rotTheta, 0.0, 0.0, 1.0);
	glCallList(regHex);
	glPopMatrix();
	glutSwapBuffers();
	glFlush();
}

void rotateHex()
{
	rotTheta += 3.0;
	if (rotTheta > 360.0)
		rotTheta -= 360.0;
	glutPostRedisplay();
}


/*重绘函数，防止窗口变化*/
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-320.0,320.0,-320.0,320.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
}

void mouseFcn(GLint button, GLint action, GLint x, GLint y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (action == GLUT_DOWN)
			{
				glutIdleFunc(rotateHex);
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (action == GLUT_DOWN)
			{
				glutIdleFunc(NULL);
			}
			break;
		default:
			break;
	}
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(150, 150);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Animation Example!");

	init();
	glutDisplayFunc(displayHex);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(mouseFcn);
	glutMainLoop();
}