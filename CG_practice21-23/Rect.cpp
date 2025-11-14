#include "Rect.h"

Rect::Rect(const float rad, const glm::vec3 color)
{
	vertices =
	{
		{ {  rad, 0.0f,  rad }, color, {0.0f, 1.0f, 0.0f} },
		{ { -rad, 0.0f,  rad }, color, {0.0f, 1.0f, 0.0f} },
		{ { -rad, 0.0f, -rad }, color, {0.0f, 1.0f, 0.0f} },
		{ {  rad, 0.0f, -rad }, color, {0.0f, 1.0f, 0.0f} }
	};

	index =
	{
		0, 1, 3, 1, 2, 3,
	};

	initBuffer();
}

const std::vector<glm::vec3> Rect::getPos()
{
	std::vector<glm::vec3> pos;
	for (int i{}; i < vertices.size(); ++i)
	{
		pos.push_back(vertices[i].pos);
	}

	return pos;
}

void Rect::initBuffer()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	// 위치 (location = 0)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(0);

	// 색상 (location = 1)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	// 노멀벡터 (location = 2)
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);

	// index 연결하기
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), index.data(), GL_STATIC_DRAW);
}

void Rect::updateVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void Rect::Draw(GLuint shaderProgram)
{
	updateVBO();
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	glm::mat4 model = glm::mat4(1.0f);
	GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(index.size()), GL_UNSIGNED_INT, 0);
}