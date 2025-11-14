#include "Cube.h"
#include "Mountain.h"

Cube::Cube(int practiceNum)
{
	if (practiceNum == 21)
	{
		float length = 1.0f;

		// Á¤»ç°¢Çü Å×½ºÆ®
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
			{ {  length, -length, length }, {0.0f, 1.0f, 0.0f} },
			{ { -length, -length, length }, {0.0f, 0.0f, 1.0f} },
		};

		index =
		{
			// ¿À¸¥ÂÊ¸é
			0, 1, 5, 0, 5, 4,
			// ¿ÞÂÊ¸é
			3, 6, 2, 3, 7, 6,
			// À­¸é
			0, 7, 3, 0, 4, 7,
			// ¾Æ·§¸é
			1, 2, 6, 1, 6, 5,
			// µÞ¸é
			4, 5, 6, 4, 6, 7,
		};
	}
	else if (practiceNum == 25)
	{
		float length = 1.0f;

		// Á¤»ç°¢Çü Å×½ºÆ®
		vertices =
		{
			// ¾Õ,µÚ
			{ {  length,  length, length }, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f} },
			{ {  length, -length, length }, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f} },
			{ { -length, -length, length }, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f} },
			{ { -length,  length, length }, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f} },
			{ {  length,  length, -length }, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, -1.0f} },
			{ {  length, -length, -length }, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, -1.0f} },
			{ { -length, -length, -length }, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, -1.0f} },
			{ { -length,  length, -length }, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, -1.0f} },

			// ÁÂ,¿ì
			{ {  length,  length, length },  {0.0f, 1.0f, 0.0f}, { 1.0f, 0.0f, 0.0f} },
			{ {  length, -length, length },  {0.0f, 1.0f, 0.0f}, { 1.0f, 0.0f, 0.0f} },
			{ { -length, -length, length },  {0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} },
			{ { -length,  length, length },  {0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} },
			{ {  length,  length, -length }, {0.0f, 1.0f, 0.0f}, { 1.0f, 0.0f, 0.0f} },
			{ {  length, -length, -length }, {0.0f, 1.0f, 0.0f}, { 1.0f, 0.0f, 0.0f} },
			{ { -length, -length, -length }, {0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} },
			{ { -length,  length, -length }, {0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f} },

			// »ó,ÇÏ
			{ {  length,  length, length },  {1.0f, 1.0f, 0.0f}, {0.0f,  1.0f, 0.0f} },
			{ {  length, -length, length },  {0.7f, 0.7f, 0.7f}, {0.0f, -1.0f, 0.0f} },
			{ { -length, -length, length },  {0.7f, 0.7f, 0.7f}, {0.0f, -1.0f, 0.0f} },
			{ { -length,  length, length },  {1.0f, 1.0f, 0.0f}, {0.0f,  1.0f, 0.0f} },
			{ {  length,  length, -length }, {1.0f, 1.0f, 0.0f}, {0.0f,  1.0f, 0.0f} },
			{ {  length, -length, -length }, {0.7f, 0.7f, 0.7f}, {0.0f, -1.0f, 0.0f} },
			{ { -length, -length, -length }, {0.7f, 0.7f, 0.7f}, {0.0f, -1.0f, 0.0f} },
			{ { -length,  length, -length }, {1.0f, 1.0f, 0.0f}, {0.0f,  1.0f, 0.0f} }

		};

		index =
		{
			
			// ¾Õ¸é
			0, 3, 1, 1, 3, 2,
			// µÞ¸é
			4, 5, 6, 4, 6, 7,
			
			// ¿ÞÂÊ¸é
			11, 14, 10, 11, 15, 14,
			// ¿À¸¥ÂÊ¸é
			8, 9, 13, 8, 13, 12,

			// À­¸é
			16, 23, 19, 16, 20, 23,
			// ¾Æ·§¸é
			17, 18, 22, 17, 22, 21

		};
	}

	initBuffer();
}

Cube::Cube(float rad)
{
	const float color = 1.0f;

	const float length = rad;
	vertices =
	{
		// ¾Õ,µÚ
		{ {  length,  length, length }, {color, color, color}, {0.0f, 0.0f, 1.0f} },
		{ {  length, -length, length }, {color, color, color}, {0.0f, 0.0f, 1.0f} },
		{ { -length, -length, length }, {color, color, color}, {0.0f, 0.0f, 1.0f} },
		{ { -length,  length, length }, {color, color, color}, {0.0f, 0.0f, 1.0f} },
		{ {  length,  length, -length }, {color, color, color}, {0.0f, 0.0f, -1.0f} },
		{ {  length, -length, -length }, {color, color, color}, {0.0f, 0.0f, -1.0f} },
		{ { -length, -length, -length }, {color, color, color}, {0.0f, 0.0f, -1.0f} },
		{ { -length,  length, -length }, {color, color, color}, {0.0f, 0.0f, -1.0f} },

		// ÁÂ,¿ì
		{ {  length,  length, length },  {color, color, color}, { 1.0f, 0.0f, 0.0f} },
		{ {  length, -length, length },  {color, color, color}, { 1.0f, 0.0f, 0.0f} },
		{ { -length, -length, length },  {color, color, color}, {-1.0f, 0.0f, 0.0f} },
		{ { -length,  length, length },  {color, color, color}, {-1.0f, 0.0f, 0.0f} },
		{ {  length,  length, -length }, {color, color, color}, { 1.0f, 0.0f, 0.0f} },
		{ {  length, -length, -length }, {color, color, color}, { 1.0f, 0.0f, 0.0f} },
		{ { -length, -length, -length }, {color, color, color}, {-1.0f, 0.0f, 0.0f} },
		{ { -length,  length, -length }, {color, color, color}, {-1.0f, 0.0f, 0.0f} },

		// »ó,ÇÏ
		{ {  length,  length, length },  {color, color, color}, {0.0f,  1.0f, 0.0f} },
		{ {  length, -length, length },  {color, color, color}, {0.0f, -1.0f, 0.0f} },
		{ { -length, -length, length },  {color, color, color}, {0.0f, -1.0f, 0.0f} },
		{ { -length,  length, length },  {color, color, color}, {0.0f,  1.0f, 0.0f} },
		{ {  length,  length, -length }, {color, color, color}, {0.0f,  1.0f, 0.0f} },
		{ {  length, -length, -length }, {color, color, color}, {0.0f, -1.0f, 0.0f} },
		{ { -length, -length, -length }, {color, color, color}, {0.0f, -1.0f, 0.0f} },
		{ { -length,  length, -length }, {color, color, color}, {0.0f,  1.0f, 0.0f} }

	};

	index =
	{

		// ¾Õ¸é
		0, 3, 1, 1, 3, 2,
		// µÞ¸é
		4, 5, 6, 4, 6, 7,

		// ¿ÞÂÊ¸é
		11, 14, 10, 11, 15, 14,
		// ¿À¸¥ÂÊ¸é
		8, 9, 13, 8, 13, 12,

		// À­¸é
		16, 23, 19, 16, 20, 23,
		// ¾Æ·§¸é
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

	// À§Ä¡ (location = 0)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(0);

	// »ö»ó (location = 1)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	// ³ë¸Öº¤ÅÍ (location = 2)
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);

	// index ¿¬°áÇÏ±â
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), index.data(), GL_STATIC_DRAW);
}

void Cube::updateVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
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

void Cube::rotate(glm::vec3 v, float rad)
{
	for (int i{}; i < vertices.size(); ++i)
	{
		glm::vec4 pos(vertices[i].pos.x, vertices[i].pos.y, vertices[i].pos.z, 1.0f);
		glm::mat4 rotMatrix = glm::mat4(1.0f);
		rotMatrix = glm::rotate(rotMatrix, glm::radians(rad), v);
		pos = rotMatrix * pos;
		vertices[i].pos.x = pos.x;
		vertices[i].pos.y = pos.y;
		vertices[i].pos.z = pos.z;

		pos = glm::vec4(vertices[i].normal.x, vertices[i].normal.y, vertices[i].normal.z, 1.0f);
		rotMatrix = glm::mat4(1.0f);
		rotMatrix = glm::rotate(rotMatrix, glm::radians(rad), v);
		pos = rotMatrix * pos;
		vertices[i].normal.x = pos.x;
		vertices[i].normal.y = pos.y;
		vertices[i].normal.z = pos.z;
	}
}

void Cube::revolution(glm::vec3 v, float rad)
{
	for (int i{}; i < vertices.size(); ++i)
	{
		glm::vec4 pos(vertices[i].pos.x, vertices[i].pos.y, vertices[i].pos.z, 1.0f);
		glm::mat4 rotMatrix = glm::mat4(1.0f);
		rotMatrix = glm::rotate(rotMatrix, glm::radians(rad), v);
		pos = rotMatrix * pos;
		vertices[i].pos.x = pos.x;
		vertices[i].pos.y = pos.y;
		vertices[i].pos.z = pos.z;
	}
	
}

void Cube::changePolygon()
{
	if (type == Type::cube)
	{
		const float color = 1.0f;
		const float length = 1.0f;
		vertices =
		{
			// ¾Õ,µÚ
			{ {  length,  length, length },  vertices[0].color, {0.0f, 0.0f, 1.0f} },
			{ {  length, -length, length },  vertices[1].color, {0.0f, 0.0f, 1.0f} },
			{ { -length, -length, length },  vertices[2].color, {0.0f, 0.0f, 1.0f} },
			{ { -length,  length, length },  vertices[3].color, {0.0f, 0.0f, 1.0f} },
			{ {  length,  length, -length }, vertices[4].color, {0.0f, 0.0f, -1.0f} },
			{ {  length, -length, -length }, vertices[5].color, {0.0f, 0.0f, -1.0f} },
			{ { -length, -length, -length }, vertices[6].color, {0.0f, 0.0f, -1.0f} },
			{ { -length,  length, -length }, vertices[7].color, {0.0f, 0.0f, -1.0f} },

			// ÁÂ,¿ì
			{ {  length,  length, length },  vertices[8].color, { 1.0f, 0.0f, 0.0f} },
			{ {  length, -length, length },  vertices[9].color, { 1.0f, 0.0f, 0.0f} },
			{ { -length, -length, length },  vertices[10].color, {-1.0f, 0.0f, 0.0f} },
			{ { -length,  length, length },  vertices[11].color, {-1.0f, 0.0f, 0.0f} },
			{ {  length,  length, -length }, vertices[12].color, { 1.0f, 0.0f, 0.0f} },
			{ {  length, -length, -length }, vertices[13].color, { 1.0f, 0.0f, 0.0f} },
			{ { -length, -length, -length }, vertices[14].color, {-1.0f, 0.0f, 0.0f} },
			{ { -length,  length, -length }, vertices[15].color, {-1.0f, 0.0f, 0.0f} },

			// »ó,ÇÏ
			{ {  length,  length, length },  vertices[16].color, {0.0f,  1.0f, 0.0f} },
			{ {  length, -length, length },  vertices[17].color, {0.0f, -1.0f, 0.0f} },
			{ { -length, -length, length },  vertices[18].color, {0.0f, -1.0f, 0.0f} },
			{ { -length,  length, length },  vertices[19].color, {0.0f,  1.0f, 0.0f} },
			{ {  length,  length, -length }, vertices[20].color, {0.0f,  1.0f, 0.0f} },
			{ {  length, -length, -length }, vertices[21].color, {0.0f, -1.0f, 0.0f} },
			{ { -length, -length, -length }, vertices[22].color, {0.0f, -1.0f, 0.0f} },
			{ { -length,  length, -length }, vertices[23].color, {0.0f,  1.0f, 0.0f} }

		};

		index =
		{

			// ¾Õ¸é
			0, 3, 1, 1, 3, 2,
			// µÞ¸é
			4, 5, 6, 4, 6, 7,

			// ¿ÞÂÊ¸é
			11, 14, 10, 11, 15, 14,
			// ¿À¸¥ÂÊ¸é
			8, 9, 13, 8, 13, 12,

			// À­¸é
			16, 23, 19, 16, 20, 23,
			// ¾Æ·§¸é
			17, 18, 22, 17, 22, 21

		};
	}
	else if (type == Type::squarePyramid)
	{
		const float color = 1.0f;
		const float length = 1.0f;
		vertices =
		{
			// ¾Õ,µÚ
			{ {  0.0f,  length, 0.0f },		 vertices[0].color, {0.0f, 0.0f, 1.0f} },
			{ {  length, -length, length },  vertices[1].color, {0.0f, 0.0f, 1.0f} },
			{ { -length, -length, length },  vertices[2].color, {0.0f, 0.0f, 1.0f} },
			{ { -0.0f,  length, 0.0f },		 vertices[3].color, {0.0f, 0.0f, 1.0f} },
			{ {  0.0f,  length, -0.0f },	 vertices[4].color, {0.0f, 0.0f, -1.0f} },
			{ {  length, -length, -length }, vertices[5].color, {0.0f, 0.0f, -1.0f} },
			{ { -length, -length, -length }, vertices[6].color, {0.0f, 0.0f, -1.0f} },
			{ { -0.0f,  length, -0.0f },	 vertices[7].color, {0.0f, 0.0f, -1.0f} },
			
			// ÁÂ,¿ì
			{ {  0.0f,  length, 0.0f },		 vertices[8].color, { 1.0f, 0.0f, 0.0f} },
			{ {  length, -length, length },  vertices[9].color, { 1.0f, 0.0f, 0.0f} },
			{ { -length, -length, length },  vertices[10].color, {-1.0f, 0.0f, 0.0f} },
			{ { -0.0f,  length, 0.0f },		 vertices[11].color, {-1.0f, 0.0f, 0.0f} },
			{ {  0.0f,  length, -0.0f },	 vertices[12].color, { 1.0f, 0.0f, 0.0f} },
			{ {  length, -length, -length }, vertices[13].color, { 1.0f, 0.0f, 0.0f} },
			{ { -length, -length, -length }, vertices[14].color, {-1.0f, 0.0f, 0.0f} },
			{ { -0.0f,  length, -0.0f },	 vertices[15].color, {-1.0f, 0.0f, 0.0f} },

			// »ó,ÇÏ
			{ {  0.0f,  length, 0.0f },		 vertices[16].color, {0.0f,  1.0f, 0.0f} },
			{ {  length, -length, length },  vertices[17].color, {0.0f, -1.0f, 0.0f} },
			{ { -length, -length, length },  vertices[18].color, {0.0f, -1.0f, 0.0f} },
			{ { -0.0f,  length, 0.0f },		 vertices[19].color, {0.0f,  1.0f, 0.0f} },
			{ {  0.0f,  length, -0.0f },	 vertices[20].color, {0.0f,  1.0f, 0.0f} },
			{ {  length, -length, -length }, vertices[21].color, {0.0f, -1.0f, 0.0f} },
			{ { -length, -length, -length }, vertices[22].color, {0.0f, -1.0f, 0.0f} },
			{ { -0.0f,  length, -0.0f },	 vertices[23].color, {0.0f,  1.0f, 0.0f} }

		};

		index =
		{

			// ¾Õ¸é
			0, 3, 1, 1, 3, 2,
			// µÞ¸é
			4, 5, 6, 4, 6, 7,

			// ¿ÞÂÊ¸é
			11, 14, 10, 11, 15, 14,
			// ¿À¸¥ÂÊ¸é
			8, 9, 13, 8, 13, 12,

			// À­¸é
			16, 23, 19, 16, 20, 23,
			// ¾Æ·§¸é
			17, 18, 22, 17, 22, 21

		};
	}
}
