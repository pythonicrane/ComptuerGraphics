/**
* 计算机图形学第三版 glViewport示例
* glViewport为视窗，glOrtho2D为正交投影显示
* glViewport是指定在窗口中显示的位置和大小
* glOrtho2D是指定三维坐标系中正交投影的区域来显示在glViewport或者窗口中
* glOrtho2D长宽比例不一致会产生形变
*
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
	//gluOrtho2D(-100.0, 100.0, -100.0, 100);
	glMatrixMode(GL_MODELVIEW);
}

/*画三角形*/
void triangle(wcPt2D * verts)
{
	GLint k;
	glBegin(GL_TRIANGLES);
	for (k = 0; k < 3; k++)
		glVertex2f(verts[k].x, verts[k].y);
	glEnd();
}


/*执行函数*/
void displayFcn()
{
	wcPt2D verts[3] = { { 0.0,0.0 },{ 100.0,0.0 },{ 50.0,100.0 } };
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glViewport(0,0,300,300);
	triangle(verts);

	//gluOrtho2D(50, winWidth, ywcMin, winHeight);
	glColor3f(1.0, 0.0, 0.0);
	glViewport(300, 0, 300, 300);
	triangle(verts);


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
	//glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}