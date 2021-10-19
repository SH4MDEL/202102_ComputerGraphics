#include "Sun.h"

Sun::Sun()
{
	translatePosX = 0.0f, translatePosY = 0.0f, translatePosZ = 0.0f;
	rotate = false;
	rotatePos = 0.0f;
	obj = gluNewQuadric();
}

void Sun::drawSolid()
{
	//gluDeleteQuadric(obj);
	gluQuadricDrawStyle(obj, GLU_FILL);
	gluSphere(obj, 0.2, 30, 30);
}

void Sun::drawWire()
{
	//gluDeleteQuadric(obj);
	gluQuadricDrawStyle(obj, GLU_LINE);
	gluSphere(obj, 0.2, 30, 30);
}