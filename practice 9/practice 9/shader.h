#pragma once
#include "stdafx.h"

extern GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
extern GLuint vertexShader, fragmentShader; //--- 세이더 객체

void make_vertexShaders();
void make_fragmentShaders();

char* filetobuf(const char* file);