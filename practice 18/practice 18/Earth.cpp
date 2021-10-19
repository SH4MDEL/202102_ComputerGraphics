#include "Earth.h"

Earth::Earth()
{
	r = 0.7;
	translatePosX = 0.0f, translatePosY = 0.0f, translatePosZ = 0.0f;
	obj = gluNewQuadric();
}

void Earth::drawSolid()
{
	//gluDeleteQuadric(obj);
	gluQuadricDrawStyle(obj, GLU_FILL);
	gluSphere(obj, 0.1, 30, 30);
}

void Earth::drawWire()
{
	//gluDeleteQuadric(obj);
	gluQuadricDrawStyle(obj, GLU_LINE);
	gluSphere(obj, 0.1, 30, 30);
}

void Earth::updateS()
{
	i++;
	translatePosX = (GLfloat)(0.7 * glm::cos(2 * M_PI / 20 * 0.1 * i));
	translatePosZ = (GLfloat)(0.7 * glm::sin(2 * M_PI / 20 * 0.1 * i));
}

void Earth::updateM()
{
	i++;
	translatePosX = (GLfloat)(0.7 * glm::cos(2 * M_PI / 20 * 0.15 * i));
	translatePosZ = (GLfloat)(0.7 * glm::sin(2 * M_PI / 20 * 0.15 * i));
}

void Earth::updateH()
{
	i++;
	translatePosX = (GLfloat)(0.7 * glm::cos(2 * M_PI / 20 * 0.2 * i));
	translatePosZ = (GLfloat)(0.7 * glm::sin(2 * M_PI / 20 * 0.2 * i));
}
