#pragma once
#include "stdafx.h"
#include "random_only.h"

struct Mountain
{
	GLfloat data[6][2][2][3][3];		// ũ��� ���� ������ �Էµ˴ϴ�.
	GLuint vao[6], vbo[6][2];			// �� ���� ũ��� ���� ������ vao�� ���ε��˴ϴ�.

	glm::mat4 myFactor;					// ���� ��Ұ� ����� 4x4 ����Դϴ�.

	////////////////////////////////////////////////////////////////////////
	// ��Ÿ �ʿ��� ������ ����
	GLint xPos, zPos, scale;
	GLfloat HeightFromGround, MaxHeightRatio, minHeightRatio, scalePos, scaleVelo;
	GLint status;
	random_only ro;
	bool low;
	////////////////////////////////////////////////////////////////////////

	Mountain();							// ������
	void initBuffer();					// ũ��� ���� ������ vao �� vbo�� ���ε��մϴ�. ���� �Լ����� ȣ��������մϴ�.
	void draw();						// ������ �׸��ϴ�.

	void allReset();					// ��� ������ �ʱ�ȭ�մϴ�. �����ڿ����� ȣ���ϸ�, ��Ÿ �ʿ��� �� ȣ���մϴ�.
	void update();						// ��ü�� ������ ������Ʈ�մϴ�.

	void putFactor(glm::mat4 inputFactor);	// �̵� ������ �ٲߴϴ�.
	glm::mat4 getFactor();					// �̵� ������ ��ȯ�մϴ�.

	////////////////////////////////////////////////////////////////////////
	// ��Ÿ �ʿ��� �Լ��� ����
	void add_data(GLint xPos, GLint zPos);
	void start_wave();
	void stop_wave();
	void make_road();
	void low_height();

	void speedup();
	void speeddown();
	////////////////////////////////////////////////////////////////////////
};

