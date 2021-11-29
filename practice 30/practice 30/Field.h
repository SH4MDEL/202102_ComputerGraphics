#pragma once
#include "stdafx.h"

struct Field
{
	GLfloat data[2][2][3][3];		// 크기와 색상 정보가 입력됩니다.
	GLfloat texture_data[2][3][2];
	GLuint vao, vbo[3];			// 한 면의 크기와 색상 정보가 vao에 바인딩됩니다.
	unsigned int texture;
	unsigned char* image;

	glm::mat4 myFactor;					// 변한 요소가 저장된 4x4 행렬입니다.

	int objColorLocation;
	int tLocation;

	////////////////////////////////////////////////////////////////////////
	// 기타 필요한 변수들 생성
	////////////////////////////////////////////////////////////////////////

	Field();						// 생성자
	void initBuffer(GLuint s_program);					// 크기와 색상 정보를 vao 및 vbo에 바인딩합니다. 메인 함수에서 호출해줘야합니다.
	void initTexture(GLint s_program);
	void draw();						// 원점에 그립니다.

	void allReset();					// 모든 정보를 초기화합니다. 생성자에서도 호출하며, 기타 필요할 때 호출합니다.
	void update();						// 객체의 정보를 업데이트합니다.

	void putFactor(glm::mat4 inputFactor);	// 이동 정보를 바꿉니다.
	glm::mat4 getFactor();					// 이동 정보를 반환합니다.

	////////////////////////////////////////////////////////////////////////
	// 기타 필요한 함수들 생성

	////////////////////////////////////////////////////////////////////////
};

