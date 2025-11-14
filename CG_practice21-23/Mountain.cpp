#include "Mountain.h"

Mountain::Mountain(float length, int row, int col)
{
	base = new Rect(length, glm::vec3(0.2f,0.1f,0.03f));
	
	int treeIdx = 0;
	const float width = length / row;
	const float height = length / col;

	for (float i{-length}; i < length; i += 2 * width)
	{
		for (float j{ -length}; j < length; j += 2 * height)
		{
			trees.push_back(new Cube(width, height, glm::vec3(urd(gen),urd(gen),urd(gen))));
			trees[treeIdx++]->move(glm::vec3(i + width, 0.0f, j + height));
		}
	}
}

void Mountain::update()
{
	if (isTreeMove)
	{
		for (auto& tree : trees)
		{
			tree->changeHeight();
			tree->updateHeight();
		}
	}
	
}

void Mountain::draw(GLuint shaderProgram)
{
	if (drawBase)
	{
		base->Draw(shaderProgram);
	}
		
	for (const auto& tree : trees)
	{
		tree->Draw(shaderProgram);
	}
}

void Mountain::changeSpeed(float amount)
{
	for (auto& tree : trees)
	{
		tree->changeSpeed(amount);
	}
}