#pragma once
#include "stdafx.h"


class Framework
{
private:
	GLchar* vertexSource, *fragmentSource; //--- 소스코드 저장 변수
	GLuint vertexShader, fragmentShader; //--- 세이더 객체
	GLuint s_program;

	const GLfloat triShape[3][3] = { //--- 삼각형 위치 값
	{ -0.5, -0.5, 0.0 },
	{ 0.5, -0.5, 0.0 },
	{ 0.0, 0.5, 0.0 } };
	const GLfloat colors[3][3] = { //--- 삼각형 꼭지점 색상
		{ 1.0, 0.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 0.0, 1.0 } };
	GLuint vao, vbo[2];
public:
	void make_vertexShaders();
	void make_fragmentShaders();
	void initBuffer();
	void initShader();
	GLuint make_shaderProgram();
	GLvoid drawScene();
	GLvoid Reshape(int w, int h);

	char* filetobuf(const char* file);
};

