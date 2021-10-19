#include "stdafx.h"
#include "Line.h"

Line::Line(GLfloat sx, GLfloat sy, GLfloat sz, GLfloat ex, GLfloat ey, GLfloat ez, int setColor) 
{
	data[0][0][0] = sx, data[0][0][1] = sy, data[0][0][2] = sz;		// 위치
	data[0][1][0] = ex, data[0][1][1] = ey, data[0][1][2] = ez;

	if (setColor == 0) {
		data[1][0][0] = 0.0f, data[1][0][1] = 0.0f, data[1][0][2] = 0.0f;		// 색상
		data[1][1][0] = 0.0f, data[1][1][1] = 0.0f, data[1][1][2] = 0.0f;
	}
	else if (setColor == 1) {
		data[1][0][0] = 1.0f, data[1][0][1] = 0.0f, data[1][0][2] = 0.0f;		// 색상
		data[1][1][0] = 1.0f, data[1][1][1] = 0.0f, data[1][1][2] = 0.0f;
	}
	else if (setColor == 2) {
		data[1][0][0] = 0.0f, data[1][0][1] = 1.0f, data[1][0][2] = 0.0f;		// 색상
		data[1][1][0] = 0.0f, data[1][1][1] = 1.0f, data[1][1][2] = 0.0f;
	}
	else if (setColor == 3) {
		data[1][0][0] = 0.0f, data[1][0][1] = 0.0f, data[1][0][2] = 1.0f;		// 색상
		data[1][1][0] = 0.0f, data[1][1][1] = 0.0f, data[1][1][2] = 1.0f;
	}
}

void Line::initBuffer()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(2, vbo);
	for (int i = 0; i < 2; i++) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), data[i], GL_STATIC_DRAW);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(i);
	}
}