#pragma once
#pragma once

#include "header.h"
#include "Character.h"

class Camera
{
private:
	glm::vec3 pos = glm::vec3(0.0f, 10.0f, 10.0f);		// 위치
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);	// 바라보는 방향
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);			// 업벡터

	float fovy = 45.0f;		// 뷰잉 각도
	float width = 1920.0f;	// 폭
	float height = 1080.0f;	// 높이
	float zNear = 0.1f;		// 가까운 클리핑 평면까지의 거리
	float zFar = 100.0f;	// 먼	 클리핑 평면까지의 거리

	std::string viewType{ "perspective" };

	std::string camType{ "none" };
public:
	void settingCamera(GLuint shaderProgram);

	void update(Character* character);

	const glm::vec3 getPos() const { return pos; }

	void setViewType(std::string str) { viewType = str; }
	const std::string getViewType() const { return viewType; }

	void changeWidthHeight(float w, float h) { width = w, height = h; }
	void move(float x, float y, float z = 0.0f) 
	{ 
		pos.x += x; pos.y += y; pos.z += z; 
	}

	// rotateX가 true면 x축회전, false면 y축회전으로 함
	void rotate(float theta, glm::vec3 axis = glm::vec3(0.0f,1.0f,0.0f));
	void rotateFromView(float theta, glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f));

	void toFirstPerson() { camType = std::string("firstPerson"); };
	void toThirdPerson() { camType = std::string("thirdPerson"); };
};