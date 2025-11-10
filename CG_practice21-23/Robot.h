#pragma once

#include "header.h"
#include "Cube.h"

class Robot
{
public:
	Robot();
	void initBuffer();
	void updateVBO();

	void move(glm::vec3 v);

	void Draw(GLuint shaderProgram);
private:
	GLuint VAO = 0, VBO = 0, EBO = 0;

	std::vector<Vertex> orgVertices;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> index;
};