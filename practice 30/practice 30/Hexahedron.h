#pragma once
#include "stdafx.h"

struct Hexahedron
{
	GLfloat data[6][2][2][3][3];		// ũ��� ���� ������ �Էµ˴ϴ�.
	GLfloat texture_data[6][2][3][2];
	GLuint vao[6], vbo[6][3];			// �� ���� ũ��� ���� ������ vao�� ���ε��˴ϴ�.
	unsigned int texture[6];
	unsigned char* image[6];

	glm::mat4 myFactor;					// ���� ��Ұ� ����� 4x4 ����Դϴ�.

	int objColorLocation;
	int tLocation;

	////////////////////////////////////////////////////////////////////////
	// ��Ÿ �ʿ��� ������ ����
	bool drawed;
	bool Xrotate, Yrotate;
	GLfloat XrotatePos, YrotatePos;
	////////////////////////////////////////////////////////////////////////

	Hexahedron();						// ������
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


