#include "Mountain.h"

Mountain::Mountain(float length, int row, int col)
{
	base = new Rect(length, glm::vec3(0.2f,0.1f,0.03f));
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
