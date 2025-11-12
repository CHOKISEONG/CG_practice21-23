#pragma once

#include "header.h"

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec3 normal;
};

class Cube
{
public:
	// 실습 번호마다 맞게 생성을 위해
	Cube(int practiceNum);

	// 실습21 작은 큐브 생성을 위한 생성자
	Cube(float zPos, float rad);

	const std::vector<glm::vec3> getPos();

	void initBuffer();
	void updateVBO();
	void Draw(GLuint shaderProgram);

	void move(glm::vec3 v);
	void rotate(float dx = 0.0f, float dy = 0.0f);
private:
	GLuint VAO = 0, VBO = 0, EBO = 0;

	std::vector<Vertex> orgVertices;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> index;
	glm::vec3 bottomPos = glm::vec3(0.0f, 0.0f, 0.0f);

	float rotateAmount = 0.0f;

	bool isThisHavePhysics = false;
	bool isBaseOpened = false;
};