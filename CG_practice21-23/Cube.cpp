#include "Cube.h"
#include "Mountain.h"

Cube::Cube(float width, float height, glm::vec3 color)
{
	vertices =
	{
		// 앞,뒤
		{ {  width, 0.0f, height }, color, {0.0f, 1.0f, 0.0f} },
		{ {  width, 0.0f, height }, color, {0.0f, 1.0f, 0.0f} },
		{ { -width, 0.0f, height }, color, {0.0f, 1.0f, 0.0f} },
		{ { -width, 0.0f, height }, color, {0.0f, 1.0f, 0.0f} },
		{ {  width, 0.0f, -height }, color, {0.0f, 1.0f, 0.0f} },
		{ {  width, 0.0f, -height }, color, {0.0f, 1.0f, 0.0f} },
		{ { -width, 0.0f, -height }, color, {0.0f, 1.0f, 0.0f} },
		{ { -width, 0.0f, -height }, color, {0.0f, 1.0f, 0.0f} },

		// 좌,우
		{ {  width, 0.0f, height },  color, {0.0f, 1.0f, 0.0f} },
		{ {  width, 0.0f, height },  color, {0.0f, 1.0f, 0.0f} },
		{ { -width, 0.0f, height },  color, {0.0f, 1.0f, 0.0f} },
		{ { -width, 0.0f, height },  color, {0.0f, 1.0f, 0.0f} },
		{ {  width, 0.0f, -height }, color, {0.0f, 1.0f, 0.0f} },
		{ {  width, 0.0f, -height }, color, {0.0f, 1.0f, 0.0f} },
		{ { -width, 0.0f, -height }, color, {0.0f, 1.0f, 0.0f} },
		{ { -width, 0.0f, -height }, color, {0.0f, 1.0f, 0.0f} },

		// 상,하
		{ {  width, 0.0f, height },  color, {0.0f, 1.0f, 0.0f} },
		{ {  width, 0.0f, height },  color, {0.0f, 1.0f, 0.0f} },
		{ { -width, 0.0f, height },  color, {0.0f, 1.0f, 0.0f} },
		{ { -width, 0.0f, height },  color, {0.0f, 1.0f, 0.0f} },
		{ {  width, 0.0f, -height }, color, {0.0f, 1.0f, 0.0f} },
		{ {  width, 0.0f, -height }, color, {0.0f, 1.0f, 0.0f} },
		{ { -width, 0.0f, -height }, color, {0.0f, 1.0f, 0.0f} },
		{ { -width, 0.0f, -height }, color, {0.0f, 1.0f, 0.0f} }

	};

	index =
	{

		// 앞면
		0, 3, 1, 1, 3, 2,
		// 뒷면
		4, 5, 6, 4, 6, 7,

		// 왼쪽면
		11, 14, 10, 11, 15, 14,
		// 오른쪽면
		8, 9, 13, 8, 13, 12,

		// 윗면
		16, 23, 19, 16, 20, 23,
		// 아랫면
		17, 18, 22, 17, 22, 21

	};

	initBuffer();
}

const std::vector<glm::vec3> Cube::getPos()
{
	std::vector<glm::vec3> pos;
	for (int i{}; i < vertices.size(); ++i)
	{
		pos.push_back(vertices[i].pos);
	}
	
	return pos;
}

void Cube::initBuffer()
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

void Cube::updateVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void Cube::updateHeight()
{
	vertices[0].pos.y =  height;
	vertices[3].pos.y =  height;
	vertices[4].pos.y =  height;
	vertices[7].pos.y =  height;

	vertices[8].pos.y =  height;
	vertices[11].pos.y =  height;
	vertices[12].pos.y =  height;
	vertices[15].pos.y =  height;

	vertices[16].pos.y =  height;
	vertices[19].pos.y =  height;
	vertices[20].pos.y =  height;
	vertices[23].pos.y =  height;
}

void Cube::changeHeight()
{
	if (speed < 0.0f && height + speed < minHeight)
	{
		height = 0.0f;
		speed = -speed;
	}
	else if (height + speed > maxHeight)
	{
		height = maxHeight;
		speed = -speed;
	}
	else
	{
		height += speed;
	}
}
void Cube::changeSpeed(float amount)
{
	if (speed + amount > 0.0f && speed + amount < 1.0f)
	{
		speed += amount;
	}
}

void Cube::Draw(GLuint shaderProgram) {
	updateVBO();

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	glm::mat4 model = glm::mat4(1.0f);
	GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(index.size()), GL_UNSIGNED_INT, 0);
}

void Cube::move(glm::vec3 v)
{
	for (auto& i : vertices)
	{
		i.pos += v;
	}
}