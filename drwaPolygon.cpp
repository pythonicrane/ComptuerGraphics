#include <gl/glut.h>
#include <iostream>
using namespace std;

// //边标志算法
// void edgeMarkFill(int n,int *points)
// {
// 	 int flag=0;//标志位，判断在图形区域内(1)，还是在外面(0)
// 	 int c1=0,c2=0;//c1为边界色，c2为背景色
// 	 int maxX=0,minX=0,maxY=0,minY=0;
// 	 int i=0,j=0;

// 	 //求maxX和minX
// 	 for(i=0,maxX=minX=points[0];i<n*2;i+=2)
// 	 {
// 	  if(maxX<points[i])
// 	   maxX=points[i];
// 	  else
// 	   minX=points[i];
// 	 }
// 	 //求maxY和minY
// 	 for(i=1,maxY=minY=points[1];i<n*2;i+=2)
// 	 {
// 	  if(maxY<points[i])
// 	   maxY=points[i];
// 	  else
// 	   minY=points[i];
// 	 }

// 	 //下面进行边标志填充
// 	 for(i=minY+1;i<maxY;i++)
// 	 {
// 	  for(j=minX;j<=maxX;j++)
// 	  {
// 	   c1=c2;
// 	   c2=getpixel(j,i);//getpixel()返回值为该像素点的RGB值
// 	   if(c1==WHITE&&c2==BLACK)
// 		flag=!flag;
// 	   if(flag)
// 		putpixel(j,i,WHITE);
// 	  }

// 	  //为现实效果而延迟时间的空循环
// 	  for(int cc=0;cc<10000000;cc++);

// 	 }
// }

void drawFun()
{
	int points[]={50,50,200,100,200,250,100,250,50,80,50,50};//定义多边形点的坐标
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 6;i++)
	{
		glVertex2i(points[2*i],points[2*i+1]);
		cout << points[2 * i] << " " << points[2 * i + 1] << endl;
	}
	// glVertex2i(0,0);
	// glVertex2i(0,50);
	// glVertex2i(100,200);
	// glVertex2i(60,300);
	// glVertex2i(0,450);

	glEnd();
	glFlush();
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.5);//窗口背景颜色
	glMatrixMode(GL_PROJECTION);//矩阵模型，接下来做什么操作
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);//2D正交投影
}

void reshape(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
}

int main(int argc,char ** argv)
{
	 glutInit(&argc,argv);
	 glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	 glutInitWindowPosition(10, 10);
	 glutInitWindowSize(1000, 1000);
	 glutCreateWindow("Test");
	 init();
	 glutDisplayFunc(drawFun);
	 glutReshapeFunc(reshape);//为什么要加这个？!!!不加这个绘制会越界
	 glutMainLoop();
	 return 0;
}