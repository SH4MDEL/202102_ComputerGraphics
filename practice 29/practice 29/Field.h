#pragma once
#include "stdafx.h"

struct Field
{
	GLfloat data[2][2][3][3];
	GLuint vao, vbo[2];
	glm::mat4 myFactor;

	int objColorLocation;

	Field();
	void initBuffer(GLuint s_program);
	void draw();

	void putFactor(glm::mat4 inputFactor);
	glm::mat4 getFactor();
};

