/**
* 计算机图形学第三版第14章P345-OpenGL自带函数生成Bezier曲面
* 三维立体显示标准模版
* @author ZhaoHeln 2018年1月11日 12:41:47
*/

//预编译加载动态链接库
// #pragma comment(lib,"glut32.lib")
// #pragma comment(lib,"glu32.lib")
// #pragma comment(lib,"opengl32.lib")

#include<gl/glut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;


GLsizei winWidth = 600, winHeight = 600;//WIN窗口大小
//观察点参数，默认为(0,0,1,  0,0,0,  0,1,0)
GLfloat px0 = 1.0, py0 = 0.0, pz0 = 1.0;//观察点在世界坐标系的坐标
GLfloat xref = 0.0, yref = 0.0, zref = 0.0;//所观察的方向(所看的点)
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;//相机的正上向量(相机的正上方所对应的方向)
//二维裁剪窗口或者三维裁剪立体
GLfloat viewSize = 10.0;
GLfloat xwMin = -viewSize, xwMax = viewSize, ywMin = -viewSize,ywMax = viewSize;//透视投影近观察面"大小"，相对于观察坐标系
GLfloat dnear = -viewSize, dfar = viewSize;//近观察面距离，远观察面距离，都是观察系坐标下，必须为正


void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

//控制点
GLint nNumPoints = 3;

GLfloat ctrlPoints[3][3][3] =
{
	{ { -4.0f, 0.0f, 4.0f },
	{ -2.0f, 4.0f, 4.0f },
	{ 4.0f, 0.0f, 4.0f } },

	{ { -4.0f, 0.0f, 0.0f },
	{ -2.0f, 4.0f, 0.0f },
	{ 4.0f, 0.0f, 0.0f } },

	{ { -4.0f, 0.0f, -4.0f },
	{ -2.0f, 4.0f, -4.0f },
	{ 4.0f, 0.0f, -4.0f } }
};

//画控制点
void DrawPoints()
{
	int i, j;

	glColor3f(1.0f, 0.0f, 0.0f); //把点放大一点，看得更清楚
	glPointSize(5.0f);

	glBegin(GL_POINTS);
	for (i = 0; i < nNumPoints; i++)
		for (j = 0; j < 3; j++)
			glVertex3fv(ctrlPoints[i][j]);
	glEnd();
}


/* 生成Beizer曲面 */
void RenderScene()
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 保存模型视图矩阵
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//旋转一定的角度方便观察
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(60.0f, 1.0f, 0.0f, 0.0f);


	glColor3f(0.0f, 0.0f, 1.0f); //设置映射方式，只需要设置一次可以在SetupRC中调用。
	glMap2f(GL_MAP2_VERTEX_3, //生成的数据类型
		0.0f, // u的下界
		10.0f, //u的上界
		3, //数据中点的间隔
		3, //u方向上的阶
		0.0f, //v的下界
		10.0f, //v的上界
		9, // 控制点之间的间隔
		3, // v方向上的阶
		&ctrlPoints[0][0][0]); //控制点数组
							   //启用求值器
	glEnable(GL_MAP2_VERTEX_3);
	//从0到10映射一个包含10个点的网格
	glMapGrid2f(10, 0.0f, 10.0f, 10, 0.0f, 10.0f);
	// 计算网格
	glEvalMesh2(GL_LINE, 0, 10, 0, 10);
	//画控制点
	DrawPoints();

	glPopMatrix();

	glutSwapBuffers();//本程序可以省略
	glFlush();//这个是必要的，没有就不能显示曲面

}

/* 生成球体 */
void displayFcn()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);//设置颜色

	glPushMatrix();//输入矩阵
	glTranslatef(1.0, 1.0, 0.0);//把放置的坐标移到世界坐标的某个点
	glutWireSphere(7.5, 100, 60);//绘制球体，参数分别为，球半径，经纬网格数
	glPopMatrix();//输出

	glFlush();
}


/*重绘函数，防止窗口变化*/
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	//glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    // glOrtho,gluLookAt顺序为什么不能交换？
    glOrtho(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
    gluLookAt(px0, py0, pz0, xref, yref, zref, Vx, Vy, Vz);

    /* 或者也可以用投影矩阵 */
	//gluPerspective(fovy, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
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