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
    glLineWidth(2.0);
    glVertex2f(x, y); //画点
    glEnd();
}

void putPixelEllipse(int x, int y, int x0, int y0)
{
    putPixel(x + x0, y + y0);
    putPixel(x + x0, -y + y0);
    putPixel(-x + x0, y + y0);
    putPixel(-x + x0, -y + y0);
}

void MidBresenhamEllipse(int x0, int y0, int a, int b)
{
    int x = 0;
    int y = b;
    double sqa = a * a;
    double sqb = b * b;
    double dt = sqa + sqb * (-b + 0.25);
    putPixelEllipse(x, y, x0, y0);
    while (sqb * (x + 1) < sqa * (y - 0.5))
    {
        if (dt < 0)
        {
            dt += sqb * (2 * x + 3);
        }
        else
        {
            dt += sqb * (2 * x + 3) + sqa * (-2 * y + 2);
            y--;
        }
        x++;
        putPixelEllipse(x, y, x0, y0);
    }
    dt = (b * (x + 0.5)) * 2 + (a * (y - 1)) * 2 - (a * b) * 2;
    while (y > 0)
    {
        if (dt < 0)
        {
            dt += sqb * (2 * x + 2) + sqa * (-2 * y + 3);
            x++;
        }
        else
        {
            dt += sqa * (-2 * y + 3);
        }
        y--;//注意放在else外面
        putPixelEllipse(x, y, x0, y0);
    }
}

//绘画汇总函数
void displaycallFun()
{
    MidBresenhamEllipse(250, 250, 200, 100);
    MidBresenhamEllipse(250, 250, 100, 200);
    MidBresenhamEllipse(250, 250, 200, 200);
    MidBresenhamEllipse(250, 250, 100, 100);
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