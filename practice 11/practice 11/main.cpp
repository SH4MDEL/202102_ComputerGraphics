#pragma once
#include "shader.h"
#include "initShader.h"
#include "make_shaderProgram.h"
#include "stdafx.h"
void initBuffer();
void reinitBuffer();

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> colors(0, 10);

bool isDivide(GLfloat x11, GLfloat y11, GLfloat x12, GLfloat y12, GLfloat x21, GLfloat y21, GLfloat x22, GLfloat y22);
bool isCross(GLfloat x11, GLfloat y11, GLfloat x12, GLfloat y12, GLfloat x21, GLfloat y21, GLfloat x22, GLfloat y22);
bool isIn(GLfloat mx, GLfloat my);

GLvoid drawScene();
GLvoid motion(int x, int y);
GLvoid mouse(int button, int state, int x, int y);
GLvoid Reshape(int w, int h);

GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체
GLuint s_program;

GLclampf xPos = 0, yPos = 0, myxPos = 0, myyPos = 0;

struct VecterArray {
	GLuint linevao[2], linevbo[2][2];
	GLuint rectanglevao[2], rectanglevbo[2][2];
};
VecterArray va;


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

struct _Rectangle {
	GLfloat data[2][2][3][3];
	bool clicked, sized;
	_Rectangle() {
		clicked = false, sized = false;
		data[0][0][0][0] = -0.5f, data[0][0][0][1] = -0.5f, data[0][0][0][2] = 0.0f;		// 위치
		data[0][0][1][0] = 0.5f, data[0][0][1][1] = -0.5f, data[0][0][1][2] = 0.0f;
		data[0][0][2][0] = 0.5f, data[0][0][2][1] = 0.5f, data[0][0][2][2] = 0.0f;

		data[0][1][0][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][2] = (GLfloat)colors(gen) / 10.0f;		// 색상
		data[0][1][1][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][1][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][1][2] = (GLfloat)colors(gen) / 10.0f;
		data[0][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][2][2] = (GLfloat)colors(gen) / 10.0f;

		data[1][0][0][0] = 0.5f, data[1][0][0][1] = 0.5f, data[1][0][0][2] = 0.0f;		// 위치
		data[1][0][1][0] = -0.5f, data[1][0][1][1] = 0.5f, data[1][0][1][2] = 0.0f;
		data[1][0][2][0] = -0.5f, data[1][0][2][1] = -0.5f, data[1][0][2][2] = 0.0f;

		data[1][1][0][0] = data[0][1][2][0], data[1][1][0][1] = data[0][1][2][1], data[1][1][0][2] = data[0][1][2][2];		// 색상
		data[1][1][1][0] = (GLfloat)colors(gen) / 10.0f, data[1][1][1][1] = (GLfloat)colors(gen) / 10.0f, data[1][1][1][2] = (GLfloat)colors(gen) / 10.0f;
		data[1][1][2][0] = data[0][1][0][0], data[1][1][2][1] = data[0][1][0][1], data[1][1][2][2] = data[0][1][0][2];
	}
	void releftdown(GLfloat x, GLfloat y) {
		data[0][0][0][0] = x, data[0][0][0][1] = y;
		data[1][0][2][0] = x, data[1][0][2][1] = y;
	}
	void rerightdown(GLfloat x, GLfloat y) {
		data[0][0][1][0] = x, data[0][0][1][1] = y;
	}
	void rerightup(GLfloat x, GLfloat y) {
		data[0][0][2][0] = x, data[0][0][2][1] = y;
		data[1][0][0][0] = x, data[1][0][0][1] = y;
	}
	void releftup(GLfloat x, GLfloat y) {
		data[1][0][1][0] = x, data[1][0][1][1] = y;
	}
	void setposi(GLfloat x, GLfloat y) {
		data[0][0][0][0] = -0.5f, data[0][0][0][1] = -0.5f, data[0][0][0][2] = 0.0f;		// 위치
		data[0][0][1][0] = 0.5f, data[0][0][1][1] = -0.5f, data[0][0][1][2] = 0.0f;
		data[0][0][2][0] = 0.5f, data[0][0][2][1] = 0.5f, data[0][0][2][2] = 0.0f;

		data[1][0][0][0] = 0.5f, data[1][0][0][1] = 0.5f, data[1][0][0][2] = 0.0f;		// 위치
		data[1][0][1][0] = -0.5f, data[1][0][1][1] = 0.5f, data[1][0][1][2] = 0.0f;
		data[1][0][2][0] = -0.5f, data[1][0][2][1] = -0.5f, data[1][0][2][2] = 0.0f;
	}
};
_Rectangle rectangle;


int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("practice 11");

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

	for (int i = 0; i < 2; i++) {
		glBindVertexArray(va.linevao[i]);
		glDrawArrays(GL_LINES, 0, 2);
	}

	for (int i = 0; i < 2; i++) {
		glBindVertexArray(va.rectanglevao[i]);
		glDrawArrays(GL_LINE_STRIP, 0, 3);
	}

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid mouse(int button, int state, int x, int y) {

	y = -(y - glutGet(GLUT_WINDOW_HEIGHT));
	myxPos = (((GLclampf)x - ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0));
	myyPos = (((GLclampf)y - ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0));
	xPos = (((GLclampf)x - ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0));
	yPos = (((GLclampf)y - ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0));
	if (button == GLUT_LEFT_BUTTON) {
		rectangle.clicked = true;
		rectangle.sized = false;
	}
}

GLvoid motion(int x, int y)
{
	if (rectangle.clicked == true && x >= 0 && x <= glutGet(GLUT_WINDOW_WIDTH) && y >= 0 && y <= glutGet(GLUT_WINDOW_HEIGHT)) {
		y = -(y - glutGet(GLUT_WINDOW_HEIGHT));
		xPos = (((GLclampf)x - ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0));
		yPos = (((GLclampf)y - ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0));
		if (xPos < 0 && yPos < 0 && rectangle.data[0][0][0][0] >= xPos - 0.05 && rectangle.data[0][0][0][0] <= xPos + 0.05 && 
			rectangle.data[0][0][0][1] >= yPos - 0.05 && rectangle.data[0][0][0][1] <= yPos + 0.05) {
			rectangle.releftdown(xPos, yPos);
			rectangle.sized = true;
		}
		else if (xPos > 0 && yPos < 0 && rectangle.data[0][0][1][0] >= xPos - 0.05 && rectangle.data[0][0][1][0] <= xPos + 0.05 &&
			rectangle.data[0][0][1][1] >= yPos - 0.05 && rectangle.data[0][0][1][1] <= yPos + 0.05) {
			rectangle.rerightdown(xPos, yPos);
			rectangle.sized = true;
		}
		else if (xPos > 0 && yPos > 0 && rectangle.data[0][0][2][0] >= xPos - 0.05 && rectangle.data[0][0][2][0] <= xPos + 0.05 &&
			rectangle.data[0][0][2][1] >= yPos - 0.05 && rectangle.data[0][0][2][1] <= yPos + 0.05) {
			rectangle.rerightup(xPos, yPos);
			rectangle.sized = true;
		}
		else if (xPos < 0 && yPos > 0 && rectangle.data[1][0][1][0] >= xPos - 0.05 && rectangle.data[1][0][1][0] <= xPos + 0.05 &&
			rectangle.data[1][0][1][1] >= yPos - 0.05 && rectangle.data[1][0][1][1] <= yPos + 0.05) {
			rectangle.releftup(xPos, yPos);
			rectangle.sized = true;
		}
		else if (isIn(xPos, yPos) && rectangle.sized == false) {
			if ((rectangle.data[0][0][0][0] < -0.02f && myxPos - xPos <= 0) || (myxPos - xPos >= 0)) {
				rectangle.data[0][0][0][0] -= myxPos - xPos;
				rectangle.data[1][0][2][0] -= myxPos - xPos;
			}
			if ((rectangle.data[0][0][0][1] < -0.02f && myyPos - yPos <= 0) || (myyPos - yPos >= 0)) {
				rectangle.data[0][0][0][1] -= myyPos - yPos;
				rectangle.data[1][0][2][1] -= myyPos - yPos;
			}
			if ((rectangle.data[0][0][1][0] > 0.02f && myxPos - xPos >= 0) || (myxPos - xPos <= 0)) {
				rectangle.data[0][0][1][0] -= myxPos - xPos;
			}
			if ((rectangle.data[0][0][1][1] < -0.02f && myyPos - yPos <= 0) || (myyPos - yPos >= 0)) {
				rectangle.data[0][0][1][1] -= myyPos - yPos;
			}

			if ((rectangle.data[0][0][2][0] > 0.02f && myxPos - xPos >= 0) || (myxPos - xPos <= 0)) {
				rectangle.data[0][0][2][0] -= myxPos - xPos;
				rectangle.data[1][0][0][0] -= myxPos - xPos;
			}
			if ((rectangle.data[0][0][2][1] > 0.02f && myyPos - yPos >= 0) || (myyPos - yPos <= 0)) {
				rectangle.data[0][0][2][1] -= myyPos - yPos;
				rectangle.data[1][0][0][1] -= myyPos - yPos;
			}
			if ((rectangle.data[1][0][1][0] < -0.02f && myxPos - xPos <= 0) || (myxPos - xPos >= 0)) {
				rectangle.data[1][0][1][0] -= myxPos - xPos;
			}
			if ((rectangle.data[1][0][1][1] > 0.02f && myyPos - yPos >= 0) || (myyPos - yPos <= 0)) {
				rectangle.data[1][0][1][1] -= myyPos - yPos;
			}
			myxPos = xPos;
			myyPos = yPos;
		}
		else {
			rectangle.clicked = false;
			rectangle.sized = false;
		}
		reinitBuffer();
		glutPostRedisplay();
	}
	else {
		rectangle.clicked = false;
	}
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

void initBuffer()
{
	glGenVertexArrays(2, va.linevao);
	for (int i = 0; i < 2; i++) {
		glBindVertexArray(va.linevao[i]);
		glGenBuffers(2, va.linevbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, va.linevbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), line.data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}

	glGenVertexArrays(2, va.rectanglevao);
	for (int i = 0; i < 2; i++) {
		glBindVertexArray(va.rectanglevao[i]);
		glGenBuffers(3, va.rectanglevbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, va.rectanglevbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), rectangle.data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}
}

void reinitBuffer()
{
	for (int i = 0; i < 2; i++) {
		glBindVertexArray(va.rectanglevao[i]);
		glGenBuffers(3, va.rectanglevbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, va.rectanglevbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), rectangle.data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}
}

bool isDivide(GLfloat x11, GLfloat y11, GLfloat x12, GLfloat y12, GLfloat x21, GLfloat y21, GLfloat x22, GLfloat y22)
{
	GLfloat f1 = (x12 - x11) * (y21 - y11) - (y12 - y11) * (x21 - x11);
	GLfloat f2 = (x12 - x11) * (y22 - y11) - (y12 - y11) * (x22 - x11);
	if (f1 * f2 < 0) {
		return true;
	}
	return false;
}

bool isCross(GLfloat x11, GLfloat y11, GLfloat x12, GLfloat y12, GLfloat x21, GLfloat y21, GLfloat x22, GLfloat y22)
{
	GLfloat b1 = isDivide(x11, y11, x12, y12, x21, y21, x22, y22);
	GLfloat b2 = isDivide(x21, y21, x22, y22, x11, y11, x12, y12);
	if (b1 && b2) {
		return true;
	}
	return false;
}

bool isIn(GLfloat mx, GLfloat my)
{
	int crosspoint = 0;
	if (isCross(mx, my, 5.0f, 5.0f, rectangle.data[0][0][0][0], rectangle.data[0][0][0][1], rectangle.data[0][0][1][0], rectangle.data[0][0][1][1])) {
		crosspoint++;
	}
	if (isCross(mx, my, 5.0f, 5.0f, rectangle.data[0][0][1][0], rectangle.data[0][0][0][1], rectangle.data[0][0][2][0], rectangle.data[0][0][2][1])) {
		crosspoint++;
	}
	if (isCross(mx, my, 5.0f, 5.0f, rectangle.data[0][0][2][0], rectangle.data[0][0][2][1], rectangle.data[1][0][1][0], rectangle.data[1][0][1][1])) {
		crosspoint++;
	}
	if (isCross(mx, my, 5.0f, 5.0f, rectangle.data[1][0][1][0], rectangle.data[1][0][1][1], rectangle.data[0][0][0][0], rectangle.data[0][0][0][1])) {
		crosspoint++;
	}
	if (crosspoint % 2 == 1) {
		return true;
	}
	return false;
}