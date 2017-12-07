/**
*计算机图形学第三版第二章概述例子
*@author ZhaoHeln 2017年11月30日 17:18:30
*/
#include<gl/glut.h>

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.5);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
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
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("An Example OpenGL Program");
	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();
	return 0;
}
