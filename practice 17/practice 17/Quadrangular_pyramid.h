#pragma once
#include "stdafx.h"

struct Quadrangular_pyramid {
	GLfloat data[6][2][3][3];
	GLuint vao[6], vbo[6][2];

	Quadrangular_pyramid();
	void initBuffer();
};
