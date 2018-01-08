
#define GLUT_DISABLE_ATEXIT_HACK
#include <math.h>

#include "gl/glut.h"
#pragma comment(lib, "glut32.lib")

#define RADIUS 50.0f
#define SIZE 100.0f

#define CONE         1
#define TETRAHEDRON  2
#define CUBE         3
#define DODECAHEDRON 4
#define ICONSAHEDRON 5
#define OCTAHEDRON   6
#define SPHERE       7
#define TOURUS       8
#define TEAPOT       9
#define WIRED        10

GLboolean bWire = false;
GLint nSelected = CONE;

void OnDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); //ʹ����ȼ��

	glPushMatrix();
	{
		glColor3f(1.0f, 0.0f, 0.0f);

		glEnable(GL_NORMALIZE);  //��һ��������
		switch(nSelected)
		{
		case(CONE):             //Բ׶��
			if (bWire)
			{
				glutWireCone(RADIUS, 2 * RADIUS, 30, 30);
			}
			else
			{
				glutSolidCone(RADIUS, 2 * RADIUS, 30, 30);
			}
			break;

		case(TETRAHEDRON):     //������
			glPushMatrix();
			{
				glScalef(RADIUS, RADIUS, RADIUS);
				if(bWire)
				{
					glutWireTetrahedron();
				}
				else
				{
					glutSolidTetrahedron();
				}
			}
			glPopMatrix();
			break;

		case(CUBE):   //������
			if(bWire)
			{
				glutWireCube(1.5 * RADIUS);
			}
			else
			{
				glutSolidCube(1.5 * RADIUS);
			}
			break;

		case(DODECAHEDRON): //��ʮ������
			glPushMatrix();
			{
				glScalef(RADIUS/2, RADIUS/2, RADIUS/2);
				if(bWire)
				{
					glutWireDodecahedron();
				}
				else
				{
					glutSolidDodecahedron();
				}
			}
			glPopMatrix();
			break;

		case(ICONSAHEDRON):  //��������
			glPushMatrix();
			{
				glScalef(RADIUS, RADIUS, RADIUS);
				if(bWire)
				{
					glutWireIcosahedron();
				}
				else
				{
					glutSolidIcosahedron();
				}
			}
			glPopMatrix();
			break;

		case(OCTAHEDRON):   //����
			glPushMatrix();
			{
				glScalef(RADIUS, RADIUS, RADIUS);
				if(bWire)
				{
					glutWireOctahedron();
				}
				else
				{
					glutSolidOctahedron();
				}
			}
			glPopMatrix();
			break;

		case(SPHERE):   //Բ����
			if(bWire)
			{
				glutWireSphere(RADIUS, 30, 30);
			}
			else
			{
				glutSolidSphere(RADIUS, 30, 30);
			}
			break;

		case(TOURUS):  // ���
			if(bWire)
			{
				glutWireTorus(RADIUS / 2, RADIUS, 30, 30);
			}
			else
			{
				glutSolidTorus(RADIUS / 2, RADIUS, 30, 30);
			}
			break;

		case(TEAPOT):
			if(bWire)
			{
				glutWireTeapot(RADIUS);
			}
			else
			{
				glutSolidTeapot(RADIUS);
			}
		}
	}
	glPopMatrix();
	glutSwapBuffers();
}

void OnReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);

	float aspect = (float)h / (float)w;

	if(w <= h)
	{
		glOrtho(-SIZE, SIZE, -SIZE * aspect, SIZE * aspect, -SIZE, SIZE);
	}
	else
	{
		glOrtho(-SIZE / aspect, SIZE / aspect, -SIZE, SIZE, -SIZE, SIZE);
	}
	gluLookAt(10.0f, 20.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void OnMenu(int value)
{
	if(value == WIRED)
	{
		bWire = !bWire;
	}
	else
	{
		nSelected = value;
	}
	glutPostRedisplay();
}

void CreateMenu()
{
	glutAddMenuEntry("Բ׶��", CONE);
	glutAddMenuEntry("������", TETRAHEDRON);
	glutAddMenuEntry("������", CUBE);
	glutAddMenuEntry("��ʮ������", DODECAHEDRON);
	glutAddMenuEntry("����ʮ����", ICONSAHEDRON);
	glutAddMenuEntry("��������", OCTAHEDRON);
	glutAddMenuEntry("����", SPHERE);
	glutAddMenuEntry("Բ����", TOURUS);
	glutAddMenuEntry("���", TEAPOT);
	glutAddMenuEntry("�߿��ʵ��", WIRED);

	glutAttachMenu(GLUT_RIGHT_BUTTON);  //ָ���˵��¼�������Ҽ���������
}

void SetupLights()
{
	GLfloat ambientLight[]  = {0.2f,  0.2f,  0.2f,  1.0f};//������
	GLfloat diffuseLight[]  = {0.9f,  0.9f,  0.9f,  1.0f};//������
	GLfloat specularLight[] = {1.0f,  1.0f,  1.0f,  1.0f};//�����
	GLfloat lightPos[]      = {50.0f, 80.0f, 60.0f, 1.0f};//��Դλ��

	glEnable(GL_LIGHTING);								//���ù���
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);		//���û�����Դ
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);		//�����������Դ
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);	//���þ����Դ
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);		//���õƹ�λ��
	glEnable(GL_LIGHT0);								//�򿪵�һ���ƹ�

	glEnable(GL_COLOR_MATERIAL);						//���ò��ʵ���ɫ����
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);	//ָ��������ɫ����
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight); //ָ�����϶Ծ����ķ�Ӧ
	glMateriali(GL_FRONT, GL_SHININESS, 100);           //ָ������ϵ��
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);										//��ʼ��OpenGL
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   //������ʾģʽ
	glutInitWindowSize(600, 480);
	glutCreateWindow("GLUT�ṩ��9��ʵ�����");

	glutCreateMenu(OnMenu);
	glutReshapeFunc(OnReshape);
	glutDisplayFunc(OnDisplay);

	CreateMenu();					//ʵ�����ɲ˵�
	SetupLights();					//���ù���

	glutMainLoop();					//����OpenGL��ѭ��
}