#include "Cube.h"

Cube::Cube(int practiceNum, int type)
{
	if (practiceNum == 21)
	{
		// 공을 튀길 공간
		if (type == 0)
		{
			float length = 1.0f;

			// 정사각형 테스트
			vertices =
			{
				{ {  length,  length, length }, {1.0f, 0.0f, 0.0f} },
				{ {  length, -length, length }, {0.0f, 1.0f, 0.0f} },
				{ { -length, -length, length }, {0.0f, 0.0f, 1.0f} },
				{ { -length,  length, length }, {1.0f, 1.0f, 0.0f} },
				{ {  length,  length, -length }, {0.7f, 0.7f, 0.7f} },
				{ {  length, -length, -length }, {0.7f, 0.7f, 0.7f} },
				{ { -length, -length, -length }, {0.7f, 0.7f, 0.7f} },
				{ { -length,  length, -length }, {0.7f, 0.7f, 0.7f} },
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
		// 바닥에 닿아있는 육면체
		else if (type == 1)
		{

		}
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

void Cube::updateVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void Cube::Draw(GLuint shaderProgram) {
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(index.size()), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Cube::rotate(float dx, float dy)
{
	const float rad = (dx > 0) ? -1.0f : 1.0f;
	if (rotateAmount >= 60.0f && rad > 0.0f) return;
	if (rotateAmount <= -60.0f && rad < 0.0f) return;

	for (int i{}; i < vertices.size(); ++i)
	{
		glm::vec4 pos(vertices[i].pos.x, vertices[i].pos.y, vertices[i].pos.z, 1.0f);
		glm::mat4 rotMatrix = glm::mat4(1.0f);
		rotMatrix = glm::rotate(rotMatrix, glm::radians(rad), glm::vec3(0.0f, 0.0f, 1.0f));
		pos = rotMatrix * pos;
		vertices[i].pos.x = pos.x;
		vertices[i].pos.y = pos.y;
		vertices[i].pos.z = pos.z;
	}

	rotateAmount += rad;

	updateVBO();
}
