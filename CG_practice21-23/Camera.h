#pragma once
#pragma once

#include "header.h"

class Camera
{
private:
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 5.0f);		// 위치
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);	// 바라보는 방향
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);			// 업벡터

	float fovy = 45.0f;		// 뷰잉 각도
	float width = 1920.0f;	// 폭
	float height = 1080.0f;	// 높이
	float zNear = 0.1f;		// 가까운 클리핑 평면까지의 거리
	float zFar = 100.0f;	// 먼	 클리핑 평면까지의 거리

	bool isRotating = false;
	bool isRotateSelf = false;
	float rotateSpeed = 0.5f;
public:
	void settingCamera(GLuint shaderProgram);

	void update();
	void changeWidthHeight(float w, float h) { width = w, height = h; }
	void move(float x, float y, float z = 0.0f)
	{ 
		pos += glm::vec3(x, y, z);
		direction += glm::vec3(x, y, z);
	}

	// rotateX가 true면 x축회전, false면 y축회전으로 함
	void rotate(float theta, bool rotateX);
	void rotateFromView(float theta, bool rotateX);
	void rotateStart(float speed) { isRotating = true; isRotateSelf = false; rotateSpeed = speed; }
	void rotateStartY(float speed) { isRotating = true; isRotateSelf = true; rotateSpeed = speed; }
	void rotateStop() { isRotating = false; rotateSpeed = 0.0f; }
};