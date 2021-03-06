#pragma once
#include "stdafx.h"
struct Crane_Lefthand
{
	GLfloat data[6][2][2][3][3];
	GLuint vao[6], vbo[6][2];
	GLfloat HeightFromGround;
	glm::mat4 myFactor;

	GLuint rMove;
	GLfloat rMovePos;

	Crane_Lefthand();
	void initBuffer();
	void draw();

	void putFactor(glm::mat4 inputFactor);
	glm::mat4 getFactor();

	void allReset();
	void update();
};

