#include "Ball.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> coordinate(-90, 90);
std::uniform_int_distribution<int> boool(0, 1);

Ball::Ball()
{
	allReset();
	obj = gluNewQuadric();
}

void Ball::allReset()
{
	xDir = boool(gen), zDir = boool(gen);
	xPos = coordinate(gen) / 100.0f, yPos = coordinate(gen) / 100.0f, zPos = coordinate(gen) / 100.0f;
}

void Ball::update(bool opened)
{
	if (xDir) {
		if (opened) {
			xPos += 0.01f;
		}
		else if (xPos + 0.1f + 0.01f >= 1.0f) {
			xDir = false;
			xPos = 0.99f;
		}
		else {
			xPos += 0.01f;
		}
	}
	else {
		if (xPos - 0.1f - 0.01f <= -1.0f) {
			xDir = true;
			xPos = -0.99f;
		}
		else {
			xPos -= 0.01f;
		}
	}
	if (zDir) {
		if (opened) {
			zPos += 0.01f;
		}
		else if (zPos + 0.1f + 0.01f >= 1.0f) {
			zDir = false;
			zPos = 0.99f;
		}
		else {
			zPos += 0.01f;
		}
	}
	else {
		if (zPos - 0.1f - 0.01f <= -1.0f) {
			zDir = true;
			zPos = -0.99f;
		}
		else {
			zPos -= 0.01f;
		}
	}
}

void Ball::draw()
{
	//gluDeleteQuadric(obj);
	gluQuadricDrawStyle(obj, GLU_FILL);
	gluSphere(obj, 0.1, 30, 30);
}

void Ball::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::translate(myFactor, glm::vec3(xPos, yPos, zPos));
}

glm::mat4 Ball::getFactor()
{
	return myFactor;
}