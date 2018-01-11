#include <windows.h>
#include <GL/glut.h>

GLUnurbsObj *theNurb;

GLfloat ctrlpoints[12][3] = { { 4,0,0 },{ 2.828,2.828,0 },{ 0,4,0 },{ -2.828,2.828,0 },
{ -4,0,0 },{ -2.828,-2.828,0 },{ 0,-4,0 },{ 2.828,-2.828,0 },
{ 4,0,0 },{ 2.828,2.828,0 },{ 0,4,0 },{ 2.828,2.828,0 } };
//控制点

GLfloat color[12][3] = { { 1.0,0.0,0.0 },{ 1.0,1.0,0.0 },{ 0.0,1.0,0.0 },{ -1.0,1.0,0.0 },
{ -1.0,0.0,0.0 },{ -1.0,-1.0,0.0 },{ 0.0,-1.0,0.0 },{ 1.0,-1.0,0.0 },
{ 1.0,0.0,0.0 },{ 1.0,1.0,0.0 },{ 0.0,1.0,0.0 },{ 1.0,1.0,0.0 } };

GLfloat knots[15] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);//设置背景色
	theNurb = gluNewNurbsRenderer();//创建NURBS对象theNurb
	gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 10);
}

/*绘制曲线*/
void myDisplay(void)
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	glLineWidth(3.0);

	/*绘制曲线*/
	gluBeginCurve(theNurb);
	gluNurbsCurve(theNurb, 15, knots, 3, &ctrlpoints[0][0], 3, GL_MAP1_VERTEX_3);
	gluNurbsCurve(theNurb, 15, knots, 3, &ctrlpoints[0][0], 3, GL_MAP1_COLOR_4);
	gluEndCurve(theNurb);

	/*绘制点*/
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	for (i = 0; i < 8; i++)
		glVertex2fv(&ctrlpoints[i][0]);
	glEnd();

	glutSwapBuffers();
}

void myReshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-10.0, 10.0, -10.0*(GLfloat)h / (GLfloat)w, 10.0*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-10.0*(GLfloat)w / (GLfloat)h, 10.0*(GLfloat)w / (GLfloat)h, -10.0, 10.0, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -9.0);
}

int main(int argc, char ** argv)
{
	/*初始化*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(200, 200);

	/*创建窗口*/
	glutCreateWindow("NURBS curve");

	/*绘制与显示*/
	myInit();

	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);

	glutMainLoop();
	return(0);
}