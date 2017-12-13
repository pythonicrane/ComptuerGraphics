#include <gl/glut.h>
#include <iostream>

/**
 * 使用GLUT写的画点函数
 * @author zhaoheln 2017年12月11日 20:55:45
*/
void putPixel(int x, int y)
{                             //画点的方法
    glColor3f(1.0, 0.0, 0.0); //画笔颜色
    glPointSize(1.0);         //画笔粗细
    glBegin(GL_POINTS);
    glVertex2f(x, y); //画点
    glEnd();
}

/**
 * BresenhamCircle画圆算法
 * 设圆心为O(0,0),初始点为(0,R),当画到Xp点的时候，下一点可以取T(Xp+1,Yp)或B(Xp+1,Yp-1)
 * 由方程F(x,y) = x^2+y^2 -R^2可得到点(x,y)在圆内还是圆外，F(T),F(B)是点T,B与圆比较
 * 记 D=F(T)+F(B)，当D>0,取B，D更新为D+4*Xp-4*Yp+10
 * 当D<0时，取T,D更新为D+4Xp+6;
 * @author zhaoheln 2017年12月13日 21:34:06
 */
void BresenhamCircle(int x0, int y0, int radius)
{
    int x = 0;
    int y = radius;//初始点（0，R）
    int d = 3 - (radius << 1);//代进F()函数，得初始的D
    while (x <= y)//循环第一象限上半区
    {
        //圆的八方对称点,画出第一象限上半区的点，即可得到其他七个区的七个点
        putPixel(x+x0, y+y0);
        putPixel(y+x0, x+y0);
        putPixel(-x+x0, y+y0);
        putPixel(-y+x0, x+y0);
        putPixel(-y+x0, -x+y0);
        putPixel(-x+x0, -y+y0);
        putPixel(x+x0, -y+y0);
        putPixel(y+x0, -x+y0);
        if (d <= 0)
        {
            d += (x << 2) + 6;
        }
        else
        {
            d += ((x - y) << 2) + 10;
            y--;
        }
        x++;
    }
}

/**
 * 中心点画圆算法
 * 设当前画点为P(Xp,Yp),则下一点为T(Xp+1,Yp)或B(Xp+1,Yp-1)
 * TB的中点为M(Xp+1,Yp-0.5),点M的D=F(x,y)=（Xp+1)^2+(Yp-0.5)^2-R^2
 * 当D>0，取B，则下一个中心点D1=F(Xp+2,Yp-1.5)=D+2Xp-2Yp+5
 * 当D<0，取T，则下一个中心点D1=F(Xp+2,Yp-0.5)=D+2Xp+3
 * 初始D为F(0,R-0.5)=1.25-R,令新D=d=D+0.25,则初始d为1-R
*/
void MidPointCircle(int x0, int y0, int radius)
{
    int x = 0;
    int y = radius;
    int d = 1 - radius;
    while(y>x)
    {
        //圆的八方对称点,画出第一象限上半区的点，即可得到其他七个区的七个点
        putPixel(x+x0, y+y0);
        putPixel(y+x0, x+y0);
        putPixel(-x+x0, y+y0);
        putPixel(-y+x0, x+y0);
        putPixel(-y+x0, -x+y0);
        putPixel(-x+x0, -y+y0);
        putPixel(x+x0, -y+y0);
        putPixel(y+x0, -x+y0);
        if(d<0)
        {
            d += (x << 1) + 3;
        }else
        {
            d += ((x - y) << 1) + 5;
            y--;
        }
        x++;
    }
}

void MidPointCircleOptimize(int x0, int y0, int radius)
{
    int x = 0;
    int y = radius;
    int d = 1 - radius;
    int dt = 3;
    int db = -(radius << 1) + 5;
    while (y>x)
    {
        //圆的八方对称点,画出第一象限上半区的点，即可得到其他七个区的七个点
        putPixel(x+x0, y+y0);
        putPixel(y+x0, x+y0);
        putPixel(-x+x0, y+y0);
        putPixel(-y+x0, x+y0);
        putPixel(-y+x0, -x+y0);
        putPixel(-x+x0, -y+y0);
        putPixel(x+x0, -y+y0);
        putPixel(y+x0, -x+y0);
        if(d<0)
        {
            d += dt;
            db += 2;
            dt += 2;
        }else
        {
            d += db;
            dt += 2;
            db += 4;
            y--;
        }
        x++;
    }
}


//绘画汇总函数
void displaycallFun()
{
    MidPointCircleOptimize(250, 250, 50);
    MidPointCircleOptimize(250, 250, 100);
    MidPointCircleOptimize(250, 250, 200);
    MidPointCircleOptimize(250, 250, 250);
}

//OpenGL绘画基本设置
void display()
{
    //Start:初始化GL绘图
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 500, 500);
    //  End:初始化GL绘图

    displaycallFun();

    //Strat:强制刷新缓冲，保证绘图命令将被执行
    glFlush();
    //  End:强制刷新缓冲，保证绘图命令将被执行
}

//主函数
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