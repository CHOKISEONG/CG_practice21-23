#include "stb_image.h"
#include "Background.h"

Background::Background(const char* filename)
{
	vertices =
	{
		{ {  1.0f,  1.0f, 0.99f }, {1.0f, 1.0f} },
		{ {  1.0f, -1.0f, 0.99f }, {1.0f, 0.0f} },
		{ { -1.0f, -1.0f, 0.99f }, {0.0f, 0.0f} },
		{ { -1.0f,  1.0f, 0.99f }, {0.0f, 1.0f} }
	};

	index =
	{
		0, 3, 1, 1, 3, 2
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(BG), vertices.data(), GL_STATIC_DRAW);

	// 위치 (location = 0)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BG), (void*)offsetof(BG, pos));
	glEnableVertexAttribArray(0);

	// 텍스쳐 (location = 2)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BG), (void*)offsetof(BG, texture));
	glEnableVertexAttribArray(2);

	// index 연결하기
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), index.data(), GL_STATIC_DRAW);
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(filename, &width, &height, &numberOfChannel, 0);
	if (!data)
	{
		std::cerr << "Failed to load texture: " << filename << std::endl;
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

void Background::Draw(GLuint shaderProgram)
{ 
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	// 텍스처 활성/바인딩 및 샘플러 설정
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	GLint samplerLoc = glGetUniformLocation(shaderProgram, "outTexture");
	glUniform1i(samplerLoc, 0);

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(index.size()), GL_UNSIGNED_INT, 0);
}
