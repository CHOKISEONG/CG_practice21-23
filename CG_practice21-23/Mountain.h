#pragma once

#include "Cube.h"
#include "Rect.h"
#include "header.h"

class Mountain
{
public:
	Mountain(float length = 5.0f, int _row = 5, int _col = 5);

	void update();
	void draw(GLuint shaderProgram);

	void stop() { isTreeMove = false; }
	void resume() { isTreeMove = true; }
	void changeSpeed(float amount);

	void changeToMaze();
private:
	Rect* base;
	std::vector<Cube*> trees;
	int row, col;

	bool isTreeMove = true;
	bool drawBase = false;
};