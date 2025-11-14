#pragma once

#include "header.h"

class Cube
{
public:
	// rad 길이의 큐브 생성을 위한 생성자
	Cube(float rad, glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f));

	const std::vector<glm::vec3> getPos();

	void initBuffer();
	void updateVBO();
	void Draw(GLuint shaderProgram);

	void move(glm::vec3 v);
private:
	GLuint VAO = 0, VBO = 0, EBO = 0;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> index;
};