#pragma once

#include "header.h"

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 color;
};

class Cube
{
public:
	Cube();
	void initBuffer();

	void Draw(GLuint shaderProgram);
private:
	GLuint VAO = 0, VBO = 0, EBO = 0;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> index;
};