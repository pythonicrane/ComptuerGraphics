/**
* 计算机图形学第三版第20章P468-OpenGL拾取操作
* 三维立体显示标准模版
* @author ZhaoHeln 2018年1月28日 12:15:12
*/

/*预编译加载动态链接库*/
// #pragma comment(lib,"glut32.lib")
// #pragma comment(lib,"glu32.lib")
// #pragma comment(lib,"opengl32.lib")

#include<gl/glut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;

GLsizei winWidth = 600, winHeight = 600;//WIN窗口大小
/*观察点参数，默认为(0,0,1,  0,0,0,  0,1,0)*/
GLfloat px0 = 1.0, py0 = 0.0, pz0 = 1.0;//观察点在世界坐标系的坐标
GLfloat xref = 0.0, yref = 0.0, zref = 0.0;//所观察的方向(所看的点)
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;//相机的正上向量(相机的正上方所对应的方向)
/*二维裁剪窗口或者三维裁剪立体*/
GLfloat viewSize = 300;
GLfloat xwMin = 0, xwMax = viewSize, ywMin = 0, ywMax = viewSize;//透视投影近观察面"大小"，相对于观察坐标系
GLfloat dnear = -viewSize, dfar = viewSize;//近观察面距离，远观察面距离，都是观察系坐标下，必须为正

const GLint pickBuffSize = 32;


/*
* 顶点对象
*/
class scrPt
{
public:
	GLint x;
	GLint y;
};

/*
* 初始化函数
*/
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void rects(GLenum mode)
{
	if (mode == GL_SELECT)
		glPushName(30);
	glColor3f(1.0,0.0,0.0);
	glRecti(40,130,150,260);

	if (mode == GL_SELECT)
		glPushName(10);
	glColor3f(0.0, 0.0, 1.0);
	glRecti(150, 130, 260, 260);

	if (mode == GL_SELECT)
		glPushName(20);
	glColor3f(0.0, 1.0, 0.0);
	glRecti(40, 40, 260, 130);
}

void processPicks(GLint nPicks, GLuint pickBuffer[])
{
	GLint j, k;
	GLuint objID, *ptr;
	cout << "Number of objects picked = " << nPicks << endl << endl;
	ptr = pickBuffer;

	for (j = 0; j < nPicks; j++)
	{
		objID = *ptr;
		cout << "    Stack positio = " << objID << endl;
		ptr++;
		cout << "    Min depth = " << float(*ptr / 0x7fffffff);
		ptr++;
		cout << "    Max depth = " << float(*ptr / 0x7fffffff) << endl;
		ptr++;
		cout << "    Stack IDs are:\n";
		for (k = 0; k < objID; k++)
		{
			cout << *ptr;
			ptr++;
		}
		cout << endl << endl;
	}
}

void pickRects(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	GLuint pickBuffer[pickBuffSize];
	GLint npicks, vpArray[4];
	if (button != GLUT_LEFT_BUTTON || action != GLUT_DOWN)
		return;
	glSelectBuffer(pickBuffSize, pickBuffer);
	glRenderMode(GL_SELECT);
	glInitNames();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glGetIntegerv(GL_VIEWPORT, vpArray);
	gluPickMatrix(GLdouble(xMouse), GLdouble(vpArray[3] - yMouse), 5.0, 5.0, vpArray);
	gluOrtho2D(xwMin, winWidth, ywMin, winHeight);
	rects(GL_SELECT);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glFlush();

	npicks = glRenderMode(GL_RENDER);
	processPicks(npicks, pickBuffer);
	glutPostRedisplay();
}

/*
* 显示循环调用函数
*/
void displayFcn()
{
	glClear(GL_COLOR_BUFFER_BIT);
	rects(GL_RENDER);
	glFlush();//注销后，重绘窗口会出现问题
}

/*
* 重绘函数，防止窗口变化
*/
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	winWidth = newWidth;
	winHeight = newHeight;
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwMin, winWidth, ywMin, winHeight);
	//glClear(GL_COLOR_BUFFER_BIT);//和displayFcn函数中的至少存在一个
}


int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Computer Graphics!");

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(pickRects);//鼠标响应调用
	glutMainLoop();
}