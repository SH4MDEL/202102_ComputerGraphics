#pragma once
#include "stdafx.h"

struct Line {
	GLfloat data[2][2][3];
	GLuint vao, vbo[2];

	glm::mat4 myFactor;

	Line(int setColor);

	void initBuffer(GLuint s_program);
	void draw();

	void allReset();					// ��� ������ �ʱ�ȭ�մϴ�. �����ڿ����� ȣ���ϸ�, ��Ÿ �ʿ��� �� ȣ���մϴ�.
	void update();						// ��ü�� ������ ������Ʈ�մϴ�.

	void putFactor(glm::mat4 inputFactor);	// �̵� ������ �ٲߴϴ�.
	glm::mat4 getFactor();
};
