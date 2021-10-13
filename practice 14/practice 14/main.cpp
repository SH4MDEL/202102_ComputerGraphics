#pragma once
#include "shader.h"
#include "initShader.h"
#include "make_shaderProgram.h"
#include "stdafx.h"
void initBuffer();

GLvoid drawScene();
GLvoid Keyboard(unsigned char inputKey, int x, int y);
GLvoid SpecialKeyboard(int key, int x, int y);
GLvoid TimerFunction(int value);
GLvoid Reshape(int w, int h);

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> colors(0, 10);

GLchar *vertexSource, *fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체
GLuint s_program;

struct VectexArray {
	GLuint line_vao[2], line_vbo[2][2];
	GLuint hexahedron_vao[6], hexahedron_vbo[6][2];
	GLuint tetrahedron_vao[6], tetrahedron_vbo[6][2];
};
VectexArray va;

struct RunControl {
	bool visibility, wire;
	bool xRotate, yRotate;
	float xRotatePos, yRotatePos;
	float xObjectPos, yObjectPos;
	RunControl() {
		reset();
	}
	void reset() {
		visibility = true;
		wire = false;
		xRotate = false;
		yRotate = false;
		xRotatePos = 30.0f, yRotatePos = -30.0f;
		xObjectPos = 0.0f, yObjectPos = 0.0f;
	}
};
RunControl rc;

struct _Line {
	GLfloat data[2][2][2][3];
	_Line() {
		data[0][0][0][0] = 1.0f, data[0][0][0][1] = 0.0f, data[0][0][0][2] = 0.0f;		// 위치
		data[0][0][1][0] = -1.0f, data[0][0][1][1] = 0.0f, data[0][0][1][2] = 0.0f;

		data[0][1][0][0] = 0.0f, data[0][1][0][1] = 0.0f, data[0][1][0][2] = 0.0f;		// 색상
		data[0][1][1][0] = 0.0f, data[0][1][1][1] = 0.0f, data[0][1][1][2] = 0.0f;

		data[1][0][0][0] = 0.0f, data[1][0][0][1] = 1.0f, data[1][0][0][2] = 0.0f;		// 위치
		data[1][0][1][0] = 0.0f, data[1][0][1][1] = -1.0f, data[1][0][1][2] = 0.0f;

		data[1][1][0][0] = 0.0f, data[1][1][0][1] = 0.0f, data[1][1][0][2] = 0.0f;		// 색상
		data[1][1][1][0] = 0.0f, data[1][1][1][1] = 0.0f, data[1][1][1][2] = 0.0f;
	}
};
_Line line;

struct Hexahedron {
	GLfloat data[6][2][2][3][3];
	bool drawed;
	Hexahedron() {

		// 전면 좌표
		data[0][0][0][0][0] = -0.5f, data[0][0][0][0][1] = -0.5f, data[0][0][0][0][2] = 0.5f;
		data[0][0][0][1][0] = 0.5f, data[0][0][0][1][1] = -0.5f, data[0][0][0][1][2] = 0.5f;
		data[0][0][0][2][0] = -0.5f, data[0][0][0][2][1] = 0.5f, data[0][0][0][2][2] = 0.5f;

		data[0][0][1][0][0] = -0.5f, data[0][0][1][0][1] = 0.5f, data[0][0][1][0][2] = 0.5f;
		data[0][0][1][1][0] = 0.5f, data[0][0][1][1][1] = -0.5f, data[0][0][1][1][2] = 0.5f;
		data[0][0][1][2][0] = 0.5f, data[0][0][1][2][1] = 0.5f, data[0][0][1][2][2] = 0.5f;

		// 전면 색상
		data[0][1][0][0][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][0][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][0][2] = (GLfloat)colors(gen) / 10.0f;
		data[0][1][0][1][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][1][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][1][2] = (GLfloat)colors(gen) / 10.0f;
		data[0][1][0][2][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][2][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][2][2] = (GLfloat)colors(gen) / 10.0f;

		data[0][1][1][0][0] = data[0][1][0][2][0], data[0][1][1][0][1] = data[0][1][0][2][1], data[0][1][1][0][2] = data[0][1][0][2][2];
		data[0][1][1][1][0] = data[0][1][0][1][0], data[0][1][1][1][1] = data[0][1][0][1][1], data[0][1][1][1][2] = data[0][1][0][1][2];
		data[0][1][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][1][2][2] = (GLfloat)colors(gen) / 10.0f;


		// 상단 좌표
		data[1][0][0][0][0] = 0.5f, data[1][0][0][0][1] = 0.5f, data[1][0][0][0][2] = 0.5f;
		data[1][0][0][1][0] = 0.5f, data[1][0][0][1][1] = 0.5f, data[1][0][0][1][2] = -0.5f;
		data[1][0][0][2][0] = -0.5f, data[1][0][0][2][1] = 0.5f, data[1][0][0][2][2] = 0.5f;

		data[1][0][1][0][0] = -0.5f, data[1][0][1][0][1] = 0.5f, data[1][0][1][0][2] = 0.5f;
		data[1][0][1][1][0] = 0.5f, data[1][0][1][1][1] = 0.5f, data[1][0][1][1][2] = -0.5f;
		data[1][0][1][2][0] = -0.5f, data[1][0][1][2][1] = 0.5f, data[1][0][1][2][2] = -0.5f;

		// 상단 색상
		data[1][1][0][0][0] = data[0][1][1][2][0], data[1][1][0][0][1] = data[0][1][1][2][1], data[1][1][0][0][2] = data[0][1][1][2][2];
		data[1][1][0][1][0] = (GLfloat)colors(gen) / 10.0f, data[1][1][0][1][1] = (GLfloat)colors(gen) / 10.0f, data[1][1][0][1][2] = (GLfloat)colors(gen) / 10.0f;
		data[1][1][0][2][0] = data[0][1][0][2][0], data[1][1][0][2][1] = data[0][1][0][2][1], data[1][1][0][2][2] = data[0][1][0][2][2];

		data[1][1][1][0][0] = data[0][1][0][2][0], data[1][1][1][0][1] = data[0][1][0][2][1], data[1][1][1][0][2] = data[0][1][0][2][2];
		data[1][1][1][1][0] = data[1][1][0][1][0], data[1][1][1][1][1] = data[1][1][0][1][1], data[1][1][1][1][2] = data[1][1][0][1][2];
		data[1][1][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[1][1][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[1][1][1][2][2] = (GLfloat)colors(gen) / 10.0f;

		// 좌측 좌표
		data[2][0][0][0][0] = -0.5f, data[2][0][0][0][1] = 0.5f, data[2][0][0][0][2] = -0.5f;
		data[2][0][0][1][0] = -0.5f, data[2][0][0][1][1] = -0.5f, data[2][0][0][1][2] = -0.5f;
		data[2][0][0][2][0] = -0.5f, data[2][0][0][2][1] = -0.5f, data[2][0][0][2][2] = 0.5f;

		data[2][0][1][0][0] = -0.5f, data[2][0][1][0][1] = -0.5f, data[2][0][1][0][2] = 0.5f;
		data[2][0][1][1][0] = -0.5f, data[2][0][1][1][1] = 0.5f, data[2][0][1][1][2] = 0.5f;
		data[2][0][1][2][0] = -0.5f, data[2][0][1][2][1] = 0.5f, data[2][0][1][2][2] = -0.5f;

		// 좌측 색상
		data[2][1][0][0][0] = data[1][1][1][2][0], data[2][1][0][0][1] = data[1][1][1][2][1], data[2][1][0][0][2] = data[1][1][1][2][2];
		data[2][1][0][1][0] = (GLfloat)colors(gen) / 10.0f, data[2][1][0][1][1] = (GLfloat)colors(gen) / 10.0f, data[2][1][0][1][2] = (GLfloat)colors(gen) / 10.0f;
		data[2][1][0][2][0] = data[0][1][0][0][0], data[2][1][0][2][1] = data[0][1][0][0][1], data[2][1][0][2][2] = data[0][1][0][0][2];

		data[2][1][1][0][0] = data[0][1][0][0][0], data[2][1][1][0][1] = data[0][1][0][0][1], data[2][1][1][0][2] = data[0][1][0][0][2];
		data[2][1][1][1][0] = data[0][1][0][2][0], data[2][1][1][1][1] = data[0][1][0][2][1], data[2][1][1][1][2] = data[0][1][0][2][2];
		data[2][1][1][2][0] = data[1][1][1][2][0], data[2][1][1][2][1] = data[1][1][1][2][1], data[2][1][1][2][2] = data[1][1][1][2][2];

		// 후면 좌표
		data[3][0][0][0][0] = -0.5f, data[3][0][0][0][1] = 0.5f, data[3][0][0][0][2] = -0.5f;
		data[3][0][0][1][0] = -0.5f, data[3][0][0][1][1] = -0.5f, data[3][0][0][1][2] = -0.5f;
		data[3][0][0][2][0] = 0.5f, data[3][0][0][2][1] = 0.5f, data[3][0][0][2][2] = -0.5f;

		data[3][0][1][0][0] = 0.5f, data[3][0][1][0][1] = 0.5f, data[3][0][1][0][2] = -0.5f;
		data[3][0][1][1][0] = -0.5f, data[3][0][1][1][1] = -0.5f, data[3][0][1][1][2] = -0.5f;
		data[3][0][1][2][0] = 0.5f, data[3][0][1][2][1] = -0.5f, data[3][0][1][2][2] = -0.5f;

		// 후면 색상
		data[3][1][0][0][0] = data[1][1][1][2][0], data[3][1][0][0][1] = data[1][1][1][2][1], data[3][1][0][0][2] = data[1][1][1][2][2];
		data[3][1][0][1][0] = data[2][1][0][1][0], data[3][1][0][1][1] = data[2][1][0][1][1], data[3][1][0][1][2] = data[2][1][0][1][2];
		data[3][1][0][2][0] = data[1][1][0][1][0], data[3][1][0][2][1] = data[1][1][0][1][1], data[3][1][0][2][2] = data[1][1][0][1][2];

		data[3][1][1][0][0] = data[1][1][0][1][0], data[3][1][1][0][1] = data[1][1][0][1][1], data[3][1][1][0][2] = data[1][1][0][1][2];
		data[3][1][1][1][0] = data[2][1][0][1][0], data[3][1][1][1][1] = data[2][1][0][1][1], data[3][1][1][1][2] = data[2][1][0][1][2];
		data[3][1][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[3][1][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[3][1][1][2][2] = (GLfloat)colors(gen) / 10.0f;

		// 하단 좌표
		data[4][0][0][0][0] = 0.5f, data[4][0][0][0][1] = -0.5f, data[4][0][0][0][2] = -0.5f;
		data[4][0][0][1][0] = 0.5f, data[4][0][0][1][1] = -0.5f, data[4][0][0][1][2] = 0.5f;
		data[4][0][0][2][0] = -0.5f, data[4][0][0][2][1] = -0.5f, data[4][0][0][2][2] = 0.5f;

		data[4][0][1][0][0] = -0.5f, data[4][0][1][0][1] = -0.5f, data[4][0][1][0][2] = 0.5f;
		data[4][0][1][1][0] = -0.5f, data[4][0][1][1][1] = -0.5f, data[4][0][1][1][2] = -0.5f;
		data[4][0][1][2][0] = 0.5f, data[4][0][1][2][1] = -0.5f, data[4][0][1][2][2] = -0.5f;

		// 하단 색상
		data[4][1][0][0][0] = data[3][1][1][2][0], data[4][1][0][0][1] = data[3][1][1][2][1], data[4][1][0][0][2] = data[3][1][1][2][2];
		data[4][1][0][1][0] = data[0][1][0][1][0], data[4][1][0][1][1] = data[0][1][0][1][1], data[4][1][0][1][2] = data[0][1][0][1][2];
		data[4][1][0][2][0] = data[0][1][0][0][0], data[4][1][0][2][1] = data[0][1][0][0][1], data[4][1][0][2][2] = data[0][1][0][0][2];

		data[4][1][1][0][0] = data[0][1][0][0][0], data[4][1][1][0][1] = data[0][1][0][0][1], data[4][1][1][0][2] = data[0][1][0][0][2];
		data[4][1][1][1][0] = data[2][1][0][1][0], data[4][1][1][1][1] = data[2][1][0][1][1], data[4][1][1][1][2] = data[2][1][0][1][2];
		data[4][1][1][2][0] = data[3][1][1][2][0], data[4][1][1][2][1] = data[3][1][1][2][1], data[4][1][1][2][2] = data[3][1][1][2][2];

		// 우측 좌표
		data[5][0][0][0][0] = 0.5f, data[5][0][0][0][1] = -0.5f, data[5][0][0][0][2] = -0.5f;
		data[5][0][0][1][0] = 0.5f, data[5][0][0][1][1] = 0.5f, data[5][0][0][1][2] = -0.5f;
		data[5][0][0][2][0] = 0.5f, data[5][0][0][2][1] = -0.5f, data[5][0][0][2][2] = 0.5f;

		data[5][0][1][0][0] = 0.5f, data[5][0][1][0][1] = -0.5f, data[5][0][1][0][2] = 0.5f;
		data[5][0][1][1][0] = 0.5f, data[5][0][1][1][1] = 0.5f, data[5][0][1][1][2] = -0.5f;
		data[5][0][1][2][0] = 0.5f, data[5][0][1][2][1] = 0.5f, data[5][0][1][2][2] = 0.5f;
		
		// 우측 색상
		data[5][1][0][0][0] = data[3][1][1][2][0], data[5][1][0][0][1] = data[3][1][1][2][1], data[5][1][0][0][2] = data[3][1][1][2][2];
		data[5][1][0][1][0] = data[1][1][0][1][0], data[5][1][0][1][1] = data[1][1][0][1][1], data[5][1][0][1][2] = data[1][1][0][1][2];
		data[5][1][0][2][0] = data[0][1][0][1][0], data[5][1][0][2][1] = data[0][1][0][1][1], data[5][1][0][2][2] = data[0][1][0][1][2];

		data[5][1][1][0][0] = data[0][1][0][1][0], data[5][1][1][0][1] = data[0][1][0][1][1], data[5][1][1][0][2] = data[0][1][0][1][2];
		data[5][1][1][1][0] = data[1][1][0][1][0], data[5][1][1][1][1] = data[1][1][0][1][1], data[5][1][1][1][2] = data[1][1][0][1][2];
		data[5][1][1][2][0] = data[0][1][1][2][0], data[5][1][1][2][1] = data[0][1][1][2][1], data[5][1][1][2][2] = data[0][1][1][2][2];

		drawed_reset();
	}
	void drawed_reset() {
		drawed = false;
	}
};
Hexahedron hexa;

struct Tetrahedron {
	GLfloat data[6][2][3][3];
	bool drawed;
	Tetrahedron() {

		// 하단 사각형 좌표
		data[0][0][0][0] = -0.5f, data[0][0][0][1] = -0.5f, data[0][0][0][2] = 0.5f;
		data[0][0][1][0] = -0.5f, data[0][0][1][1] = -0.5f, data[0][0][1][2] = -0.5f;
		data[0][0][2][0] = 0.5f, data[0][0][2][1] = -0.5f, data[0][0][2][2] = 0.5f;

		data[1][0][0][0] = 0.5f, data[1][0][0][1] = -0.5f, data[1][0][0][2] = 0.5f;
		data[1][0][1][0] = -0.5f, data[1][0][1][1] = -0.5f, data[1][0][1][2] = -0.5f;
		data[1][0][2][0] = 0.5f, data[1][0][2][1] = -0.5f, data[1][0][2][2] = -0.5f;

		// 하단 사각형 색상
		data[0][1][0][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][2] = (GLfloat)colors(gen) / 10.0f;
		data[0][1][1][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][1][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][1][2] = (GLfloat)colors(gen) / 10.0f;
		data[0][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][2][2] = (GLfloat)colors(gen) / 10.0f;

		data[1][1][0][0] = data[0][1][2][0], data[1][1][0][1] = data[0][1][2][1], data[1][1][0][2] = data[0][1][2][2];
		data[1][1][1][0] = data[0][1][1][0], data[1][1][1][1] = data[0][1][1][1], data[1][1][1][2] = data[0][1][1][2];
		data[1][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[1][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[1][1][2][2] = (GLfloat)colors(gen) / 10.0f;

		// 우측 삼각형 좌표
		data[2][0][0][0] = 0.5f, data[2][0][0][1] = -0.5f, data[2][0][0][2] = -0.5f;
		data[2][0][1][0] = 0.0f, data[2][0][1][1] = 0.5f, data[2][0][1][2] = 0.0f;
		data[2][0][2][0] = 0.5f, data[2][0][2][1] = -0.5f, data[2][0][2][2] = 0.5f;

		// 우측 삼각형 색상
		data[2][1][0][0] = (GLfloat)colors(gen) / 10.0f, data[2][1][0][1] = (GLfloat)colors(gen) / 10.0f, data[2][1][0][2] = (GLfloat)colors(gen) / 10.0f;
		data[2][1][1][0] = (GLfloat)colors(gen) / 10.0f, data[2][1][1][1] = (GLfloat)colors(gen) / 10.0f, data[2][1][1][2] = (GLfloat)colors(gen) / 10.0f;
		data[2][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[2][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[2][1][2][2] = (GLfloat)colors(gen) / 10.0f;

		// 정면 삼각형 좌표
		data[3][0][0][0] = 0.5f, data[3][0][0][1] = -0.5f, data[3][0][0][2] = 0.5f;
		data[3][0][1][0] = 0.0f, data[3][0][1][1] = 0.5f, data[3][0][1][2] = 0.0f;
		data[3][0][2][0] = -0.5f, data[3][0][2][1] = -0.5f, data[3][0][2][2] = 0.5f;

		// 정면 삼각형 색상
		data[3][1][0][0] = (GLfloat)colors(gen) / 10.0f, data[3][1][0][1] = (GLfloat)colors(gen) / 10.0f, data[3][1][0][2] = (GLfloat)colors(gen) / 10.0f;
		data[3][1][1][0] = data[2][1][1][0], data[3][1][1][1] = data[2][1][1][1], data[3][1][1][2] = data[2][1][1][2];
		data[3][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[3][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[3][1][2][2] = (GLfloat)colors(gen) / 10.0f;

		// 좌측 삼각형 좌표
		data[4][0][0][0] = -0.5f, data[4][0][0][1] = -0.5f, data[4][0][0][2] = 0.5f;
		data[4][0][1][0] = 0.0f, data[4][0][1][1] = 0.5f, data[4][0][1][2] = 0.0f;
		data[4][0][2][0] = -0.5f, data[4][0][2][1] = -0.5f, data[4][0][2][2] = -0.5f;

		// 좌측 삼각형 색상
		data[4][1][0][0] = (GLfloat)colors(gen) / 10.0f, data[4][1][0][1] = (GLfloat)colors(gen) / 10.0f, data[4][1][0][2] = (GLfloat)colors(gen) / 10.0f;
		data[4][1][1][0] = data[2][1][1][0], data[4][1][1][1] = data[2][1][1][1], data[4][1][1][2] = data[2][1][1][2];
		data[4][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[4][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[4][1][2][2] = (GLfloat)colors(gen) / 10.0f;

		// 후면 삼각형 좌표
		data[5][0][0][0] = -0.5f, data[5][0][0][1] = -0.5f, data[5][0][0][2] = -0.5f;
		data[5][0][1][0] = 0.0f, data[5][0][1][1] = 0.5f, data[5][0][1][2] = 0.0f;
		data[5][0][2][0] = 0.5f, data[5][0][2][1] = -0.5f, data[5][0][2][2] = -0.5f;

		// 후면 삼각형 색상
		data[5][1][0][0] = (GLfloat)colors(gen) / 10.0f, data[5][1][0][1] = (GLfloat)colors(gen) / 10.0f, data[5][1][0][2] = (GLfloat)colors(gen) / 10.0f;
		data[5][1][1][0] = data[2][1][1][0], data[5][1][1][1] = data[2][1][1][1], data[5][1][1][2] = data[2][1][1][2];
		data[5][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[5][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[5][1][2][2] = (GLfloat)colors(gen) / 10.0f;

		drawed_reset();
	}
	void drawed_reset() {
		drawed = false;
	}
};
Tetrahedron tetra;

int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("practice 14");

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {					// glew 초기화
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initialized\n";
	}

	glewInit();
	initShader();
	initBuffer();

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutTimerFunc(10, TimerFunction, 1);

	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	//--- 변경된 배경색 설정
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(s_program);

	for (int i = 0; i < 2; i++) {
		glBindVertexArray(va.line_vao[i]);
		glDrawArrays(GL_LINES, 0, 2);
	}

	glm::mat4 OBJECT = glm::mat4(1.0f);
	OBJECT = glm::translate(OBJECT, glm::vec3(rc.xObjectPos, rc.yObjectPos, 0.0));
	OBJECT = glm::rotate(OBJECT, (float)glm::radians(rc.xRotatePos), glm::vec3(1.0, 0.0, 0.0));
	OBJECT = glm::rotate(OBJECT, (float)glm::radians(rc.yRotatePos), glm::vec3(0.0, 1.0, 0.0));
	unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(OBJECT)); //--- modelTransform 변수에 변환 값 적용하기

	for (int i = 0; i < 6; i++) {
		if (rc.visibility) {
			glEnable(GL_DEPTH_TEST);
		}
		if (rc.wire == false) {
			if (hexa.drawed == true) {
				glBindVertexArray(va.hexahedron_vao[i]);
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
			if (tetra.drawed == true) {
				glBindVertexArray(va.tetrahedron_vao[i]);
				glDrawArrays(GL_TRIANGLES, 0, 3);
			}
		}
		else {
			if (hexa.drawed == true) {
				glBindVertexArray(va.hexahedron_vao[i]);
				glDrawArrays(GL_LINE_LOOP, 0, 6);
			}
			if (tetra.drawed == true) {
				glBindVertexArray(va.tetrahedron_vao[i]);
				glDrawArrays(GL_LINE_LOOP, 0, 3);
			}
		}
		if (rc.visibility) {
			glDisable(GL_DEPTH_TEST);
		}
	}
	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'C':
	case 'c':
		hexa.drawed_reset();
		tetra.drawed_reset();
		hexa.drawed = true;
		break;
	case 'P':
	case 'p':
		hexa.drawed_reset();
		tetra.drawed_reset();
		tetra.drawed = true;
		break;
	case 'H':
	case 'h':
		if (rc.visibility) {
			rc.visibility = false;
		}
		else {
			rc.visibility = true;
		}
		break;
	case 'X':
	case 'x':
		if (rc.xRotate) {
			rc.xRotate = false;
		}
		else {
			rc.xRotate = true;
		}
		break;
	case 'Y':
	case 'y':
		if (rc.yRotate) {
			rc.yRotate = false;
		}
		else {
			rc.yRotate = true;
		}
		break;
	case 'w':
	case 'W':
		if (rc.wire) {
			rc.wire = false;
		}
		else {
			rc.wire = true;
		}
		break;
	case 'S':
	case 's':
		rc.reset();
		break;
	case 'Q':
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) {
		rc.xObjectPos -= 0.01f;
	}
	if (key == GLUT_KEY_RIGHT) {
		rc.xObjectPos += 0.01f;
	}
	if (key == GLUT_KEY_UP) {
		rc.yObjectPos += 0.01f;
	}
	if (key == GLUT_KEY_DOWN) {
		rc.yObjectPos -= 0.01f;
	}
}


GLvoid TimerFunction(int value)
{
	if (rc.xRotate == true) {
		rc.xRotatePos += 0.5f;
	}
	if (rc.yRotate == true) {
		rc.yRotatePos += 0.5f;
	}
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, value);
	return;
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

void initBuffer()
{
	glGenVertexArrays(2, va.line_vao);
	for (int i = 0; i < 2; i++) {
		glBindVertexArray(va.line_vao[i]);
		glGenBuffers(2, va.line_vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, va.line_vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), line.data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}

	glGenVertexArrays(6, va.hexahedron_vao);
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(va.hexahedron_vao[i]);
		glGenBuffers(2, va.hexahedron_vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, va.hexahedron_vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), hexa.data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}

	glGenVertexArrays(6, va.tetrahedron_vao);
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(va.tetrahedron_vao[i]);
		glGenBuffers(2, va.tetrahedron_vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, va.tetrahedron_vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), tetra.data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}
}

