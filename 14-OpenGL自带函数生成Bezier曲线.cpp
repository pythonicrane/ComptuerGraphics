/**
* 计算机图形学第三版第14章P345-OpenGL自带函数生成Bezier曲线
* @author ZhaoHeln 2018年1月10日 20:59:28
*/
#include<gl/glut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;

GLsizei winWidth = 600, winHeight = 600;


void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);


}


/*执行函数*/
void displayFcn()
{
	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat ControlP[4][3] =
	{
		{ -66,-88,0 },
		{ -44,55,0 },
		{ 22,-33,0 },
		{ 77,66,0 }
	};
	/* 一维取值器的程序函数 */
	glMap1f(GL_MAP1_VERTEX_3,//生成的数据类型
		0, //u值的下限界
		1, //u值的上限界
		3, //顶点在数据中的间隔，x,y,z所以间隔是3
		4, //控制点的个数，减去1即为阶数
		*ControlP//保存控制点数据指针
	);
	glEnable(GL_MAP1_VERTEX_3);//根据函数Map1对贝赛尔曲线的设置，启用glEvalCoord1, glEvalMesh1, glEvalPoint1,在三维空间里生成曲线

	glColor3f(1, 0, 0);
	glLineWidth(1);

	/* 第一种方法：以线段模拟曲线 */
	//GLint nDivide=100;//将曲线切分多少份，以直线表达
	//glBegin(GL_LINE_STRIP);
	//for (int i = 0; i <= nDivide; i++)
	//{
	//	glEvalCoord1f((GLfloat)i/(GLfloat)nDivide);//参数为u（0.0~1.0）
	//}
	//glEnd();

	/* 第二种方法：opengl自带生成函数 */

	glMapGrid1f(100, 0, 1);//定义一个均匀分布的0到1的网格，中间有100个阶段
	glEvalMesh1(GL_LINE, 0, 50);//从上面生成的网格的0-50画线
								//对所有已启用的求职器应用当前定义的一维网格。
								//mode参数可以是GL_POINT、GL_LINE。
								//这个函数相当于为从i1到i2的每一步调用glMapGrid1d函数，其中0<i1,i2<n;
	glColor3f(0, 0, 1);
	glEvalMesh1(GL_LINE, 50, 100);//从上面生成的网格的50-100画线
	glFlush();
}

/*重绘函数，防止窗口变化*/
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
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