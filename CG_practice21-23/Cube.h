#pragma once

#include "header.h"

class Cube
{
public:
	enum class Type
	{
		cube,
		squarePyramid
	};

	// 실습 번호마다 맞게 생성을 위해
	Cube(int practiceNum);

	// rad 길이의 큐브 생성을 위한 생성자
	Cube(float rad);

	const std::vector<glm::vec3> getPos();

	void initBuffer();
	void updateVBO();
	void Draw(GLuint shaderProgram);

	void move(glm::vec3 v);
	void rotate(glm::vec3 v, float rad = 1.0f);
	void revolution(glm::vec3 v, float rad = 1.0f);

	void setType(Type _type) { type = _type; }
	Type getType() { return type; }
	void changePolygon();
private:
	GLuint VAO = 0, VBO = 0, EBO = 0;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> index;

	Type type;
};