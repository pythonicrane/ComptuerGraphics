/**
*计算机图形学第三版第13章P308二次曲面对象
*@author ZhaoHeln 2018年1月8日 15:46:07
*/
#include<gl/glut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;

GLsizei winWidth = 500, winHeight = 500;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}


/*执行函数*/
void displayFcn()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,1.0);//设置颜色
	gluLookAt(2.0, 2.0, 2.0,0.0, 0.0, 0.0, 0.0, 0.0,1.0);//设置观察点

	glPushMatrix();//输入矩阵
	glTranslatef(1.0, 1.0, 0.0);//把放置的坐标移到世界坐标的某个点
	glutWireSphere(0.75, 80, 60);//绘制球体，参数分别为，球半径，经纬网格数
	glPopMatrix();//输出

	glPushMatrix();
	glTranslatef(1.0,-0.5,0.5);
	glutWireCone(0.7,2.0,70,60);//圆锥体，参数为底面圆半径，高度，经纬网格数
	glPopMatrix();

	GLUquadricObj * cylinder;//定义曲面对象变量
	glPushMatrix();
	glTranslatef(0.0, 1.2, 0.8);
	cylinder = gluNewQuadric();//激活二次曲面绘制器
	gluQuadricDrawStyle(cylinder, GLU_LINE);//设置二次曲面绘制风格
	gluCylinder(cylinder,0.6,0,1.5,60,40);//画圆柱，参数为对象变量，底部和顶部圆半径，高，经纬网格数，顶部半径为0即圆锥体
	glPopMatrix();

	glFlush();
}

/*重绘函数，防止窗口变化*/
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0,0.0,5.0);
	glMatrixMode(GL_MODELVIEW);
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