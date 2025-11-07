#define _CRT_SECURE_NO_WARNINGS 

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/glm/glm.hpp>
#include <GL/glm/ext.hpp>
#include <GL/glm/gtc/matrix_transform.hpp>

void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();
char* filetobuf(const char* file);
void initBuffer();

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

GLint windowWidth, windowHeight;
GLuint shaderProgramID;
GLchar* vertexSource, * fragmentSource;
GLuint vertexShader, fragmentShader;

const GLfloat triShape[3][3]
{
	{ -0.5f, -0.5f, 0.0f },
	{ 0.5f, -0.5f, 0.0f },
	{ 0.0f, 0.5f, 0.0f }
};
const GLfloat colors[3][3]
{
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f }
};

GLuint vao, vbo[2];

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("practice 21");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	make_vertexShaders();
	make_fragmentShaders();
	make_shaderProgram();

	initBuffer();

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
	glUseProgram(shaderProgramID);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	glViewport(0, 0, windowWidth, windowHeight);
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

void make_vertexShaders()
{
	vertexSource = filetobuf("vertex.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	glCompileShader(vertexShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if(!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}
void make_fragmentShaders()
{
	fragmentSource = filetobuf("fragment.glsl");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	glCompileShader(fragmentShader);
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}
void make_shaderProgram()
{
	make_vertexShaders();
	make_fragmentShaders();

	shaderProgramID = glCreateProgram();

	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgramID);
}
char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb");
	if (!fptr)
		return NULL;
	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0;
	return buf;
}

void initBuffer()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(2, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}
