#pragma once
#include "stdafx.h"

struct Field
{
	GLfloat data[2][2][3][3];
	GLuint vao, vbo[2];
	glm::mat4 myFactor;

	GLint xPos, zPos;

	Field();
	void initBuffer();
	void draw();

	void add_data(GLint xPos, GLint zPos);

	void putFactor(glm::mat4 inputFactor);
	glm::mat4 getFactor();
};

