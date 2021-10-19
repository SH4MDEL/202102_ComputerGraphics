#pragma once
#include "stdafx.h"

struct Sun
{
	GLfloat a, b, c;
	GLfloat translatePosX, translatePosY, translatePosZ;
	GLfloat rotatePos;
	bool rotate;
	GLUquadricObj* obj;
	Sun();
	void drawSolid();
	void drawWire();
};

