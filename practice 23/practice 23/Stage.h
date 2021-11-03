#pragma once
#include "stdafx.h"

struct Stage
{
	GLfloat data[5][2][2][3][3];		// ũ��� ���� ������ �Էµ˴ϴ�.
	GLuint vao[5], vbo[5][2];			// �� ���� ũ��� ���� ������ vao�� ���ε��˴ϴ�.

	glm::mat4 myFactor;					// ���� ��Ұ� ����� 4x4 ����Դϴ�.

	////////////////////////////////////////////////////////////////////////
	// ��Ÿ �ʿ��� ������ ����
	GLfloat xPos, zPos, rPos;
	GLfloat HeightFromGround;
	GLint stageStatus;
	bool opened;
	GLfloat openPos;
	////////////////////////////////////////////////////////////////////////

	Stage();						// ������
	void initBuffer();					// ũ��� ���� ������ vao �� vbo�� ���ε��մϴ�. ���� �Լ����� ȣ��������մϴ�.
	void draw();						// ������ �׸��ϴ�.

	void allReset();					// ��� ������ �ʱ�ȭ�մϴ�. �����ڿ����� ȣ���ϸ�, ��Ÿ �ʿ��� �� ȣ���մϴ�.
	void update();						// ��ü�� ������ ������Ʈ�մϴ�.

	void putFactor(glm::mat4 inputFactor);	// �̵� ������ �ٲߴϴ�.
	glm::mat4 getFactor();					// �̵� ������ ��ȯ�մϴ�.

	////////////////////////////////////////////////////////////////////////
	// ��Ÿ �ʿ��� �Լ��� ����
	glm::mat4 getleftDoorFactor();
	glm::mat4 getrightDoorFactor();
	void drawleft();
	void drawright();
	////////////////////////////////////////////////////////////////////////
};

