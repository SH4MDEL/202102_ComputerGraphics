#pragma once
#include "shader.h"
#include "initShader.h"
#include "make_shaderProgram.h"
#include "stdafx.h"
void initBuffer();
void reinitBuffer();

#define DOT_COUNT 480
#define PI 3.141592

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 5);

GLvoid drawScene();
GLvoid mouse(int button, int state, int x, int y);
GLvoid TimerFunction(int value);
GLvoid Reshape(int w, int h);

GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체
GLuint s_program;
GLfloat xPos = 0, yPos = 0;
bool doit = false;

struct VecterArray {
	GLuint vao[DOT_COUNT], vbo[DOT_COUNT][2];
};
VecterArray va;

struct BGD {
	GLfloat bgd[3];
	BGD() {
		bgdset();
	}
	void bgdset()
	{
		for (int i = 0; i < 3; i++) {
			bgd[i] = (GLfloat)dis(gen) / 10.0 + 0.5f;
		}
	}

};
BGD background;

struct Tornado {
	GLfloat data[DOT_COUNT][2][3];
	bool drawed[DOT_COUNT];
	int now;
	GLfloat length;
	int round;

	Tornado() {
		now = 0;
		length = 0.0f;
		round = 0;
		for (int i = 0; i < DOT_COUNT; i++) {
			drawed[i] = false;
		}
	}
	void cursorset(GLfloat mx, GLfloat my) {
		length = 0.0f;
		for (int i = 0; i < DOT_COUNT / 2; i++) {
			data[i][0][0] = mx + (length) * (GLfloat)cos(PI / 40 * round);
			data[i][0][1] = my + (length) * (GLfloat)sin(PI / 40 * round);
			data[i][0][2] = 0.0f;
			length += 0.001f;
			round++;
			data[i][1][0] = 0.0f;
			data[i][1][1] = 0.0f;
			data[i][1][2] = 0.0f;

			glBindVertexArray(va.vao[i]);
			for (int j = 0; j < 2; j++) {
				glBindBuffer(GL_ARRAY_BUFFER, va.vbo[i][j]);
				glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), data[i][j], GL_STATIC_DRAW);
				glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(j);
			}
		}
		for (int i = DOT_COUNT / 2; i < DOT_COUNT; i++) {
			data[i][0][0] = (GLfloat)((0.48f) + mx + (length) * -cos(PI / 40 * round));
			data[i][0][1] = (GLfloat)(my + (length) * -sin(PI / 40 * round));
			data[i][0][2] = 0.0f;
			length -= 0.001f;
			round--;
			data[i][1][0] = 0.0f;
			data[i][1][1] = 0.0f;
			data[i][1][2] = 0.0f;

			glBindVertexArray(va.vao[i]);
			for (int j = 0; j < 2; j++) {
				glBindBuffer(GL_ARRAY_BUFFER, va.vbo[i][j]);
				glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), data[i][j], GL_STATIC_DRAW);
				glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(j);
			}
		}
		//reinitBuffer();
	}
	bool cursorloop() {
		if (now == DOT_COUNT) {
			now = 0;
			return false;
		}
		else {
			drawed[now] = true;
			now++;
			return true;
		}
	}
};
Tornado tornado;

int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("practice 9");

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
	glutTimerFunc(20, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	//--- 변경된 배경색 설정
	glClearColor(background.bgd[0], background.bgd[1], background.bgd[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(s_program);
	glPointSize(3.0);

	for (int i = 0; i < DOT_COUNT; i++) {
		if (tornado.drawed[i] == true) {
			glBindVertexArray(va.vao[i]);
			glDrawArrays(GL_POINTS, 0, 1);
		}
	}

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid mouse(int button, int state, int x, int y) 
{
	y = -(y - glutGet(GLUT_WINDOW_HEIGHT));
	xPos = (((GLclampf)x - ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0));
	yPos = (((GLclampf)y - ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0));

	if (doit == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		background.bgdset();
		for (int i = 0; i < DOT_COUNT; i++) {
			tornado.drawed[i] = false;
		}
		tornado.cursorset(xPos, yPos);
		doit = true;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		glutLeaveMainLoop();
	}

}

GLvoid TimerFunction(int value)
{
	if (doit) {
		if (tornado.cursorloop()) {
			glutPostRedisplay();
			glutTimerFunc(20, TimerFunction, value);
		}
		else {
			doit = false;
			glutPostRedisplay();
			glutTimerFunc(20, TimerFunction, value);
		}
	}
	else {
		glutPostRedisplay();
		glutTimerFunc(20, TimerFunction, value);
	}
	return;
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

void initBuffer()
{
	glGenVertexArrays(DOT_COUNT, va.vao); //--- VAO 를 지정하고 할당하기
	for (int i = 0; i < DOT_COUNT; i++) {
		glBindVertexArray(va.vao[i]);

		glGenBuffers(2, va.vbo[i]); //--- 2개의 VBO를 지정하고 할당하기
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, va.vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), tornado.data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}
}

void reinitBuffer()
{
	for (int i = 0; i < DOT_COUNT; i++) {
		glBindVertexArray(va.vao[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, va.vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), tornado.data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}
}
