#include "Robot.h"

Robot::Robot()
{
	const float length = 0.1f;
	const float threeQuarterLength = 0.075f;
	const float halfLength = 0.05f;
	const float oneQuarterLength = 0.025f;

	// 지랄났는데 일단 이 방법으로
	vertices =
	{
		// 몸통 (0~7)
		{ {  length,  length, length },  {1.0f, 0.0f, 0.0f} },
		{ {  length, -length, length },  {1.0f, 0.0f, 0.0f} },
		{ { -length, -length, length },  {1.0f, 0.0f, 0.0f} },
		{ { -length,  length, length },  {1.0f, 0.0f, 0.0f} },
		{ {  length,  length, -length }, {1.0f, 0.0f, 0.0f} },
		{ {  length, -length, -length }, {1.0f, 0.0f, 0.0f} },
		{ { -length, -length, -length }, {1.0f, 0.0f, 0.0f} },
		{ { -length,  length, -length }, {1.0f, 0.0f, 0.0f} },

		// 왼쪽 다리 (8~15)
		{ { -oneQuarterLength	, -length		, oneQuarterLength },  {0.0f, 1.0f, 0.0f} },
		{ { -oneQuarterLength	, -length * 2	, oneQuarterLength },  {0.0f, 1.0f, 0.0f} },
		{ { -threeQuarterLength	, -length * 2	, oneQuarterLength },  {0.0f, 1.0f, 0.0f} },
		{ { -threeQuarterLength	, -length		, oneQuarterLength },  {0.0f, 1.0f, 0.0f} },
		{ { -oneQuarterLength	, -length		, -oneQuarterLength }, {0.0f, 1.0f, 0.0f} },
		{ { -oneQuarterLength	, -length * 2	, -oneQuarterLength }, {0.0f, 1.0f, 0.0f} },
		{ { -threeQuarterLength	, -length * 2	, -oneQuarterLength }, {0.0f, 1.0f, 0.0f} },
		{ { -threeQuarterLength	, -length		, -oneQuarterLength }, {0.0f, 1.0f, 0.0f} },

		// 오른쪽 다리 (16~23)
		{ { threeQuarterLength	, -length		, oneQuarterLength },  {0.0f, 1.0f, 0.0f} },
		{ { threeQuarterLength	, -length * 2	, oneQuarterLength },  {0.0f, 1.0f, 0.0f} },
		{ { oneQuarterLength	, -length * 2	, oneQuarterLength },  {0.0f, 1.0f, 0.0f} },
		{ { oneQuarterLength	, -length		, oneQuarterLength },  {0.0f, 1.0f, 0.0f} },
		{ { threeQuarterLength	, -length 		, -oneQuarterLength }, {0.0f, 1.0f, 0.0f} },
		{ { threeQuarterLength	, -length * 2	, -oneQuarterLength }, {0.0f, 1.0f, 0.0f} },
		{ { oneQuarterLength	, -length * 2	, -oneQuarterLength }, {0.0f, 1.0f, 0.0f} },
		{ { oneQuarterLength	, -length 		, -oneQuarterLength }, {0.0f, 1.0f, 0.0f} },

		// 왼쪽 팔 (24~31)
		{ { -length				, halfLength	, oneQuarterLength },  {0.0f, 0.0f, 1.0f} },
		{ { -length				, -halfLength	, oneQuarterLength },  {0.0f, 0.0f, 1.0f} },
		{ { -length - halfLength, -halfLength	, oneQuarterLength },  {0.0f, 0.0f, 1.0f} },
		{ { -length - halfLength, halfLength	, oneQuarterLength },  {0.0f, 0.0f, 1.0f} },
		{ { -length				, halfLength	, -oneQuarterLength }, {0.0f, 0.0f, 1.0f} },
		{ { -length				, -halfLength	, -oneQuarterLength }, {0.0f, 0.0f, 1.0f} },
		{ { -length - halfLength, -halfLength	, -oneQuarterLength }, {0.0f, 0.0f, 1.0f} },
		{ { -length - halfLength, halfLength	, -oneQuarterLength }, {0.0f, 0.0f, 1.0f} },

		// 오른쪽 팔 (32~39)
		{ { length + halfLength	,  halfLength	, oneQuarterLength },  {0.0f, 0.0f, 1.0f} },
		{ { length + halfLength	, -halfLength	, oneQuarterLength },  {0.0f, 0.0f, 1.0f} },
		{ { length				, -halfLength	, oneQuarterLength },  {0.0f, 0.0f, 1.0f} },
		{ { length				,  halfLength	, oneQuarterLength },  {0.0f, 0.0f, 1.0f} },
		{ { length + halfLength	,  halfLength	, -oneQuarterLength }, {0.0f, 0.0f, 1.0f} },
		{ { length + halfLength	, -halfLength	, -oneQuarterLength }, {0.0f, 0.0f, 1.0f} },
		{ { length				, -halfLength	, -oneQuarterLength }, {0.0f, 0.0f, 1.0f} },
		{ { length				,  halfLength	, -oneQuarterLength }, {0.0f, 0.0f, 1.0f} },

		// 얼굴 (40~47)
		{ {  halfLength, length * 2	, halfLength },  {1.0f, 1.0f, 0.0f} },
		{ {  halfLength, length		, halfLength },  {1.0f, 1.0f, 0.0f} },
		{ { -halfLength, length		, halfLength },  {1.0f, 1.0f, 0.0f} },
		{ { -halfLength, length * 2	, halfLength },  {1.0f, 1.0f, 0.0f} },
		{ {  halfLength, length * 2	, -halfLength }, {1.0f, 1.0f, 0.0f} },
		{ {  halfLength, length		, -halfLength }, {1.0f, 1.0f, 0.0f} },
		{ { -halfLength, length		, -halfLength }, {1.0f, 1.0f, 0.0f} },
		{ { -halfLength, length * 2	, -halfLength }, {1.0f, 1.0f, 0.0f} },

		// 코 (48~55)
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
	index.reserve(260); // 살짝 넉넉하게 잡음
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

	move(glm::vec3(0.0f, -0.8f, 0.0f));
}

void Robot::move(glm::vec3 v)
{
	for (auto& i : vertices)
	{
		i.pos += v;
	}

	updateVBO();
}

void Robot::update(std::vector<Cube*>& cube)
{
	// 0 - 몸통 
	// 8,16 - 다리 
	// 24,32 - 팔
	// 40,48 - 얼굴,코

	// 팔 흔들기 먼저
	shakeArm();
	
	// 큐브랑 충돌 체크
	if (checkCollide(cube))
	{
		// 그다음은 점프하는거 처리
		jump();

		// 마지막은 이동하기
		moving();
	}

	updateVBO();
}

bool Robot::checkCollide(std::vector<Cube*>& cube)
{
	// 구현 안함
	
	return true;
}

void Robot::shakeArm()
{
	static float shakeAmount = 0.0f;
	if (shakeAmount >= 0.5f)
	{
		shakeSpeed = -shakeSpeed;
	}
	else if (shakeAmount <= -0.5f)
	{
		shakeSpeed = -shakeSpeed;
	}

	for (int i{ 24 }; i < 40; i += 8)
	{
		float rotateSpeed = (i == 24) ? shakeSpeed : -shakeSpeed;

		glm::vec3 A = vertices[i].pos;
		glm::vec3 B = vertices[i + 3].pos;
		glm::vec3 axis = glm::normalize(B - A);

		glm::vec4 pos(vertices[i + 1].pos, 1.0f);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, A);
		model = glm::rotate(model, rotateSpeed, axis);
		model = glm::translate(model, -A);
		pos = model * pos;

		vertices[i + 1].pos = glm::vec3(pos);

		pos = glm::vec4(vertices[i + 2].pos, 1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, A);
		model = glm::rotate(model, rotateSpeed, axis);
		model = glm::translate(model, -A);
		pos = model * pos;

		vertices[i + 2].pos = glm::vec3(pos);

		A = vertices[i + 4].pos;
		B = vertices[i + 7].pos;
		axis = glm::normalize(B - A);

		pos = glm::vec4(vertices[i + 5].pos, 1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, A);
		model = glm::rotate(model, rotateSpeed, axis);
		model = glm::translate(model, -A);
		pos = model * pos;

		vertices[i + 5].pos = glm::vec3(pos);

		pos = glm::vec4(vertices[i + 6].pos, 1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, A);
		model = glm::rotate(model, rotateSpeed, axis);
		model = glm::translate(model, -A);
		pos = model * pos;

		vertices[i + 6].pos = glm::vec3(pos);
	}
	

	shakeAmount += shakeSpeed;
}

void Robot::shakeLeg(bool isOpposite)
{
	if (jumpAmount >= 0.5f)
	{
		legSpeed = -legSpeed;
	}
	else if (jumpAmount <= -0.5f)
	{
		legSpeed = -legSpeed;
	}
	for (int i{ 8 }; i < 24; i += 8)
	{
		float rotateSpeed = legSpeed;
		if (isOpposite && i == 8)
		{
			rotateSpeed = -rotateSpeed;
		}

		glm::vec3 A = vertices[i].pos;
		glm::vec3 B = vertices[i + 3].pos;
		glm::vec3 axis = glm::normalize(B - A);

		glm::vec4 pos(vertices[i + 1].pos, 1.0f);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, A);
		model = glm::rotate(model, rotateSpeed, axis);
		model = glm::translate(model, -A);
		pos = model * pos;

		vertices[i + 1].pos = glm::vec3(pos);

		pos = glm::vec4(vertices[i + 2].pos, 1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, A);
		model = glm::rotate(model, rotateSpeed, axis);
		model = glm::translate(model, -A);
		pos = model * pos;

		vertices[i + 2].pos = glm::vec3(pos);

		A = vertices[i + 4].pos;
		B = vertices[i + 7].pos;
		axis = glm::normalize(B - A);

		pos = glm::vec4(vertices[i + 5].pos, 1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, A);
		model = glm::rotate(model, rotateSpeed, axis);
		model = glm::translate(model, -A);
		pos = model * pos;

		vertices[i + 5].pos = glm::vec3(pos);

		pos = glm::vec4(vertices[i + 6].pos, 1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, A);
		model = glm::rotate(model, rotateSpeed, axis);
		model = glm::translate(model, -A);
		pos = model * pos;

		vertices[i + 6].pos = glm::vec3(pos);
	}


	jumpAmount += legSpeed;
}

void Robot::moving()
{
	// 1. tmp를 먼저 이동시켜보고
	std::vector<Vertex> tmp = vertices;
	for (auto& i : tmp)
	{
		i.pos += moveDir;
	}
	// 2. 벽이랑 충돌 안하는 이동일 때만 원본인 vertices를 이동하게 함
	if (tmp[26].pos.x >= -1.0f && tmp[32].pos.x <= 1.0f
		&& tmp[0].pos.z <= 1.0f && tmp[4].pos.z >= -1.0f)
	{
		for (auto& i : vertices)
		{
			i.pos += moveDir;
		}
	}
	if (moveDir != glm::vec3(0.0f, 0.0f, 0.0f))
	{
		shakeLeg(true);
		shakeArm();
	}
}
void Robot::jump()
{
	// 땅에 있으면 리턴
	if (onGround) return;

	move(glm::vec3(0.0f, jumpSpeed, 0.0f));
	jumpSpeed += gravity;

	// 점프 처리 후 땅에 있으면 땅에 있는 상태로 전환
	if (vertices[9].pos.y <= -1.0f)
	{
		jumpSpeed = 0.03f;
		move(glm::vec3(0.0f, -vertices[9].pos.y - 1.0f, 0.0f));
		onGround = true;
	}
}

void Robot::initBuffer()
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

	// index 연결하기
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), index.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void Robot::updateVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void Robot::goBackToOriginal()
{
	vertices = orgVertices;
}

void Robot::Draw(GLuint shaderProgram) {
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	glm::mat4 model = glm::mat4(1.0f);
	GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_LINES, static_cast<GLsizei>(index.size()), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}