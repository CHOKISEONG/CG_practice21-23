#pragma once

#include "header.h"

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 color;
};

class Robot
{
public:
	Robot();


private:
	GLuint VAO = 0, VBO = 0, EBO = 0;

	std::vector<Vertex> orgVertices;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> index;
};