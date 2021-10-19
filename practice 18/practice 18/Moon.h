#pragma once
#include "stdafx.h"

#define M_PI 3.1415926535897932384626433832795

struct Moon
{
	GLint i;
	GLfloat a, b, c;
	GLfloat r, translatePosX, translatePosY, translatePosZ;
	GLUquadricObj* obj;
	Moon();
	void drawSolid();
	void drawWire();
	void updateS();
	void updateM();
	void updateH();
};

