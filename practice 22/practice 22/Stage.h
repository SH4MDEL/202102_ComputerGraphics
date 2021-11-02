#pragma once
#include "stdafx.h"

// �⺻ ������ü ���� ���Դϴ�.
struct Stage
{
	GLfloat data[6][2][2][3][3];		// ũ��� ���� ������ �Էµ˴ϴ�.
	GLuint vao[6], vbo[6][2];			// �� ���� ũ��� ���� ������ vao�� ���ε��˴ϴ�.

	glm::mat4 myFactor;					// ���� ��Ұ� ����� 4x4 ����Դϴ�.

	////////////////////////////////////////////////////////////////////////
	// ��Ÿ �ʿ��� ������ ����
	GLfloat HeightFromGround;
	glm::mat4 myDoorFactor;
	bool opendoor;
	GLfloat opendoorPos;
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
	void drawDoor();
	void putDoorFactor(glm::mat4 inputFactor);
	glm::mat4 getDoorFactor();
	////////////////////////////////////////////////////////////////////////
};

