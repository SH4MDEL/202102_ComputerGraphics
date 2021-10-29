#pragma once
#include "stdafx.h"

struct Field
{
	GLfloat data[2][2][3][3];
	GLuint vao, vbo[2];

	Field();
	void initBuffer();
	void draw();

	glm::mat4 getFactor();
};

