#define _CRT_SECURE_NO_WARNINGS 

#include "GLGL.h"
#include "Camera.h"
#include "Cube.h"
#include "Ball.h"
#include "Robot.h"

// 셰이더, 마우스 위치
GLGL* GLGL::my = nullptr;
GLuint shaderProgramID;
float crx, cry;
float pvx, pvy;

// 카메라
Camera* cam = nullptr;

// 그릴 도형들
Cube* cube = nullptr;
std::vector<Cube*> smallCube;
Robot* robot;

void make_objects()
{
	cam = new Camera();

	cube = new Cube(22);

	robot = new Robot();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> randPos(-0.8f, 0.8f);

	smallCube.push_back(new Cube(glm::vec2(randPos(gen), randPos(gen)), 0.11f));
	smallCube.push_back(new Cube(glm::vec2(randPos(gen), randPos(gen)), 0.13f));
	smallCube.push_back(new Cube(glm::vec2(randPos(gen), randPos(gen)), 0.15f));
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
//	cube->rotate(dx, dy);
//
//	if (!cube->getBaseOpened())
//	{
//		for (auto& sc : smallCube)
//			sc->rotate(dx, dy);
//	}
//	
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
	for (const auto& sc : smallCube)
		sc->Draw(shaderProgramID);
	robot->Draw(shaderProgramID);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
}
GLvoid GLGL::Idle()
{
	cube->baseOpenAnimation();
	for (auto& sc : smallCube)
		sc->handlePhysics(cube);
	robot->update(smallCube);
	cam->update();

	glutPostRedisplay();
}
GLvoid GLGL::Keyboard(unsigned char key, int x, int y)
{
	static float isOpen = false;
	static double ballSize = 0.0;
	switch (key)
	{
	case'o':case'O':
		cube->CubeOpen();
		break;
	// 상하좌우이동
	case'w':
		robot->setMoving(glm::vec3(0.0f, 0.0f, -robot->getSpeed()));
		break;
	case'a':
		robot->setMoving(glm::vec3(-robot->getSpeed(), 0.0f, 0.0f));
		break;
	case's':
		robot->setMoving(glm::vec3(0.0f, 0.0f, robot->getSpeed()));
		break;
	case'd':
		robot->setMoving(glm::vec3(robot->getSpeed(), 0.0f, 0.0f));
		break;
	// 속도 증감
	case'+':
		robot->increaseMoveSpeed();
		std::cout << "속도: " << robot->getSpeed() << "\n";
		break;
	case'-':
		robot->decreaseMoveSpeed();
		std::cout << "속도: " << robot->getSpeed() << "\n";
		break;
	// 점프
	case'j':
		if (robot->isOnGround())
		{
			robot->jumpStart();
		}
		break;
	// 초기화
	case'i':
		robot->goBackToOriginal();
		break;
	case 'z':
		cam->move(0.0f, 0.0f, 1.0f);
		break;
	case 'Z':
		cam->move(0.0f, 0.0f, -1.0f);
		break;
	case'x':
		cam->move(1.0f, 0.0f, 0.0f);
		break;
	case'X':
		cam->move(-1.0f, 0.0f, 0.0f);
		break;
	case'y':
		cam->rotateStart(0.1f);
		break;
	case'Y':
		cam->rotateStart(-0.1f);
		break;
	case'.':
		cam->rotateStop();
	default:
		break;
	}
}
void GLGL::KeyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'w':
		robot->setMoving(glm::vec3(0.0f, 0.0f, 0.0f));
		break;
	case'a':
		robot->setMoving(glm::vec3(0.0f, 0.0f, 0.0f));
		break;
	case's':
		robot->setMoving(glm::vec3(0.0f, 0.0f, 0.0f));
		break;
	case'd':
		robot->setMoving(glm::vec3(0.0f, 0.0f, 0.0f));
		break;
	}
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
	
	make_objects();

	glutDisplayFunc(GLGL::Draw);
	glutReshapeFunc(GLGL::ReShape);
	//glutMouseFunc(GLGL::Mouse);
	//glutMotionFunc(GLGL::Motion);
	//glutPassiveMotionFunc(GLGL::PassiveMotion);
	glutKeyboardFunc(GLGL::Keyboard);
	glutKeyboardUpFunc(GLGL::KeyboardUp);
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
