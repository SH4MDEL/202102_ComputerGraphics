#pragma once
#include "stdafx.h"

struct Field
{
	GLfloat data[2][2][3][3];		// ũ��� ���� ������ �Էµ˴ϴ�.
	GLfloat texture_data[2][3][2];
	GLuint vao, vbo[3];			// �� ���� ũ��� ���� ������ vao�� ���ε��˴ϴ�.
	unsigned int texture;
	unsigned char* image;

	glm::mat4 myFactor;					// ���� ��Ұ� ����� 4x4 ����Դϴ�.

	int objColorLocation;
	int tLocation;

	////////////////////////////////////////////////////////////////////////
	// ��Ÿ �ʿ��� ������ ����
	////////////////////////////////////////////////////////////////////////

	Field();						// ������
	void initBuffer(GLuint s_program);					// ũ��� ���� ������ vao �� vbo�� ���ε��մϴ�. ���� �Լ����� ȣ��������մϴ�.
	void initTexture(GLint s_program);
	void draw();						// ������ �׸��ϴ�.

	void allReset();					// ��� ������ �ʱ�ȭ�մϴ�. �����ڿ����� ȣ���ϸ�, ��Ÿ �ʿ��� �� ȣ���մϴ�.
	void update();						// ��ü�� ������ ������Ʈ�մϴ�.

	void putFactor(glm::mat4 inputFactor);	// �̵� ������ �ٲߴϴ�.
	glm::mat4 getFactor();					// �̵� ������ ��ȯ�մϴ�.

	////////////////////////////////////////////////////////////////////////
	// ��Ÿ �ʿ��� �Լ��� ����

	////////////////////////////////////////////////////////////////////////
};

