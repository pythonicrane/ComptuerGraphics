#include <GL/glut.h>
#include <math.h>
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#define PI 3.1415926
GLfloat xRot = 0;
GLfloat yRot = 0;
GLfloat zRot = 0;

void Init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	// 把着色模式设置为单调着色
	glShadeModel(GL_FLAT); //glShadeModel(GL_SMOOTH);
						   // 把顺时针环绕的多边形设为正面，这与默认是相反的，因为我们使用的是三角形扇
	glFrontFace(GL_CW);
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
}
void SpecialKeys(int key, int x, int y)//方向键和F1旋转
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if (key> 356.0f)
		xRot = 0.0f;

	if (key< -1.0f)
		xRot = 355.0f;

	if (key> 356.0f)
		yRot = 0.0f;

	if (key< -1.0f)
		yRot = 355.0f;

	if (key == GLUT_KEY_F1) //绕着z轴旋转
		zRot += 5.0f;

	// 使用新的坐标重新绘制场景
	glutPostRedisplay();
}
void RenderScene()
{
	// 存储坐标和角度
	GLfloat x, y, z, angle, x1, y1;
	// 用于三角形颜色的交替设置
	int iPivot = 1;
	// 用默认颜色设置背景色，并清除深度缓冲区（必须的，因为3D空间有视景深度）
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//打开剔除功能（背面剔除，它用于消除一个表面的背面）
	//glEnable(GL_CULL_FACE);
	// 打开深度测试,如果不打开深度测试，3D锥体的显示就会与现实情况不符合
	glEnable(GL_DEPTH_TEST);

	// 保存矩阵状态并旋转
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLE_FAN);
	// 三角形扇的共享顶点，z轴中心点上方
	glVertex3f(0.0f, 0.0f, 0.75);
	for (angle = 0.0f; angle < (2.0f * PI + PI / 8.0f); angle += (PI / 8.0f)) {
		// 计算下一个顶点的位置
		x = 0.50f * sin(angle);
		y = 0.50f * cos(angle);
		if ((iPivot % 2) == 0) {
			glColor3f(1.0f, 1.0f, 0.0f);
		}
		else {
			glColor3f(0.0f, 1.0f, 1.0f);
		}
		// 增加基准值，下次改变颜色
		++iPivot;
		// 指定三角形扇的下一个顶点
		glVertex2f(x, y);
	}
	glEnd();

	// 绘制一个新的三角形扇，作为覆盖圆锥的底
	glBegin(GL_TRIANGLE_FAN);
	// 三角形扇的共享顶点，中心位于原点
	glVertex3f(0.0f, 0.0f, 0.0f);
	for (angle = 0.0f; angle < (2.0f * PI + PI / 8.0f); angle += (PI / 8.0f)) {
		// 计算下一个顶点的位置
		x = 0.50f * sin(angle);
		y = 0.50f * cos(angle);
		if ((iPivot % 2) == 0) {
			glColor3f(0.5f, 0.0f, 0.5f);
		}
		else {
			glColor3f(1.0f, 0.0f, 1.0f);
		}
		// 增加基准值，下次改变颜色
		++iPivot;
		// 指定三角形扇的下一个顶点
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}
int main(int argv, char *argc[]) {

	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(400, 300);
	glutCreateWindow("3D空间绘制圆锥面");
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(SpecialKeys);
	Init();
	glutMainLoop();
}