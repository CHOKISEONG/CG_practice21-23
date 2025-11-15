#include "Camera.h"

void Camera::settingCamera(GLuint shaderProgram)
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(pos, direction, up);

	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection = glm::mat4(1.0f);

	if (viewType == "perspective")
	{
		projection = glm::perspective(fovy, width / height, zNear, zFar);
	}
	else if (viewType == "ortho")
	{
		projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -100.0f, 100.0f);
	}

	unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	unsigned int viewPosLocation = glGetUniformLocation(shaderProgram, "viewPos");
	glUniform3f(viewPosLocation, pos.x, pos.y, pos.z);
}

void Camera::update(Character* character)
{
	glm::vec3 dir = character->getDir();

	if (camType == std::string("firstPerson"))
	{
		if (dir != glm::vec3(0.0f, 0.0f, 0.0f))
		{
			pos = character->getPos()  + glm::vec3(0.0f, 0.4f, 0.0f);
			direction = character->getPos() + dir + glm::vec3(0.0f, 0.4f, 0.0f);
		}
	}
	else if (camType == std::string("thirdPerson"))
	{
		if (dir != glm::vec3(0.0f, 0.0f, 0.0f))
		{
			pos = character->getPos() + glm::vec3(0.0f, 3.0f, 3.0f);
			direction = character->getPos();
		}
	}
}

void Camera::rotate(float theta, glm::vec3 axis)
{
	glm::vec3 look = direction - pos;
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(theta), axis);
	look = glm::vec3(rotation * glm::vec4(look, 1.0f));
	direction = pos + look;
}

void Camera::rotateFromView(float theta, glm::vec3 axis)
{
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(theta), axis);
	pos = glm::vec3(rotation * glm::vec4(pos, 1.0f));
}
