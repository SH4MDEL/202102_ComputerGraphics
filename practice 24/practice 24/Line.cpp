#include "stdafx.h"
#include "Line.h"

Line::Line(int setColor)
{
	if (setColor == 0) {
		data[0][0][0] = -2.0f, data[0][0][1] = 0.0f, data[0][0][2] = 0.0f;		// 위치
		data[0][1][0] = 2.0f, data[0][1][1] = 0.0f, data[0][1][2] = 0.0f;

		data[1][0][0] = 0.0f, data[1][0][1] = 0.0f, data[1][0][2] = 0.0f;		// 색상
		data[1][1][0] = 0.0f, data[1][1][1] = 0.0f, data[1][1][2] = 0.0f;
	}
	else if (setColor == 1) {
		data[0][0][0] = -2.0f, data[0][0][1] = 0.0f, data[0][0][2] = 0.0f;		// 위치
		data[0][1][0] = 2.0f, data[0][1][1] = 0.0f, data[0][1][2] = 0.0f;

		data[1][0][0] = 1.0f, data[1][0][1] = 0.0f, data[1][0][2] = 0.0f;		// 색상
		data[1][1][0] = 1.0f, data[1][1][1] = 0.0f, data[1][1][2] = 0.0f;
	}
	else if (setColor == 2) {
		data[0][0][0] = 0.0f, data[0][0][1] = -2.0f, data[0][0][2] = 0.0f;		// 위치
		data[0][1][0] = 0.0f, data[0][1][1] = 2.0f, data[0][1][2] = 0.0f;

		data[1][0][0] = 0.0f, data[1][0][1] = 1.0f, data[1][0][2] = 0.0f;		// 색상
		data[1][1][0] = 0.0f, data[1][1][1] = 1.0f, data[1][1][2] = 0.0f;
	}
	else if (setColor == 3) {
		data[0][0][0] = 0.0f, data[0][0][1] = 0.0f, data[0][0][2] = -2.0f;		// 위치
		data[0][1][0] = 0.0f, data[0][1][1] = 0.0f, data[0][1][2] = 2.0f;

		data[1][0][0] = 0.0f, data[1][0][1] = 0.0f, data[1][0][2] = 1.0f;		// 색상
		data[1][1][0] = 0.0f, data[1][1][1] = 0.0f, data[1][1][2] = 1.0f;
	}
}

void Line::initBuffer(GLuint s_program)
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

void Line::allReset()
{

}

void Line::update()
{

}

void Line::draw()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, 2);
}

void Line::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
}

glm::mat4 Line::getFactor() 
{
	return myFactor;
}
