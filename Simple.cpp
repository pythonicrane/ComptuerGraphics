/**
*�����ͼ��ѧ������ڶ��¸�������
*@author ZhaoHeln 2017��11��30�� 17:18:30
*/
#include<gl/glut.h>

void init(void)
{
	glutSetColor(0, 0.0f, 0.0f, 0.0f);
	glutSetColor(1, 1.0f, 0.0f, 0.0f);
	glutSetColor(2, 0.0f, 1.0f, 0.0f);
	glutSetColor(3, 0.0f, 0.0f, 1.0f);
	glClearColor(1.0, 1.0, 1.0, 0.5);//���ڱ�����ɫ
	glMatrixMode(GL_PROJECTION);//����ģ�ͣ���������ʲô����
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);//2D����ͶӰ
}

void lineSegment(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINT);
	glVertex2i(50, 100);
	glVertex2i(75, 150);
	glVertex2i(100, 200);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	/*GLUT��ʼ��*/
	glutInit(&argc, argv);//��һ�����õĺ�����
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//��ʾ��ʽ
	glutInitWindowPosition(50, 100);//��ʾλ��
	glutInitWindowSize(400, 300);//���ڴ�С
	glutCreateWindow("An Example OpenGL Program");//�������ڲ���ֵ��������
	init();//��ʼ��
	glutDisplayFunc(lineSegment);//������ʾ����
	glutMainLoop();//ѭ������
	return 0;
}
