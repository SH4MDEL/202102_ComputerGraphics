#include "stdafx.h"
#include "Quadrangular_pyramid.h"

Quadrangular_pyramid::Quadrangular_pyramid()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> colors(0, 10);

	// 하단 사각형 좌표
	data[0][0][0][0] = -0.3f, data[0][0][0][1] = -0.3f, data[0][0][0][2] = 0.3f;
	data[0][0][1][0] = -0.3f, data[0][0][1][1] = -0.3f, data[0][0][1][2] = -0.3f;
	data[0][0][2][0] = 0.3f, data[0][0][2][1] = -0.3f, data[0][0][2][2] = 0.3f;

	data[1][0][0][0] = 0.3f, data[1][0][0][1] = -0.3f, data[1][0][0][2] = 0.3f;
	data[1][0][1][0] = -0.3f, data[1][0][1][1] = -0.3f, data[1][0][1][2] = -0.3f;
	data[1][0][2][0] = 0.3f, data[1][0][2][1] = -0.3f, data[1][0][2][2] = -0.3f;

	// 하단 사각형 색상
	data[0][1][0][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][2] = (GLfloat)colors(gen) / 10.0f;
	data[0][1][1][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][1][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][1][2] = (GLfloat)colors(gen) / 10.0f;
	data[0][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][2][2] = (GLfloat)colors(gen) / 10.0f;

	data[1][1][0][0] = data[0][1][2][0], data[1][1][0][1] = data[0][1][2][1], data[1][1][0][2] = data[0][1][2][2];
	data[1][1][1][0] = data[0][1][1][0], data[1][1][1][1] = data[0][1][1][1], data[1][1][1][2] = data[0][1][1][2];
	data[1][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[1][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[1][1][2][2] = (GLfloat)colors(gen) / 10.0f;

	// 우측 삼각형 좌표
	data[2][0][0][0] = 0.3f, data[2][0][0][1] = -0.3f, data[2][0][0][2] = -0.3f;
	data[2][0][1][0] = 0.0f, data[2][0][1][1] = 0.3f, data[2][0][1][2] = 0.0f;
	data[2][0][2][0] = 0.3f, data[2][0][2][1] = -0.3f, data[2][0][2][2] = 0.3f;

	// 우측 삼각형 색상
	data[2][1][0][0] = (GLfloat)colors(gen) / 10.0f, data[2][1][0][1] = (GLfloat)colors(gen) / 10.0f, data[2][1][0][2] = (GLfloat)colors(gen) / 10.0f;
	data[2][1][1][0] = (GLfloat)colors(gen) / 10.0f, data[2][1][1][1] = (GLfloat)colors(gen) / 10.0f, data[2][1][1][2] = (GLfloat)colors(gen) / 10.0f;
	data[2][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[2][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[2][1][2][2] = (GLfloat)colors(gen) / 10.0f;

	// 정면 삼각형 좌표
	data[3][0][0][0] = 0.3f, data[3][0][0][1] = -0.3f, data[3][0][0][2] = 0.3f;
	data[3][0][1][0] = 0.0f, data[3][0][1][1] = 0.3f, data[3][0][1][2] = 0.0f;
	data[3][0][2][0] = -0.3f, data[3][0][2][1] = -0.3f, data[3][0][2][2] = 0.3f;

	// 정면 삼각형 색상
	data[3][1][0][0] = (GLfloat)colors(gen) / 10.0f, data[3][1][0][1] = (GLfloat)colors(gen) / 10.0f, data[3][1][0][2] = (GLfloat)colors(gen) / 10.0f;
	data[3][1][1][0] = data[2][1][1][0], data[3][1][1][1] = data[2][1][1][1], data[3][1][1][2] = data[2][1][1][2];
	data[3][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[3][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[3][1][2][2] = (GLfloat)colors(gen) / 10.0f;

	// 좌측 삼각형 좌표
	data[4][0][0][0] = -0.3f, data[4][0][0][1] = -0.3f, data[4][0][0][2] = 0.3f;
	data[4][0][1][0] = 0.0f, data[4][0][1][1] = 0.3f, data[4][0][1][2] = 0.0f;
	data[4][0][2][0] = -0.3f, data[4][0][2][1] = -0.3f, data[4][0][2][2] = -0.3f;

	// 좌측 삼각형 색상
	data[4][1][0][0] = (GLfloat)colors(gen) / 10.0f, data[4][1][0][1] = (GLfloat)colors(gen) / 10.0f, data[4][1][0][2] = (GLfloat)colors(gen) / 10.0f;
	data[4][1][1][0] = data[2][1][1][0], data[4][1][1][1] = data[2][1][1][1], data[4][1][1][2] = data[2][1][1][2];
	data[4][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[4][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[4][1][2][2] = (GLfloat)colors(gen) / 10.0f;

	// 후면 삼각형 좌표
	data[5][0][0][0] = -0.3f, data[5][0][0][1] = -0.3f, data[5][0][0][2] = -0.3f;
	data[5][0][1][0] = 0.0f, data[5][0][1][1] = 0.3f, data[5][0][1][2] = 0.0f;
	data[5][0][2][0] = 0.3f, data[5][0][2][1] = -0.3f, data[5][0][2][2] = -0.3f;

	// 후면 삼각형 색상
	data[5][1][0][0] = (GLfloat)colors(gen) / 10.0f, data[5][1][0][1] = (GLfloat)colors(gen) / 10.0f, data[5][1][0][2] = (GLfloat)colors(gen) / 10.0f;
	data[5][1][1][0] = data[2][1][1][0], data[5][1][1][1] = data[2][1][1][1], data[5][1][1][2] = data[2][1][1][2];
	data[5][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[5][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[5][1][2][2] = (GLfloat)colors(gen) / 10.0f;

}

void Quadrangular_pyramid::initBuffer()
{
	glGenVertexArrays(6, vao);
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(vao[i]);
		glGenBuffers(2, vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}
}
