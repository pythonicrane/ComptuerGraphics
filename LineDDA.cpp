#include<stdlib.h>
#include<math.h>
#include<gl/glut.h>
inline int myround(const float a)
{
	return int(a + 0.5);
}

void putPixel(int x, int y) {//画点的方法
	glColor3f(0.0, 1.0, 1.0);//画笔颜色
	glPointSize(5.0);//画笔粗细
	glBegin(GL_POINTS);
	glVertex2f(x, y);//画点
	glEnd();
}


/**
*计算机图形学第三版  DDA画直线算法 算法
*@author ZhaoHeln 2017年11月30日 17:18:30
*/
void lineDDA(int x0, int y0, int xEnd, int yEnd)
{
	int dx = xEnd - x0;
	int dy = yEnd - y0;
	int steps, k;
	float xIncrement, yIncrement;
	float x = x0, y = y0;

	if (fabs(dx) > fabs(dy))
	{
		steps = fabs(dx);
	}
	else
	{
		steps = fabs(dy);
	}

	xIncrement = float(dx) / float(steps);
	yIncrement = float(dy) / float(steps);
	putPixel(myround(x), myround(y));
	for (k = 0;k < steps;k++)
	{
		x += xIncrement;
		y += yIncrement;
		putPixel(myround(x), myround(y));
	}

}

void display(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);
	//坐标起点及终点
	lineDDA(0, 0, 500, 0);
	lineDDA(0, 0, 0, 500);
	lineDDA(0, 500, 500, 500);
	lineDDA(500, 0, 500, 500);
	lineDDA(0, 0, 500, 500);//k=1
	lineDDA(0, 0, 500, 250);
	lineDDA(0, 250, 500, 500);
	lineDDA(0, 500, 500, 0);//k=-1
	lineDDA(0, 250, 500, 0);
	lineDDA(0, 500, 500, 250);
	lineDDA(250, 0, 250, 500);//k=0
	lineDDA(0, 250, 500, 250);//k不存在

	glFlush();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("DDA_line");
	glutDisplayFunc(display);
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glutMainLoop();
	return 0;

}

