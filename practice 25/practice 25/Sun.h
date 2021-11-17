#pragma once
#include "stdafx.h"

struct Sun
{
	GLuint object;
	GLuint vao[3], vbo[3][2];

	int objColorLocation;

	glm::mat4 myFactor;
	Sun();

	void initBuffer(int s_program);
	void draw();

	void allReset();					// ��� ������ �ʱ�ȭ�մϴ�. �����ڿ����� ȣ���ϸ�, ��Ÿ �ʿ��� �� ȣ���մϴ�.
	void update();						// ��ü�� ������ ������Ʈ�մϴ�.

	void putFactor(glm::mat4 inputFactor);	// �̵� ������ �ٲߴϴ�.
	glm::mat4 getFactor();					// �̵� ������ ��ȯ�մϴ�.
};