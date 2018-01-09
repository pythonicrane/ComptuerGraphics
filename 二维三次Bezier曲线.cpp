/**
*计算机图形学第三版第14章P323-二维三次Bezier曲线示例
*@author ZhaoHeln 2018年1月9日 13:40:43
*/
#include<gl/glut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;

GLsizei winWidth = 600, winHeight = 600;
GLfloat xwcMin = -50.0, xwcMax = 50.0;
GLfloat ywcMin = -50.0, ywcMax = 50.0;

//三维坐标对象
class wcPt3D
{
public:
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//glMatrixMode(GL_PROJECTION);
	//glViewport(0, 0, winWidth, winHeight);
	//gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
}

/* 画点 */
void plotPoint(wcPt3D bezCurvePt)
{
	glBegin(GL_POINTS);//!!!一定要是GL_POINTS，少个S就不会显示
	glVertex2f(bezCurvePt.x,bezCurvePt.y);
	glEnd();
	//cout << "X:" << bezCurvePt.x << "  Y:" << bezCurvePt.y << endl;
}

/*计算排列组合*/
void binomialCoeffs(GLint n, GLint *C)
{
	GLint k, j;
	for (k = 0; k <= n; k++)
	{
		C[k] = 1;
		for (j = n; j >= k + 1; j--)
			C[k] *= j;
		for (j = n - k; j >= 2; j--)
			C[k] /= j;
	}
}

/* Bezier曲线计算公式
* @pragma 系数u,计算结果点，控制点个数，控制点数组指针，保存常系数的数组指针
* 四个控制点的Bezier曲线计算公式，类似于莱布尼茨公式
* P(u)=(1-u)^3*P0+3*(1-u)^2*u*P1+3*(1-u)*u^2*P2+u^3*P3;
*/
void computeBezPt(GLfloat u,wcPt3D *bezPt,GLint nCtrlPts,wcPt3D *ctrlPts,GLint *C)
{
	GLint k, n = nCtrlPts - 1;
	GLfloat bezBlendFcn;
	bezPt->x = bezPt->y = bezPt->z = 0;
	for (k = 0; k < nCtrlPts; k++)
	{
		//包含四部分，排列组合系数，(1-u)的n-k次幂，u的k次幂，x
		bezBlendFcn = C[k] * pow(u, k)*pow(1 - u, n - k);
		bezPt->x += bezBlendFcn*ctrlPts[k].x;
		bezPt->y += bezBlendFcn*ctrlPts[k].y;
		bezPt->y += bezBlendFcn*ctrlPts[k].z;
	}

}

/* bezier函数求曲线上的点
* @pragma 控制点数组指针，控制点个数，画点数量
*/
void bezier(wcPt3D*ctrlPts, GLint nCtrlPts, GLint nBezCurvePts)
{
	wcPt3D bezCurvePt;
	GLfloat u;
	GLint *C, k;
	C = new GLint[nCtrlPts];
	binomialCoeffs(nCtrlPts-1,C);
	for (k = 0; k <= nBezCurvePts; k++)//画点数量次循环计算Bezier
	{
		u = GLfloat(k) / GLfloat(nBezCurvePts);
		computeBezPt(u,&bezCurvePt,nCtrlPts,ctrlPts,C);
		plotPoint(bezCurvePt);
	}
	delete[]C;
}




/*执行函数*/
void displayFcn()
{
	GLint nCtrlPts = 4;
	GLint nBezCurvePts = 1000;
	wcPt3D ctrlPts[4] = //四个控制点
	{
		{-40.0,-40.0,0.0},
		{-10.0,200.0,0.0},
		{10.0,-200.0,0.0},
		{40.0,40.0,0.0}
	};

	// GLint nCtrlPts = 6;
	// GLint nBezCurvePts = 2000;
	// wcPt3D ctrlPts[6] = //6个控制点
	// {
	// 	{0.0,-40.0,0.0},
	// 	{-40.0,-40.0,0.0},
	// 	{-40.0,0.0,0.0},
	// 	{50.0,50.0,0.0},
	// 	{40.0,0.0,0.0},
	// 	{ 0.0,-40.0,0.0 },
	// };

	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(4);
	glColor3f(1.0, 0.0, 0.0);//设置颜色
	bezier(ctrlPts,nCtrlPts,nBezCurvePts);

	glFlush();
}

/*重绘函数，防止窗口变化*/
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);//这里写错成winWidth，winHeight导致显示很小
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Bezier Curve");

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}