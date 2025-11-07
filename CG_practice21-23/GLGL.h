#pragma once

#include "header.h"

class GLGL
{
public:
	static GLGL* getInstance() { return my; }

	static void make_vertexShaders();
	static void make_fragmentShaders();
	static void make_shaderProgram();
	static char* filetobuf(const char* file);
	static void Draw();
	static void ReShape(int w, int h);
	static void Motion(int x, int y);
	static void PassiveMotion(int x, int y);
	static void Idle();
	static void Mouse(int button, int state, int x, int y);
	static void Keyboard(unsigned char key, int x, int y);
	static void KeyboardUp(unsigned char key, int x, int y);
	static void SpecialKeyboard(int key, int x, int y);
	

	void run(int argc, char** argv);

	int screenWidth() { return width; }
	int screenHeight() { return height; }
	void screenWResize(int width) { my->width = width; }
	void screenHResize(int height) { my->height = height; }


private:
	static GLGL* my;
	GLuint width = 1920, height = 1080;
	GLchar* vertexSource, * fragmentSource;
	GLuint vertexShader, fragmentShader;
};