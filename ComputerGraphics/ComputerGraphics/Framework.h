#pragma once
#include "stdafx.h"


class Framework
{
private:
	GLchar* vertexSource, *fragmentSource; //--- �ҽ��ڵ� ���� ����
	GLuint vertexShader, fragmentShader; //--- ���̴� ��ü
	GLuint s_program;

	const GLfloat triShape[3][3] = { //--- �ﰢ�� ��ġ ��
	{ -0.5, -0.5, 0.0 },
	{ 0.5, -0.5, 0.0 },
	{ 0.0, 0.5, 0.0 } };
	const GLfloat colors[3][3] = { //--- �ﰢ�� ������ ����
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

