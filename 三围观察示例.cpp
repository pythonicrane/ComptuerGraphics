/**
*计算机图形学第三版第10章P265三维观察示例
*@author ZhaoHeln 2018年1月5日 19:24:46
*/
#include<gl/glut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;

GLsizei winWidth = 600, winHeight = 600;//WIN窗口大小
GLfloat px0 = 100.0, py0 = 50.0, pz0 = 50.0;//观察点在世界坐标系的坐标
GLfloat xref = 50.0, yref = 50.0, zref = 10.0;//所观察的方向(所看的点)
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;//相机的正上向量(相机的正上方所对应的方向)

GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;//透视投影近观察面"大小"，不是坐标，观察坐标系

GLfloat dnear = 25.0, dfar = 125.0;//近观察面距离，远观察面距离，都是观察系坐标下，必须为正



void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(px0, py0, pz0, xref, yref, zref, Vx, Vy, Vz);//设置观察点

	glMatrixMode(GL_PROJECTION);
	glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);//设置透视投影
	//gluPerspective(75,1,dnear,dfar);//设置透视投影的另一种方法
}

/*执行函数*/
void displayFcn()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0);
	glVertex3f(100.0, 100.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);

	glEnd();

	glFlush();
}

/*重绘函数，防止窗口变化*/
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0,0,newWidth,newHeight);
	winWidth = newWidth;
	winHeight = newHeight;
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Perspective View of A square!");

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}