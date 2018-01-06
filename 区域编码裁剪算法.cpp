/**
* 计算机图形学第三版 区域码裁剪算法
* @author ZhaoHeln 2018年1月6日 15:39:19
*/

#include<gl/glut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;

GLsizei winWidth = 600, winHeight = 600;
GLfloat xwcMin = 0.0, xwcMax = 600.0;
GLfloat ywcMin = 0.0, ywcMax = 600.0;

const GLint winLeftBitCode = 0x1;
const GLint winRightBitCode = 0x2;
const GLint winBottomBitCode = 0x4;
const GLint winTopBitCode = 0x8;;

//顶点对象
class wcPt2D
{
public:
	GLfloat x;
	GLfloat y;
};

/* 内部判定函数 */
inline GLint inside(GLint code)
{
	return GLint(!code);//某一端点是否完全在裁减区域内，即0000
}

/* 排除函数 */
inline GLint reject(GLint code1, GLint code2)
{
	return GLint(code1&code2);//存在某一裁剪边全在外侧，即线段就全部在外面
}

/* 全包含函数 */
inline GLint accept(GLint code1, GLint code2)
{
	return GLint(!(code1 | code2));//只有0000|0000才为真，即全部在内部
}

/*
* 区域编码函数
* 0000，分别代表上部、底部、右边、左边，0代表在裁减区域内，1代表在裁剪区域外
*/
GLubyte encode(wcPt2D pt, wcPt2D winMin, wcPt2D winMax)
{
	GLubyte code = 0x00;
	if (pt.x < winMin.x)
		code = code | winLeftBitCode;
	if (pt.x > winMax.x)
		code = code | winRightBitCode;
	if (pt.y < winMin.y)				//!!!代码直接复制，写成pt.x，y方向不能裁剪的BUG
		code = code | winBottomBitCode;
	if (pt.y > winMax.y)
		code = code | winTopBitCode;

	return code;
}

/*
* 交换线段首尾坐标函数
*/
void swapPts(wcPt2D * p1, wcPt2D *p2)
{
	wcPt2D tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

/*
* 交换线段首尾区域编码函数
*/
void swapCodes(GLubyte *c1, GLubyte *c2)
{
	GLubyte tmp;
	tmp = *c1;
	*c2 = *c1;
	*c1 = tmp;
}

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
* 区域码裁剪算法
* 参数依次为裁减窗口的左下角，右上角，线段起点和终点
*/
void lineClipCode(wcPt2D winMin, wcPt2D winMax, wcPt2D lStart, wcPt2D lEnd)
{
	GLubyte code1, code2;//保存线段首尾区域码
	GLint done = false;//是否裁剪完标记
	GLint plotLine = false;//裁剪后，线段是否还存在
	GLfloat m;//保存斜率
	while (!done)//只有当四个裁剪边全部裁剪完才会退出循环
	{
		cout << "startX:" << lStart.x << " startY:" << lStart.y << endl;
		cout << "EndX:" << lEnd.x << " EndY:" << lEnd.y << endl;
		//每次while操作都要重新进行区域编码
		code1 = encode(lStart, winMin, winMax);
		code2 = encode(lEnd, winMin, winMax);
		if (accept(code1, code2))//线段完全在裁减区域内部情况
		{
			done = true;
			plotLine = true;
		}
		else
		{
			cout << "HELLO"<<endl;
			if (reject(code1, code2))//线段完全在裁减区域外面情况
			{
				done = true;
				plotLine = false;
			}
			else//线段部分在裁减区域中情况，lStart，lEnd至少有一点在某一裁剪边的外部
			{
				if (inside(code1))//起始点是否完全在裁减区域内，若是，则与lEnd将换，因为lEnd必定不全在四条裁剪边内部
				{
					swapPts(&lStart, &lEnd);
					swapCodes(&code1, &code2);
				}
				if (lEnd.x != lStart.x)
				{
					m = (lEnd.y - lStart.y) / (lEnd.x - lStart.x);//计算线段斜率
				}

				//依次进行左，右，下，上裁剪，每次while循环只会进行一次，最多四次
				if (code1&winLeftBitCode)
				{
					lStart.y += (winMin.x - lStart.x)*m;
					lStart.x = winMin.x;
				}
				else
				{
					if (code1&winRightBitCode)
					{
						lStart.y += (winMax.x - lStart.x)*m;
						lStart.x = winMax.x;
					}
					else
					{
						if (code1 & winBottomBitCode)
						{
							if (lEnd.x != lStart.x)
								lStart.x += (winMin.y - lStart.y) / m;
							lStart.y = winMin.y;
						}
						else
						{
							if (code1 & winTopBitCode)
							{
								if (lEnd.x != lStart.x)
									lStart.x += (winMax.y - lStart.y) / m;
								lStart.y = winMax.y;
							}
						}
					}
				}//左右下上裁剪操作

			}
		}
	}//while(!done)

	if (plotLine)//画线
	{
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);

		glVertex2f(lStart.x , lStart.y);
		glVertex2f(lEnd.x , lEnd.y);
		glEnd();
	}
}

void lineClipCode2(wcPt2D winMin, wcPt2D winMax, GLfloat lsx, GLfloat lsy, GLfloat lex, GLfloat ley)
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
	lineClipCode(winMin, winMax, lineStart, lineEnd);//裁剪
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

	lineClipCode2(winMin, winMax, 300,0, 300, 600);
	lineClipCode2(winMin, winMax, 100, 600, 500, 0);
	lineClipCode2(winMin, winMax, 0, 0, 600, 600);
	lineClipCode2(winMin, winMax, 0, 0, 600, 600);
	lineClipCode2(winMin, winMax, 600, 0, 0, 600);
	lineClipCode2(winMin, winMax, 120, 110, 460, 120);
	lineClipCode2(winMin, winMax, 30, 450, 270, 600);
	lineClipCode2(winMin, winMax, 450, 550, 520, 10);
	lineClipCode2(winMin, winMax, 450, 320, 380, 560);
	lineClipCode2(winMin, winMax, 130, 400, 440, 305);
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