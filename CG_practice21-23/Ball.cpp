#include "Ball.h"

Ball::Ball(GLdouble rad, float x, float y, float z)
	: radius(rad), pos(glm::vec3(x, y, z))
{
	obj = gluNewQuadric();
	moveDir.x = urd(gen) - 0.5f;
	moveDir.y = urd(gen) - 0.5f;

	colors[0] = 0.8f + urd(gen) * 0.2f;
	colors[1] = 0.8f + urd(gen) * 0.2f;
	colors[2] = 0.8f + urd(gen) * 0.2f;
}

Ball::~Ball()
{
	gluDeleteQuadric(obj);
}

void Ball::update()
{
	pos.y -= urd(gen) * 0.05f;
	if (pos.y <= 0.0f)
	{
		pos.y = 10.0f;
	}
}

void Ball::draw(GLuint shaderProgram, DrawType drawType) const
{
	glUseProgram(shaderProgram);

	glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);
	GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	int obj_colorLocation = glGetUniformLocation(shaderProgram, "obj_color");
	glUniform3f(obj_colorLocation, colors[0], colors[1], colors[2]);

	if (drawType == DrawType::DRAW_SOLID)		gluQuadricDrawStyle(obj, GLU_FILL);
	else if (drawType == DrawType::DRAW_WIRE)		gluQuadricDrawStyle(obj, GLU_LINE);
	else if (drawType == DrawType::DRAW_SILHOUETTE)	gluQuadricDrawStyle(obj, GLU_SILHOUETTE);
	else if (drawType == DrawType::DRAW_POINT)		gluQuadricDrawStyle(obj, GLU_POINT);

	gluSphere(obj, radius, slices, stacks);
}