#pragma once
#include "stdafx.h"
#include "ObjRead.h"

struct Earth
{
	objRead objReader;
	GLuint object;
	GLuint vao[3], vbo[3][2];

	int objColorLocation;

	glm::mat4 myFactor;
	Earth();

	void initBuffer(int s_program);
	void draw();

	void allReset();					// 모든 정보를 초기화합니다. 생성자에서도 호출하며, 기타 필요할 때 호출합니다.
	void update();						// 객체의 정보를 업데이트합니다.

	void putFactor(glm::mat4 inputFactor);	// 이동 정보를 바꿉니다.
	glm::mat4 getFactor();					// 이동 정보를 반환합니다.
};

