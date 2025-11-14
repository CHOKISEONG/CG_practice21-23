#pragma once

#include "header.h"
#include "Cube.h"

class Character
{
public:
	Character(glm::vec3 v = glm::vec3(0.0f, 0.0f, 5.0f));
	void initBuffer();
	void updateVBO();

	void goBackToOriginal(); // 처음 상태, 위치로

	bool isOnGround() { return onGround; }
	void setMoving(const glm::vec3 v) { moveDir = v; }
	void setAngle(float theta) { angle = theta; }
	const float getSpeed() const { return moveSpeed; }

	void increaseMoveSpeed() { if (moveSpeed <= 0.005f) moveSpeed += 0.002f; }
	void decreaseMoveSpeed() { if (moveSpeed >= 0.002f) moveSpeed -= 0.001f; }
	void move(glm::vec3 v);

	void update(const std::vector<Cube*>& cube);
	bool checkCollide(const std::vector<Cube*>& cube);
	void shakeArm();
	void shakeLeg(bool isOpposite = false);

	// move함수는 인자값만큼 이동, moving함수는 이동키 처리하는 거 
	void moving();
	void jump();
	void jumpStart() { onGround = false; }

	void Draw(GLuint shaderProgram);
private:
	GLuint VAO = 0, VBO = 0, EBO = 0;

	std::vector<Vertex> orgVertices;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> index;

	// 중심 좌표
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);

	// 이동할 방향 (벡터 아니고 속도 포함임)
	glm::vec3 moveDir = glm::vec3(0.0f, 0.0f, 0.0f);
	
	// 이동할 방향으로 그릴 때 회전시킬 용도
	float angle = 0.0f;

	// 이동 속도
	float moveSpeed = 0.003f;

	// 팔 흔드는 속도
	float shakeSpeed = 0.01f;

	// 점프할 때 다리 움직이는 속도
	float legSpeed = 0.05f;

	// 땅에 있는지 확인 용 ( 현재 땅은 y축으로 -1.0f 임 )
	bool onGround = true;

	// 점프하기 위한 중력과 점프속도
	const float gravity = -0.0005f;
	float jumpSpeed = 0.03f;
	float jumpAmount = 0.0f;
};