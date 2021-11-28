#pragma once
#include "stdafx.h"

struct Quadrangular
{
	GLfloat data[6][2][3][3];
	GLfloat texture_data[6][3][2];
	GLuint vao[6], vbo[6][2];
	unsigned int texture[6];
	unsigned char* image[6];

	glm::mat4 myFactor;

	int objColorLocation;
	int tLocation;

	////////////////////////////////////////////////////////////////////////
	// 기타 필요한 변수들 생성
	bool drawed;
	bool Xrotate, Yrotate;
	GLfloat XrotatePos, YrotatePos;
	////////////////////////////////////////////////////////////////////////

	Quadrangular();
	void initBuffer(GLuint s_program);
	void initTexture(GLint s_program);
	void draw();						// 원점에 그립니다.

	void allReset();					// 모든 정보를 초기화합니다. 생성자에서도 호출하며, 기타 필요할 때 호출합니다.
	void update();						// 객체의 정보를 업데이트합니다.

	void putFactor(glm::mat4 inputFactor);	// 이동 정보를 바꿉니다.
	glm::mat4 getFactor();					// 이동 정보를 반환합니다.
};

