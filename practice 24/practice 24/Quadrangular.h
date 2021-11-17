#pragma once
#include "stdafx.h"

struct Quadrangular
{
	GLfloat data[6][2][3][3];
	GLuint vao[6], vbo[6][2];

	glm::mat4 myFactor;
	glm::mat4 myLFactor;
	glm::mat4 myRFactor;
	glm::mat4 myFFactor;
	glm::mat4 myBFactor;

	int objColorLocation;

	////////////////////////////////////////////////////////////////////////
	// ��Ÿ �ʿ��� ������ ����
	bool drawed;
	bool rotate;
	GLfloat rotatePos;
	bool open;
	GLfloat openPos;
	////////////////////////////////////////////////////////////////////////

	Quadrangular();

	void initBuffer(GLuint s_program);
	void draw();						// ������ �׸��ϴ�.

	void allReset();					// ��� ������ �ʱ�ȭ�մϴ�. �����ڿ����� ȣ���ϸ�, ��Ÿ �ʿ��� �� ȣ���մϴ�.
	void update();						// ��ü�� ������ ������Ʈ�մϴ�.

	void putFactor(glm::mat4 inputFactor);	// �̵� ������ �ٲߴϴ�.
	glm::mat4 getFactor();					// �̵� ������ ��ȯ�մϴ�.

	void rdraw();
	void fdraw();
	void ldraw();
	void bdraw();
};

