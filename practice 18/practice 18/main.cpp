#pragma once
#include "make_vertexShaders.h"
#include "make_fragmentShaders.h"
#include "make_shaderProgram.h"
#include "stdafx.h"

#include "Sun.h"
#include "Orbit.h"
#include "Earth.h"
#include "s_Orbit.h"
#include "Moon.h"

#define M_PI 3.1415926535897932384626433832795

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

struct RunControl {
	bool solid;
	bool proj;
	RunControl() { reset(); }
	void reset() {
		solid = true;
		proj = false;
	}
};
RunControl rc;

struct ObjectManager {
	Sun sun;
	Orbit orbit[3];
	Earth earth[3];
	s_Orbit sorbit[3];
	Moon moon[3];

	ObjectManager() {
		earth[0].translatePosX = (GLfloat)(0.7 * glm::cos(2 * M_PI / 20 * 0));
		earth[0].translatePosZ = (GLfloat)(0.7 * glm::sin(2 * M_PI / 20 * 0));
		earth[1].translatePosX = (GLfloat)(0.7 * glm::cos(2 * M_PI / 20 * 8));
		earth[1].translatePosZ = (GLfloat)(0.7 * glm::sin(2 * M_PI / 20 * 8));
		earth[2].translatePosX = (GLfloat)(0.7 * glm::cos(2 * M_PI / 20 * 15));
		earth[2].translatePosZ = (GLfloat)(0.7 * glm::sin(2 * M_PI / 20 * 15));

		moon[0].translatePosX = (GLfloat)(0.25 * glm::cos(2 * M_PI / 20 * 0));
		moon[0].translatePosZ = (GLfloat)(0.25 * glm::sin(2 * M_PI / 20 * 0));
		moon[1].translatePosX = (GLfloat)(0.25 * glm::cos(2 * M_PI / 20 * 9));
		moon[1].translatePosZ = (GLfloat)(0.25 * glm::sin(2 * M_PI / 20 * 9));
		moon[2].translatePosX = (GLfloat)(0.25 * glm::cos(2 * M_PI / 20 * 17));
		moon[2].translatePosZ = (GLfloat)(0.25 * glm::sin(2 * M_PI / 20 * 17));

		sun.a = (GLfloat)colors(gen) / 10.0f;
		sun.b = (GLfloat)colors(gen) / 10.0f;
		sun.c = (GLfloat)colors(gen) / 10.0f;
		for (int i = 0; i < 3; i++) {
			earth[i].a = (GLfloat)colors(gen) / 10.0f;
			earth[i].b = (GLfloat)colors(gen) / 10.0f;
			earth[i].c = (GLfloat)colors(gen) / 10.0f;
			moon[i].a = (GLfloat)colors(gen) / 10.0f;
			moon[i].b = (GLfloat)colors(gen) / 10.0f;
			moon[i].c = (GLfloat)colors(gen) / 10.0f;
		}
	}

	void initMyBuffer() {
		for (int i = 0; i < 3; i++) {
			orbit[i].initBuffer();
			sorbit[i].initBuffer();
		}
	}
	
};
ObjectManager om;


int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("practice 18");

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {					// glew 초기화
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initialized\n";
	}
	om.initMyBuffer();

	glewInit();
	make_vertexShaders(vertexSource, vertexShader);
	make_fragmentShaders(fragmentSource, fragmentShader);
	s_program = make_shaderProgram(vertexShader, fragmentShader);


	glutDisplayFunc(drawScene);

	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, TimerFunction, 1);

	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	//--- 변경된 배경색 설정
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(s_program);

	int vColorLocation = glGetUniformLocation(s_program, "myColor");

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.0f); //--- 카메라 위치
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


	glm::mat4 projection = glm::mat4(1.0f);
	if (rc.proj) {
		projection = glm::perspective(glm::radians(45.0f), 700.0f / 700.0f, 0.1f, 50.0f);
	}
	else {
		projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
	}
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.2)); //--- 공간을 약간 뒤로 미뤄줌
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);


	unsigned int modelLocation = glGetUniformLocation(s_program, "ModelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glEnable(GL_DEPTH_TEST);

	glm::mat4 basicSet = glm::mat4(1.0f);
	basicSet = glm::rotate(basicSet, glm::radians(-10.0f), glm::vec3(1.0, 0.0, 0.0));
	//basicSet = glm::rotate(basicSet, glm::radians(30.0f), glm::vec3(0.0, 1.0, 0.0));

	glm::mat4 sunFactor = basicSet;
	glm::mat4 orbit0Factor = basicSet;
	glm::mat4 orbit1Factor = basicSet;
	glm::mat4 orbit2Factor = basicSet;
	glm::mat4 earth0Factor = basicSet;
	glm::mat4 earth1Factor = basicSet;
	glm::mat4 earth2Factor = basicSet;
	glm::mat4 sorbit0Factor = basicSet;
	glm::mat4 sorbit1Factor = basicSet;
	glm::mat4 sorbit2Factor = basicSet;
	glm::mat4 moon0Factor = basicSet;
	glm::mat4 moon1Factor = basicSet;
	glm::mat4 moon2Factor = basicSet;

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(basicSet));


	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(sunFactor));

	if (rc.solid) {
		sunFactor = glm::translate(sunFactor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(sunFactor));
		glUniform4f(vColorLocation, om.sun.a, om.sun.b, om.sun.c, 1.0);
		om.sun.drawSolid();

		orbit0Factor = glm::translate(orbit0Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
		orbit0Factor = glm::rotate(orbit0Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(orbit0Factor));
		glUniform4f(vColorLocation, 1.0, 1.0, 1.0, 1.0);
		om.orbit[0].draw();

		orbit1Factor = glm::translate(orbit1Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
		orbit1Factor = glm::rotate(orbit1Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
		orbit1Factor = glm::rotate(orbit1Factor, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(orbit1Factor));
		om.orbit[1].draw();

		orbit2Factor = glm::translate(orbit2Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
		orbit2Factor = glm::rotate(orbit2Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
		orbit2Factor = glm::rotate(orbit2Factor, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(orbit2Factor));
		om.orbit[2].draw();

		earth0Factor = glm::translate(earth0Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
		earth0Factor = glm::rotate(earth0Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
		earth0Factor = glm::translate(earth0Factor, glm::vec3(om.earth[0].translatePosX, om.earth[0].translatePosY, om.earth[0].translatePosZ));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(earth0Factor));
		glUniform4f(vColorLocation, om.earth[0].a, om.earth[0].b, om.earth[0].c, 1.0);
		om.earth[0].drawSolid();

		earth1Factor = glm::translate(earth1Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
		earth1Factor = glm::rotate(earth1Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
		earth1Factor = glm::rotate(earth1Factor, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		earth1Factor = glm::translate(earth1Factor, glm::vec3(om.earth[1].translatePosX, om.earth[1].translatePosY, om.earth[1].translatePosZ));
		glUniform4f(vColorLocation, om.earth[1].a, om.earth[1].b, om.earth[1].c, 1.0);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(earth1Factor));
		om.earth[1].drawSolid();

		earth2Factor = glm::translate(earth2Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
		earth2Factor = glm::rotate(earth2Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
		earth2Factor = glm::rotate(earth2Factor, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		earth2Factor = glm::translate(earth2Factor, glm::vec3(om.earth[2].translatePosX, om.earth[2].translatePosY, om.earth[2].translatePosZ));
		glUniform4f(vColorLocation, om.earth[2].a, om.earth[2].b, om.earth[2].c, 1.0);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(earth2Factor));
		om.earth[2].drawSolid();

		sorbit0Factor = glm::translate(sorbit0Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
		sorbit0Factor = glm::rotate(sorbit0Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
		sorbit0Factor = glm::translate(sorbit0Factor, glm::vec3(om.earth[0].translatePosX, om.earth[0].translatePosY, om.earth[0].translatePosZ));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(sorbit0Factor));
		glUniform4f(vColorLocation, 1.0, 1.0, 1.0, 1.0);
		om.sorbit[0].draw();

		sorbit1Factor = glm::translate(sorbit1Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
		sorbit1Factor = glm::rotate(sorbit1Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
		sorbit1Factor = glm::rotate(sorbit1Factor, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		sorbit1Factor = glm::translate(sorbit1Factor, glm::vec3(om.earth[1].translatePosX, om.earth[1].translatePosY, om.earth[1].translatePosZ));
		sorbit1Factor = glm::rotate(sorbit1Factor, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(sorbit1Factor));
		om.sorbit[1].draw();

		sorbit2Factor = glm::translate(sorbit2Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
		sorbit2Factor = glm::rotate(sorbit2Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
		sorbit2Factor = glm::rotate(sorbit2Factor, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		sorbit2Factor = glm::translate(sorbit2Factor, glm::vec3(om.earth[2].translatePosX, om.earth[2].translatePosY, om.earth[2].translatePosZ));
		sorbit2Factor = glm::rotate(sorbit2Factor, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		glUniform4f(vColorLocation, 1.0, 1.0, 1.0, 1.0);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(sorbit2Factor));
		om.sorbit[2].draw();

		moon0Factor = glm::translate(moon0Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
		moon0Factor = glm::rotate(moon0Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
		moon0Factor = glm::translate(moon0Factor, glm::vec3(om.moon[0].translatePosX, om.moon[0].translatePosY, om.moon[0].translatePosZ));
		moon0Factor = glm::translate(moon0Factor, glm::vec3(om.earth[0].translatePosX, om.earth[0].translatePosY, om.earth[0].translatePosZ));
		glUniform4f(vColorLocation, om.moon[0].a, om.moon[0].b, om.moon[0].c, 1.0);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(moon0Factor));
		om.moon[0].drawSolid();

		moon1Factor = glm::translate(moon1Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
		moon1Factor = glm::rotate(moon1Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
		moon1Factor = glm::translate(moon1Factor, glm::vec3(om.moon[1].translatePosX, om.moon[1].translatePosY, om.moon[1].translatePosZ));
		moon1Factor = glm::rotate(moon1Factor, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		moon1Factor = glm::translate(moon1Factor, glm::vec3(om.earth[1].translatePosX, om.earth[1].translatePosY, om.earth[1].translatePosZ));
		moon1Factor = glm::rotate(moon1Factor, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		glUniform4f(vColorLocation, om.moon[1].a, om.moon[1].b, om.moon[1].c, 1.0);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(moon1Factor));
		om.moon[1].drawSolid();

		moon2Factor = glm::translate(moon2Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
		moon2Factor = glm::rotate(moon2Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
		moon2Factor = glm::translate(moon2Factor, glm::vec3(om.moon[2].translatePosX, om.moon[2].translatePosY, om.moon[2].translatePosZ));
		moon2Factor = glm::rotate(moon2Factor, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		moon2Factor = glm::translate(moon2Factor, glm::vec3(om.earth[2].translatePosX, om.earth[2].translatePosY, om.earth[2].translatePosZ));
		moon2Factor = glm::rotate(moon2Factor, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
		glUniform4f(vColorLocation, om.moon[2].a, om.moon[2].b, om.moon[2].c, 1.0);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(moon2Factor));
		om.moon[2].drawSolid();

	}
	else {
	sunFactor = glm::translate(sunFactor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(sunFactor));
	glUniform4f(vColorLocation, om.sun.a, om.sun.b, om.sun.c, 1.0);
	om.sun.drawWire();

	orbit0Factor = glm::translate(orbit0Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
	orbit0Factor = glm::rotate(orbit0Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(orbit0Factor));
	glUniform4f(vColorLocation, 1.0, 1.0, 1.0, 1.0);
	om.orbit[0].draw();

	orbit1Factor = glm::translate(orbit1Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
	orbit1Factor = glm::rotate(orbit1Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
	orbit1Factor = glm::rotate(orbit1Factor, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(orbit1Factor));
	om.orbit[1].draw();

	orbit2Factor = glm::translate(orbit2Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
	orbit2Factor = glm::rotate(orbit2Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
	orbit2Factor = glm::rotate(orbit2Factor, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(orbit2Factor));
	om.orbit[2].draw();

	earth0Factor = glm::translate(earth0Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
	earth0Factor = glm::rotate(earth0Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
	earth0Factor = glm::translate(earth0Factor, glm::vec3(om.earth[0].translatePosX, om.earth[0].translatePosY, om.earth[0].translatePosZ));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(earth0Factor));
	glUniform4f(vColorLocation, om.earth[0].a, om.earth[0].b, om.earth[0].c, 1.0);
	om.earth[0].drawWire();

	earth1Factor = glm::translate(earth1Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
	earth1Factor = glm::rotate(earth1Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
	earth1Factor = glm::rotate(earth1Factor, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	earth1Factor = glm::translate(earth1Factor, glm::vec3(om.earth[1].translatePosX, om.earth[1].translatePosY, om.earth[1].translatePosZ));
	glUniform4f(vColorLocation, om.earth[1].a, om.earth[1].b, om.earth[1].c, 1.0);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(earth1Factor));
	om.earth[1].drawWire();

	earth2Factor = glm::translate(earth2Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
	earth2Factor = glm::rotate(earth2Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
	earth2Factor = glm::rotate(earth2Factor, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	earth2Factor = glm::translate(earth2Factor, glm::vec3(om.earth[2].translatePosX, om.earth[2].translatePosY, om.earth[2].translatePosZ));
	glUniform4f(vColorLocation, om.earth[2].a, om.earth[2].b, om.earth[2].c, 1.0);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(earth2Factor));
	om.earth[2].drawWire();

	sorbit0Factor = glm::translate(sorbit0Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
	sorbit0Factor = glm::rotate(sorbit0Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
	sorbit0Factor = glm::translate(sorbit0Factor, glm::vec3(om.earth[0].translatePosX, om.earth[0].translatePosY, om.earth[0].translatePosZ));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(sorbit0Factor));
	glUniform4f(vColorLocation, 1.0, 1.0, 1.0, 1.0);
	om.sorbit[0].draw();

	sorbit1Factor = glm::translate(sorbit1Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
	sorbit1Factor = glm::rotate(sorbit1Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
	sorbit1Factor = glm::rotate(sorbit1Factor, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	sorbit1Factor = glm::translate(sorbit1Factor, glm::vec3(om.earth[1].translatePosX, om.earth[1].translatePosY, om.earth[1].translatePosZ));
	sorbit1Factor = glm::rotate(sorbit1Factor, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(sorbit1Factor));
	om.sorbit[1].draw();

	sorbit2Factor = glm::translate(sorbit2Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
	sorbit2Factor = glm::rotate(sorbit2Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
	sorbit2Factor = glm::rotate(sorbit2Factor, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	sorbit2Factor = glm::translate(sorbit2Factor, glm::vec3(om.earth[2].translatePosX, om.earth[2].translatePosY, om.earth[2].translatePosZ));
	sorbit2Factor = glm::rotate(sorbit2Factor, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	glUniform4f(vColorLocation, 1.0, 1.0, 1.0, 1.0);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(sorbit2Factor));
	om.sorbit[2].draw();

	moon0Factor = glm::translate(moon0Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
	moon0Factor = glm::rotate(moon0Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
	moon0Factor = glm::translate(moon0Factor, glm::vec3(om.moon[0].translatePosX, om.moon[0].translatePosY, om.moon[0].translatePosZ));
	moon0Factor = glm::translate(moon0Factor, glm::vec3(om.earth[0].translatePosX, om.earth[0].translatePosY, om.earth[0].translatePosZ));
	glUniform4f(vColorLocation, om.moon[0].a, om.moon[0].b, om.moon[0].c, 1.0);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(moon0Factor));
	om.moon[0].drawWire();

	moon1Factor = glm::translate(moon1Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
	moon1Factor = glm::rotate(moon1Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
	moon1Factor = glm::translate(moon1Factor, glm::vec3(om.moon[1].translatePosX, om.moon[1].translatePosY, om.moon[1].translatePosZ));
	moon1Factor = glm::rotate(moon1Factor, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	moon1Factor = glm::translate(moon1Factor, glm::vec3(om.earth[1].translatePosX, om.earth[1].translatePosY, om.earth[1].translatePosZ));
	moon1Factor = glm::rotate(moon1Factor, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	glUniform4f(vColorLocation, om.moon[1].a, om.moon[1].b, om.moon[1].c, 1.0);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(moon1Factor));
	om.moon[1].drawWire();

	moon2Factor = glm::translate(moon2Factor, glm::vec3(om.sun.translatePosX, om.sun.translatePosY, om.sun.translatePosZ));
	moon2Factor = glm::rotate(moon2Factor, glm::radians(om.sun.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
	moon2Factor = glm::translate(moon2Factor, glm::vec3(om.moon[2].translatePosX, om.moon[2].translatePosY, om.moon[2].translatePosZ));
	moon2Factor = glm::rotate(moon2Factor, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	moon2Factor = glm::translate(moon2Factor, glm::vec3(om.earth[2].translatePosX, om.earth[2].translatePosY, om.earth[2].translatePosZ));
	moon2Factor = glm::rotate(moon2Factor, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	glUniform4f(vColorLocation, om.moon[2].a, om.moon[2].b, om.moon[2].c, 1.0);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(moon2Factor));
	om.moon[2].drawWire();
	}

	

	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'm':
	case 'M':
		if (rc.solid) {
			rc.solid = false;
		}
		else {
			rc.solid = true;
		}
		break;
	case 'w':
	case 'W':
		om.sun.translatePosY += 0.05f;
		break;
	case 'A':
	case 'a':
		om.sun.translatePosX -= 0.05f;
		break;
	case 's':
	case 'S':
		om.sun.translatePosY -= 0.05f;
		break;
	case 'd':
	case 'D':
		om.sun.translatePosX += 0.05f;
		break;
	case 'z':
	case 'Z':
		om.sun.translatePosZ -= 0.05f;
		break;
	case 'x':
	case 'X':
		om.sun.translatePosZ += 0.05f;
		break;
	case 'y':
	case 'Y':
		if (om.sun.rotate) {
			om.sun.rotate = false;
		}
		else {
			om.sun.rotate = true;
		}
		break;
	case 'p':
	case 'P':
		if (rc.proj) {
			rc.proj = false;
		}
		else {
			rc.proj = true;
		}
		break;
	}
	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	if (om.sun.rotate) {
		om.sun.rotatePos += 0.5f;
	}
	om.earth[0].updateS();
	om.earth[1].updateH();
	om.earth[2].updateM();
	om.moon[0].updateM();
	om.moon[1].updateH();
	om.moon[2].updateS();

	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, value);
	return;
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}
