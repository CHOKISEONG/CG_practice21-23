#pragma once

#include "header.h"

class Rect
{
public:
	// 기본은 한 변의 길이가 2.0f인 빨간색 바닥
	Rect(const float rad = 1.0f, const glm::vec3 color = glm::vec3(1.0f,0.0f,0.0f));

	const std::vector<glm::vec3> getPos();

	void initBuffer();
	void updateVBO();
	void Draw(GLuint shaderProgram);
private:
	GLuint VAO = 0, VBO = 0, EBO = 0;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> index;
};