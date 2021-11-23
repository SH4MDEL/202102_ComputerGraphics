#pragma once
#include "stdafx.h"

struct Sierpinski
{
	GLfloat base[2][3][3];		// �ϴ� �簢�� ��ǥ
	GLuint bvao[2], bvbo[2][2];

	GLfloat right[2][729][3][3];
	GLfloat front[2][729][3][3];
	GLfloat left[2][729][3][3];
	GLfloat back[2][729][3][3];
	GLuint vao[4], vbo[4][2];

	GLint level, count;

	glm::mat4 myFactor;
	int objColorLocation;

	Sierpinski(GLint level);

	void make_sierpinski_right(GLint level, GLfloat upx, GLfloat upy, GLfloat upz, GLfloat leftx, GLfloat lefty, GLfloat leftz, GLfloat rightx, GLfloat righty, GLfloat rightz);
	void make_sierpinski_front(GLint level, GLfloat upx, GLfloat upy, GLfloat upz, GLfloat leftx, GLfloat lefty, GLfloat leftz, GLfloat rightx, GLfloat righty, GLfloat rightz);
	void make_sierpinski_left(GLint level, GLfloat upx, GLfloat upy, GLfloat upz, GLfloat leftx, GLfloat lefty, GLfloat leftz, GLfloat rightx, GLfloat righty, GLfloat rightz);
	void make_sierpinski_back(GLint level, GLfloat upx, GLfloat upy, GLfloat upz, GLfloat leftx, GLfloat lefty, GLfloat leftz, GLfloat rightx, GLfloat righty, GLfloat rightz);

	void initBuffer(GLuint s_program);
	void draw();						// ������ �׸��ϴ�.

	void update();						// ��ü�� ������ ������Ʈ�մϴ�.

	void putFactor(glm::mat4 inputFactor);	// �̵� ������ �ٲߴϴ�.
	glm::mat4 getFactor();					// �̵� ������ ��ȯ�մϴ�.
};

