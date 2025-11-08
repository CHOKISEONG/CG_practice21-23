#include "Ball.h"

Ball::Ball(GLdouble rad, float x, float y, float z)
	: radius(rad), pos(glm::vec3(x, y, z))
{
	obj = gluNewQuadric();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> zeroToOne(0.0f,1.0f);
	moveDir.x = zeroToOne(gen) - 0.5f;
	moveDir.y = zeroToOne(gen) - 0.5f;

	colors[0] = zeroToOne(gen);
	colors[1] = zeroToOne(gen);
	colors[2] = zeroToOne(gen);
}

Ball::~Ball()
{
	gluDeleteQuadric(obj);
}

bool Ball::isBallInPolygon(const std::vector<glm::vec3> rectPoints)
{
	for (int i = 0; i < 4; ++i) {
		glm::vec2 p1 = rectPoints[i];
		glm::vec2 p2 = rectPoints[(i + 1) % 4];

		glm::vec2 edge = p2 - p1;
		glm::vec2 toBall = glm::vec2(pos.x, pos.y) - p1;

		float t = glm::clamp(glm::dot(toBall, edge) / glm::dot(edge, edge), 0.0f, 1.0f);
		glm::vec2 closest = p1 + t * edge;

		float dist = glm::distance(glm::vec2(pos.x, pos.y), closest);

		if (dist < radius) {
			return true;
		}
	}
	return false;
}

void Ball::update(const std::vector<glm::vec3> rectPoints)
{
	pos.x += moveDir.x / 40;
	pos.y += moveDir.y / 40;

	if (isBallInPolygon(rectPoints)) {
		glm::vec2 toCenter = -glm::vec2(pos.x, pos.y);
		if (glm::length(toCenter) > 0.0001f) {
			glm::vec2 dir = glm::normalize(toCenter);
			moveDir.x = dir.x * glm::length(moveDir);
			moveDir.y = dir.y * glm::length(moveDir);
		}
	}
}

void Ball::draw(GLuint shaderProgram, DrawType drawType) const
{
	glUseProgram(shaderProgram);

	glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);
	GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	if (drawType == DrawType::DRAW_SOLID)		gluQuadricDrawStyle(obj, GLU_FILL);
	else if (drawType == DrawType::DRAW_WIRE)		gluQuadricDrawStyle(obj, GLU_LINE);
	else if (drawType == DrawType::DRAW_SILHOUETTE)	gluQuadricDrawStyle(obj, GLU_SILHOUETTE);
	else if (drawType == DrawType::DRAW_POINT)		gluQuadricDrawStyle(obj, GLU_POINT);

	glPushMatrix();

	glTranslatef(pos.x, pos.y, pos.z);
	glColor3f(colors[0], colors[1], colors[2]);
	gluSphere(obj, radius, slices, stacks);

	glPopMatrix();
}