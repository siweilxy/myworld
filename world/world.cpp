#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#define ColoredVertex(c, v) do{ glColor3fv(c); glVertex3fv(v); }while(0)
static int angle = 0;
static int rotateMode = 0;
 
void myDisplay(void)
{
	static int list = 0;
	if (list == 0)
	{
		GLfloat
			PointA[] = { 0.5f, 0.5f, -0.5f },
			PointB[] = { 0.5f, -0.5f, -0.5f },
			PointC[] = { -0.5f, -0.5f, -0.5f },
			PointD[] = { -0.5f, 0.5f, -0.5f },
			PointE[] = { 0.5f, 0.5f, 0.5f },
			PointF[] = { 0.5f, -0.5f, 0.5f },
			PointG[] = { -0.5f, -0.5f, 0.5f },
			PointH[] = { -0.5f, 0.5f, 0.5f };
		GLfloat
			ColorA[] = { 1, 0, 0 },
			ColorB[] = { 0, 1, 0 },
			ColorC[] = { 0, 0, 1 },
			ColorD[] = { 1, 1, 0 },
			ColorE[] = { 1, 0, 1 },
			ColorF[] = { 0, 1, 1 },
			ColorG[] = { 1, 1, 1 },
			ColorH[] = { 0, 0, 0 };
 
		list = glGenLists(1);
		glNewList(list, GL_COMPILE);
		
		// 面1
		glBegin(GL_POLYGON);
		ColoredVertex(ColorA, PointA);
		ColoredVertex(ColorE, PointE);
		ColoredVertex(ColorH, PointH);
		ColoredVertex(ColorD, PointD);
		glEnd();
		
		// 面2
		glBegin(GL_POLYGON);
		ColoredVertex(ColorD, PointD);
		ColoredVertex(ColorC, PointC);
		ColoredVertex(ColorB, PointB);
		ColoredVertex(ColorA, PointA);
		glEnd();
		
		// 面3
		glBegin(GL_POLYGON);
		ColoredVertex(ColorA, PointA);
		ColoredVertex(ColorB, PointB);
		ColoredVertex(ColorF, PointF);
		ColoredVertex(ColorE, PointE);
		glEnd();
		
		// 面4
		glBegin(GL_POLYGON);
		ColoredVertex(ColorE, PointE);
		ColoredVertex(ColorH, PointH);
		ColoredVertex(ColorG, PointG);
		ColoredVertex(ColorF, PointF);
		glEnd();
		
		// 面5
		glBegin(GL_POLYGON);
		ColoredVertex(ColorF, PointF);
		ColoredVertex(ColorB, PointB);
		ColoredVertex(ColorC, PointC);
		ColoredVertex(ColorG, PointG);
		glEnd();
		
		// 面6
		glBegin(GL_POLYGON);
		ColoredVertex(ColorG, PointG);
		ColoredVertex(ColorH, PointH);
		ColoredVertex(ColorD, PointD);
		ColoredVertex(ColorC, PointC);
		glEnd();
		glEndList();
 
		glEnable(GL_DEPTH_TEST);
	}
	
	// 已经创建了显示列表，在每次绘制正四面体时将调用它
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(angle / 10, 1, 0.5, 0.0);
	glCallList(list);
	glPopMatrix();
	glutSwapBuffers();
}
 
void myIdle(void)
{
	++angle;
	if (angle >= 3600.0f)
	{
		angle = 0.0f;
	}
	myDisplay();
}
 
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

    const GLubyte* name = glGetString(GL_VENDOR); //返回负责当前OpenGL实现厂商的名字
    const GLubyte* biaoshifu = glGetString(GL_RENDERER); //返回一个渲染器标识符，通常是个硬件平台
    const GLubyte* OpenGLVersion =glGetString(GL_VERSION); //返回当前OpenGL实现的版本号
    const GLubyte* gluVersion= gluGetString(GLU_VERSION); //返回当前GLU工具库版本
    printf("OpenGL实现厂商的名字：%s\n", name);
    printf("渲染器标识符：%s\n", biaoshifu);
    printf("OOpenGL实现的版本号：%s\n",OpenGLVersion );
    printf("OGLU工具库版本：%s\n", gluVersion);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("First OpenGL Program");
	
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myIdle);     //空闲调用
 
	glutMainLoop();
 
	return 0;

}
