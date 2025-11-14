#pragma once

#include "header.h"

class Cube
{
public:
	Cube(float width, float height, glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f));

	const std::vector<glm::vec3> getPos();

	void initBuffer();
	void updateVBO();

	void updateHeight();
	void changeHeight(const float amount);
	void Draw(GLuint shaderProgram);

	void move(glm::vec3 v);
private:
	GLuint VAO = 0, VBO = 0, EBO = 0;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> index;

	float height = 0.0f;
	float maxHeight = urd(gen) * 3.0f;
};