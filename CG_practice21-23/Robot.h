#pragma once

#include "header.h"
#include "Cube.h"

class Robot
{
public:
	Robot();
	void initBuffer();
	void updateVBO();

	void goBackToOriginal(); // 처음 상태, 위치로

	void setMoving(const glm::vec3 v) { moveDir = v; }
	const float getSpeed() const { return moveSpeed; }

	void increaseMoveSpeed() { if (moveSpeed <= 0.005f) moveSpeed += 0.002f; }
	void decreaseMoveSpeed() { if (moveSpeed >= 0.002f) moveSpeed -= 0.001f; }
	void move();
	void move(glm::vec3 v);

	void update();
	void shakeArm();

	void Draw(GLuint shaderProgram);
private:
	GLuint VAO = 0, VBO = 0, EBO = 0;

	std::vector<Vertex> orgVertices;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> index;

	glm::vec3 moveDir = glm::vec3(0.0f,0.0f,0.0f);
	float moveSpeed = 0.003f;
	float shakeSpeed = 0.01f;
};