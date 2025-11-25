#pragma once

#include "header.h"

struct BG
{
	glm::vec3 pos;
	glm::vec2 texture;
};

class Background
{
public:
	Background(const char* filename);

	void Draw(GLuint shaderProgram);
private:
	GLuint VAO = 0, VBO = 0, EBO = 0;

	unsigned int texture;
	BITMAPINFO* bmp;
	GLsizei width, height, numberOfChannel;

	std::vector<BG> vertices;
	std::vector<unsigned int> index;
};