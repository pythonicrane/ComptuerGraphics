/**
* 计算机图形学第三版第20章P462-键盘输入
* 三维立体显示标准模版
* @author ZhaoHeln 2018年1月26日 15:08:07
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

GLsizei winWidth = 600, winHeight = 600;//WIN窗口大小
/*观察点参数，默认为(0,0,1,  0,0,0,  0,1,0)*/
GLfloat px0 = 1.0, py0 = 0.0, pz0 = 1.0;//观察点在世界坐标系的坐标
GLfloat xref = 0.0, yref = 0.0, zref = 0.0;//所观察的方向(所看的点)
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;//相机的正上向量(相机的正上方所对应的方向)
/*二维裁剪窗口或者三维裁剪立体*/
GLfloat viewSize = 600;
GLfloat xwMin = 0, xwMax = viewSize, ywMin = 0,ywMax = viewSize;//透视投影近观察面"大小"，相对于观察坐标系
GLfloat dnear = -viewSize, dfar = viewSize;//近观察面距离，远观察面距离，都是观察系坐标下，必须为正

GLint endPtCtr = 0;//鼠标是否为终点标记

/*
* 顶点对象
*/
class scrPt
{
    public:
      GLint x;
      GLint y;
};

/*
* 初始化
*/
void init()
{
	glClearColor(0.0, 1.0, 1.0, 0.5);
    glMatrixMode(GL_PROJECTION);
	gluOrtho2D(xwMin, winWidth, ywMin, winHeight);
}



void plotPoint(GLint x,GLint y)
{
    glColor3f(1.0,0.0,0.0);
    glPointSize(3.0);
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
}

void curveDrawing(GLubyte curvePlotKey,GLint xMouse,GLint yMouse)
{
    GLint x = xMouse;
    GLint y = winHeight - yMouse;
    switch (curvePlotKey)
    {
        case 'c':
            plotPoint(x, y);
            break;
        default:
            break;
    }
    glFlush();
}

/*
* 显示循环调用函数
*/
void displayFcn()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glFlush();//注销后，重绘窗口会出现问题
}

/*
* 重绘函数，防止窗口变化
*/
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
    endPtCtr = 0;
    winWidth = newWidth;
    winHeight = newHeight;
    glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(xwMin, winWidth, ywMin, winHeight);
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
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
    glutKeyboardFunc(curveDrawing);
	glutMainLoop();
}