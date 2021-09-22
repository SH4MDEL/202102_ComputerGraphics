#pragma once
#include "shader.h"
#include "initShader.h"
#include "make_shaderProgram.h"
#include "stdafx.h"
void initBuffer();
void reinitBuffer();

GLvoid drawScene();
GLvoid TimerFunction(int value);
GLvoid Reshape(int w, int h);

GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체
GLuint s_program;

enum Object_Status {
	Line,
	Triangle,
	_Rectangle,
	Pentagon,
	Dot
};

enum Colors {
	Blue,
	Yellow,
	Green,
	Red
};

struct VecterArray {
	GLuint linevao[2], linevbo[2][2];
	GLuint objectvao[4][3], objectvbo[4][3][2];
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

struct _Object {
	GLfloat data[3][2][3][3];	// 삼각형수 / 좌표및색 / 3개의정점 / 3개의좌표
	GLfloat ox, oy;
	int status;
	bool datastatus[3];
	_Object(GLfloat ox, GLfloat oy, int status, int colors) : ox(ox), oy(oy), status(status) {
		colorset(colors);
		if (status == Object_Status::Line) {
			lineset();
		}
		else if (status == Object_Status::Triangle) {
			triangleset();
		}
		else if (status == Object_Status::_Rectangle) {
			rectangleset();
		}
		else if (status == Object_Status::Pentagon) {
			pentagonset();
		}
	}
	void colorset(int colors) {
		if (colors == Colors::Blue) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int k = 0; k < 3; k++) {
						if (k == 2) {
							data[i][1][j][k] = 1.0f;
						}
						else {
							data[i][1][j][k] = 0.0f;
						}
					}
				}
			}
		}
		else if (colors == Colors::Yellow) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int k = 0; k < 3; k++) {
						if (k == 0 || k == 1) {
							data[i][1][j][k] = 1.0f;
						}
						else {
							data[i][1][j][k] = 0.0f;
						}
					}
				}
			}
		}
		else if (colors == Colors::Green) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int k = 0; k < 3; k++) {
						if (k == 1) {
							data[i][1][j][k] = 1.0f;
						}
						else {
							data[i][1][j][k] = 0.0f;
						}
					}
				}
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int k = 0; k < 3; k++) {
						if (k == 0) {
							data[i][1][j][k] = 1.0f;
						}
						else {
							data[i][1][j][k] = 0.0f;
						}
					}
				}
			}
		}
	}
	void lineset() {
		datastatus[0] = true;
		datastatus[1] = false;
		datastatus[2] = false;

		data[0][0][0][0] = ox - 0.1f, data[0][0][0][1] = oy - 0.1f, data[0][0][0][2] = 0.0f;
		data[0][0][1][0] = ox + 0.1f, data[0][0][1][1] = oy - 0.1f, data[0][0][1][2] = 0.0f;
		data[0][0][2][0] = ox, data[0][0][2][1] = oy - 0.1f, data[0][0][2][2] = 0.0f;	//

		data[1][0][0][0] = ox, data[1][0][0][1] = oy + 0.1f, data[1][0][0][2] = 0.0f;
		data[1][0][1][0] = ox - 0.05f, data[1][0][1][1] = oy, data[1][0][1][2] = 0.0f;	//
		data[1][0][2][0] = ox - 0.1f, data[1][0][2][1] = oy - 0.1f, data[1][0][2][2] = 0.0f;

		data[2][0][0][0] = ox, data[2][0][0][1] = oy + 0.1f, data[2][0][0][2] = 0.0f;
		data[2][0][1][0] = ox + 0.1f, data[2][0][1][1] = oy - 0.1f, data[2][0][1][2] = 0.0f;
		data[2][0][2][0] = ox + 0.05f, data[2][0][2][1] = oy, data[2][0][2][2] = 0.0f; //
	}
	void triangleset() {
		datastatus[0] = true;
		datastatus[1] = false;
		datastatus[2] = false;

		data[0][0][0][0] = ox - 0.1f, data[0][0][0][1] = oy - 0.1f, data[0][0][0][2] = 0.0f;
		data[0][0][1][0] = ox + 0.1f, data[0][0][1][1] = oy - 0.1f, data[0][0][1][2] = 0.0f;
		data[0][0][2][0] = ox, data[0][0][2][1] = oy + 0.1f, data[0][0][2][2] = 0.0f;

		data[1][0][0][0] = ox, data[1][0][0][1] = oy + 0.1f, data[1][0][0][2] = 0.0f;
		data[1][0][1][0] = ox - 0.05f, data[1][0][1][1] = oy, data[1][0][1][2] = 0.0f;	//
		data[1][0][2][0] = ox - 0.1f, data[1][0][2][1] = oy - 0.1f, data[1][0][2][2] = 0.0f;

		data[2][0][0][0] = ox, data[2][0][0][1] = oy + 0.1f, data[2][0][0][2] = 0.0f;
		data[2][0][1][0] = ox + 0.1f, data[2][0][1][1] = oy - 0.1f, data[2][0][1][2] = 0.0f;
		data[2][0][2][0] = ox + 0.05f, data[2][0][2][1] = oy, data[2][0][2][2] = 0.0f; //
	}
	void rectangleset() {
		datastatus[0] = true;
		datastatus[1] = true;
		datastatus[2] = true;

		data[0][0][0][0] = ox - 0.1f, data[0][0][0][1] = oy - 0.1f, data[0][0][0][2] = 0.0f;
		data[0][0][1][0] = ox + 0.1f, data[0][0][1][1] = oy - 0.1f, data[0][0][1][2] = 0.0f;
		data[0][0][2][0] = ox, data[0][0][2][1] = oy + 0.1f, data[0][0][2][2] = 0.0f;

		data[1][0][0][0] = ox, data[1][0][0][1] = oy + 0.1f, data[1][0][0][2] = 0.0f;
		data[1][0][1][0] = ox - 0.1f, data[1][0][1][1] = oy + 0.1f, data[1][0][1][2] = 0.0f;	//
		data[1][0][2][0] = ox - 0.1f, data[1][0][2][1] = oy - 0.1f, data[1][0][2][2] = 0.0f;

		data[2][0][0][0] = ox, data[2][0][0][1] = oy + 0.1f, data[2][0][0][2] = 0.0f;
		data[2][0][1][0] = ox + 0.1f, data[2][0][1][1] = oy - 0.1f, data[2][0][1][2] = 0.0f;
		data[2][0][2][0] = ox + 0.1f, data[2][0][2][1] = oy + 0.1f, data[2][0][2][2] = 0.0f; //
	}
	void pentagonset() {
		datastatus[0] = true;
		datastatus[1] = true;
		datastatus[2] = true;

		data[0][0][0][0] = ox - 0.1f, data[0][0][0][1] = oy - 0.1f, data[0][0][0][2] = 0.0f;
		data[0][0][1][0] = ox + 0.1f, data[0][0][1][1] = oy - 0.1f, data[0][0][1][2] = 0.0f;
		data[0][0][2][0] = ox, data[0][0][2][1] = oy + 0.1f, data[0][0][2][2] = 0.0f;

		data[1][0][0][0] = ox, data[1][0][0][1] = oy + 0.1f, data[1][0][0][2] = 0.0f;
		data[1][0][1][0] = ox - 0.1f, data[1][0][1][1] = oy, data[1][0][1][2] = 0.0f;	//
		data[1][0][2][0] = ox - 0.1f, data[1][0][2][1] = oy - 0.1f, data[1][0][2][2] = 0.0f;

		data[2][0][0][0] = ox, data[2][0][0][1] = oy + 0.1f, data[2][0][0][2] = 0.0f;
		data[2][0][1][0] = ox + 0.1f, data[2][0][1][1] = oy - 0.1f, data[2][0][1][2] = 0.0f;
		data[2][0][2][0] = ox + 0.1f, data[2][0][2][1] = oy, data[2][0][2][2] = 0.0f; //
	}
	void dotset() {
		datastatus[0] = true;
		datastatus[1] = false;
		datastatus[2] = false;

		data[0][0][0][0] = ox - 0.1f, data[0][0][0][1] = oy - 0.1f, data[0][0][0][2] = 0.0f;
		data[0][0][1][0] = ox - 0.1f, data[0][0][1][1] = oy - 0.1f, data[0][0][1][2] = 0.0f; //
		data[0][0][2][0] = ox - 0.1f, data[0][0][2][1] = oy - 0.1f, data[0][0][2][2] = 0.0f;	//

		data[1][0][0][0] = ox, data[1][0][0][1] = oy + 0.1f, data[1][0][0][2] = 0.0f;
		data[1][0][1][0] = ox - 0.05f, data[1][0][1][1] = oy, data[1][0][1][2] = 0.0f;	//
		data[1][0][2][0] = ox - 0.1f, data[1][0][2][1] = oy - 0.1f, data[1][0][2][2] = 0.0f;

		data[2][0][0][0] = ox, data[2][0][0][1] = oy + 0.1f, data[2][0][0][2] = 0.0f;
		data[2][0][1][0] = ox + 0.1f, data[2][0][1][1] = oy - 0.1f, data[2][0][1][2] = 0.0f;
		data[2][0][2][0] = ox + 0.05f, data[2][0][2][1] = oy, data[2][0][2][2] = 0.0f; //
	}
	void change() {
		if (status == Object_Status::Line) {
			if (data[0][0][2][1] >= oy + 0.1f) {
				status = Object_Status::Triangle;
				triangleset();
			}
			else {
				data[0][0][2][1] += 0.02f;
			}
		}
		else if (status == Object_Status::Triangle) {
			datastatus[1] = true;
			datastatus[2] = true;
			if (data[1][0][1][0] <= ox - 0.1f) {
				status = Object_Status::_Rectangle;
				rectangleset();
			}
			else {
				data[1][0][1][0] -= 0.005f;
			}

			if (data[1][0][1][1] >= oy + 0.1f) {
				status = Object_Status::_Rectangle;
				rectangleset();
			}
			else {
				data[1][0][1][1] += 0.01f;
			}

			if (data[2][0][2][0] >= ox + 0.1f) {
				status = Object_Status::_Rectangle;
				rectangleset();
			}
			else {
				data[2][0][2][0] += 0.005f;
			}

			if (data[2][0][2][1] >= oy + 0.1f) {
				status = Object_Status::_Rectangle;
				rectangleset();
			}
			else {
				data[2][0][2][1] += 0.01f;
			}
		}
		else if (status == Object_Status::_Rectangle) {
			if (data[1][0][1][1] <= oy) {
				status = Object_Status::Pentagon;
				pentagonset();
			}
			else {
				data[1][0][1][1] -= 0.01f;
			}
			if (data[2][0][2][1] <= oy) {
				status = Object_Status::Pentagon;
				pentagonset();
			}
			else {
				data[2][0][2][1] -= 0.01f;
			}
		}
		else if (status == Object_Status::Pentagon) {
			datastatus[1] = false;
			datastatus[2] = false;
			if (data[0][0][1][0] <= ox - 0.1f) {
				status = Object_Status::Dot;
				dotset();
			}
			else {
				data[0][0][1][0] -= 0.02f;
			}
			if (data[0][0][2][0] <= ox - 0.1f) {
				status = Object_Status::Dot;
				dotset();
			}
			else {
				data[0][0][2][0] -= 0.01f;
			}
			if (data[0][0][2][1] <= oy - 0.1f) {
				status = Object_Status::Dot;
				dotset();
			}
			else {
				data[0][0][2][1] -= 0.02f;
			}
		}
		else if (status == Object_Status::Dot) {
			if (data[0][0][1][0] >= ox + 0.1f) {
				status = Object_Status::Line;
				lineset();
			}
			else {
				data[0][0][1][0] += 0.02f;
			}
			if (data[0][0][2][0] >= ox) {
				status = Object_Status::Line;
				lineset();
			}
			else {
				data[0][0][2][0] += 0.01f;
			}
		}
	}
};
_Object object[4] = {
	_Object(-0.5f, 0.5f, Object_Status::Line, Colors::Blue), 
	_Object(0.5f, 0.5f, Object_Status::Triangle, Colors::Yellow),
	_Object(-0.5f, -0.5f, Object_Status::_Rectangle, Colors::Green),
	_Object(0.5f, -0.5f, Object_Status::Pentagon, Colors::Red)
};

int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("practice 10");

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
	glutTimerFunc(50, TimerFunction, 1);
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

	glPointSize(2.0);


	for (int i = 0; i < 2; i++) {
		glBindVertexArray(va.linevao[i]);
		glDrawArrays(GL_LINES, 0, 2);
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (object[i].datastatus[j]) {
				glBindVertexArray(va.objectvao[i][j]);
				if (object[i].status == Object_Status::Line) {
					glDrawArrays(GL_LINES, 0, 3);
				}
				if (object[i].status == Object_Status::Dot) {
					glDrawArrays(GL_POINTS, 0, 1);
				}
				glDrawArrays(GL_TRIANGLES, 0, 3);

			}
		}
	}

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid TimerFunction(int value)
{
	for (int i = 0; i < 4; i++) {
		object[i].change();
	}
	reinitBuffer();
	glutPostRedisplay();
	glutTimerFunc(50, TimerFunction, value);
	return;
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

	for (int i = 0; i < 4; i++) {
		glGenVertexArrays(3, va.objectvao[i]);
		for (int j = 0; j < 3; j++) {
			glBindVertexArray(va.objectvao[i][j]);
			glGenBuffers(3, va.objectvbo[i][j]);
			for (int k = 0; k < 2; k++) {
				glBindBuffer(GL_ARRAY_BUFFER, va.objectvbo[i][j][k]);
				glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), object[i].data[j][k], GL_STATIC_DRAW);
				glVertexAttribPointer(k, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(k);

			}
		}
	}
}

void reinitBuffer()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			glBindVertexArray(va.objectvao[i][j]);
			glGenBuffers(3, va.objectvbo[i][j]);
			for (int k = 0; k < 2; k++) {
				glBindBuffer(GL_ARRAY_BUFFER, va.objectvbo[i][j][k]);
				glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), object[i].data[j][k], GL_STATIC_DRAW);
				glVertexAttribPointer(k, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(k);

			}
		}
	}
}