#pragma once

#include "Cube.h"
#include "Rect.h"
#include "header.h"

class Mountain
{
public:
	Mountain(float length = 5.0f, int row = 5, int col = 5);

	void draw(GLuint shaderProgram);
private:
	Rect* base;
	std::vector<Cube*> trees;
};