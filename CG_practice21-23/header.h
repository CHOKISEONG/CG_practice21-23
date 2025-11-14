#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <random>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <GL/glm/glm.hpp>
#include <GL/glm/ext.hpp>
#include <GL/glm/gtc/matrix_transform.hpp>

extern std::random_device rd;
extern std::mt19937 gen;
extern std::uniform_real_distribution<float> urd;
extern std::uniform_int_distribution<int> uid;

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec3 normal;
};