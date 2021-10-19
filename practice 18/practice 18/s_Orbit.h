#pragma once
#include "stdafx.h"

#define M_PI 3.1415926535897932384626433832795

struct s_Orbit
{
	GLfloat data[20][2][2][3];
	GLuint vao[20], vbo[20][2];
	GLfloat r;


	s_Orbit();
	void initBuffer();
	void draw();
};

