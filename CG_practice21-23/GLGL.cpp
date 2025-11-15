#define _CRT_SECURE_NO_WARNINGS 

#include "GLGL.h"
#include "Camera.h"
#include "Cube.h"
#include "Character.h"
#include "Rect.h"
#include "Mountain.h"
#include "Light.h"

GLGL* GLGL::my = nullptr;
GLuint shaderProgramID;

Camera* cam = nullptr;

Camera* minimapCam = nullptr;

Light* light = nullptr; 
Mountain* mt = nullptr; 
bool isMountainIsMaze = false;

Character* character = nullptr;

// 상하좌우 키 감지용
// 0-상
// 1-하
// 2-좌
// 3-우
bool move_state[4];
glm::vec3 moveDir;

int mtX, mtY;
void make_objects()
{
	cam = new Camera();
	minimapCam = new Camera();
	minimapCam->move(0.0f, 0.0f, -9.0f);

	mt = new Mountain(5.0f, mtX, mtY);

	light = new Light(glm::vec3(0.0f, 5.0f, 0.0f));
}

void FixedUpdate(int nothing)
{
	mt->update();
	if (character != nullptr)
	{
		if (move_state[2])
		{
			if (move_state[0])
			{
				moveDir = glm::vec3(-0.01f, 0.0f, -0.01f);
				character->setAngle(-135.0f);
			}
			else if (move_state[1])
			{
				moveDir = glm::vec3(-0.01f, 0.0f, 0.01f);
				character->setAngle(-45.0f);
			}
			else
			{
				moveDir = glm::vec3(-0.015f, 0.0f, 0.0f);
				character->setAngle(-90.0f);
			}
		}
		else if (move_state[3])
		{
			if (move_state[0])
			{
				moveDir = glm::vec3(0.01f, 0.0f, -0.01f);
				character->setAngle(135.0f);
			}
			else if (move_state[1])
			{
				moveDir = glm::vec3(0.01f, 0.0f, 0.01f);
				character->setAngle(45.0f);
			}
			else
			{
				moveDir = glm::vec3(0.015f, 0.0f, 0.0f);
				character->setAngle(90.0f);
			}
		}
		else if (move_state[0])
		{
			moveDir = glm::vec3(0.0f, 0.0f, -0.015f);
			character->setAngle(180.0f);
		}
		else if (move_state[1])
		{
			moveDir = glm::vec3(0.0f, 0.0f, 0.015f);
			character->setAngle(0.0f);
		}
		else
		{
			moveDir = glm::vec3(0.0f, 0.0f, 0.0f);
		}
		character->setMoving(moveDir);
		character->update(mt->getTrees());
		light->teleport(character->getPos() + glm::vec3(0.0f, -0.3f, 0.0f));
	}
	if (character != nullptr)
	{
		cam->update(character);
	}
	
	glutTimerFunc(10, FixedUpdate, NULL);
}
GLvoid GLGL::Draw()
{
	glutPostRedisplay();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgramID);

	// 원래 카메라
	glViewport(0, 0, my->width - 400, my->height);
	cam->settingCamera(shaderProgramID);

	light->applyLight(shaderProgramID);
	mt->draw(shaderProgramID);
	if (character != nullptr)
	{
		character->Draw(shaderProgramID);
	}
	
	// 미니맵
	glViewport(my->width - 400, my->height - 300, 400, 300);
	minimapCam->settingCamera(shaderProgramID);

	light->applyLight(shaderProgramID);
	mt->draw(shaderProgramID);
	if (character != nullptr)
	{
		character->Draw(shaderProgramID);
	}

	glutSwapBuffers();
}
GLvoid GLGL::Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'o':
		// 직각 투영
		cam->setViewType(std::string("ortho"));
		break;
	case'p':
		// 원근 투영
		cam->setViewType(std::string("perspective"));
		break;
	case'z':
		// (원근 투영때만) z축 이동
		if (cam->getViewType() == std::string("perspective"))
		{
			cam->move(0.0f, 0.0f, -0.5f);
		}
		break;
	case'Z':
		// (원근 투영때만) z축 이동
		if (cam->getViewType() == std::string("perspective"))
		{
			cam->move(0.0f, 0.0f, 0.5f);
		}
		break;
	case'm':
		// 육면체들의 위/아래로 움직인다.
		mt->resume();
		break;
	case'M':
		// 육면체들이 움직이는거 멈춤
		mt->stop();
		break;
	case'y':
		// 카메라가 y축 기준 양의 방향 회전
		cam->rotateFromView(0.5f);
		break;
	case'Y':
		// 카메라가 y축 기준 음의 방향 회전
		cam->rotateFromView(-0.5f);
		break;
	case'r':
		// 미로 제작
		if (!isMountainIsMaze)
		{
			mt->changeToMaze();
			isMountainIsMaze = true;
		}
		break;
	case'v':
		// 육면체들 움직임이 멈추고 낮은 높이로 변함
		mt->unityTreeSize();
		break;
	case's':
		// 미로에서 객체가 나타남
		character = new Character();
		light->teleport(glm::vec3(0.0f, 0.5f, 5.0f));
		break;
	case'+':
		// 육면체 위/아래 움직이는 속도 증가
		mt->changeSpeed(0.01f);
		break;
	case'-':
		// 육면체 위/아래 움직이는 속도 감소
		mt->changeSpeed(-0.01f);
		break;
	case'1':
		// 카메라 1인칭
		cam->toFirstPerson();
		break;
	case'3':
		// 카메라 3인칭
		cam->toThirdPerson();
		break;
	case'j':
		character->jumpStart();
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
	// 객체 이동
	switch (key)
	{
	case GLUT_KEY_UP:
		move_state[0] = true;
		break;
	case GLUT_KEY_DOWN:
		move_state[1] = true;
		break;
	case GLUT_KEY_LEFT:
		move_state[2] = true;
		break;
	case GLUT_KEY_RIGHT:
		move_state[3] = true;
		break;
	default:
		break;
	}
}
void GLGL::SpecialKeyboardUp(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		move_state[0] = false;
		break;
	case GLUT_KEY_DOWN:
		move_state[1] = false;
		break;
	case GLUT_KEY_LEFT:
		move_state[2] = false;
		break;
	case GLUT_KEY_RIGHT:
		move_state[3] = false;
		break;
	default:
		break;
	}
}

GLvoid GLGL::ReShape(int w, int h)
{
	my->width = w;
	my->height = h;
	glViewport(0, 0, my->width, my->height);
}
void GLGL::run(int argc, char** argv)
{
	std::cout << "가로와 세로의 개수를 입력해주세요.\n";
	std::cout << "제한 : 5 ~ 25\n";
	std::cin >> mtX >> mtY;

	std::cout << " o/p: 투영을 선택한다 (직각 투영 / 원근 투영) " <<
		"\n z / Z: 원근 투영 시 z축으로 이동할 수있게한다. " <<
		"\n m / M : 육면체들이 위 아래로움직인다 / 멈춘다. " <<
		"\n 움직이는속도와높이의최대값은다양하다.최대 / 최소높이는본인이정한다. " <<
		"\n y / Y : 카메라가 바닥의 y축을 기준으로 양 / 음방향으로회전한다. " <<
		"\n r : 미로를 제작한다. " <<
		"\n 가로와세로를나눈등분에서미로가만들어지면그해당칸의육면체는사라지고미로가생긴다. " <<
		"\n v : 육면체들 움직임이 멈추고낮은높이로변한다. " <<
		"\n 미로에서움직이는객체확인할수있다.다시누르면움직임다시시작된다. " <<
		"\n s : 미로에서 객체가 나타난다. " <<
		"\n → / ← / ↑ / ↓ : 객체를 미로에서 앞 / 뒤 / 좌 / 우 이동. " <<
		"\n + / -: 육면체 이동하는 속도 증가 / 감소 " <<
		"\n 1 / 3 : 카메라 시점 1인칭 / 3인칭 변환 " <<
		"\n 1인칭시점(객체시점) / 3인칭시점(쿼터뷰시점) " <<
		"\n c : 모든 값 초기화 " <<
		"\n q : 프로그램 종료";
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

	//glutFullScreen();

	make_shaderProgram();
	
	make_objects();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(GLGL::Draw);
	glutReshapeFunc(GLGL::ReShape);
	glutKeyboardFunc(GLGL::Keyboard);
	glutSpecialFunc(GLGL::SpecialKeyboard);
	glutSpecialUpFunc(GLGL::SpecialKeyboardUp);
	glutTimerFunc(10, FixedUpdate, NULL);
	
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
