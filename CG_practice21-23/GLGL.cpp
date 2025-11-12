#define _CRT_SECURE_NO_WARNINGS 

#include "GLGL.h"
#include "Camera.h"
#include "Cube.h"
#include "Ball.h"

// 셰이더, 마우스 위치
GLGL* GLGL::my = nullptr;
GLuint shaderProgramID;

// 카메라
Camera* cam = nullptr;

// 그릴 도형들
Cube* cube = nullptr;

void make_objects()
{
	cam = new Camera();

	cube = new Cube(25);
}

GLvoid GLGL::ReShape(int w, int h)
{
	my->width = w;
	my->height = h;
	glViewport(0, 0, my->width, my->height);
}
//GLvoid GLGL::PassiveMotion(int x, int y)
//{
//	crx = (2.0f * x - my->width) / my->width;
//	cry = -(2.0f * y - my->height) / my->height;
//
//	float dx = crx - pvx;
//	float dy = cry - pvy;
//
//	pvx = crx;
//	pvy = cry;
//}
//GLvoid GLGL::Motion(int x, int y)
//{
//	crx = (2.0f * x - my->width) / my->width;
//	cry = -(2.0f * y - my->height) / my->height;
//
//	pvx = crx;
//	pvy = cry;
//
//	glutPostRedisplay();
//}
GLvoid GLGL::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramID);

	cam->settingCamera(shaderProgramID);

	cube->Draw(shaderProgramID);

	// 조명의 위치
	unsigned int lightPosLocation = glGetUniformLocation(shaderProgramID, "lightPos");
	glUniform3f(lightPosLocation, 0.0, 0.0, 5.0);

	static float tmp = 0.0f;
	tmp += 0.001f;

	// 조명의 색깔 (흰색으로 함)
	int lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor");
	glUniform3f(lightColorLocation, tmp, tmp, tmp);
	

	// 카메라 위치
	unsigned int viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos");
	glm::vec3 camPos = cam->getPos();
	glUniform3f(viewPosLocation, camPos.x, camPos.y, camPos.z);


	

	glutSwapBuffers();
}
GLvoid GLGL::Idle()
{
	cam->update();

	glutPostRedisplay();
}
GLvoid GLGL::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'n':
		// 육면체 / 사각뿔 그리기
		break;
	case'm':
		// 조명 켜기/끄기
		break;
	case'y':
		// 객체를 y축에 대하여 회전(제자리에서 자전)
		break;
	case'r':
		// 조명을 객체의 중심 y축에 대하여 양/음 뱡향으로 공전
		break;
	case'z':
		// 조명을 객체에 가깝게 이동
		break;
	case'Z':
		// 조명을 객체에 멀게 이동
		break;
	case'q':
		exit(0);
		break;
	default:
		break;
	}
}
GLvoid GLGL::SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	default:
		break;
	}

	glutPostRedisplay();
}
//GLvoid GLGL::Mouse(int button, int state, int x, int y)
//{
//	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
//	{
//		std::cout << "바닥이 열린다.\n";
//
//		cube->baseOpen();
//	}
//}

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
	
	make_objects();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(GLGL::Draw);
	glutReshapeFunc(GLGL::ReShape);
	//glutMouseFunc(GLGL::Mouse);
	//glutMotionFunc(GLGL::Motion);
	//glutPassiveMotionFunc(GLGL::PassiveMotion);
	glutKeyboardFunc(GLGL::Keyboard);
	//glutSpecialFunc(GLGL::SpecialKeyboard);
	glutIdleFunc(GLGL::Idle);
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
