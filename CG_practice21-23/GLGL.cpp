#define _CRT_SECURE_NO_WARNINGS 

#include "GLGL.h"
#include "Camera.h"
#include "Cube.h"
#include "Character.h"
#include "Mountain.h"
#include "KeyState.h"
#include "Light.h"

GLGL* GLGL::my = nullptr;
GLuint shaderProgramID;

Camera* cam = nullptr;

Camera* minimapCam = nullptr;

Light* light = nullptr;

Mountain* mt = nullptr;
int mtX, mtY;
bool isMountainIsMaze = false;

Character* character = nullptr;
std::vector<Character*> shadows;
int shadowsTimer = 0;

glm::vec3 moveDir;

float timer = 30.0f;
char str[10];

void make_objects()
{
	cam = new Camera();
	minimapCam = new Camera();
	minimapCam->move(0.0f, 0.0f, -9.0f);
	minimapCam->setViewType(std::string("ortho"));

	mt = new Mountain(5.0f, mtX, mtY);
	isMountainIsMaze = false;

	light = new Light(glm::vec3(0.0f, 5.0f, 0.0f));
}

void FixedUpdate(int nothing)
{
	mt->update();
	if (character)
	{
		if (keyState.arrows[Arrows::Left])
		{
			if (keyState.arrows[Arrows::Up])
			{
				moveDir = glm::vec3(-0.01f, 0.0f, -0.01f);
				character->setAngle(-135.0f);
			}
			else if (keyState.arrows[Arrows::Down])
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
		else if (keyState.arrows[Arrows::Right])
		{
			if (keyState.arrows[Arrows::Up])
			{
				moveDir = glm::vec3(0.01f, 0.0f, -0.01f);
				character->setAngle(135.0f);
			}
			else if (keyState.arrows[Arrows::Down])
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
		else if (keyState.arrows[Arrows::Up])
		{
			moveDir = glm::vec3(0.0f, 0.0f, -0.015f);
			character->setAngle(180.0f);
		}
		else if (keyState.arrows[Arrows::Down])
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
		cam->update(character);

		
	}

	if (keyState.alphabets[Alphabets::y])
	{
		cam->rotateFromView(0.5f);
	}
	if (keyState.alphabets[Alphabets::Y])
	{
		cam->rotateFromView(-0.5f);
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
	glViewport(0, 0, my->width, my->height);

	cam->settingCamera(shaderProgramID);

	if (light)
	{
		light->applyLight(shaderProgramID);
	}
	
	if (character)
	{
		character->Draw(shaderProgramID);
		for (const auto& shadow : shadows)
		{
			shadow->Draw(shaderProgramID, Character::DrawType::STRIP);
		}
	}
	mt->draw(shaderProgramID);
	
	

	// 미니맵
	glViewport(my->width - 600, my->height - 400, 600, 400);
	minimapCam->settingCamera(shaderProgramID);

	if (light)
	{
		light->applyLight(shaderProgramID);
	}

	if (character)
	{
		character->Draw(shaderProgramID);
	}
	mt->draw(shaderProgramID);

	glutSwapBuffers();
}
GLvoid GLGL::Keyboard(unsigned char key, int x, int y)
{
	keyState.keyDown(key);
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
		light->dontDrawBox();
		light->teleport(glm::vec3(0.0f, -5.0f, 0.0f));
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
	case'c':
		// 모든 값 초기화
		make_objects();
		delete character;
		character = nullptr;
		shadows.clear();
		break;
	case'q':
		exit(0);
		break;
	default:
		break;
	}
}
GLvoid GLGL::KeyboardUp(unsigned char key, int x, int y)
{
	// 걍 다 초기화하게 함
	keyState.keyClear();
}
GLvoid GLGL::SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		keyState.arrowDown(Arrows::Up);
		break;
	case GLUT_KEY_DOWN:
		keyState.arrowDown(Arrows::Down);
		break;
	case GLUT_KEY_LEFT:
		keyState.arrowDown(Arrows::Left);
		break;
	case GLUT_KEY_RIGHT:
		keyState.arrowDown(Arrows::Right);
		break;
	default:
		break;
	}
}
GLvoid GLGL::SpecialKeyboardUp(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		keyState.arrowUp(Arrows::Up);
		break;
	case GLUT_KEY_DOWN:
		keyState.arrowUp(Arrows::Down);
		break;
	case GLUT_KEY_LEFT:
		keyState.arrowUp(Arrows::Left);
		break;
	case GLUT_KEY_RIGHT:
		keyState.arrowUp(Arrows::Right);
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
void makeShadows(int nothing)
{
	if (character)
	{
		if (!character->isOnGround())
		{
			shadows.push_back(new Character(*character));
			if (shadows.size() > 20)
			{
				shadows.erase(shadows.begin());
			}

			for (auto& shadow : shadows)
			{
				shadow->setAngle(shadow->getAngle() + 0.1f);
			}
		}
		else
		{
			if (shadows.size() > 0)
			{
				shadows.erase(shadows.begin());
			}
			shadowsTimer = 30;
		}

		shadowsTimer += 10;
	}

	glutTimerFunc(shadowsTimer, makeShadows, NULL);
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
		"\n j : 점프하기 " <<
		"\n c : 모든 값 초기화 " <<
		"\n q : 프로그램 종료";
	my = this;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(my->width, my->height);
	glutCreateWindow("homework");

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
	glutKeyboardUpFunc(GLGL::KeyboardUp);
	glutSpecialFunc(GLGL::SpecialKeyboard);
	glutSpecialUpFunc(GLGL::SpecialKeyboardUp);
	glutTimerFunc(10, FixedUpdate, NULL);
	glutTimerFunc(100, makeShadows, NULL);
	
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
