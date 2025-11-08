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
	// 실습 번호마다 맞게 생성을 위해
	Cube(int practiceNum, int type = 0);
	void initBuffer();
	void updateVBO();
	void Draw(GLuint shaderProgram);

	void rotate(float dx = 0.0f, float dy = 0.0f);
private:
	GLuint VAO = 0, VBO = 0, EBO = 0;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> index;
	float midPoint[3] = { 0.0f,0.0f };

	float rotateAmount = 0.0f;
};