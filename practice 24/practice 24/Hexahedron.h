#pragma once
#include "stdafx.h"

struct Hexahedron
{

	GLfloat data[6][2][2][3][3];		// ũ��� ���� ������ �Էµ˴ϴ�.
	GLuint vao[6], vbo[6][2];			// �� ���� ũ��� ���� ������ vao�� ���ε��˴ϴ�.

	glm::mat4 myFactor;					// ���� ��Ұ� ����� 4x4 ����Դϴ�.
	glm::mat4 myHeadFactor;
	glm::mat4 mySlideFactor;
	glm::mat4 myFrontFactor;

	int objColorLocation;

	////////////////////////////////////////////////////////////////////////
	// ��Ÿ �ʿ��� ������ ����
	bool drawed;
	bool rotate;
	GLfloat rotatePos;
	bool head;
	GLfloat headPos;
	bool slide;
	GLfloat slidePos;
	bool front;
	GLfloat frontPos;
	////////////////////////////////////////////////////////////////////////

	Hexahedron();						// ������
	void initBuffer(GLuint s_program);					// ũ��� ���� ������ vao �� vbo�� ���ε��մϴ�. ���� �Լ����� ȣ��������մϴ�.
	void ReBuffer();
	void draw();						// ������ �׸��ϴ�.

	void allReset();					// ��� ������ �ʱ�ȭ�մϴ�. �����ڿ����� ȣ���ϸ�, ��Ÿ �ʿ��� �� ȣ���մϴ�.
	void update();						// ��ü�� ������ ������Ʈ�մϴ�.

	void putFactor(glm::mat4 inputFactor);	// �̵� ������ �ٲߴϴ�.
	glm::mat4 getFactor();					// �̵� ������ ��ȯ�մϴ�.

	////////////////////////////////////////////////////////////////////////
	// ��Ÿ �ʿ��� �Լ��� ����
	void headdraw();
	void putHeadFactor(glm::mat4 inputFactor);
	glm::mat4 getHeadFactor();

	void slidedraw();
	void putSlideFactor(glm::mat4 inputFactor);
	glm::mat4 getSlideFactor();

	void frontdraw();
	void putFrontFactor(glm::mat4 inputFactor);
	glm::mat4 getFrontFactor();

	////////////////////////////////////////////////////////////////////////
};


