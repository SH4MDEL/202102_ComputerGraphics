#pragma once
#include "stdafx.h"

struct Light
{
	GLfloat data[6][2][2][3][3];		// ũ��� ���� ������ �Էµ˴ϴ�.
	GLuint vao[6], vbo[6][2];			// �� ���� ũ��� ���� ������ vao�� ���ε��˴ϴ�.

	glm::mat4 myFactor;					// ���� ��Ұ� ����� 4x4 ����Դϴ�.

	int lightPosLocation;
	int objColorLocation;
	int lightColorLocation;

	Light();						// ������
	void initBuffer(GLuint s_program);					// ũ��� ���� ������ vao �� vbo�� ���ε��մϴ�. ���� �Լ����� ȣ��������մϴ�.
	void draw();						// ������ �׸��ϴ�.

	void allReset();					// ��� ������ �ʱ�ȭ�մϴ�. �����ڿ����� ȣ���ϸ�, ��Ÿ �ʿ��� �� ȣ���մϴ�.
	void update();						// ��ü�� ������ ������Ʈ�մϴ�.

	void putFactor(glm::mat4 inputFactor);	// �̵� ������ �ٲߴϴ�.
	glm::mat4 getFactor();					// �̵� ������ ��ȯ�մϴ�.


	GLint rotate;
	GLfloat rotatePos, zPos;
	bool onoff;
};

