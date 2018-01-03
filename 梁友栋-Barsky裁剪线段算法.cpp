/**
* 计算机图形学第三版 梁友栋-Barsky裁剪算法
* @author ZhaoHeln 2018年1月3日 20:11:47
*/

/*
梁友栋-Barsky裁剪算法实现：
1、初始化线段交点的参数：u1=0，u2=1；
2、计算出各个裁剪边界的p、q值；
3、根据p、q来判断：是舍弃线段还是改变交点的参数。
（1） 当p<0时，参数r用于更新u1； 　　　　　（u1=max{u1，…，rk}）
（2） 当p>0时，参数r用于更新u2。 　　　　　（u2=min{u2，…，rk}）
（3）如果更新了u1或u2后，使u1>u2，则舍弃该线段。
（4）当p=0且q<0时，因为线段平行于边界并且位于边界之外，则舍弃该线段。见下图所示。
4、p、q的四个值经判断后，如果该线段未被舍弃，则裁剪线段的端点坐标由参数u1和u2的值决定。
*/
#include<gl/glut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;

GLsizei winWidth = 600, winHeight = 600;
GLfloat xwcMin = 0.0, xwcMax = 600.0;
GLfloat ywcMin = 0.0, ywcMax = 600.0;

//顶点对象
class wcPt2D
{
public:
	GLfloat x;
	GLfloat y;
};

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(xwcMin, winWidth, ywcMin, winHeight);
}

/*画裁剪框*/
void ClipRect(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);//画封闭的折线
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glVertex2f(x2, y1);
	glEnd();

}

/*
* 梁友栋-Barsky裁剪算法
* 参数依次为裁减窗口的左下角，右上角，线段起点和终点
*/
void lineClipLiangBarsky(wcPt2D winMin, wcPt2D winMax, wcPt2D lStart, wcPt2D lEnd)
{
	GLint flag = 0;//标记是否抛弃，true的时候为抛弃
	GLfloat u1 = 0.0, u2 = 1.0;//初始化参数方程交点系数的最小和最大值
	GLfloat p[4], q[4];
	GLfloat r;
	p[0] = lStart.x - lEnd.x;
	p[1] = -p[0];
	p[2] = lStart.y - lEnd.y;
	p[3] = -p[2];

	q[0] = lStart.x - winMin.x;
	q[1] = winMax.x - lStart.x;
	q[2] = lStart.y - winMin.y;
	q[3] = winMax.y - lStart.y;

	for (int i = 0; i < 4; i++)
	{
		r = q[i] / p[i];
		if (p[i] < 0)
		{
			u1 = ((r>u1)?r:u1);
			if (u1 > u2)
			{
				flag = 1;
			}
		}
		else if (p[i] > 0)
		{
			u2 = ((r < u2) ? r : u2);
			if (u1 > u2)
			{
				flag = 1;
			}
		}
		else
		{
			if (q[i] < 0)
			{
				flag = 1;
			}
		}
	}
	if (!flag)
	{

		cout << lStart.x - u1*p[0] << " " << lStart.y + u1*p[1] << endl;
		cout << lStart.x - u2*p[0] << " " << lStart.y + u2*p[1] << endl;
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);//画线

		glVertex2f(lStart.x - u1*p[0], lStart.y - u1*p[2]);
		glVertex2f(lStart.x - u2*p[0], lStart.y - u2*p[2]);
		glEnd();
	}
}

void lineClipLiangBarsky2(wcPt2D winMin, wcPt2D winMax, GLfloat lsx,GLfloat lsy, GLfloat lex, GLfloat ley)
{
	wcPt2D lineStart, lineEnd;
	lineStart.x = lsx;
	lineStart.y = lsy;
	lineEnd.x = lex;
	lineEnd.y = ley;
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);//画出原来的线段
	glVertex2f(lineStart.x, lineStart.y);
	glVertex2f(lineEnd.x, lineEnd.y);
	glEnd();
	lineClipLiangBarsky(winMin, winMax, lineStart, lineEnd);//裁剪
}


/*执行函数*/
void displayFcn()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);

	wcPt2D winMin, winMax;//设置裁剪框
	winMin.x = 100.0;
	winMin.y = 100.0;
	winMax.x = 500.0;
	winMax.y = 500.0;

	ClipRect(winMin.x, winMin.y, winMax.x, winMax.y);

	lineClipLiangBarsky2(winMin, winMax,0,0,600,600);
	lineClipLiangBarsky2(winMin, winMax, 0, 0, 600, 600);
	lineClipLiangBarsky2(winMin, winMax, 600, 0, 0, 600);
	lineClipLiangBarsky2(winMin, winMax, 120, 110, 460, 120);
	lineClipLiangBarsky2(winMin, winMax, 30, 450, 270, 600);
	lineClipLiangBarsky2(winMin, winMax, 450, 550, 520, 10);
	lineClipLiangBarsky2(winMin, winMax, 450, 320, 380, 560);
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
	glutCreateWindow("Computer Graphics Test!");

	init();
	glutDisplayFunc(displayFcn);
	//glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}