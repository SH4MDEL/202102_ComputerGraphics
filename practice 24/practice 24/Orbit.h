#pragma once
#include "stdafx.h"

#define M_PI 3.1415926535897932384626433832795

struct Orbit
{
	GLfloat data[20][2][2][3];
	GLuint vao[20], vbo[20][2];
	GLfloat r, scalePos;

	int objColorLocation;

	glm::mat4 myFactor;

	Orbit();

	void initBuffer(GLuint s_program);
	void draw();

	void allReset();					// ��� ������ �ʱ�ȭ�մϴ�. �����ڿ����� ȣ���ϸ�, ��Ÿ �ʿ��� �� ȣ���մϴ�.
	void update();						// ��ü�� ������ ������Ʈ�մϴ�.

	void putFactor(glm::mat4 inputFactor);	// �̵� ������ �ٲߴϴ�.
	glm::mat4 getFactor();
};

