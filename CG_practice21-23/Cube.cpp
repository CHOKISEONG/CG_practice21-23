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
			{ {  length,  length, -length }, {0.7f, 0.7f, 0.7f} },
			{ {  length, -length, -length }, {0.7f, 0.7f, 0.7f} },
			{ { -length, -length, -length }, {0.7f, 0.7f, 0.7f} },
			{ { -length,  length, -length }, {0.7f, 0.7f, 0.7f} },
			{ {  length, -length, length }, {0.0f, 1.0f, 0.0f} },
			{ { -length, -length, length }, {0.0f, 0.0f, 1.0f} },
		};
		orgVertices = vertices;
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

		bottomPos.y = -length;
	}

	initBuffer();
}

Cube::Cube(float zPos, float rad)
{
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> zeroToOne(0.0f, 1.0f);
	const float color = zeroToOne(gen);

	vertices =
	{
		{ {  rad,  rad, rad }, {color, color, color} },
		{ {  rad, -rad, rad }, {color, color, color} },
		{ { -rad, -rad, rad }, {color, color, color} },
		{ { -rad,  rad, rad }, {color, color, color} },
		{ {  rad,  rad, -rad },	{color, color, color} },
		{ {  rad, -rad, -rad },	{color, color, color} },
		{ { -rad, -rad, -rad },	{color, color, color} },
		{ { -rad,  rad, -rad },	{color, color, color} },
	};
	orgVertices = vertices;
	index =
	{
		0, 5, 1, 0, 4, 5,
		3, 2, 6, 3, 6, 7,
		0, 3, 7, 0, 7, 4,
		1, 6, 2, 1, 5, 6,
		4, 6, 5, 4, 7, 6,
		0, 1, 2, 0, 2, 3
	};
	bottomPos.y = -rad;

	isThisHavePhysics = true;
	move(glm::vec3(0.0f, -1.0f + rad, zPos));

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

	glm::mat4 model = glm::mat4(1.0f);
	GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(index.size()), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Cube::move(glm::vec3 v)
{
	for (auto& i : vertices)
	{
		i.pos += v;
	}
	bottomPos += v;

	updateVBO();
}

void Cube::rotate(float dx, float dy)
{
	const float rad = (dx > 0) ? -0.1f : 0.1f;
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

	glm::vec4 pos(bottomPos.x, bottomPos.y, bottomPos.z, 1.0f);
	glm::mat4 rotMatrix = glm::mat4(1.0f);
	rotMatrix = glm::rotate(rotMatrix, glm::radians(rad), glm::vec3(0.0f, 0.0f, 1.0f));
	pos = rotMatrix * pos;
	bottomPos.x = pos.x;
	bottomPos.y = pos.y;
	bottomPos.z = pos.z;

	rotateAmount += rad;

	updateVBO();
}

void Cube::adaptC(Cube* c)
{
	glm::vec2 a(c->vertices[1].pos.x, c->vertices[1].pos.y);
	glm::vec2 b(c->vertices[2].pos.x, c->vertices[2].pos.y);

	glm::vec2 point1(vertices[1].pos.x, vertices[1].pos.y);
	glm::vec2 point2(vertices[2].pos.x, vertices[2].pos.y);

	glm::vec2 ab = b - a;
	glm::vec2 abNorm = glm::normalize(ab);
	glm::vec2 normal(-abNorm.y, abNorm.x);

	float dist1 = glm::dot(point1 - a, normal);
	float dist2 = glm::dot(point2 - a, normal);

	float avgDist = (dist1 + dist2) / 2.0f;
	const float threshold = 1e-3f;

	if (fabs(avgDist) > threshold)
		move(glm::vec3(-normal.x * avgDist, -normal.y * avgDist, 0.0f));
}

void Cube::baseOpen()
{
	isBaseOpened = true;

	index =
	{
		// 오른쪽면
		0, 1, 5, 0, 5, 4,
		// 왼쪽면
		3, 6, 2, 3, 7, 6,
		// 윗면
		0, 7, 3, 0, 4, 7,
		// 아랫면
		8, 9, 6, 8, 6, 5,
		// 뒷면
		4, 5, 6, 4, 6, 7,
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), index.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void Cube::baseOpenAnimation()
{
	if (!isBaseOpened) return;
	static float angleAmount = 0.0f;
	if (angleAmount <= -1.5f) return;

	glm::vec3 A = vertices[5].pos; 
	glm::vec3 B = vertices[6].pos; 
	glm::vec3 axis = glm::normalize(B - A); 
	constexpr float angle = glm::radians(-1.0f); 

	glm::vec4 pos(vertices[8].pos, 1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, A);         
	model = glm::rotate(model, angle, axis);  
	model = glm::translate(model, -A);        
	pos = model * pos;

	vertices[8].pos = glm::vec3(pos);

	pos = glm::vec4(vertices[9].pos, 1.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, A);
	model = glm::rotate(model, angle, axis);
	model = glm::translate(model, -A);
	pos = model * pos;

	vertices[9].pos = glm::vec3(pos);

	angleAmount += angle;
	updateVBO();
}

void Cube::handlePhysics(Cube* c)
{
	if (!isThisHavePhysics) return;

	if (c->isBaseOpened)
	{
		move(glm::vec3(0.0f, -0.01f, 0.0f));
		return;
	}

	adaptC(c);

	glm::vec2 a(c->vertices[1].pos.x, c->vertices[1].pos.y);
	glm::vec2 b(c->vertices[2].pos.x, c->vertices[2].pos.y);
	glm::vec2 ab = b - a;
	glm::vec2 abNorm = glm::normalize(ab);

	glm::vec2 gravityVec(0.0f, -0.02f);
	float slideAmount = glm::dot(gravityVec, abNorm);

	glm::vec2 moveVec = abNorm * slideAmount;

	glm::vec2 p1(vertices[1].pos.x, vertices[1].pos.y);
	glm::vec2 p2(vertices[2].pos.x, vertices[2].pos.y);

	glm::vec2 p1Next = p1 + moveVec;
	glm::vec2 p2Next = p2 + moveVec;

	float ab2 = glm::dot(ab, ab);
	float t1 = glm::dot(p1Next - a, ab) / ab2;
	float t2 = glm::dot(p2Next - a, ab) / ab2;

	if (t1 >= 0.0f && t1 <= 1.0f && t2 >= 0.0f && t2 <= 1.0f)
	{
		move(glm::vec3(moveVec.x, moveVec.y, 0.0f));
	}
	
	updateVBO();
}
