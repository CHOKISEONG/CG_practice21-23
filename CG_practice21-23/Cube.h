#pragma once

#include "header.h"

class Cube
{
public:
	Cube();
	void initBuffer();

	void Draw(GLuint shaderProgram);
private:
	GLuint VAO, VBO_pos, EBO;

	std::vector<glm::vec3> vPositionList;
	std::vector<unsigned int> index;
};