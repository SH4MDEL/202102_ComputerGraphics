#pragma once
#include "stdafx.h"

struct Robot
{
	GLfloat body[6][2][2][3][3];
	GLuint body_vao[6], body_vbo[6][2];
	glm::mat4 bodyFactor;

	GLfloat head[7][2][2][3][3];
	GLuint head_vao[7], head_vbo[7][2];
	glm::mat4 headFactor;

	GLfloat leftarm[6][2][2][3][3];
	GLuint leftarm_vao[6], leftarm_vbo[6][2];
	glm::mat4 leftarmFactor;

	GLfloat leftleg[6][2][2][3][3];
	GLuint leftleg_vao[6], leftleg_vbo[6][2];
	glm::mat4 leftlegFactor;

	GLfloat rightarm[6][2][2][3][3];
	GLuint rightarm_vao[6], rightarm_vbo[6][2];
	glm::mat4 rightarmFactor;

	GLfloat rightleg[6][2][2][3][3];
	GLuint rightleg_vao[6], rightleg_vbo[6][2];
	glm::mat4 rightlegFactor;

	////////////////////////////////////////////////////////////////////////
	// 기타 필요한 변수들 생성
	GLint movement;
	GLfloat xPos, zPos, rotation;
	GLfloat HeightFromGround[6];
	bool hanging;
	GLfloat hangingPos;
	////////////////////////////////////////////////////////////////////////

	Robot();

	void initBuffer();
	void body_draw();
	void head_draw();
	void leftarm_draw();
	void leftleg_draw();
	void rightarm_draw();
	void rightleg_draw();

	void allReset();
	void update(bool up, bool down, bool left, bool right);

	void putFactor(glm::mat4 inputFactor);

	glm::mat4 getbodyFactor();
	glm::mat4 getheadFactor();
	glm::mat4 getleftarmFactor();
	glm::mat4 getleftlegFactor();
	glm::mat4 getrightarmFactor();
	glm::mat4 getrightlegFactor();
};

