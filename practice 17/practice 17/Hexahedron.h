#pragma once
#include "stdafx.h"

struct Hexahedron {
	GLfloat data[6][2][2][3][3];
	GLuint vao[6], vbo[6][2];

	Hexahedron();
	void initBuffer();
};

