#include <gl/glut.h>
#include <iostream>
#include <limits.h>
using namespace std;

int ajust(int color)
{
	return color / 255 * INT_MAX;
}

void putPixel(int x, int y)
{							  //画点的方法
	glColor3f(0.0, 1.0, 1.0); //画笔颜色
	glPointSize(5.0);		  //画笔粗细
	glBegin(GL_POINTS);
	glVertex2f(x, y); //画点
	glEnd();
}

int points[] = {20, 50, 200, 100, 200, 250, 100, 250, 50, 80, 20, 50}; //定义多边形点的坐标
int BorderColor[3] = {INT_MAX, 0, 0};								   //边界色，红色
int FillColor[3] = {0, INT_MAX, INT_MAX};							   //填充色
int BackColor[3] = {INT_MAX,INT_MAX,INT_MAX};

int cmpArryColor(const int color1[], const int color2[])
{
	if ((color1[0] == color2[0]) && (color1[1] == color2[1]) && (color1[2] == color2[2]))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int cpyArryColor(int color1[3],int color2[3])
{
	color1[0] = color2[0];
	color1[1] = color2[1];
	color1[2] = color2[2];
}

void clearArryColor(int color1[])
{
	color1[0] = 0;
	color1[1] = 0;
	color1[2] = 0;
}

//边标志算法
void edgeMarkFill(int n, int *points)
{
	int flag = 0; //标志位，判断在图形区域内(1)，还是在外面(0)
	int maxX = 0, minX = 0, maxY = 0, minY = 0;
	int i = 0, j = 0;
	int CurColor[3],tmpColor[3];

	//求maxX和minX
	for (i = 0, maxX = minX = points[0]; i < n * 2; i += 2)
	{
		if (maxX < points[i])
			maxX = points[i];
		else
			minX = points[i];
	}
	//求maxY和minY
	for (i = 1, maxY = minY = points[1]; i < n * 2; i += 2)
	{
		if (maxY < points[i])
			maxY = points[i];
		else
			minY = points[i];
	}

	//下面进行边标志填充
	for (i = minY + 1; i < maxY; i++)
	{
		flag = 0;//每次的扫描线开始标记都是0
		clearArryColor(tmpColor);
		clearArryColor(CurColor);
		for (j = minX; j <= maxX; j++)
		{
			tmpColor[0] = CurColor[0];
			tmpColor[1] = CurColor[1];
			tmpColor[2] = CurColor[2];
			glReadPixels(j, i, 1, 1, GL_RGB, GL_INT, CurColor); //getpixel()返回值为该像素点的RGB值
			if (cmpArryColor(CurColor, BorderColor)&&cmpArryColor(tmpColor, BackColor))
			{//遇到边界，将标记变成1，获取一个临时前一个点的变量，因为斜率大于1，画线可能存在两个点在同一个y上。
				flag = !flag;
				continue;//边界不用着色
			}
			if (flag)
			{
				glColor3iv(BorderColor);
				glPointSize(1.0); //画笔粗细
				glBegin(GL_POINTS);
					glVertex2f(j,i); //画点
				glEnd();
			}
		}
	}
}

void drawFun()
{

	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0, 0.0, 0.0);
	glColor3iv(BorderColor);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 6; i++)
	{
		glVertex2i(points[2 * i], points[2 * i + 1]);
		cout << points[2 * i] << " " << points[2 * i + 1] << endl;
	}
	// glVertex2i(0,0);
	// glVertex2i(0,50);
	// glVertex2i(100,200);
	// glVertex2i(60,300);
	// glVertex2i(0,450);

	glEnd();
	edgeMarkFill(6, points);
	glFlush();
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);   //窗口背景颜色
	glMatrixMode(GL_PROJECTION);		//矩阵模型，接下来做什么操作
	gluOrtho2D(0.0, 200.0, 0.0, 150.0); //2D正交投影
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Test");
	init();
	glutDisplayFunc(drawFun);
	glutReshapeFunc(reshape); //为什么要加这个？!!!不加这个绘制会越界
	glutMainLoop();
	return 0;
}