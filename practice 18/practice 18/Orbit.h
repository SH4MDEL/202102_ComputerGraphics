#pragma once
#include "stdafx.h"

#define M_PI 3.1415926535897932384626433832795

struct Orbit
{
	GLfloat data[20][2][2][3];
	GLuint vao[20], vbo[20][2];
	GLfloat r;


	Orbit();
	void initBuffer();
	void draw();
};

