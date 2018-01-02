/**
*计算机图形学第三版第八章P190二维观察例子
*@author ZhaoHeln 2018年1月2日 16:19:43
*/
#include<gl/glut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;

GLsizei winWidth = 600, winHeight = 600;
GLfloat xwcMin = 0.0, xwcMax = 225.0;
GLfloat ywcMin = 0.0, ywcMax = 225.0;

//顶点对象
class wcPt2D
{
public:
	GLfloat x;
	GLfloat y;
};

typedef GLfloat Matrix3x3[3][3];
Matrix3x3 matComposite;
const GLdouble pi = 3.14159;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(xwcMin, winWidth, ywcMin, winHeight);
}

















/*执行函数*/
void displayFcn()
{

	glFlush();
}

/*重绘函数，防止窗口变化*/
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwcMin, winWidth, ywcMin, winHeight);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Geometric Transformation!");

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}