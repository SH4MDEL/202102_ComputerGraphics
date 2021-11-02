#pragma once
#include "stdafx.h"

struct eraser_bottom
{
	GLfloat data[6][2][2][3][3];		// 크기와 색상 정보가 입력됩니다.
	GLuint vao[6], vbo[6][2];			// 한 면의 크기와 색상 정보가 vao에 바인딩됩니다.

	glm::mat4 myFactor;					// 변한 요소가 저장된 4x4 행렬입니다.

	////////////////////////////////////////////////////////////////////////
	// 기타 필요한 변수들 생성
	GLfloat xPos, zPos;
	GLfloat HeightFromGround;
	////////////////////////////////////////////////////////////////////////

	eraser_bottom();						// 생성자
	void initBuffer();					// 크기와 색상 정보를 vao 및 vbo에 바인딩합니다. 메인 함수에서 호출해줘야합니다.
	void draw();						// 원점에 그립니다.

	void allReset();					// 모든 정보를 초기화합니다. 생성자에서도 호출하며, 기타 필요할 때 호출합니다.
	void update();						// 객체의 정보를 업데이트합니다.

	void putFactor(glm::mat4 inputFactor);	// 이동 정보를 바꿉니다.
	glm::mat4 getFactor();					// 이동 정보를 반환합니다.

	////////////////////////////////////////////////////////////////////////
	// 기타 필요한 함수들 생성
	void w();
	void s();
	void a();
	void d();
	////////////////////////////////////////////////////////////////////////
};

