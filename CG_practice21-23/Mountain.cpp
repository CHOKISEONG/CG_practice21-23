#include "Mountain.h"

Mountain::Mountain(float length, int _row, int _col)
{
	row = _row;
	col = _col;
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

void Mountain::changeToMaze()
{
	drawBase = true;

	// 일단 중간 길 뚫어서 풀 수 있는 미로를 만들고
	int max = (row > col) ? row : col;
	trees.erase(trees.end() - (col * row) / 2);
	for (int i{}; i < max; ++i)
	{
		trees.erase(trees.end() - (col * row) / 2);
		trees.erase(trees.end() - (col * row) / 2 + max);
	}
	// 나머지 중에 랜덤으로 좀 지움
	if (max > 10)
	{
		for (int i{}; i < static_cast<int>(trees.size()) / 2; ++i)
		{
			trees.erase(trees.begin() + uid(gen) % trees.size());
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