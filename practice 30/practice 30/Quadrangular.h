#pragma once
#include "stdafx.h"

struct Quadrangular
{
	GLfloat data[6][2][3][3];
	GLfloat texture_data[6][3][2];
	GLuint vao[6], vbo[6][2];
	unsigned int texture[6];
	unsigned char* image[6];

	glm::mat4 myFactor;

	int objColorLocation;
	int tLocation;

	////////////////////////////////////////////////////////////////////////
	// ��Ÿ �ʿ��� ������ ����
	bool drawed;
	bool Xrotate, Yrotate;
	GLfloat XrotatePos, YrotatePos;
	////////////////////////////////////////////////////////////////////////

	Quadrangular();
	void initBuffer(GLuint s_program);
	void initTexture(GLint s_program);
	void draw();						// ������ �׸��ϴ�.

	void allReset();					// ��� ������ �ʱ�ȭ�մϴ�. �����ڿ����� ȣ���ϸ�, ��Ÿ �ʿ��� �� ȣ���մϴ�.
	void update();						// ��ü�� ������ ������Ʈ�մϴ�.

	void putFactor(glm::mat4 inputFactor);	// �̵� ������ �ٲߴϴ�.
	glm::mat4 getFactor();					// �̵� ������ ��ȯ�մϴ�.
};

