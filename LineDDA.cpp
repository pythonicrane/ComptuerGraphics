#include<stdlib.h>
#include<math.h>
#include<gl/glut.h>
inline int myround(const float a)
{
	return int(a + 0.5);
}

void putPixel(int x, int y) {//����ķ���
	glColor3f(0.0, 1.0, 1.0);//������ɫ
	glPointSize(5.0);//���ʴ�ϸ
	glBegin(GL_POINTS);
	glVertex2f(x, y);//����
	glEnd();
}


/**
*�����ͼ��ѧ������  DDA��ֱ���㷨 �㷨
*@author ZhaoHeln 2017��11��30�� 17:18:30
*/
void lineDDA(int x0, int y0, int xEnd, int yEnd)
{
	int dx = xEnd - x0;
	int dy = yEnd - y0;
	int steps, k;
	float xIncrement, yIncrement;
	float x = x0, y = y0;

	if (fabs(dx) > fabs(dy))
	{
		steps = fabs(dx);
	}
	else
	{
		steps = fabs(dy);
	}

	xIncrement = float(dx) / float(steps);
	yIncrement = float(dy) / float(steps);
	putPixel(myround(x), myround(y));
	for (k = 0;k < steps;k++)
	{
		x += xIncrement;
		y += yIncrement;
		putPixel(myround(x), myround(y));
	}

}

void display(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);
	//������㼰�յ�
	lineDDA(0, 0, 500, 0);
	lineDDA(0, 0, 0, 500);
	lineDDA(0, 500, 500, 500);
	lineDDA(500, 0, 500, 500);
	lineDDA(0, 0, 500, 500);//k=1
	lineDDA(0, 0, 500, 250);
	lineDDA(0, 250, 500, 500);
	lineDDA(0, 500, 500, 0);//k=-1
	lineDDA(0, 250, 500, 0);
	lineDDA(0, 500, 500, 250);
	lineDDA(250, 0, 250, 500);//k=0
	lineDDA(0, 250, 500, 250);//k������

	glFlush();
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

