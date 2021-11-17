#pragma once
#include "stdafx.h"

#define M_PI 3.1415926535897932384626433832795

struct Orbit
{
	GLfloat data[20][2][2][3];
	GLuint vao[20], vbo[20][2];
	GLfloat r, scalePos;

	int objColorLocation;

	glm::mat4 myFactor;

	Orbit();

	void initBuffer(GLuint s_program);
	void draw();

	void allReset();					// 모든 정보를 초기화합니다. 생성자에서도 호출하며, 기타 필요할 때 호출합니다.
	void update();						// 객체의 정보를 업데이트합니다.

	void putFactor(glm::mat4 inputFactor);	// 이동 정보를 바꿉니다.
	glm::mat4 getFactor();
};

