/**
* 计算机图形学第三版第14章P460-鼠标输入
* 三维立体显示标准模版
* @author ZhaoHeln 2018年1月26日 11:29:55
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

/*
* 画线段函数
*/
void drawLineSegment(scrPt endPt1,scrPt endPt2)
{
    cout << "Draw Line!\n";
	glColor3f(0.0, 0.0, 1.0);//设置颜色
    glBegin(GL_LINES);
        glVertex2i(endPt1.x, endPt1.y);
        glVertex2i(endPt2.x, endPt2.y);
    glEnd();
}

/*
* 鼠标响应事件
*/
void polyLine(GLint button,GLint action,GLint xMouse,GLint yMouse)
{
    static scrPt endPt1, endPt2;
    cout << "MouseClick!\n";
    if(endPtCtr == 0)
    {
        if(button==GLUT_LEFT_BUTTON && action == GLUT_DOWN)
        {
            endPt1.x = xMouse;
            endPt1.y = winHeight - yMouse;
            endPtCtr = 1;
        }else
        {
            if(button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)
                exit(0);
        }
    }
    else
    {
        if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
        {
            endPt2.x = xMouse;
            endPt2.y = winHeight - yMouse;

            drawLineSegment(endPt1,endPt2);
            endPt1 = endPt2;
        }else
        {
            if(button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)
                exit(0);
        }
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

/*重绘函数，防止窗口变化*/
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
    glutMouseFunc(polyLine);
	glutMainLoop();
}