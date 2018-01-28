/**
* 计算机图形学第三版第20章P468-OpenGL拾取操作
* 三维立体显示标准模版
* @author ZhaoHeln 2018年1月28日 12:15:12
*/

/*预编译加载动态链接库*/
// #pragma comment(lib,"glut32.lib")
// #pragma comment(lib,"glu32.lib")
// #pragma comment(lib,"opengl32.lib")

#include<gl/glut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;

GLsizei winWidth = 400, winHeight = 400;//WIN窗口大小
/*观察点参数，默认为(0,0,1,  0,0,0,  0,1,0)*/
GLfloat px0 = 1.0, py0 = 0.0, pz0 = 1.0;//观察点在世界坐标系的坐标
GLfloat xref = 0.0, yref = 0.0, zref = 0.0;//所观察的方向(所看的点)
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;//相机的正上向量(相机的正上方所对应的方向)
/*二维裁剪窗口或者三维裁剪立体*/
GLfloat viewSize = 300;
GLfloat xwMin = 0, xwMax = viewSize, ywMin = 0, ywMax = viewSize;//透视投影近观察面"大小"，相对于观察坐标系
GLfloat dnear = -viewSize, dfar = viewSize;//近观察面距离，远观察面距离，都是观察系坐标下，必须为正

GLfloat red = 1.0, green = 1.0, blue = 1.0;
GLenum fillMode = GL_SMOOTH;

/*
* 初始化
*/
void init()
{
	glClearColor(0.6, 0.6, 0.6, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(xwMin, xwMax, ywMin, ywMax);
}

/*
* 菜单处理函数
*/
void fillOption(GLint selectedOption)
{
	switch (selectedOption)
	{
	case 1:
		fillMode = GL_FLAT;
		break;
	case 2:
		fillMode = GL_SMOOTH;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void displayTriangle()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(fillMode);
	glColor3f(red, green, blue);

	/* 绘制三角形，三个顶点分别是红绿蓝色的 */
	glBegin(GL_TRIANGLES);
		glColor3f(red, 0.0, 0.0);
		glVertex2i(280, 20);
		glColor3f(0.0, green, 0.0);
		glVertex2i(160, 280);
		glColor3f(0.0, 0.0, blue);
		glVertex2i(20, 100);
	glEnd();
	glFlush();
}



/*
* 重绘函数，防止窗口变化
*/
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	winWidth = newWidth;
	winHeight = newHeight;
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwMin, (GLfloat)winWidth, ywMin, (GLfloat)winHeight);
	displayTriangle();//重新绘制三角形
	glFlush();
	//glClear(GL_COLOR_BUFFER_BIT);//和displayFcn函数中的至少存在一个
}


int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Computer Graphics!");

	init();
	glutDisplayFunc(displayTriangle);

	/* 创建右键菜单 */
	glutCreateMenu(fillOption);//创建菜单
		glutAddMenuEntry("Solid-Color Fill", 1);//一级菜单第一个
		glutAddMenuEntry("Color-Interpolation Fill", 2);//一级菜单第二个
	glutAttachMenu(GLUT_RIGHT_BUTTON);//指定调用菜单的按键，这里是右键

	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}