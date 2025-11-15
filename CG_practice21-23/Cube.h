#pragma once

#include "header.h"

class Cube
{
public:
	Cube(float width, float height, glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f));

	const std::vector<glm::vec3> getPos();

	void initBuffer();
	void updateVBO();

	void move(glm::vec3 v);
	void teleport(glm::vec3 v);
	void Draw(GLuint shaderProgram);

	void updateHeight();
	void changeHeight();
	void changeHeight(float _height) { height = _height; }
	void changeSpeed(float amount);
	const float getSpeed() const { return speed; }
	const float getHeight() const { return height; }
	void changeColor(glm::vec3 color);

	// p가 큐브 안에 있는지 검사
	bool checkCollide(glm::vec3 p);
	bool checkOnCube(glm::vec3 p);
private:
	GLuint VAO = 0, VBO = 0, EBO = 0;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> index;

	float minHeight = urd(gen) / 2;
	float maxHeight = urd(gen) * 3.0f;
	float height = minHeight;
	float speed = urd(gen) / 100;
};