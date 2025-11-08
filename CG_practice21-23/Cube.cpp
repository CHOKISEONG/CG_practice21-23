#include "Cube.h"

Cube::Cube(int practiceNum)
{
	if (practiceNum == 21)
	{
		float length = 1.0f;

		// 정사각형 테스트
		vertices =
		{
			{ {  length,  length, length }, {1.0f, 0.0f, 0.0f} },
			{ {  length, -length, length }, {0.0f, 1.0f, 0.0f} },
			{ { -length, -length, length }, {0.0f, 0.0f, 1.0f} },
			{ { -length,  length, length }, {1.0f, 1.0f, 0.0f} },
			{ {  length,  length, -length }, {1.0f, 1.0f, 1.0f} },
			{ {  length, -length, -length }, {1.0f, 1.0f, 1.0f} },
			{ { -length, -length, -length }, {1.0f, 1.0f, 1.0f} },
			{ { -length,  length, -length }, {1.0f, 1.0f, 1.0f} },
		};
		index =
		{

			// 오른쪽면
			0, 1, 5, 0, 5, 4,
			// 왼쪽면
			3, 6, 2, 3, 7, 6,
			// 윗면
			0, 7, 3, 0, 4, 7,
			// 아랫면
			1, 2, 6, 1, 6, 5,
			// 뒷면
			4, 5, 6, 4, 6, 7,
		};
	}

	initBuffer();
}

void Cube::initBuffer() 
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),vertices.data(),GL_STATIC_DRAW);

	// 위치 (location = 0)
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(0);

	// 색상 (location = 1)
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	// index 연결하기
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), index.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void Cube::Draw(GLuint shaderProgram) {
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(index.size()), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	
}