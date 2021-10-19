#include "stdafx.h"
#include "s_Orbit.h"

s_Orbit::s_Orbit()
{
	r = 0.25f;
	for (int i = 0; i < 20; i++) {
		data[i][0][0][0] = (GLfloat)(r * glm::cos(2 * M_PI / 20 * i));
		data[i][0][0][1] = 0.0f;
		data[i][0][0][2] = (GLfloat)(r * glm::sin(2 * M_PI / 20 * i));

		data[i][0][1][0] = (GLfloat)(r * glm::cos(2 * M_PI / 20 * (i + 1)));
		data[i][0][1][1] = 0.0f;
		data[i][0][1][2] = (GLfloat)(r * glm::sin(2 * M_PI / 20 * (i + 1)));

		data[i][1][0][0] = 1.0f;
		data[i][1][0][1] = 1.0f;
		data[i][1][0][2] = 1.0f;

		data[i][1][1][0] = 1.0f;
		data[i][1][1][1] = 1.0f;
		data[i][1][1][2] = 1.0f;
	}
}

void s_Orbit::initBuffer()
{
	glGenVertexArrays(20, vao);
	for (int i = 0; i < 20; i++) {
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

void s_Orbit::draw()
{
	for (int i = 0; i < 20; i++) {
		glBindVertexArray(vao[i]);
		glDrawArrays(GL_LINES, 0, 2);
	}
}

