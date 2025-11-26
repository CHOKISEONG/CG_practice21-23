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
		squarePyramid,
		square
	};

	enum class Face
	{
		Front,
		Back,
		Right,
		Left,
		Top,
		Bottom,
		All
	};

	// 코딩 시험 준비용
	Cube(float length, const char* str);

	const std::vector<glm::vec3> getPos();

	void initBuffer();
	void initTexture(const char* str);

	void updateVBO();
	void Draw(GLuint shaderProgram);

	void move(glm::vec3 v) 
	{
		position += v;
	}
	void rotate(glm::vec3 v, float rad = 1.0f);
	void rotateWithPivot(glm::vec3 v, float rad, Face face, glm::vec3 pivot = glm::vec3(0.0f,0.0f,0.0f));

	Type getType() { return type; }
	void changePolygon(Type type);
private:
	GLuint VAO = 0, VBO = 0, EBO = 0;

	unsigned int texture;
	BITMAPINFO* bmp;
	GLsizei width, height, numberOfChannel;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> index;

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

	Type type;
};