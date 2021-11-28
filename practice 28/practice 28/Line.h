#pragma once
#include "stdafx.h"

struct Line {
	GLfloat data[3][2][2][3];
	GLuint vao[3], vbo[3][2];

	Line();
	void initBuffer();
	void draw();
};

