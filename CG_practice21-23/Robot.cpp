#include "Robot.h"

Robot::Robot()
{
	const float length = 0.1f;
	const float threeQuarterLength = 0.075f;
	const float halfLength = 0.05f;
	const float oneQuarterLength = 0.025f;

	// Áö¶ö³µ´Âµ¥ ÀÏ´Ü ÀÌ ¹æ¹ýÀ¸·Î
	vertices =
	{
		// ¸öÅë
		{ {  length,  length, length },  {1.0f, 0.0f, 0.0f} },
		{ {  length, -length, length },  {1.0f, 0.0f, 0.0f} },
		{ { -length, -length, length },  {1.0f, 0.0f, 0.0f} },
		{ { -length,  length, length },  {1.0f, 0.0f, 0.0f} },
		{ {  length,  length, -length }, {1.0f, 0.0f, 0.0f} },
		{ {  length, -length, -length }, {1.0f, 0.0f, 0.0f} },
		{ { -length, -length, -length }, {1.0f, 0.0f, 0.0f} },
		{ { -length,  length, -length }, {1.0f, 0.0f, 0.0f} },

		// ¿ÞÂÊ ´Ù¸®
		{ { -oneQuarterLength	, -length		, oneQuarterLength },  {0.0f, 1.0f, 0.0f} },
		{ { -oneQuarterLength	, -length * 2	, oneQuarterLength },  {0.0f, 1.0f, 0.0f} },
		{ { -threeQuarterLength	, -length * 2	, oneQuarterLength },  {0.0f, 1.0f, 0.0f} },
		{ { -threeQuarterLength	, -length		, oneQuarterLength },  {0.0f, 1.0f, 0.0f} },
		{ { -oneQuarterLength	, -length		, -oneQuarterLength }, {0.0f, 1.0f, 0.0f} },
		{ { -oneQuarterLength	, -length * 2	, -oneQuarterLength }, {0.0f, 1.0f, 0.0f} },
		{ { -threeQuarterLength	, -length * 2	, -oneQuarterLength }, {0.0f, 1.0f, 0.0f} },
		{ { -threeQuarterLength	, -length		, -oneQuarterLength }, {0.0f, 1.0f, 0.0f} },

		// ¿À¸¥ÂÊ ´Ù¸®
		{ { threeQuarterLength	, -length		, oneQuarterLength },  {0.0f, 1.0f, 0.0f} },
		{ { threeQuarterLength	, -length * 2	, oneQuarterLength },  {0.0f, 1.0f, 0.0f} },
		{ { oneQuarterLength	, -length * 2	, oneQuarterLength },  {0.0f, 1.0f, 0.0f} },
		{ { oneQuarterLength	, -length		, oneQuarterLength },  {0.0f, 1.0f, 0.0f} },
		{ { threeQuarterLength	, -length 		, -oneQuarterLength }, {0.0f, 1.0f, 0.0f} },
		{ { threeQuarterLength	, -length * 2	, -oneQuarterLength }, {0.0f, 1.0f, 0.0f} },
		{ { oneQuarterLength	, -length * 2	, -oneQuarterLength }, {0.0f, 1.0f, 0.0f} },
		{ { oneQuarterLength	, -length 		, -oneQuarterLength }, {0.0f, 1.0f, 0.0f} },

		// ¿ÞÂÊ ÆÈ
		{ { -length				, halfLength	, oneQuarterLength },  {0.0f, 0.0f, 1.0f} },
		{ { -length				, -halfLength	, oneQuarterLength },  {0.0f, 0.0f, 1.0f} },
		{ { -length - halfLength, -halfLength	, oneQuarterLength },  {0.0f, 0.0f, 1.0f} },
		{ { -length - halfLength, halfLength	, oneQuarterLength },  {0.0f, 0.0f, 1.0f} },
		{ { -length				, halfLength	, -oneQuarterLength }, {0.0f, 0.0f, 1.0f} },
		{ { -length				, -halfLength	, -oneQuarterLength }, {0.0f, 0.0f, 1.0f} },
		{ { -length - halfLength, -halfLength	, -oneQuarterLength }, {0.0f, 0.0f, 1.0f} },
		{ { -length - halfLength, halfLength	, -oneQuarterLength }, {0.0f, 0.0f, 1.0f} },

		// ¿À¸¥ÂÊ ÆÈ
		{ { length + halfLength	,  halfLength	, oneQuarterLength },  {0.0f, 0.0f, 1.0f} },
		{ { length + halfLength	, -halfLength	, oneQuarterLength },  {0.0f, 0.0f, 1.0f} },
		{ { length				, -halfLength	, oneQuarterLength },  {0.0f, 0.0f, 1.0f} },
		{ { length				,  halfLength	, oneQuarterLength },  {0.0f, 0.0f, 1.0f} },
		{ { length + halfLength	,  halfLength	, -oneQuarterLength }, {0.0f, 0.0f, 1.0f} },
		{ { length + halfLength	, -halfLength	, -oneQuarterLength }, {0.0f, 0.0f, 1.0f} },
		{ { length				, -halfLength	, -oneQuarterLength }, {0.0f, 0.0f, 1.0f} },
		{ { length				,  halfLength	, -oneQuarterLength }, {0.0f, 0.0f, 1.0f} },

		// ¾ó±¼
		{ {  halfLength, length * 2	, halfLength },  {1.0f, 1.0f, 0.0f} },
		{ {  halfLength, length		, halfLength },  {1.0f, 1.0f, 0.0f} },
		{ { -halfLength, length		, halfLength },  {1.0f, 1.0f, 0.0f} },
		{ { -halfLength, length * 2	, halfLength },  {1.0f, 1.0f, 0.0f} },
		{ {  halfLength, length * 2	, -halfLength }, {1.0f, 1.0f, 0.0f} },
		{ {  halfLength, length		, -halfLength }, {1.0f, 1.0f, 0.0f} },
		{ { -halfLength, length		, -halfLength }, {1.0f, 1.0f, 0.0f} },
		{ { -halfLength, length * 2	, -halfLength }, {1.0f, 1.0f, 0.0f} },

		// ÄÚ
		{ {  oneQuarterLength, length + threeQuarterLength	, halfLength * 3 },		{0.0f, 1.0f, 1.0f} },
		{ {  oneQuarterLength, length + oneQuarterLength	, halfLength * 3 },		{0.0f, 1.0f, 1.0f} },
		{ { -oneQuarterLength, length + oneQuarterLength	, halfLength * 3 },		{0.0f, 1.0f, 1.0f} },
		{ { -oneQuarterLength, length + threeQuarterLength	, halfLength * 3 },		{0.0f, 1.0f, 1.0f} },
		{ {  oneQuarterLength, length + threeQuarterLength	, halfLength + 0.001f },{0.0f, 1.0f, 1.0f} },
		{ {  oneQuarterLength, length + oneQuarterLength	, halfLength + 0.001f },{0.0f, 1.0f, 1.0f} },
		{ { -oneQuarterLength, length + oneQuarterLength	, halfLength + 0.001f },{0.0f, 1.0f, 1.0f} },
		{ { -oneQuarterLength, length + threeQuarterLength	, halfLength + 0.001f },{0.0f, 1.0f, 1.0f} }
	};
	orgVertices = vertices;
	index.reserve(260); // »ìÂ¦ ³Ë³ËÇÏ°Ô ÀâÀ½
	for (int i{}; i < 8 * 7; i += 8)
	{
		index.push_back(i + 0); index.push_back(i + 1); index.push_back(i + 5); index.push_back(i + 0); index.push_back(i + 5); index.push_back(i + 4);
		index.push_back(i + 3); index.push_back(i + 6); index.push_back(i + 2); index.push_back(i + 3); index.push_back(i + 7); index.push_back(i + 6);
		index.push_back(i + 0); index.push_back(i + 7); index.push_back(i + 3); index.push_back(i + 0); index.push_back(i + 4); index.push_back(i + 7);
		index.push_back(i + 1); index.push_back(i + 2); index.push_back(i + 6); index.push_back(i + 1); index.push_back(i + 6); index.push_back(i + 5);
		index.push_back(i + 4); index.push_back(i + 5); index.push_back(i + 6); index.push_back(i + 4); index.push_back(i + 6); index.push_back(i + 7);
		index.push_back(i + 0); index.push_back(i + 1); index.push_back(i + 2); index.push_back(i + 0); index.push_back(i + 2); index.push_back(i + 3);
	}

	initBuffer();
}


void Robot::move(glm::vec3 v)
{
	for (auto& i : vertices)
	{
		i.pos += v;
	}

	updateVBO();
}

void Robot::initBuffer()
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

	// index ¿¬°áÇÏ±â
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), index.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void Robot::updateVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void Robot::Draw(GLuint shaderProgram) {
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	glm::mat4 model = glm::mat4(1.0f);
	GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(index.size()), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}