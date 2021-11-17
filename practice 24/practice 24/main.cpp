#pragma once
#include "make_vertexShaders.h"
#include "make_fragmentShaders.h"
#include "make_shaderProgram.h"
#include "stdafx.h"

#include "Line.h"
#include "Orbit.h"
#include "Hexahedron.h"
#include "Quadrangular.h"
#include "Light.h"

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
	bool hidden_surface;
	bool proj;

	RunControl() {
		reset();

	}
	void reset() {
		proj = true;
		hidden_surface = true;
	}
};
RunControl rc;

struct ObjectManager {
	Line line[3] = { Line(1), Line(2), Line(3) };
	Orbit orbit;
	Hexahedron hexa;
	Quadrangular quad;
	Light light;

	void initMyBuffer(GLuint s_program) {
		line[0].initBuffer(s_program);
		line[1].initBuffer(s_program);
		line[2].initBuffer(s_program);
		orbit.initBuffer(s_program);
		hexa.initBuffer(s_program);
		quad.initBuffer(s_program);
		light.initBuffer(s_program);
	}

	void allReset() {
		line[0].allReset();
		line[1].allReset();
		line[2].allReset();
		orbit.allReset();
		hexa.allReset();
		quad.allReset();
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
	glutCreateWindow("practice 24");

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

	glm::vec3 cameraPos = glm::vec3(-2.0f, 2.0f, 2.0f); //--- 카메라 위치
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	unsigned int viewPos = glGetUniformLocation(s_program, "viewPos"); //--- 바라보는 방향 프래그먼트 셰이더로 전달
	glUniform3f(viewPos, -2.0f, 2.0f, 2.0f);

	glm::mat4 projection = glm::mat4(1.0f);
	if (rc.proj) {
		projection = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 200.0f);
	}
	else {
		projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -4.0f, 4.0f);
	}
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.2)); //--- 공간을 약간 뒤로 미뤄줌
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	unsigned int modelLocation = glGetUniformLocation(s_program, "ModelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 basicSet = glm::mat4(1.0f);

	if (rc.hidden_surface) {
		glEnable(GL_DEPTH_TEST);
	}

	om.light.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.light.getFactor()));
	om.light.draw();

	om.line[0].putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.line[0].getFactor()));
	om.line[0].draw();

	om.line[1].putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.line[1].getFactor()));
	om.line[1].draw();

	om.line[2].putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.line[2].getFactor()));
	om.line[2].draw();

	om.orbit.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.orbit.getFactor()));
	om.orbit.draw();

	om.hexa.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.hexa.getFactor()));
	om.hexa.draw();

	om.hexa.putHeadFactor(om.hexa.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.hexa.getHeadFactor()));
	om.hexa.headdraw();

	om.hexa.putSlideFactor(om.hexa.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.hexa.getSlideFactor()));
	om.hexa.slidedraw();

	om.hexa.putFrontFactor(om.hexa.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.hexa.getFrontFactor()));
	om.hexa.frontdraw();

	om.quad.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.quad.getFactor()));
	om.quad.draw();

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.quad.myRFactor));
	om.quad.rdraw();

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.quad.myLFactor));
	om.quad.ldraw();

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.quad.myFFactor));
	om.quad.fdraw();

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.quad.myBFactor));
	om.quad.bdraw();

	if (rc.hidden_surface) {
		glDisable(GL_DEPTH_TEST);
	}
	glutPostRedisplay();
	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'h':
	case 'H':
		if (rc.hidden_surface) {
			rc.hidden_surface = false;
		}
		else {
			rc.hidden_surface = true;
		}
		break;
	case 'y':
	case 'Y':
		if (om.hexa.rotate) {
			om.hexa.rotate = false;
			om.quad.rotate = false;
		}
		else {
			om.hexa.rotate = true;
			om.quad.rotate = true;
		}
		break;
	case 't':
	case 'T':
		om.hexa.drawed = true;
		om.quad.drawed = false;
		if (om.hexa.head) {
			om.hexa.head = false;
		}
		else {
			om.hexa.head = true;
		}
		break;
	case 'f':
	case 'F':
		om.hexa.drawed = true;
		om.quad.drawed = false;
		if (om.hexa.front) {
			om.hexa.front = false;
		}
		else {
			om.hexa.front = true;
		}
		break;
	case '1':
		om.hexa.drawed = true;
		om.quad.drawed = false;
		om.hexa.slide = true;
		break;
	case '2':
		om.hexa.drawed = true;
		om.quad.drawed = false;
		om.hexa.slide = false;
		break;
	case 'o':
		om.hexa.drawed = false;
		om.quad.drawed = true;
		om.quad.open = true;
		break;
	case 'O':
		om.hexa.drawed = false;
		om.quad.drawed = true;
		om.quad.open = false;
		break;
	case 'p':
		rc.proj = true;
		break;
	case 'P':
		rc.proj = false;
		break;
	case 'm':
		om.light.onoff = true;
		break;
	case 'M':
		om.light.onoff = false;
		break;
	case 'r':
		if (om.light.rotate == 0) {
			om.light.rotate = 1;
		}
		else {
			om.light.rotate = 0;
		}
		break;
	case 'R':
		if (om.light.rotate == 0) {
			om.light.rotate = 2;
		}
		else {
			om.light.rotate = 0;
		}
		break;
	case 'z':
		om.light.zPos += 0.1f;
		om.orbit.scalePos += 0.07f;

		break;
	case 'Z':
		om.light.zPos -= 0.1f;
		om.orbit.scalePos -= 0.07f;
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
	om.line[0].update();
	om.line[1].update();
	om.line[2].update();
	om.orbit.update();
	om.hexa.update();
	om.quad.update();
	om.light.update();
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, value);
	return;
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}
