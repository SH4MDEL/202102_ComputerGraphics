#include "stdafx.h"
#include "Line.h"

Line::Line() 
{
	data[0][0][0][0] = -1.0f, data[0][0][0][1] = 0.0f, data[0][0][0][2] = 0.0f;		// 위치
	data[0][0][1][0] = 1.0f, data[0][0][1][1] = 0.0f, data[0][0][1][2] = 0.0f;

	data[0][1][0][0] = 0.0f, data[0][1][0][1] = 1.0f, data[0][1][0][2] = 0.0f;
	data[0][1][1][0] = 0.0f, data[0][1][1][1] = 1.0f, data[0][1][1][2] = 0.0f;

	data[1][0][0][0] = 0.0f, data[1][0][0][1] = -1.0f, data[1][0][0][2] = 0.0f;		// 위치
	data[1][0][1][0] = 0.0f, data[1][0][1][1] = 1.0f, data[1][0][1][2] = 0.0f;

	data[1][1][0][0] = 0.0f, data[1][1][0][1] = 1.0f, data[1][1][0][2] = 0.0f;
	data[1][1][1][0] = 0.0f, data[1][1][1][1] = 1.0f, data[1][1][1][2] = 0.0f;

	data[2][0][0][0] = 0.0f, data[2][0][0][1] = 0.0f, data[2][0][0][2] = -1.0f;		// 위치
	data[2][0][1][0] = 0.0f, data[2][0][1][1] = 0.0f, data[2][0][1][2] = 1.0f;
	
	data[2][1][0][0] = 0.0f, data[2][1][0][1] = 1.0f, data[2][1][0][2] = 0.0f;
	data[2][1][1][0] = 0.0f, data[2][1][1][1] = 1.0f, data[2][1][1][2] = 0.0f;

}

void Line::initBuffer()
{
	glGenVertexArrays(3, vao);
	for (int i = 0; i < 3; i++) {
		glBindVertexArray(vao[i]);
		glGenBuffers(2, vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}
}

void Line::draw()
{
	for (int i = 0; i < 3; i++) {
		glBindVertexArray(vao[i]);
		glDrawArrays(GL_LINES, 0, 2);
	}
}