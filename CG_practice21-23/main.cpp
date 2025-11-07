#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/glm/glm.hpp>
#include <GL/glm/ext.hpp>
#include <GL/glm/gtc/matrix_transform.hpp>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Idle();
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid KeyboardUp(unsigned char key, int x, int y);
GLvoid SpecialKeyboard(int key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid PassiveMotion(int x, int y);
GLvoid Motion(int x, int y);
GLvoid TimerFunction(int value);

void main(int argc, char** argv)
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("practice 21");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";


	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(SpecialKeyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutPassiveMotionFunc(PassiveMotion);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}
GLvoid drawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// 그리기 부분 구현: 그리기 관련 부분이 여기에포함된다.
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
GLvoid Idle()
{
	glutPostRedisplay();
}
GLvoid Keyboard(unsigned char key, int x, int y)
{

}
GLvoid KeyboardUp(unsigned char key, int x, int y)
{

}
GLvoid SpecialKeyboard(int key, int x, int y)
{

}
GLvoid Mouse(int button, int state, int x, int y)
{

}
GLvoid PassiveMotion(int x, int y)
{

}
GLvoid Motion(int x, int y)
{

}
GLvoid TimerFunction(int value)
{
	std::cout << "elapsed_time: " << glutGet(GLUT_ELAPSED_TIME) << "\n";
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}