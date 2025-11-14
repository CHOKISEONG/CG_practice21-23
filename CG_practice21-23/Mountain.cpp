#include "Mountain.h"

Mountain::Mountain(float length, int row, int col)
{
	base = new Rect(length, glm::vec3(0.0f,1.0f,1.0f));
	for (float i{-length}; i < float(row); i += 2 * length / row)
	{
		for (float j{ -length}; j < float(row); j += 2 * length / row)
		{
			std::cout << i << ", " << j << "\n";
		}
	}
}

void Mountain::draw(GLuint shaderProgram)
{
	base->Draw(shaderProgram);
}
