#pragma once
#include "shader.h"
#include "initShader.h"
#include "make_shaderProgram.h"
#include "stdafx.h"
void initBuffer();
void reinitEraserBuffer();
void reinitRectangleBuffer();

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 200);
std::uniform_int_distribution<int> colors(0, 10);

GLvoid drawScene();
GLvoid motion(int x, int y);
GLvoid mouse(int button, int state, int x, int y);
GLvoid Reshape(int w, int h);

GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체
GLuint s_program;

GLclampf xPos = 0, yPos = 0;

struct VecterArray {
	GLuint rectanglevao[100][2], rectanglevbo[100][2][2];
	GLuint eraservao[2], eraservbo[2][2];
};
VecterArray va;

struct _Eraser {
	GLfloat data[2][2][3][3];
	bool run;
	_Eraser() {
		run = false;
		data[0][0][0][0] = 0.0f, data[0][0][0][1] = 0.0f, data[0][0][0][2] = 0.0f;		// 위치
		data[0][0][1][0] = 0.0f, data[0][0][1][1] = 0.0f, data[0][0][1][2] = 0.0f;
		data[0][0][2][0] = 0.0f, data[0][0][2][1] = 0.0f, data[0][0][2][2] = 0.0f;

		data[0][1][0][0] = 0.0f, data[0][1][0][1] = 0.0f, data[0][1][0][2] = 0.0f;		// 색상
		data[0][1][1][0] = 0.0f, data[0][1][1][1] = 0.0f, data[0][1][1][2] = 0.0f;
		data[0][1][2][0] = 0.0f, data[0][1][2][1] = 0.0f, data[0][1][2][2] = 0.0f;

		data[1][0][0][0] = 0.0f, data[1][0][0][1] = 0.0f, data[1][0][0][2] = 0.0f;		// 위치
		data[1][0][1][0] = 0.0f, data[1][0][1][1] = 0.0f, data[1][0][1][2] = 0.0f;
		data[1][0][2][0] = 0.0f, data[1][0][2][1] = 0.0f, data[1][0][2][2] = 0.0f;

		data[1][1][0][0] = 0.0f, data[1][1][0][1] = 0.0f, data[1][1][0][2] = 0.0f;		// 색상
		data[1][1][1][0] = 0.0f, data[1][1][1][1] = 0.0f, data[1][1][1][2] = 0.0f;
		data[1][1][2][0] = 0.0f, data[1][1][2][1] = 0.0f, data[1][1][2][2] = 0.0f;
	}
	void setCoordinate(GLfloat mx, GLfloat my) {
		data[0][0][0][0] = mx - 0.04f, data[0][0][0][1] = my - 0.04f, data[0][0][0][2] = 0.0f;		// 위치
		data[0][0][1][0] = mx + 0.04f, data[0][0][1][1] = my - 0.04f, data[0][0][1][2] = 0.0f;
		data[0][0][2][0] = mx + 0.04f, data[0][0][2][1] = my + 0.04f, data[0][0][2][2] = 0.0f;

		data[1][0][0][0] = mx + 0.04f, data[1][0][0][1] = my + 0.04f, data[1][0][0][2] = 0.0f;		// 위치
		data[1][0][1][0] = mx - 0.04f, data[1][0][1][1] = my + 0.04f, data[1][0][1][2] = 0.0f;
		data[1][0][2][0] = mx - 0.04f, data[1][0][2][1] = my - 0.04f, data[1][0][2][2] = 0.0f;
	}
};
_Eraser eraser;

struct _Rectangle {
	GLfloat x, y, r, g, b;
	GLfloat data[100][2][2][3][3];
	bool drawed[100];
	_Rectangle() {
		for (int i = 0; i < 100; i++) {
			x = ((dis(gen) - 100.0f) / 100.0f);
			y = ((dis(gen) - 100.0f) / 100.0f);
			r = (GLfloat)colors(gen) / 10.0f;
			g = (GLfloat)colors(gen) / 10.0f;
			b = (GLfloat)colors(gen) / 10.0f;
			drawed[i] = true;
			data[i][0][0][0][0] = x - 0.02f, data[i][0][0][0][1] = y - 0.02f, data[i][0][0][0][2] = 0.0f;		// 위치
			data[i][0][0][1][0] = x + 0.02f, data[i][0][0][1][1] = y - 0.02f, data[i][0][0][1][2] = 0.0f;
			data[i][0][0][2][0] = x + 0.02f, data[i][0][0][2][1] = y + 0.02f, data[i][0][0][2][2] = 0.0f;

			data[i][0][1][0][0] = r, data[i][0][1][0][1] = g, data[i][0][1][0][2] = b;		// 색상
			data[i][0][1][1][0] = r, data[i][0][1][1][1] = g, data[i][0][1][1][2] = b;
			data[i][0][1][2][0] = r, data[i][0][1][2][1] = g, data[i][0][1][2][2] = b;

			data[i][1][0][0][0] = x + 0.02f, data[i][1][0][0][1] = y + 0.02f, data[i][1][0][0][2] = 0.0f;		// 위치
			data[i][1][0][1][0] = x - 0.02f, data[i][1][0][1][1] = y + 0.02f, data[i][1][0][1][2] = 0.0f;
			data[i][1][0][2][0] = x - 0.02f, data[i][1][0][2][1] = y - 0.02f, data[i][1][0][2][2] = 0.0f;

			data[i][1][1][0][0] = r, data[i][1][1][0][1] = g, data[i][1][1][0][2] = b;		// 색상
			data[i][1][1][1][0] = r, data[i][1][1][1][1] = g, data[i][1][1][1][2] = b;
			data[i][1][1][2][0] = r, data[i][1][1][2][1] = g, data[i][1][1][2][2] = b;
		}
	}
	void CollideCheck(GLfloat ex, GLfloat ey) {
		for (int i = 0; i < 100; i++) {
			if (drawed[i] == true && data[i][0][0][0][0] <= ex + 0.04f && data[i][0][0][2][0] >= ex - 0.04f &&
				data[i][0][0][0][1] <= ey + 0.04f && data[i][0][0][2][1] >= ey - 0.04f) {
				drawed[i] = false;
			}
		}
	}
};
_Rectangle rectangle;


int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 1200);
	glutCreateWindow("practice 12");

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
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
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

	for (int i = 0; i < 100; i++) {
		if (rectangle.drawed[i] == true) {
			for (int j = 0; j < 2; j++) {
				if (rectangle.drawed[i] == true) {
					glBindVertexArray(va.rectanglevao[i][j]);
					glDrawArrays(GL_TRIANGLES, 0, 3);
				}
			}
		}
	}

	if (eraser.run == true) {
		for (int i = 0; i < 2; i++) {
			glBindVertexArray(va.eraservao[i]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid mouse(int button, int state, int x, int y) {

	y = -(y - glutGet(GLUT_WINDOW_HEIGHT));
	xPos = (((GLclampf)x - ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0));
	yPos = (((GLclampf)y - ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0));
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		eraser.run = true;
	}
	else if (state == GLUT_UP) {
		eraser.run = false;
	}
}

GLvoid motion(int x, int y)
{
	if (eraser.run == true) {
		y = -(y - glutGet(GLUT_WINDOW_HEIGHT));
		xPos = (((GLclampf)x - ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0));
		yPos = (((GLclampf)y - ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0));
		eraser.setCoordinate(xPos, yPos);
		rectangle.CollideCheck(xPos, yPos);
		reinitEraserBuffer();
		glutPostRedisplay();
	}

}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

void initBuffer()
{
	for (int i = 0; i < 100; i++) {
		glGenVertexArrays(2, va.rectanglevao[i]);
		for (int j = 0; j < 2; j++) {
			glBindVertexArray(va.rectanglevao[i][j]);
			glGenBuffers(2, va.rectanglevbo[i][j]);
			for (int k = 0; k < 2; k++) {
				glBindBuffer(GL_ARRAY_BUFFER, va.rectanglevbo[i][j][k]);
				glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), rectangle.data[i][j][k], GL_STATIC_DRAW);
				glVertexAttribPointer(k, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(k);
			}
		}
	}

	glGenVertexArrays(2, va.eraservao);
	for (int i = 0; i < 2; i++) {
		glBindVertexArray(va.eraservao[i]);
		glGenBuffers(2, va.eraservbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, va.eraservbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), eraser.data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}
}

void reinitEraserBuffer()
{
	for (int i = 0; i < 2; i++) {
		glBindVertexArray(va.eraservao[i]);
		glGenBuffers(2, va.eraservbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, va.eraservbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), eraser.data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}
}

void reinitRectangleBuffer()
{
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 2; j++) {
			glBindVertexArray(va.rectanglevao[i][j]);
			glGenBuffers(2, va.rectanglevbo[i][j]);
			for (int k = 0; k < 2; k++) {
				glBindBuffer(GL_ARRAY_BUFFER, va.rectanglevbo[i][j][k]);
				glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), rectangle.data[i][j][k], GL_STATIC_DRAW);
				glVertexAttribPointer(k, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(k);
			}
		}
	}
}
