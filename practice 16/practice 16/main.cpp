#pragma once
#include "shader.h"
#include "initShader.h"
#include "make_shaderProgram.h"
#include "stdafx.h"

#define DOT_COUNT 500
#define PI 3.141592

void initBuffer();

GLvoid drawScene();
GLvoid Keyboard(unsigned char inputKey, int x, int y);
GLvoid TimerFunction(int value);
GLvoid Reshape(int w, int h);

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> colors(0, 10);

GLchar *vertexSource, *fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체
GLuint s_program;

struct VectexArray {
	GLuint vao[DOT_COUNT], vbo[DOT_COUNT][2];
	GLuint line_vao[3], line_vbo[3][2];
	GLuint hexahedron_vao[6], hexahedron_vbo[6][2];
	GLuint tetrahedron_vao[6], tetrahedron_vbo[6][2];
};
VectexArray va;

struct RunControl {
	bool rRotate;
	float xRotateObject, zRotateObject;

	float linexPos, linezPos;
	float lTranslatePos;

	float xTranslatePos, yTranslatePos, zTranslatePos;

	float aTranslatePos, bTranslatePos, cTranslatePos;

	float scaleByStandard, scaleByObject;


	RunControl() {
		reset();
	}
	void reset() {
		rRotate = false;
		xRotateObject = 0.0f, zRotateObject = 0.0f;

		linexPos = 0.0f, linezPos = 0.0f;
		lTranslatePos = 0.0f;
		xTranslatePos = -0.5f, yTranslatePos = 0.0f, zTranslatePos = 0.0f;
		aTranslatePos = 0.5f, bTranslatePos = 0.0f, cTranslatePos = 0.0f;
		scaleByStandard = 1.0f, scaleByObject = 1.0f;
	}
};
RunControl rc;

struct Tornado {
	GLfloat data[DOT_COUNT][2][3];
	bool drawed[DOT_COUNT];
	int now;
	GLfloat length;
	int round, loop;

	Tornado() {
		now = 0;
		length = 0.0f;
		round = 0;
		for (int i = 0; i < DOT_COUNT; i++) {
			data[i][0][0] = (length) * (GLfloat)cos(PI / 40 * round);
			data[i][0][1] = 0.0f;
			data[i][0][2] = (length) * (GLfloat)sin(PI / 40 * round);
			length += 0.002f;
			round++;
			data[i][1][0] = 0.0f;
			data[i][1][1] = 0.0f;
			data[i][1][2] = 0.0f;
		}
		loop = 0;
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
	float nextX() {
		return data[loop][0][0];
	}
	float nextZ() {
		return data[loop][0][2];
	}
};
Tornado tornado;

struct _Line {
	GLfloat data[3][2][2][3];
	_Line() {
		data[0][0][0][0] = 1.0f, data[0][0][0][1] = 0.0f, data[0][0][0][2] = 0.0f;		// 위치
		data[0][0][1][0] = -1.0f, data[0][0][1][1] = 0.0f, data[0][0][1][2] = 0.0f;

		data[0][1][0][0] = 0.0f, data[0][1][0][1] = 0.0f, data[0][1][0][2] = 0.0f;		// 색상
		data[0][1][1][0] = 0.0f, data[0][1][1][1] = 0.0f, data[0][1][1][2] = 0.0f;

		data[1][0][0][0] = 0.0f, data[1][0][0][1] = 1.0f, data[1][0][0][2] = 0.0f;		// 위치
		data[1][0][1][0] = 0.0f, data[1][0][1][1] = -1.0f, data[1][0][1][2] = 0.0f;

		data[1][1][0][0] = 0.0f, data[1][1][0][1] = 0.0f, data[1][1][0][2] = 0.0f;		// 색상
		data[1][1][1][0] = 0.0f, data[1][1][1][1] = 0.0f, data[1][1][1][2] = 0.0f;

		data[2][0][0][0] = 0.0f, data[2][0][0][1] = 0.0f, data[2][0][0][2] = 1.0f;		// 위치
		data[2][0][1][0] = 0.0f, data[2][0][1][1] = 0.0f, data[2][0][1][2] = -1.0f;

		data[2][1][0][0] = 0.0f, data[2][1][0][1] = 0.0f, data[2][1][0][2] = 0.0f;		// 색상
		data[2][1][1][0] = 0.0f, data[2][1][1][1] = 0.0f, data[2][1][1][2] = 0.0f;
	}
};
_Line line;

struct Hexahedron {
	GLfloat data[6][2][2][3][3];
	bool drawed;
	Hexahedron() {

		// 전면 좌표
		data[0][0][0][0][0] = -0.15f, data[0][0][0][0][1] = -0.15f, data[0][0][0][0][2] = 0.15f;
		data[0][0][0][1][0] = 0.15f, data[0][0][0][1][1] = -0.15f, data[0][0][0][1][2] = 0.15f;
		data[0][0][0][2][0] = -0.15f, data[0][0][0][2][1] = 0.15f, data[0][0][0][2][2] = 0.15f;

		data[0][0][1][0][0] = -0.15f, data[0][0][1][0][1] = 0.15f, data[0][0][1][0][2] = 0.15f;
		data[0][0][1][1][0] = 0.15f, data[0][0][1][1][1] = -0.15f, data[0][0][1][1][2] = 0.15f;
		data[0][0][1][2][0] = 0.15f, data[0][0][1][2][1] = 0.15f, data[0][0][1][2][2] = 0.15f;

		// 전면 색상
		data[0][1][0][0][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][0][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][0][2] = (GLfloat)colors(gen) / 10.0f;
		data[0][1][0][1][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][1][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][1][2] = (GLfloat)colors(gen) / 10.0f;
		data[0][1][0][2][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][2][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][2][2] = (GLfloat)colors(gen) / 10.0f;

		data[0][1][1][0][0] = data[0][1][0][2][0], data[0][1][1][0][1] = data[0][1][0][2][1], data[0][1][1][0][2] = data[0][1][0][2][2];
		data[0][1][1][1][0] = data[0][1][0][1][0], data[0][1][1][1][1] = data[0][1][0][1][1], data[0][1][1][1][2] = data[0][1][0][1][2];
		data[0][1][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][1][2][2] = (GLfloat)colors(gen) / 10.0f;


		// 상단 좌표
		data[1][0][0][0][0] = 0.15f, data[1][0][0][0][1] = 0.15f, data[1][0][0][0][2] = 0.15f;
		data[1][0][0][1][0] = 0.15f, data[1][0][0][1][1] = 0.15f, data[1][0][0][1][2] = -0.15f;
		data[1][0][0][2][0] = -0.15f, data[1][0][0][2][1] = 0.15f, data[1][0][0][2][2] = 0.15f;

		data[1][0][1][0][0] = -0.15f, data[1][0][1][0][1] = 0.15f, data[1][0][1][0][2] = 0.15f;
		data[1][0][1][1][0] = 0.15f, data[1][0][1][1][1] = 0.15f, data[1][0][1][1][2] = -0.15f;
		data[1][0][1][2][0] = -0.15f, data[1][0][1][2][1] = 0.15f, data[1][0][1][2][2] = -0.15f;

		// 상단 색상
		data[1][1][0][0][0] = data[0][1][1][2][0], data[1][1][0][0][1] = data[0][1][1][2][1], data[1][1][0][0][2] = data[0][1][1][2][2];
		data[1][1][0][1][0] = (GLfloat)colors(gen) / 10.0f, data[1][1][0][1][1] = (GLfloat)colors(gen) / 10.0f, data[1][1][0][1][2] = (GLfloat)colors(gen) / 10.0f;
		data[1][1][0][2][0] = data[0][1][0][2][0], data[1][1][0][2][1] = data[0][1][0][2][1], data[1][1][0][2][2] = data[0][1][0][2][2];

		data[1][1][1][0][0] = data[0][1][0][2][0], data[1][1][1][0][1] = data[0][1][0][2][1], data[1][1][1][0][2] = data[0][1][0][2][2];
		data[1][1][1][1][0] = data[1][1][0][1][0], data[1][1][1][1][1] = data[1][1][0][1][1], data[1][1][1][1][2] = data[1][1][0][1][2];
		data[1][1][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[1][1][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[1][1][1][2][2] = (GLfloat)colors(gen) / 10.0f;

		// 좌측 좌표
		data[2][0][0][0][0] = -0.15f, data[2][0][0][0][1] = 0.15f, data[2][0][0][0][2] = -0.15f;
		data[2][0][0][1][0] = -0.15f, data[2][0][0][1][1] = -0.15f, data[2][0][0][1][2] = -0.15f;
		data[2][0][0][2][0] = -0.15f, data[2][0][0][2][1] = -0.15f, data[2][0][0][2][2] = 0.15f;

		data[2][0][1][0][0] = -0.15f, data[2][0][1][0][1] = -0.15f, data[2][0][1][0][2] = 0.15f;
		data[2][0][1][1][0] = -0.15f, data[2][0][1][1][1] = 0.15f, data[2][0][1][1][2] = 0.15f;
		data[2][0][1][2][0] = -0.15f, data[2][0][1][2][1] = 0.15f, data[2][0][1][2][2] = -0.15f;

		// 좌측 색상
		data[2][1][0][0][0] = data[1][1][1][2][0], data[2][1][0][0][1] = data[1][1][1][2][1], data[2][1][0][0][2] = data[1][1][1][2][2];
		data[2][1][0][1][0] = (GLfloat)colors(gen) / 10.0f, data[2][1][0][1][1] = (GLfloat)colors(gen) / 10.0f, data[2][1][0][1][2] = (GLfloat)colors(gen) / 10.0f;
		data[2][1][0][2][0] = data[0][1][0][0][0], data[2][1][0][2][1] = data[0][1][0][0][1], data[2][1][0][2][2] = data[0][1][0][0][2];

		data[2][1][1][0][0] = data[0][1][0][0][0], data[2][1][1][0][1] = data[0][1][0][0][1], data[2][1][1][0][2] = data[0][1][0][0][2];
		data[2][1][1][1][0] = data[0][1][0][2][0], data[2][1][1][1][1] = data[0][1][0][2][1], data[2][1][1][1][2] = data[0][1][0][2][2];
		data[2][1][1][2][0] = data[1][1][1][2][0], data[2][1][1][2][1] = data[1][1][1][2][1], data[2][1][1][2][2] = data[1][1][1][2][2];

		// 후면 좌표
		data[3][0][0][0][0] = -0.15f, data[3][0][0][0][1] = 0.15f, data[3][0][0][0][2] = -0.15f;
		data[3][0][0][1][0] = -0.15f, data[3][0][0][1][1] = -0.15f, data[3][0][0][1][2] = -0.15f;
		data[3][0][0][2][0] = 0.15f, data[3][0][0][2][1] = 0.15f, data[3][0][0][2][2] = -0.15f;

		data[3][0][1][0][0] = 0.15f, data[3][0][1][0][1] = 0.15f, data[3][0][1][0][2] = -0.15f;
		data[3][0][1][1][0] = -0.15f, data[3][0][1][1][1] = -0.15f, data[3][0][1][1][2] = -0.15f;
		data[3][0][1][2][0] = 0.15f, data[3][0][1][2][1] = -0.15f, data[3][0][1][2][2] = -0.15f;

		// 후면 색상
		data[3][1][0][0][0] = data[1][1][1][2][0], data[3][1][0][0][1] = data[1][1][1][2][1], data[3][1][0][0][2] = data[1][1][1][2][2];
		data[3][1][0][1][0] = data[2][1][0][1][0], data[3][1][0][1][1] = data[2][1][0][1][1], data[3][1][0][1][2] = data[2][1][0][1][2];
		data[3][1][0][2][0] = data[1][1][0][1][0], data[3][1][0][2][1] = data[1][1][0][1][1], data[3][1][0][2][2] = data[1][1][0][1][2];

		data[3][1][1][0][0] = data[1][1][0][1][0], data[3][1][1][0][1] = data[1][1][0][1][1], data[3][1][1][0][2] = data[1][1][0][1][2];
		data[3][1][1][1][0] = data[2][1][0][1][0], data[3][1][1][1][1] = data[2][1][0][1][1], data[3][1][1][1][2] = data[2][1][0][1][2];
		data[3][1][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[3][1][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[3][1][1][2][2] = (GLfloat)colors(gen) / 10.0f;

		// 하단 좌표
		data[4][0][0][0][0] = 0.15f, data[4][0][0][0][1] = -0.15f, data[4][0][0][0][2] = -0.15f;
		data[4][0][0][1][0] = 0.15f, data[4][0][0][1][1] = -0.15f, data[4][0][0][1][2] = 0.15f;
		data[4][0][0][2][0] = -0.15f, data[4][0][0][2][1] = -0.15f, data[4][0][0][2][2] = 0.15f;

		data[4][0][1][0][0] = -0.15f, data[4][0][1][0][1] = -0.15f, data[4][0][1][0][2] = 0.15f;
		data[4][0][1][1][0] = -0.15f, data[4][0][1][1][1] = -0.15f, data[4][0][1][1][2] = -0.15f;
		data[4][0][1][2][0] = 0.15f, data[4][0][1][2][1] = -0.15f, data[4][0][1][2][2] = -0.15f;

		// 하단 색상
		data[4][1][0][0][0] = data[3][1][1][2][0], data[4][1][0][0][1] = data[3][1][1][2][1], data[4][1][0][0][2] = data[3][1][1][2][2];
		data[4][1][0][1][0] = data[0][1][0][1][0], data[4][1][0][1][1] = data[0][1][0][1][1], data[4][1][0][1][2] = data[0][1][0][1][2];
		data[4][1][0][2][0] = data[0][1][0][0][0], data[4][1][0][2][1] = data[0][1][0][0][1], data[4][1][0][2][2] = data[0][1][0][0][2];

		data[4][1][1][0][0] = data[0][1][0][0][0], data[4][1][1][0][1] = data[0][1][0][0][1], data[4][1][1][0][2] = data[0][1][0][0][2];
		data[4][1][1][1][0] = data[2][1][0][1][0], data[4][1][1][1][1] = data[2][1][0][1][1], data[4][1][1][1][2] = data[2][1][0][1][2];
		data[4][1][1][2][0] = data[3][1][1][2][0], data[4][1][1][2][1] = data[3][1][1][2][1], data[4][1][1][2][2] = data[3][1][1][2][2];

		// 우측 좌표
		data[5][0][0][0][0] = 0.15f, data[5][0][0][0][1] = -0.15f, data[5][0][0][0][2] = -0.15f;
		data[5][0][0][1][0] = 0.15f, data[5][0][0][1][1] = 0.15f, data[5][0][0][1][2] = -0.15f;
		data[5][0][0][2][0] = 0.15f, data[5][0][0][2][1] = -0.15f, data[5][0][0][2][2] = 0.15f;

		data[5][0][1][0][0] = 0.15f, data[5][0][1][0][1] = -0.15f, data[5][0][1][0][2] = 0.15f;
		data[5][0][1][1][0] = 0.15f, data[5][0][1][1][1] = 0.15f, data[5][0][1][1][2] = -0.15f;
		data[5][0][1][2][0] = 0.15f, data[5][0][1][2][1] = 0.15f, data[5][0][1][2][2] = 0.15f;
		
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

GLUquadricObj* qobjSphere, *qobjCylinder1, *qobjCylinder2;

int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("practice 16");

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

	unsigned int modelSelected = glGetUniformLocation(s_program, "modelSelect"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 backgroundModel = glm::mat4(1.0f);
	glm::mat4 xyModel = glm::mat4(1.0f);
	glm::mat4 firstModel = glm::mat4(1.0f);
	glm::mat4 secondModel = glm::mat4(1.0f);

	glUniform1i(modelSelected, 0);

	backgroundModel = glm::rotate(backgroundModel, (float)glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0));
	backgroundModel = glm::rotate(backgroundModel, (float)glm::radians(-30.0f), glm::vec3(0.0, 1.0, 0.0));
	unsigned int modelLocation = glGetUniformLocation(s_program, "backgroundModelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(backgroundModel)); //--- modelTransform 변수에 변환 값 적용하기

	glBindVertexArray(va.line_vao[1]);
	glDrawArrays(GL_LINES, 0, 2);


	glUniform1i(modelSelected, 3);

	xyModel = glm::rotate(xyModel, (float)glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0));
	xyModel = glm::rotate(xyModel, (float)glm::radians(-30.0f), glm::vec3(0.0, 1.0, 0.0));
	xyModel = glm::translate(xyModel, glm::vec3(0, rc.lTranslatePos, 0));
	unsigned int xyLocation = glGetUniformLocation(s_program, "xzlineModelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(xyLocation, 1, GL_FALSE, glm::value_ptr(xyModel)); //--- modelTransform 변수에 변환 값 적용하기

	glBindVertexArray(va.line_vao[0]);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(va.line_vao[2]);
	glDrawArrays(GL_LINES, 0, 2);

	if (rc.rRotate) {
		glPointSize(3.0);
		glUniform1i(modelSelected, 0);
		for (int i = 0; i < DOT_COUNT; i++) {
			glBindVertexArray(va.vao[i]);
			glDrawArrays(GL_POINTS, 0, 1);
		}
	}


	glUniform1i(modelSelected, 1);

	firstModel = glm::scale(firstModel, glm::vec3(rc.scaleByStandard, rc.scaleByStandard, rc.scaleByStandard));
	firstModel = glm::rotate(firstModel, (float)glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0));
	firstModel = glm::rotate(firstModel, (float)glm::radians(-30.0f), glm::vec3(0.0, 1.0, 0.0));
	firstModel = glm::translate(firstModel, glm::vec3(rc.xTranslatePos, rc.yTranslatePos, rc.zTranslatePos));
	firstModel = glm::scale(firstModel, glm::vec3(rc.scaleByObject, rc.scaleByObject, rc.scaleByObject));
	firstModel = glm::rotate(firstModel, (float)glm::radians(-30.0f), glm::vec3(1.0, 0.0, 0.0));
	firstModel = glm::rotate(firstModel, (float)glm::radians(30.0f), glm::vec3(0.0, 1.0, 0.0));
	unsigned int firstModelLocation = glGetUniformLocation(s_program, "firstModelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(firstModelLocation, 1, GL_FALSE, glm::value_ptr(firstModel)); //--- modelTransform 변수에 변환 값 적용하기
	for (int i = 0; i < 6; i++) {
		glEnable(GL_DEPTH_TEST);

		glBindVertexArray(va.hexahedron_vao[i]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisable(GL_DEPTH_TEST);
	}

	glUniform1i(modelSelected, 2);

	secondModel = glm::scale(secondModel, glm::vec3(rc.scaleByStandard, rc.scaleByStandard, rc.scaleByStandard));
	secondModel = glm::rotate(secondModel, (float)glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0));
	secondModel = glm::rotate(secondModel, (float)glm::radians(-30.0f), glm::vec3(0.0, 1.0, 0.0));
	if (rc.rRotate) {
		secondModel = glm::translate(secondModel, glm::vec3(rc.xRotateObject, 0.0f, rc.zRotateObject));
	}
	else {
		secondModel = glm::translate(secondModel, glm::vec3(rc.aTranslatePos, rc.bTranslatePos, rc.cTranslatePos));
	}
	secondModel = glm::scale(secondModel, glm::vec3(rc.scaleByObject, rc.scaleByObject, rc.scaleByObject));
	secondModel = glm::rotate(secondModel, (float)glm::radians(-30.0f), glm::vec3(1.0, 0.0, 0.0));
	secondModel = glm::rotate(secondModel, (float)glm::radians(30.0f), glm::vec3(0.0, 1.0, 0.0));
	unsigned int secondModelLocation = glGetUniformLocation(s_program, "secondModelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기
	glUniformMatrix4fv(secondModelLocation, 1, GL_FALSE, glm::value_ptr(secondModel)); //--- modelTransform 변수에 변환 값 적용하기

	qobjSphere = gluNewQuadric(); // 객체 생성하기
	gluQuadricDrawStyle(qobjSphere, GLU_LINE); // 도형 스타일
	gluQuadricNormals(qobjSphere, GLU_SMOOTH); // 생략 가능
	gluQuadricOrientation(qobjSphere, GLU_OUTSIDE); // 생략 가능
	gluSphere(qobjSphere, 0.2, 50, 50); // 객체 만들기

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'W':
	case 'w':
		rc.yTranslatePos += 0.01f;
		break;
	case 'S':
	case 's':
		rc.yTranslatePos -= 0.01f;
		break;
	case 'A':
	case 'a':
		rc.xTranslatePos -= 0.01f;
		break;
	case 'D':
	case 'd':
		rc.xTranslatePos += 0.01f;
		break;
	case 'Q':
	case 'q':
		rc.zTranslatePos -= 0.01f;
		break;
	case 'E':
	case 'e':
		rc.zTranslatePos += 0.01f;
		break;
	case 'I':
	case 'i':
		rc.bTranslatePos += 0.01f;
		break;
	case 'K':
	case 'k':
		rc.bTranslatePos -= 0.01f;
		break;
	case 'J':
	case 'j':
		rc.aTranslatePos -= 0.01f;
		break;
	case 'L':
	case 'l':
		rc.aTranslatePos += 0.01f;
		break;
	case 'U':
	case 'u':
		rc.cTranslatePos -= 0.01f;
		break;
	case 'O':
	case 'o':
		rc.cTranslatePos += 0.01f;
		break;
	case '1':
		rc.scaleByObject += 0.01f;
		break;
	case '2':
		rc.scaleByObject -= 0.01f;
		break;
	case '3':
		rc.scaleByStandard += 0.01f;
		break;
	case '4':
		rc.scaleByStandard -= 0.01f;
		break;
	case '5':
		rc.yTranslatePos += 0.01f;
		rc.bTranslatePos += 0.01f;
		rc.lTranslatePos += 0.01f;
		break;
	case '6':
		rc.yTranslatePos -= 0.01f;
		rc.bTranslatePos -= 0.01f;
		rc.lTranslatePos -= 0.01f;
		break;
	case 'R':
	case 'r':
		if (rc.rRotate) {
			rc.rRotate = false;
			tornado.loop = 0;
		}
		else {
			rc.rRotate = true;
		}
		break;
	case 'C':
	case 'c':
		rc.reset();
		tornado.loop = 0;
		break;
	}
	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	if (rc.rRotate) {
		if (tornado.loop == DOT_COUNT) {
			tornado.loop = 0;
			rc.xRotateObject = tornado.nextX();
			rc.zRotateObject = tornado.nextZ();
		}
		else {
			tornado.loop++;
			rc.xRotateObject = tornado.nextX();
			rc.zRotateObject = tornado.nextZ();
		}
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

	glGenVertexArrays(3, va.line_vao);
	for (int i = 0; i < 3; i++) {
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

	glGenVertexArrays(DOT_COUNT, va.vao); 
	for (int i = 0; i < DOT_COUNT; i++) {
		glBindVertexArray(va.vao[i]);

		glGenBuffers(2, va.vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, va.vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), tornado.data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}
}

