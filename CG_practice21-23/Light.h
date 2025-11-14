#pragma once

#include "header.h"
#include "Cube.h"

struct Light
{
public:
	Light(glm::vec3 _pos, glm::vec3 _color = glm::vec3(1.0f,1.0f,1.0f))
	{
		lightBox = new Cube(0.1f, 0.1f, glm::vec3(1.0f, 1.0f, 1.0f));
		lightBox->move(pos);
		pos = _pos;
		color = _color;
	}
	void turnOn() 
	{ 
		color = glm::vec3(1.0f);
	}
	void turnOff() 
	{ 
		color = glm::vec3(0.1f); 
	}

	void move(glm::vec3 v)
	{
		pos += v;
		lightBox->move(v);
	}
	void teleport(glm::vec3 v)
	{
		pos = v;
		lightBox->teleport(v);
	}

	void applyLight(GLuint shaderProgram)
	{
		unsigned int lightPosLocation = glGetUniformLocation(shaderProgram, "lightPos");
		glUniform3f(lightPosLocation, pos.x, pos.y, pos.z);

		int lightColorLocation = glGetUniformLocation(shaderProgram, "lightColor");
		glUniform3f(lightColorLocation, color.x, color.y, color.z);

		lightBox->Draw(shaderProgram);
	}

private:
	Cube* lightBox;
	glm::vec3 pos;
	glm::vec3 color;
};