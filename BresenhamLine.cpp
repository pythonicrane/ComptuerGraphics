#include <gl/glut.h>
#include <iostream>
#include <math.h>
using namespace std;

/**
 * 使用GLUT写的画点函数
 * @author zhaoheln 2017年12月11日 20:55:45
*/
void putPixel(int x, int y)
{                             //画点的方法
    glColor3f(1.0, 0.0, 0.0); //画笔颜色
    glPointSize(1.0);         //画笔粗细
    glBegin(GL_POINTS);
    glVertex2f(x, y);         //画点
    glEnd();
}

/**
 *简单Bresenham算法，应用于坐标轴第一1/8象限，即斜率0<k<1
 *  @author zhaoheln 2017年12月11日 20:15:43
*/
void DrawBresenhamlineSimple(int x0, int y0, int x1, int y1)
{
    int x = x0;
    int y = y0;
    int disx = x1 - x0;                  //x轴增量
    int disy = y1 - y0;                  //y轴增量
    float k = (float)disy / (float)disx; //获得斜率,!!!注意要用浮点运算，否则K=0
    float divError = k - 0.5;            //初始化偏差为k，减去0.5，则以y=0为相对参考轴
    for (; x <= x1; x++)                  //迭代x,注意起点和终点
    {
        putPixel(x, y);
        cout << x << " " << y << endl;
        if (divError > 0) //若偏差大于0,则y轴像素加一位
        {
            y++;
            divError = divError - 1;
        }
        divError += k;//若放在if语句前则多加了一个k,在for循环前加了一次
    }
}

/**
 * 整数Bresenham算法，应用于坐标轴第一1/8象限，即斜率0<k<1
 * 消除除法，浮点运算和乘法运算，提高效率
 *  @author zhaoheln 2017年12月11日 20:15:43
*/
void DrawBresenhamlineInteger(int x0, int y0, int x1, int y1)
{
    int x = x0;
    int y = y0;
    int disx = x1 - x0;
    int disy = y1 - y0;
    int divError = (disy<<2) - disx; //e=(f)disy/(f)disx - 0.5,两边同乘2倍disx，2disx=disx+disx,令divError=2*e*disx
    for (; x <= x1;x++)
    {
        putPixel(x, y);
        if(divError>0)
        {
            y++;
            divError -= disx<<2; //原来是e-=1,两边同乘2*disx;令divError = 2*e*disx得
        }
        divError += disy<<2;//同理，原来为e+=k,两边同乘2*disx;令divError = 2*e*disx得
    }
}

/**
 * 整数Bresenham算法，通用算法，任意斜率
 *  @author zhaoheln 2017年12月11日 20:15:43
*/
void DrawBresenhamlineIntegerCommon(int x0, int y0, int x1, int y1)
{

}

void display()
{
    //Start:初始化GL绘图
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 500, 500);
    //  End:初始化GL绘图

    DrawBresenhamlineInteger(0, 0, 500, 100);

    //Strat:强制刷新缓冲，保证绘图命令将被执行
    glFlush();
    //  End:强制刷新缓冲，保证绘图命令将被执行
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