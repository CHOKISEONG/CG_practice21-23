#include "Camera.h"

void Camera::settingCamera(GLuint shaderProgram)
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(pos, direction, up);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(fovy, width / height, zNear, zFar);

	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
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
