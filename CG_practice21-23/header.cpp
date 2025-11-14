#include "header.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> urd(0.0f,1.0f);
std::uniform_int_distribution<int> uid(0, 10000);