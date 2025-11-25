#pragma once

#include "header.h"

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 texture;
};

class Cube
{
public:
	enum class Type
	{
		cube,
		squarePyramid
	};

	// 실습 번호마다 맞게 생성을 위해
	Cube(int practiceNum, const char* str);

	const std::vector<glm::vec3> getPos();

	void initBuffer();
	void initTexture(const char* str);

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

	unsigned int texture;
	BITMAPINFO* bmp;
	GLsizei width, height, numberOfChannel;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> index;

	Type type;
};