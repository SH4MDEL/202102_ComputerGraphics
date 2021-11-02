#pragma once
#include "make_vertexShaders.h"
#include "make_fragmentShaders.h"
#include "make_shaderProgram.h"
#include "stdafx.h"

#include "Field.h"
#include "Crane_Bottom.h"
#include "Crane_Mid.h"
#include "Crane_Lefthand.h"
#include "Crane_Righthand.h"

#define M_PI 3.1415926535897932384626433832795
#define M_WINDOWX 1100 
#define M_WINDOWY 700

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
	GLfloat x, z;
	bool rotation;
	GLfloat rotationPos, revolvePos;
	RunControl() {
		reset();
	}
	void reset() {
		x = 0.0f;
		z = 0.0f;
		rotation = false;
		rotationPos = 270.0f;
		revolvePos = 90.0f;
	}
};
RunControl rc;

struct ObjectManager {

	Field field;
	Crane_Bottom bottom;
	Crane_Mid mid;
	Crane_Lefthand left;
	Crane_Righthand right;

	ObjectManager() {
		
	}

	void initMyBuffer() {
		field.initBuffer();
		bottom.initBuffer();
		mid.initBuffer();
		left.initBuffer();
		right.initBuffer();
	}

	void allStop() {
		bottom.zMove = false;
		mid.rMove = false;
		left.rMove = false;
		right.rMove = false;
	}
	
	void allReset() {
		bottom.allReset();
		mid.allReset();
		left.allReset();
		right.allReset();
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
	glutCreateWindow("practice 20");

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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(s_program);

	glViewport(0, 0, 700, 700);

	glm::vec3 cameraPos = glm::vec3(rc.x + 3.4 * cos(2 * M_PI / 360.0f * rc.rotationPos), 1.5f, rc.z + 3.4 * sin(2 * M_PI / 360.0f * rc.rotationPos)); //--- 카메라 위치
	glm::vec3 cameraDirection = glm::vec3(100 * cos(2 * M_PI / 360.0f * rc.revolvePos), 0.0f, 100 * sin(2 * M_PI / 360.0f * rc.revolvePos)); //--- 카메라 바라보는 방향
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 200.0f);
	// projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.2)); //--- 공간을 약간 뒤로 미뤄줌
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	unsigned int modelLocation = glGetUniformLocation(s_program, "ModelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 basicSet = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);

	om.field.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.field.getFactor()));
	om.field.draw();

	om.bottom.putFactor(om.field.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.bottom.getFactor()));
	om.bottom.draw();

	om.mid.putFactor(om.bottom.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.mid.getFactor()));
	om.mid.draw();

	om.left.putFactor(om.mid.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.left.getFactor()));
	om.left.draw();

	om.right.putFactor(om.mid.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.right.getFactor()));
	om.right.draw();

	glDisable(GL_DEPTH_TEST);


	glViewport(700, 0, 400, 300);

	glm::vec3 cameraPos2 = glm::vec3(5.0f * cos(2 * M_PI / 360.0f * rc.rotationPos), 0.1f, 5.0f * sin(2 * M_PI / 360.0f * rc.rotationPos)); //--- 카메라 위치
	glm::vec3 cameraDirection2 = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
	glm::vec3 cameraUp2 = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	glm::mat4 view2 = glm::mat4(1.0f);
	view2 = glm::lookAt(cameraPos2, cameraDirection2, cameraUp2);
	unsigned int viewLocation2 = glGetUniformLocation(s_program, "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation2, 1, GL_FALSE, &view2[0][0]);


	glm::mat4 projection2 = glm::mat4(1.0f);
	//projection2 = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 200.0f);
	projection2 = glm::ortho(-3.0f, 3.0f, -3.0f, 3.0f, 2.0f, 5.0f);
	projection2 = glm::translate(projection2, glm::vec3(0.0, 0.0, 1.0)); //--- 공간을 약간 뒤로 미뤄줌
	unsigned int projectionLocation2 = glGetUniformLocation(s_program, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation2, 1, GL_FALSE, &projection2[0][0]);

	glEnable(GL_DEPTH_TEST);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.field.getFactor()));
	om.field.draw();

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.bottom.getFactor()));
	om.bottom.draw();

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.mid.getFactor()));
	om.mid.draw();

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.left.getFactor()));
	om.left.draw();

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.right.getFactor()));
	om.right.draw();

	glDisable(GL_DEPTH_TEST);



	glViewport(700, 300, 400, 400);

	glm::vec3 cameraPos3 = glm::vec3(0.0f, 5.0f, 0.0f); //--- 카메라 위치
	glm::vec3 cameraDirection3 = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
	glm::vec3 cameraUp3 = glm::vec3(cos(2 * M_PI / 360.0f * rc.rotationPos), 0.0f, sin(2 * M_PI / 360.0f * rc.rotationPos)); //--- 카메라 위쪽 방향
	glm::mat4 view3 = glm::mat4(1.0f);
	view3 = glm::lookAt(cameraPos3, cameraDirection3, cameraUp3);
	unsigned int viewLocation3 = glGetUniformLocation(s_program, "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation3, 1, GL_FALSE, &view3[0][0]);


	glm::mat4 projection3 = glm::mat4(1.0f);
	//projection3 = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 200.0f);
	projection3 = glm::ortho(-3.0f, 3.0f, -3.0f, 3.0f, 2.0f, 5.0f);
	projection3 = glm::translate(projection3, glm::vec3(0.0, 0.0, 1.0)); //--- 공간을 약간 뒤로 미뤄줌
	unsigned int projectionLocation3 = glGetUniformLocation(s_program, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation3, 1, GL_FALSE, &projection3[0][0]);

	glEnable(GL_DEPTH_TEST);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.field.getFactor()));
	om.field.draw();

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.bottom.getFactor()));
	om.bottom.draw();

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.mid.getFactor()));
	om.mid.draw();

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.left.getFactor()));
	om.left.draw();

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.right.getFactor()));
	om.right.draw();

	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'b':	// 크레인의 아래 몸체가 z축 방향으로 양/음 방향으로 이동한다.
	case 'B':
		if (om.bottom.zMove == -1 || om.bottom.zMove == 0) {
			om.bottom.zMove += 2;
		}
		else {
			om.bottom.zMove -= 2;
		}
		break;
	case 'm':	// 크레인의 중앙 몸체가 y축에 대하여 양 방향으로 회전한다.
	case 'M':
		if (om.mid.rMove == 1) {
			om.mid.rMove = 0;
		}
		else {
			om.mid.rMove = 1;
		}
		break;
	case 'n':	// 크레인의 중앙 몸체가 y축에 대하여 음 방향으로 회전한다.
	case 'N':
		if (om.mid.rMove == 2) {
			om.mid.rMove = 0;
		}
		else {
			om.mid.rMove = 2;
		}
		break;
	case 't':	// 크레인의 맨 위 2개의 팔이 x축에 대하여 양/음 방향으로 서로 반대방향으로 회전한다.
	case 'T':
		if (om.left.rMove == -1 || om.left.rMove == 0) {
			om.left.rMove += 2;
		}
		else {
			om.left.rMove -= 2;
		}
		if (om.right.rMove == -1 || om.right.rMove == 0) {
			om.right.rMove += 2;
		}
		else {
			om.right.rMove -= 2;
		}
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
		rc.revolvePos += 1.0f;
		break;
	case 'Y':
		rc.revolvePos -= 1.0f;
		break;
	case 'r':	// 화면의 중심의 y축에 대하여 카메라가 회전(중심에 대하여 공전)
		rc.rotationPos += 1.0f;
		break;
	case 'R':
		rc.rotationPos -= 1.0f;
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
		rc.rotation = false;
		om.allStop();
		break;
	case 'c':	// 모든 움직임 초기화
	case 'C':
		rc.rotation = false;
		om.allReset();
		rc.reset();
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
	om.bottom.update();
	om.mid.update();
	om.left.update();
	om.right.update();
	if (rc.rotation) {
		rc.rotationPos += 1.0f;
	}

	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, value);
	return;
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	//glViewport(0, 0, w, h);
}
