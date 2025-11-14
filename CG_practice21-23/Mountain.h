#pragma once

#include "Cube.h"
#include "Rect.h"
#include "header.h"

class Mountain
{
public:
	Mountain(float length = 5.0f, int row = 5, int col = 5);

	void update();
	void draw(GLuint shaderProgram);

	void stop() { isTreeMove = false; }
	void resume() { isTreeMove = true; }
	void changeSpeed(float amount);

private:
	Rect* base;
	std::vector<Cube*> trees;

	bool isTreeMove = true;
	bool drawBase = false;
};