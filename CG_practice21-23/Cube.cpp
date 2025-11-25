#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
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
	else if (practiceNum == 25)
	{
		float length = 1.0f;

		// 정사각형 테스트
		vertices =
		{
			{ {  length,  length, length },  {0.0f, 0.0f, 1.0f }, {1.0f, 1.0f} },
			{ {  length, -length, length },  {0.0f, 0.0f, 1.0f }, {1.0f, 0.0f} },
			{ { -length, -length, length },  {0.0f, 0.0f, 1.0f }, {0.0f, 0.0f} },
			{ { -length,  length, length },  {0.0f, 0.0f, 1.0f }, {0.0f, 1.0f} },
			{ {  length,  length, -length }, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f} },
			{ {  length, -length, -length }, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f} },
			{ { -length, -length, -length }, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f} },
			{ { -length,  length, -length }, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f} },

			{ {  length,  length, length },  { 1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
			{ {  length, -length, length },  { 1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} },
			{ { -length, -length, length },  {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
			{ { -length,  length, length },  {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} },
			{ {  length,  length, -length }, { 1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} },
			{ {  length, -length, -length }, { 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
			{ { -length, -length, -length }, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} },
			{ { -length,  length, -length }, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },

			{ {  length,  length, length },  {0.0f,  1.0f, 0.0f}, {0.0f, 0.0f} },
			{ {  length, -length, length },  {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f} },
			{ { -length, -length, length },  {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f} },
			{ { -length,  length, length },  {0.0f,  1.0f, 0.0f}, {1.0f, 0.0f} },
			{ {  length,  length, -length }, {0.0f,  1.0f, 0.0f}, {0.0f, 1.0f} },
			{ {  length, -length, -length }, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f} },
			{ { -length, -length, -length }, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f} },
			{ { -length,  length, -length }, {0.0f,  1.0f, 0.0f}, {1.0f, 1.0f} }

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
	}

	initBuffer();

	// 텍스처 초기화 (stb_image 사용)
	initTexture();
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

	// 텍스쳐 (location = 2) - vec2로 수정
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
	glEnableVertexAttribArray(2);

	// index 연결하기
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), index.data(), GL_STATIC_DRAW);
}

void Cube::initTexture()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 이미지 로드 (PNG)
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load("A.png", &width, &height, &numberOfChannel, 0);
	if (!data)
	{
		std::cerr << "Failed to load texture: A.png" << std::endl;
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

GLubyte* Cube::LoadDIBitmap(const char* filename, BITMAPINFO** info)
{
	FILE* fp;
	GLubyte* bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	//--- 바이너리읽기모드로파일을연다
	if ((fopen_s(&fp, filename, "rb")) == NULL)
		return NULL;

	//--- 비트맵파일헤더를읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}

	//--- 파일이BMP 파일인지확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}

	//--- BITMAPINFOHEADER 위치로간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	//--- 비트맵이미지데이터를넣을메모리할당을한다.
	if ((*info = (BITMAPINFO*)malloc(infosize)) == NULL) {
		fclose(fp);
		return NULL;
	}

	//--- 비트맵인포헤더를읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	//--- 비트맵의크기설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth * (*info)->bmiHeader.biBitCount + 7) / 8.0 * abs((*info)->bmiHeader.biHeight);

	//--- 비트맵의크기만큼메모리를할당한다.
	if ((bits = (unsigned char*)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	//--- 비트맵데이터를bit(GLubyte 타입)에저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}

	fclose(fp);
	return bits;
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

	// 텍스처 활성/바인딩 및 샘플러 설정
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	GLint samplerLoc = glGetUniformLocation(shaderProgram, "outTexture");
	glUniform1i(samplerLoc, 0);

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
			{ {  length,  length, length },  {0.0f, 0.0f, 1.0f }, {1.0f, 1.0f} },
			{ {  length, -length, length },  {0.0f, 0.0f, 1.0f }, {1.0f, 0.0f} },
			{ { -length, -length, length },  {0.0f, 0.0f, 1.0f }, {0.0f, 0.0f} },
			{ { -length,  length, length },  {0.0f, 0.0f, 1.0f }, {0.0f, 1.0f} },
			{ {  length,  length, -length }, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f} },
			{ {  length, -length, -length }, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f} },
			{ { -length, -length, -length }, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f} },
			{ { -length,  length, -length }, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f} },
			{ {  length,  length, length },  { 1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
			{ {  length, -length, length },  { 1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} },
			{ { -length, -length, length },  {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
			{ { -length,  length, length },  {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} },
			{ {  length,  length, -length }, { 1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} },
			{ {  length, -length, -length }, { 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
			{ { -length, -length, -length }, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} },
			{ { -length,  length, -length }, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
			{ {  length,  length, length },  {0.0f,  1.0f, 0.0f}, {0.0f, 0.0f} },
			{ {  length, -length, length },  {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f} },
			{ { -length, -length, length },  {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f} },
			{ { -length,  length, length },  {0.0f,  1.0f, 0.0f}, {1.0f, 0.0f} },
			{ {  length,  length, -length }, {0.0f,  1.0f, 0.0f}, {0.0f, 1.0f} },
			{ {  length, -length, -length }, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f} },
			{ { -length, -length, -length }, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f} },
			{ { -length,  length, -length }, {0.0f,  1.0f, 0.0f}, {1.0f, 1.0f} }

		};
	}
	else if (type == Type::squarePyramid)
	{
		const float color = 1.0f;
		const float length = 1.0f;
		vertices =
		{
			// 앞,뒤, 좌, 우, 상, 하
			{ {  0.0f,  length, 0.0f },		 {0.0f, 0.0f, 1.0f }, {1.0f, 1.0f} },
			{ {  length, -length, length },  {0.0f, 0.0f, 1.0f }, {1.0f, 0.0f} },
			{ { -length, -length, length },  {0.0f, 0.0f, 1.0f }, {0.0f, 0.0f} },
			{ { -0.0f,  length, 0.0f },		 {0.0f, 0.0f, 1.0f }, {0.0f, 1.0f} },
			{ {  0.0f,  length, -0.0f },	 {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f} },
			{ {  length, -length, -length }, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f} },
			{ { -length, -length, -length }, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f} },
			{ { -0.0f,  length, -0.0f },	 {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f} },
			{ {  0.0f,  length, 0.0f },		 { 1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
			{ {  length, -length, length },  { 1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} },
			{ { -length, -length, length },  {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
			{ { -0.0f,  length, 0.0f },		 {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} },
			{ {  0.0f,  length, -0.0f },	 { 1.0f, 0.0f, 0.0f}, {0.0f, 1.0f} },
			{ {  length, -length, -length }, { 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
			{ { -length, -length, -length }, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f} },
			{ { -0.0f,  length, -0.0f },	 {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f} },
			{ {  0.0f,  length, 0.0f },		 {0.0f,  1.0f, 0.0f}, {0.0f, 0.0f} },
			{ {  length, -length, length },  {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f} },
			{ { -length, -length, length },  {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f} },
			{ { -0.0f,  length, 0.0f },		 {0.0f,  1.0f, 0.0f}, {1.0f, 0.0f} },
			{ {  0.0f,  length, -0.0f },	 {0.0f,  1.0f, 0.0f}, {0.0f, 1.0f} },
			{ {  length, -length, -length }, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f} },
			{ { -length, -length, -length }, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f} },
			{ { -0.0f,  length, -0.0f },	 {0.0f,  1.0f, 0.0f}, {1.0f, 1.0f} }

		};
	}
}
