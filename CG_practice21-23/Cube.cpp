#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Cube.h"

Cube::Cube(float length, const char* str)
{
	// 앞-뒤-우-좌-상-하 순으로 만듬
	vertices =
	{
		{ {  length,  length, length },  {0.0f, 0.0f, 1.0f }, {0.333333f, 0.5f} },
		{ {  length, -length, length },  {0.0f, 0.0f, 1.0f }, {0.333333f, 0.0f} },
		{ { -length, -length, length },  {0.0f, 0.0f, 1.0f }, {0.0f, 0.0f}      },
		{ { -length,  length, length },  {0.0f, 0.0f, 1.0f }, {0.0f, 0.5f}      },

		{ {  length,  length, -length }, {0.0f, 0.0f, -1.0f}, {0.333333f, 0.5f} },
		{ {  length, -length, -length }, {0.0f, 0.0f, -1.0f}, {0.333333f, 0.0f} },
		{ { -length, -length, -length }, {0.0f, 0.0f, -1.0f}, {0.666666f, 0.0f} },
		{ { -length,  length, -length }, {0.0f, 0.0f, -1.0f}, {0.666666f, 0.5f} },

		{ {  length,  length, length },  { 1.0f, 0.0f, 0.0f}, {1.0f, 0.5f}      },
		{ {  length, -length, length },  { 1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}      },
		{ {  length,  length, -length }, { 1.0f, 0.0f, 0.0f}, {0.666666f, 0.5f} },
		{ {  length, -length, -length }, { 1.0f, 0.0f, 0.0f}, {0.666666f, 0.0f} },

		{ { -length, -length, length },  {-1.0f, 0.0f, 0.0f}, {0.0f, 0.5f}      },
		{ { -length,  length, length },  {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}      },
		{ { -length, -length, -length }, {-1.0f, 0.0f, 0.0f}, {0.333333f, 0.5f} },
		{ { -length,  length, -length }, {-1.0f, 0.0f, 0.0f}, {0.333333f, 1.0f} },

		{ {  length,  length, length },  {0.0f,  1.0f, 0.0f}, {0.333333f, 0.5f} },
		{ { -length,  length, length },  {0.0f,  1.0f, 0.0f}, {0.666666f, 0.5f} },
		{ {  length,  length, -length }, {0.0f,  1.0f, 0.0f}, {0.333333f, 1.0f} },
		{ { -length,  length, -length }, {0.0f,  1.0f, 0.0f}, {0.666666f, 1.0f} },

		{ {  length, -length, length },  {0.0f, -1.0f, 0.0f}, {0.666666f, 0.5f} },
		{ { -length, -length, length },  {0.0f, -1.0f, 0.0f}, {1.0f, 0.5f}      },
		{ {  length, -length, -length }, {0.0f, -1.0f, 0.0f}, {0.666666f, 1.0f} },
		{ { -length, -length, -length }, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}      }
	};

	index =
	{
		// 앞면
		0, 3, 1, 1, 3, 2,
		// 뒷면
		4, 5, 6, 4, 6, 7,
			
		// 왼쪽면
		13, 14, 12, 13, 15, 14,
		// 오른쪽면
		8, 9, 11, 8, 11, 10,

		// 윗면
		16, 19, 17, 16, 18, 19,
		// 아랫면
		20, 21, 23, 20, 23, 22
	};

	initBuffer();
	initTexture(str);
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

	// 노말 (location = 1)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	// 텍스쳐 (location = 2)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
	glEnableVertexAttribArray(2);

	// index 연결하기
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), index.data(), GL_STATIC_DRAW);
}

void Cube::initTexture(const char* str)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(str, &width, &height, &numberOfChannel, 0);
	if (!data)
	{
		std::cerr << "Failed to load texture: " << str << std::endl;
		return;
	}

	GLenum format = GL_RGB;
	if (numberOfChannel == 1) format = GL_RED;
	else if (numberOfChannel == 3) format = GL_RGB;
	else if (numberOfChannel == 4) format = GL_RGBA;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
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
	model *= glm::translate(glm::mat4(1.0f), position);
	GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	// 텍스처 활성/바인딩 및 샘플러 설정
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	GLint samplerLoc = glGetUniformLocation(shaderProgram, "outTexture");
	glUniform1i(samplerLoc, 0);

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(index.size()), GL_UNSIGNED_INT, 0);
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


// 어떤 면을 돌릴지도 인자로 받아서 그 면만 돌리게
void Cube::rotateWithPivot(glm::vec3 v, float rad, Face face, glm::vec3 pivot)
{
	int start = (face == Face::All) ? 0 : static_cast<int>(face) * 4;
	int end = (face == Face::All) ? vertices.size() : static_cast<int>(face) * 4 + 4;

	glm::mat4 T1 = glm::translate(glm::mat4(1.0f), -pivot);
	glm::mat4 T2 = glm::translate(glm::mat4(1.0f), pivot);

	for (int i{ start }; i < end; ++i)
	{
		glm::vec4 pos(vertices[i].pos.x, vertices[i].pos.y, vertices[i].pos.z, 1.0f);
		glm::mat4 rotMatrix = glm::mat4(1.0f);
		rotMatrix = glm::rotate(rotMatrix, glm::radians(rad), v);
		pos = T2 * rotMatrix * T1 * pos;
		vertices[i].pos.x = pos.x;
		vertices[i].pos.y = pos.y;
		vertices[i].pos.z = pos.z;

		pos = glm::vec4(vertices[i].normal.x, vertices[i].normal.y, vertices[i].normal.z, 1.0f);
		rotMatrix = glm::mat4(1.0f);
		rotMatrix = glm::rotate(rotMatrix, glm::radians(rad), v);
		pos = T2 * rotMatrix * T1 * pos;
		vertices[i].normal.x = pos.x;
		vertices[i].normal.y = pos.y;
		vertices[i].normal.z = pos.z;
	}
}

void Cube::changePolygon(Type type_)
{
	type = type_;

	if (type == Type::cube)
	{
		const float length = 1.0f;
		vertices =
		{
			{ {  length,  length, length },  {0.0f, 0.0f, 1.0f }, {0.333333f, 0.5f} },
			{ {  length, -length, length },  {0.0f, 0.0f, 1.0f }, {0.333333f, 0.0f} },
			{ { -length, -length, length },  {0.0f, 0.0f, 1.0f }, {0.0f, 0.0f}      },
			{ { -length,  length, length },  {0.0f, 0.0f, 1.0f }, {0.0f, 0.5f}      },

			{ {  length,  length, -length }, {0.0f, 0.0f, -1.0f}, {0.333333f, 0.5f} },
			{ {  length, -length, -length }, {0.0f, 0.0f, -1.0f}, {0.333333f, 0.0f} },
			{ { -length, -length, -length }, {0.0f, 0.0f, -1.0f}, {0.666666f, 0.0f} },
			{ { -length,  length, -length }, {0.0f, 0.0f, -1.0f}, {0.666666f, 0.5f} },

			{ {  length,  length, length },  { 1.0f, 0.0f, 0.0f}, {1.0f, 0.5f}      },
			{ {  length, -length, length },  { 1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}      },
			{ {  length,  length, -length }, { 1.0f, 0.0f, 0.0f}, {0.666666f, 0.5f} },
			{ {  length, -length, -length }, { 1.0f, 0.0f, 0.0f}, {0.666666f, 0.0f} },

			{ { -length, -length, length },  {-1.0f, 0.0f, 0.0f}, {0.0f, 0.5f}      },
			{ { -length,  length, length },  {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}      },
			{ { -length, -length, -length }, {-1.0f, 0.0f, 0.0f}, {0.333333f, 0.5f} },
			{ { -length,  length, -length }, {-1.0f, 0.0f, 0.0f}, {0.333333f, 1.0f} },

			{ {  length,  length, length },  {0.0f,  1.0f, 0.0f}, {0.333333f, 0.5f} },
			{ { -length,  length, length },  {0.0f,  1.0f, 0.0f}, {0.666666f, 0.5f} },
			{ {  length,  length, -length }, {0.0f,  1.0f, 0.0f}, {0.333333f, 1.0f} },
			{ { -length,  length, -length }, {0.0f,  1.0f, 0.0f}, {0.666666f, 1.0f} },

			{ {  length, -length, length },  {0.0f, -1.0f, 0.0f}, {0.666666f, 0.5f} },
			{ { -length, -length, length },  {0.0f, -1.0f, 0.0f}, {1.0f, 0.5f}      },
			{ {  length, -length, -length }, {0.0f, -1.0f, 0.0f}, {0.666666f, 1.0f} },
			{ { -length, -length, -length }, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}      }
		};
		index =
		{
			// 앞면
			0, 3, 1, 1, 3, 2,
			// 뒷면
			4, 5, 6, 4, 6, 7,

			// 왼쪽면
			13, 14, 12, 13, 15, 14,
			// 오른쪽면
			8, 9, 11, 8, 11, 10,

			// 윗면
			16, 19, 17, 16, 18, 19,
			// 아랫면
			20, 21, 23, 20, 23, 22
		};
	}
	else if (type == Type::squarePyramid)
	{
		const float length = 1.0f;
		vertices =
		{
			// 앞,뒤, 좌, 우, 상, 하
			{ {  0.0f,  length, 0.0f },		 {0.0f, 0.0f, 1.0f }, {0.333333f, 0.5f} },
			{ {  length, -length, length },  {0.0f, 0.0f, 1.0f }, {0.333333f, 0.0f} },
			{ { -length, -length, length },  {0.0f, 0.0f, 1.0f }, {0.0f, 0.0f}      },
			{ { -0.0f,  length, 0.0f },		 {0.0f, 0.0f, 1.0f }, {0.0f, 0.5f}      },
			{ {  0.0f,  length, -0.0f },	 {0.0f, 0.0f, -1.0f}, {0.333333f, 0.5f} },
			{ {  length, -length, -length }, {0.0f, 0.0f, -1.0f}, {0.333333f, 0.0f} },
			{ { -length, -length, -length }, {0.0f, 0.0f, -1.0f}, {0.666666f, 0.0f} },
			{ { -0.0f,  length, -0.0f },	 {0.0f, 0.0f, -1.0f}, {0.666666f, 0.5f} },
			{ {  0.0f,  length, 0.0f },		 { 1.0f, 0.0f, 0.0f}, {1.0f, 0.5f}      },
			{ {  length, -length, length },  { 1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}      },
			{ {  0.0f,  length, -0.0f },	 { 1.0f, 0.0f, 0.0f}, {0.666666f, 0.5f} },
			{ {  length, -length, -length }, { 1.0f, 0.0f, 0.0f}, {0.666666f, 0.0f} },
			{ { -length, -length, length },  {-1.0f, 0.0f, 0.0f}, {0.0f, 0.5f}      },
			{ { -0.0f,  length, 0.0f },		 {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}      },
			{ { -length, -length, -length }, {-1.0f, 0.0f, 0.0f}, {0.333333f, 0.5f} },
			{ { -0.0f,  length, -0.0f },	 {-1.0f, 0.0f, 0.0f}, {0.333333f, 1.0f} },
			{ {  0.0f,  length, 0.0f },		 {0.0f,  1.0f, 0.0f}, {0.333333f, 0.5f} },
			{ { -0.0f,  length, 0.0f },		 {0.0f,  1.0f, 0.0f}, {0.666666f, 0.5f} },
			{ {  0.0f,  length, -0.0f },	 {0.0f,  1.0f, 0.0f}, {0.333333f, 1.0f} },
			{ { -0.0f,  length, -0.0f },	 {0.0f,  1.0f, 0.0f}, {0.666666f, 1.0f} },
			{ {  length, -length, length },  {0.0f, -1.0f, 0.0f}, {0.666666f, 0.5f} },
			{ { -length, -length, length },  {0.0f, -1.0f, 0.0f}, {1.0f, 0.5f}      }, 
			{ {  length, -length, -length }, {0.0f, -1.0f, 0.0f}, {0.666666f, 1.0f} },
			{ { -length, -length, -length }, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}      }
		};
		index =
		{
			// 앞면
			0, 3, 1, 1, 3, 2,
			// 뒷면
			4, 5, 6, 4, 6, 7,

			// 왼쪽면
			13, 14, 12, 13, 15, 14,
			// 오른쪽면
			8, 9, 11, 8, 11, 10,

			// 윗면
			16, 19, 17, 16, 18, 19,
			// 아랫면
			20, 21, 23, 20, 23, 22
		};
	}
	else if (type == Type::square)
	{
		vertices =
		{
			{ {  1.0f, -1.0f,  1.0f},  {0.0f, -1.0f, 0.0f}, {0.666666f, 0.5f} },
			{ { -1.0f, -1.0f,  1.0f},  {0.0f, -1.0f, 0.0f}, {1.0f, 0.5f}      },
			{ {  1.0f, -1.0f, -1.0f }, {0.0f, -1.0f, 0.0f}, {0.666666f, 1.0f} },
			{ { -1.0f, -1.0f, -1.0f }, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}      }
		};
		index =
		{
			0, 1, 3, 1, 3, 2
		};
	}
}
