#include "Mountain.h"

Mountain::Mountain(float length, int row, int col)
{
	base = new Rect(length, glm::vec3(0.2f,0.1f,0.03f));
	
	int treeIdx = 0;
	const float radius = length / row;
	for (float i{-length}; i < length; i += 2 * length / row)
	{
		for (float j{ -length}; j < length; j += 2 * length / col)
		{
			trees.push_back(new Cube(length / row, length / col, glm::vec3(urd(gen),urd(gen),urd(gen))));
			trees[treeIdx++]->move(glm::vec3(i + length / row, 0.0f, j + length / col));
		}
	}
}

void Mountain::update()
{
	for (auto& tree : trees)
	{
		tree->changeHeight(urd(gen) / 100);
		tree->updateHeight();
	}
}

void Mountain::draw(GLuint shaderProgram)
{
	base->Draw(shaderProgram);
	for (const auto& tree : trees)
	{
		tree->Draw(shaderProgram);
	}
}
