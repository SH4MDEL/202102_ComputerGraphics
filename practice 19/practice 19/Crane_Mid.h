#pragma once
#include "stdafx.h"
struct Crane_Mid
{
	GLfloat data[6][2][2][3][3];
	GLuint vao[6], vbo[6][2];
	GLfloat HeightFromGround;

	Crane_Mid();
	void initBuffer();
	void draw();

	glm::mat4 getFactor();
};

