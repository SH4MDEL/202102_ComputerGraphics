#pragma once
#include "stdafx.h"

extern GLchar* vertexSource, * fragmentSource; //--- �ҽ��ڵ� ���� ����
extern GLuint vertexShader, fragmentShader; //--- ���̴� ��ü

void make_vertexShaders();
void make_fragmentShaders();

char* filetobuf(const char* file);