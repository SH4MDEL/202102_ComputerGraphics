#pragma once
#include "stdafx.h"

struct Line {
	GLfloat data[2][2][3];
	GLuint vao, vbo[2];

	Line(GLfloat sx, GLfloat sy, GLfloat sz, GLfloat ex, GLfloat ey, GLfloat ez, int setColor);
	void initBuffer();
};

