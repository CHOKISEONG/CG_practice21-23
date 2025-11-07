#define _CRT_SECURE_NO_WARNINGS 

#include "GLGL.h"
#include "Camera.h"
#include "Cube.h"

// 셰이더, 마우스 위치
GLGL* GLGL::my = nullptr;
GLuint shaderProgramID;
float crx, cry;
float pvx, pvy;

// 카메라
Camera* cam = nullptr;

// 그릴 도형들
Cube* test = nullptr;

GLvoid GLGL::ReShape(int w, int h)
{
	my->width = w;
	my->height = h;
	glViewport(0, 0, my->width, my->height);
}
GLvoid GLGL::PassiveMotion(int x, int y)
{
	float pvx = (2.0f * x - my->width) / my->width;
	float pvy = -(2.0f * y - my->height) / my->height;
}
GLvoid GLGL::Motion(int x, int y)
{
	float crx = (2.0f * x - my->width) / my->width;
	float cry = -(2.0f * y - my->height) / my->height;

	pvx = crx;
	pvy = cry;

	glutPostRedisplay();
}
GLvoid GLGL::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgramID);
	cam->settingCamera(shaderProgramID);

	test->Draw(shaderProgramID);

	glutSwapBuffers();
}

GLvoid GLGL::Idle()
{
	cam->update();
	glutPostRedisplay();
}


GLvoid GLGL::Keyboard(unsigned char key, int x, int y)
{
	
}


GLvoid GLGL::KeyboardUp(unsigned char key, int x, int y)
{

}


GLvoid GLGL::SpecialKeyboard(int key, int x, int y)
{

}


GLvoid GLGL::Mouse(int button, int state, int x, int y)
{

}


GLvoid TimerFunction(int value)
{
	std::cout << "실행 시간: " << glutGet(GLUT_ELAPSED_TIME) / 1000 << "." << (glutGet(GLUT_ELAPSED_TIME) % 1000) / 100 << "초\n";
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}


void GLGL::run(int argc, char** argv)
{
	my = this;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(my->width, my->height);
	glutCreateWindow("openGL practice 21");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	make_shaderProgram();
	cam = new Camera();
	

	test = new Cube();

	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CW);
	//glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(GLGL::Draw);
	glutReshapeFunc(GLGL::ReShape);
	glutMouseFunc(GLGL::Mouse);
	glutMotionFunc(GLGL::Motion);
	glutPassiveMotionFunc(GLGL::PassiveMotion);
	glutKeyboardFunc(GLGL::Keyboard);
	glutKeyboardUpFunc(GLGL::KeyboardUp);
	glutSpecialFunc(GLGL::SpecialKeyboard);
	glutIdleFunc(GLGL::Idle);
	glutTimerFunc(100, TimerFunction, 1);
	glutMainLoop();
}
void GLGL::make_shaderProgram()
{
	make_vertexShaders();
	make_fragmentShaders();

	shaderProgramID = glCreateProgram();

	glAttachShader(shaderProgramID, my->vertexShader);
	glAttachShader(shaderProgramID, my->fragmentShader);
	glLinkProgram(shaderProgramID);

	glDeleteShader(my->vertexShader);
	glDeleteShader(my->fragmentShader);

	glUseProgram(shaderProgramID);
}
void GLGL::make_vertexShaders()
{
	my->vertexSource = filetobuf("vertex.glsl");
	my->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(my->vertexShader, 1, (const GLchar**)&my->vertexSource, NULL);
	glCompileShader(my->vertexShader);

	// 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(my->vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(my->vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
	else
		std::cout << "vertex shader 컴파일 성공\n";
}
void GLGL::make_fragmentShaders()
{
	my->fragmentSource = filetobuf("fragment.glsl");
	my->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(my->fragmentShader, 1, (const GLchar**)&my->fragmentSource, NULL);
	glCompileShader(my->fragmentShader);

	// 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(my->fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(my->fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: frag_shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
	else
		std::cout << "fragment shader 컴파일 성공\n";
}
char* GLGL::filetobuf(const char* file)
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
