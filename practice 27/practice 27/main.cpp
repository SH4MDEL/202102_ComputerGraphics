#pragma once
#include "make_vertexShaders.h"
#include "make_fragmentShaders.h"
#include "make_shaderProgram.h"
#include "stdafx.h"

#include "objRead.h"

#include "Light.h"
#include "Field.h"
#include "Sun.h"
#include "Earth.h"
#include "Moon.h"
#include "Snowflake.h"
#include "Sierpinski.h"

#define M_PI 3.1415926535897932384626433832795
#define M_WINDOWX 700
#define M_WINDOWY 700

GLvoid drawScene();
GLvoid Keyboard(unsigned char inputKey, int x, int y);
GLvoid TimerFunction(int value);
GLvoid Reshape(int w, int h);

GLchar *vertexSource, *fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체
GLuint s_program;

struct RunControl {
	GLfloat x, z;
	bool rotation, revolve;
	GLfloat rotationPos, revolvePos;
	bool Cameraset;
	bool snowing;
	RunControl() {
		reset();
	}
	void rotateReset() {
		rotation = false;
		rotationPos = 270.0f;
	}
	void revolveReset() {
		revolve = false;
		revolvePos = rotationPos;
	}
	void reset() {
		Cameraset = true;
		x = 0.0f;
		z = 0.0f;
		rotation = false;
		revolve = false;
		rotationPos = 270.0f;
		revolvePos = 90.0f;
		snowing = false;
	}
};
RunControl rc;

struct ObjectManager {
	objRead objReader;

	Light light;
	Field field;
	Sun sun;
	Earth earth;
	Moon moon;
	Snowflake snow[100];

	Sierpinski* sier = new Sierpinski(0);
	//Sierpinski sier = { 6 };

	void initMyBuffer(GLuint s_program) {
		GLint object = objReader.loadObj_normalize_center("sphere.obj");
		light.initBuffer(s_program);
		field.initBuffer(s_program);
		sun.initBuffer(s_program, object);
		earth.initBuffer(s_program, object);
		moon.initBuffer(s_program, object);
		sierBuffer(s_program);
		for (int i = 0; i < 100; i++) {
			snow[i].initBuffer(s_program, object);
		}
	}

	void sierBuffer(GLuint s_program) {
		sier[0].initBuffer(s_program);
	}

	void allStop() {
		light.rotate = false;
	}

	void allReset() {
		light.allReset();
	}
};
ObjectManager om;


int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(M_WINDOWX, M_WINDOWY);
	glutCreateWindow("practice 27");

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
	make_vertexShaders(vertexSource, vertexShader);
	make_fragmentShaders(fragmentSource, fragmentShader);

	s_program = make_shaderProgram(vertexShader, fragmentShader);
	om.initMyBuffer(s_program);

	glutDisplayFunc(drawScene);

	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, TimerFunction, 1);

	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	//--- 변경된 배경색 설정
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(s_program);

	glm::vec3 cameraPos = glm::vec3(rc.x + 6.0 * cos(2 * M_PI / 360.0f * rc.rotationPos), 1.5f, rc.z + 6.0 * sin(2 * M_PI / 360.0f * rc.rotationPos)); //--- 카메라 위치
	glm::vec3 cameraDirection = glm::vec3(100 * cos(2 * M_PI / 360.0f * rc.revolvePos), 0.0f, 100 * sin(2 * M_PI / 360.0f * rc.revolvePos)); //--- 카메라 바라보는 방향
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	unsigned int viewPos = glGetUniformLocation(s_program, "viewPos"); //--- 바라보는 방향 프래그먼트 셰이더로 전달
	glUniform3f(viewPos, rc.x + 6.0f * cos(2 * M_PI / 360.0f * rc.rotationPos), 1.5f, rc.z + 6.0f * sin(2 * M_PI / 360.0f * rc.rotationPos));

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 200.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.2)); //--- 공간을 약간 뒤로 미뤄줌
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	unsigned int modelLocation = glGetUniformLocation(s_program, "ModelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 basicSet = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);

	om.light.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.light.getFactor()));
	om.light.draw();

	om.field.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.field.getFactor()));
	om.field.draw();

	om.sier[0].putFactor(om.field.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.sier[0].getFactor()));
	om.sier[0].draw();

	om.sun.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.sun.getFactor()));
	om.sun.draw();

	om.earth.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.earth.getFactor()));
	om.earth.draw();

	om.moon.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.moon.getFactor()));
	om.moon.draw();

	if (rc.snowing) {
		for (int i = 0; i < 50; i++) {
			om.snow[i].putFactor(om.field.getFactor());
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.snow[i].getFactor()));
			om.snow[i].draw();
		}
	}

	glDisable(GL_DEPTH_TEST);
	glutPostRedisplay();
	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case '0':
		delete om.sier;
		om.sier = new Sierpinski(0);
		om.sierBuffer(s_program);
		break;
	case '1':
		delete om.sier;
		om.sier = new Sierpinski(1);
		om.sierBuffer(s_program);
		break;
	case '2':
		delete om.sier;
		om.sier = new Sierpinski(2);
		om.sierBuffer(s_program);
		break;
	case '3':
		delete om.sier;
		om.sier = new Sierpinski(3);
		om.sierBuffer(s_program);
		break;
	case '4':
		delete om.sier;
		om.sier = new Sierpinski(4);
		om.sierBuffer(s_program);
		break;
	case '5':
		delete om.sier;
		om.sier = new Sierpinski(5);
		om.sierBuffer(s_program);
		break;
	case '6':
		delete om.sier;
		om.sier = new Sierpinski(6);
		om.sierBuffer(s_program);
		break;
	//case '7':
	//	delete om.sier;
	//	om.sier = new Sierpinski(7);
	//	om.sierBuffer(s_program);
	//	break;
	case '+':
	case '=':
		if (om.light.raypower <= 10.0f) {
			om.light.raypower += 1.0f;
		}
		break;
	case '-':
	case '_':
		if (om.light.raypower >= 2.0f) {
			om.light.raypower -= 1.0f;
		}
		break;
	case 'r':
	case 'R':
		if (om.light.rotate) {
			om.light.rotate = false;
		}
		else {
			om.light.rotate = true;
		}
		break;
	case 'i':
		om.light.zPos += 0.1f;
		break;
	case 'o':
		om.light.zPos -= 0.1f;
		break;
	case 'z':	// 카메라가 z축 양/음 방향으로 이동
		rc.z += 0.1f;
		break;
	case 'Z':
		rc.z -= 0.1f;
		break;
	case 'x':	// 카메라가 x축 양/음 방향으로 이동
		rc.x += 0.1f;
		break;
	case 'X':
		rc.x -= 0.1f;
		break;
	case 'y':	// 카메라 기준 y축에 대해서 회전
	case 'Y':
		if (rc.revolve) {
			rc.revolve = false;
		}
		else {
			rc.revolve = true;
		}
		break;
	case 'a':	// r 명령어와 같이 화면의 중심의 축에 대하여 카메라가 회전하는 애니메이션을 진행한다/멈춘다
	case 'A':
		if (rc.rotation) {
			rc.rotation = false;
		}
		else {
			rc.rotation = true;
		}
		break;
	case 's':	// 모든 움직임 멈추기
	case 'S':
		if (rc.snowing) {
			rc.snowing = false;
		}
		else {
			rc.snowing = true;
		}
		break;
	case 'q':	// 프로그램 종료
	case 'Q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	om.light.update();
	om.sier[0].update();
	om.sun.update();
	om.earth.update();
	om.moon.update();
	if (rc.rotation) {
		rc.rotationPos += 1.0f;
		rc.revolvePos += 1.0f;
	}
	if (rc.revolve) {
		rc.revolvePos += 1.0f;
	}
	if (rc.snowing) {
		for (int i = 0; i < 50; i++) {
			om.snow[i].update();
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
