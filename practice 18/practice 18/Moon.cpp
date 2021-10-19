#include "Moon.h"

Moon::Moon()
{
	r = 0.05;
	translatePosX = 0.0f, translatePosY = 0.0f, translatePosZ = 0.0f;
	obj = gluNewQuadric();
}

void Moon::drawSolid()
{
	//gluDeleteQuadric(obj);
	gluQuadricDrawStyle(obj, GLU_FILL);
	gluSphere(obj, 0.05, 30, 30);
}

void Moon::drawWire()
{
	//gluDeleteQuadric(obj);
	gluQuadricDrawStyle(obj, GLU_LINE);
	gluSphere(obj, 0.05, 30, 30);
}

void Moon::updateS()
{
	i++;
	translatePosX = (GLfloat)(0.25 * glm::cos(2 * M_PI / 20 * 0.08 * i));
	translatePosZ = (GLfloat)(0.25 * glm::sin(2 * M_PI / 20 * 0.08 * i));
}

void Moon::updateM()
{
	i++;
	translatePosX = (GLfloat)(0.25 * glm::cos(2 * M_PI / 20 * 0.14 * i));
	translatePosZ = (GLfloat)(0.25 * glm::sin(2 * M_PI / 20 * 0.14 * i));
}

void Moon::updateH()
{
	i++;
	translatePosX = (GLfloat)(0.25 * glm::cos(2 * M_PI / 20 * 0.18 * i));
	translatePosZ = (GLfloat)(0.25 * glm::sin(2 * M_PI / 20 * 0.18 * i));
}
