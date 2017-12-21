/**
*计算机图形学第三版第二章概述例子
*@author ZhaoHeln 2017年11月30日 17:18:30
*/
#include<gl/glut.h>

void init(void)
{
	glutSetColor(0, 0.0f, 0.0f, 0.0f);
	glutSetColor(1, 1.0f, 0.0f, 0.0f);
	glutSetColor(2, 0.0f, 1.0f, 0.0f);
	glutSetColor(3, 0.0f, 0.0f, 1.0f);
	glClearColor(1.0, 1.0, 1.0, 0.5);//窗口背景颜色
	glMatrixMode(GL_PROJECTION);//矩阵模型，接下来做什么操作
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);//2D正交投影
}

void lineSegment(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINT);
	glVertex2i(50, 100);
	glVertex2i(75, 150);
	glVertex2i(100, 200);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	/*GLUT初始化*/
	glutInit(&argc, argv);//第一个调用的函数，
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//显示方式
	glutInitWindowPosition(50, 100);//显示位置
	glutInitWindowSize(400, 300);//窗口大小
	glutCreateWindow("An Example OpenGL Program");//创建窗口并赋值窗口名字
	init();//初始化
	glutDisplayFunc(lineSegment);//调用显示函数
	glutMainLoop();//循环调用
	return 0;
}
