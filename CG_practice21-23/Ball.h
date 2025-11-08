#pragma once
#pragma once

#include "header.h"
#include "Cube.h"


enum DrawType
{
    DRAW_SOLID,
    DRAW_WIRE,
    DRAW_SILHOUETTE,
    DRAW_POINT
};

class Ball
{
    GLUquadric* obj;

    glm::vec3 pos;      // 구의 위치
    GLdouble radius;    // 구의 반지름
    int slices = 20;
    int stacks = 20;

    glm::vec3 moveDir;
public:
    Ball(GLdouble rad = 1.0, float x = 0.0f, float y = 0.0f, float z = 0.0f);
    ~Ball();

    const glm::vec3 getPos() const { return pos; }
    bool isBallInPolygon(const std::vector<glm::vec3> rectPoints);

    void update(const std::vector<glm::vec3> rectPoints);

    void draw(GLuint shaderProgram, DrawType drawType) const;
};