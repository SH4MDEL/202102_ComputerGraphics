#pragma once
#include "make_vertexShaders.h"
#include "make_fragmentShaders.h"
#include "make_shaderProgram.h"
#include "stdafx.h"

#include "Line.h"
#include "Hexahedron.h"
#include "Quadrangular_pyramid.h"

GLvoid drawScene();
GLvoid Keyboard(unsigned char inputKey, int x, int y);
GLvoid TimerFunction(int value);
GLvoid Reshape(int w, int h);

GLchar *vertexSource, *fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체
GLuint s_program;

struct RunControl {
	bool drawHexa;

	bool rotate;
	float rotatePos;

	bool hidden_surface;

	bool hexaTopLoop;
	float hexaTopLoopPos;

	bool hexaFrontOpen;
	float hexaFrontOpenPos;

	bool hexaSideOpen;
	float hexaSideOpenPos;

	bool quadSideOpen;
	float quadSideOpenPos;

	bool proj;
	RunControl() { reset(); }
	void reset() {
		drawHexa = true;

		rotate = false;
		rotatePos = 0.0f;

		hidden_surface = false;

		hexaTopLoop = false;
		hexaTopLoopPos = 0.0f;

		hexaFrontOpen = false;
		hexaFrontOpenPos = 0.0f;

		hexaSideOpen = false;
		hexaSideOpenPos = 0.0f;

		quadSideOpen = false;
		quadSideOpenPos = 0.0f;

		proj = false;
	}

};
RunControl rc;

struct ObjectManager {
	Line line[3] = {
		Line(-1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1),
		Line(0.0, -1.0, 0.0, 0.0, 1.0, 0.0, 2),
		Line(0.0, 0.0, -1.0, 0.0, 0.0, 1.0, 3)
	};
	Hexahedron hexa;
	Quadrangular_pyramid quad;

	void initMyBuffer() {
		for (int i = 0; i < 3; i++) {
			line[i].initBuffer();
		}
		hexa.initBuffer();
		quad.initBuffer();
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
	glutCreateWindow("practice 17");

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
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.3)); //--- 공간을 약간 뒤로 미뤄줌
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);


	unsigned int modelLocation = glGetUniformLocation(s_program, "ModelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 basicSet = glm::mat4(1.0f);
	basicSet = glm::rotate(basicSet, glm::radians(-30.0f), glm::vec3(1.0, 0.0, 0.0));
	basicSet = glm::rotate(basicSet, glm::radians(30.0f), glm::vec3(0.0, 1.0, 0.0));

	glm::mat4 rotateFactor = basicSet;

	glm::mat4 hexaTopFactor = basicSet;
	glm::mat4 hexaFrontFactor = basicSet;
	glm::mat4 hexaLeftSideFactor = basicSet;
	glm::mat4 hexaRightSideFactor = basicSet;

	glm::mat4 quadRightFactor = basicSet;
	glm::mat4 quadFrontFactor = basicSet;
	glm::mat4 quadLeftFactor = basicSet;
	glm::mat4 quadBackFactor = basicSet;


	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(basicSet));

	if (rc.hidden_surface) {
		glEnable(GL_DEPTH_TEST);
	}

	for (int i = 0; i < 3; i++) {
		glBindVertexArray(om.line[i].vao);
		glDrawArrays(GL_LINES, 0, 2);
	}
	rotateFactor = glm::rotate(rotateFactor, glm::radians(rc.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rotateFactor));
	if (rc.drawHexa) {
		for (int i = 0; i < 6; i++) {
			if (i == 0) {
				hexaFrontFactor = glm::rotate(hexaFrontFactor, glm::radians(rc.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
				hexaFrontFactor = glm::translate(hexaFrontFactor, glm::vec3(0.0f, -0.3f, 0.3f));
				hexaFrontFactor = glm::rotate(hexaFrontFactor, glm::radians(rc.hexaFrontOpenPos), glm::vec3(1.0f, 0.0f, 0.0f));
				hexaFrontFactor = glm::translate(hexaFrontFactor, glm::vec3(0.0f, 0.3f, -0.3f));
				glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(hexaFrontFactor));
			}
			else if (i == 1) {
				hexaTopFactor = glm::rotate(hexaTopFactor, glm::radians(rc.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
				hexaTopFactor = glm::translate(hexaTopFactor, glm::vec3(0.0f, 0.3f, 0.0f));
				hexaTopFactor = glm::rotate(hexaTopFactor, glm::radians(rc.hexaTopLoopPos), glm::vec3(1.0f, 0.0f, 0.0f));
				hexaTopFactor = glm::translate(hexaTopFactor, glm::vec3(0.0f, -0.3f, 0.0f));
				glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(hexaTopFactor));
			}
			else if (i == 2) {
				glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rotateFactor));
				hexaLeftSideFactor = glm::rotate(hexaLeftSideFactor, glm::radians(rc.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
				hexaLeftSideFactor = glm::translate(hexaLeftSideFactor, glm::vec3(0.0f, rc.hexaSideOpenPos, 0.0f));
				glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(hexaLeftSideFactor));
			}
			else if (i == 5) {
				glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rotateFactor));
				hexaRightSideFactor = glm::rotate(hexaRightSideFactor, glm::radians(rc.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
				hexaRightSideFactor = glm::translate(hexaRightSideFactor, glm::vec3(0.0f, rc.hexaSideOpenPos, 0.0f));
				glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(hexaRightSideFactor));
			}
			else {
				glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rotateFactor));
			}
			glBindVertexArray(om.hexa.vao[i]);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
	else {
		for (int i = 0; i < 6; i++) {
			if (i == 2) {
				quadRightFactor = glm::rotate(quadRightFactor, glm::radians(rc.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
				quadRightFactor = glm::translate(quadRightFactor, glm::vec3(0.3f, -0.3f, 0.0f));
				quadRightFactor = glm::rotate(quadRightFactor, glm::radians(-rc.quadSideOpenPos), glm::vec3(0.0f, 0.0f, 1.0f));
				quadRightFactor = glm::translate(quadRightFactor, glm::vec3(-0.3f, 0.3f, 0.0f));
				glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(quadRightFactor));
			}
			else if (i == 3) {
				quadFrontFactor = glm::rotate(quadFrontFactor, glm::radians(rc.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
				quadFrontFactor = glm::translate(quadFrontFactor, glm::vec3(0.0f, -0.3f, 0.3f));
				quadFrontFactor = glm::rotate(quadFrontFactor, glm::radians(rc.quadSideOpenPos), glm::vec3(1.0f, 0.0f, 0.0f));
				quadFrontFactor = glm::translate(quadFrontFactor, glm::vec3(0.0f, 0.3f, -0.3f));
				glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(quadFrontFactor));
			}
			else if (i == 4) {
				quadLeftFactor = glm::rotate(quadLeftFactor, glm::radians(rc.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
				quadLeftFactor = glm::translate(quadLeftFactor, glm::vec3(-0.3f, -0.3f, 0.0f));
				quadLeftFactor = glm::rotate(quadLeftFactor, glm::radians(rc.quadSideOpenPos), glm::vec3(0.0f, 0.0f, 1.0f));
				quadLeftFactor = glm::translate(quadLeftFactor, glm::vec3(0.3f, 0.3f, 0.0f));
				glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(quadLeftFactor));
			}
			else if (i == 5) {
				quadBackFactor = glm::rotate(quadBackFactor, glm::radians(rc.rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
				quadBackFactor = glm::translate(quadBackFactor, glm::vec3(0.0f, -0.3f, -0.3f));
				quadBackFactor = glm::rotate(quadBackFactor, glm::radians(-rc.quadSideOpenPos), glm::vec3(1.0f, 0.0f, 0.0f));
				quadBackFactor = glm::translate(quadBackFactor, glm::vec3(0.0f, 0.3f, 0.3f));
				glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(quadBackFactor));
			}
			else {
				glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rotateFactor));
			}
			glBindVertexArray(om.quad.vao[i]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}
	if (rc.hidden_surface) {
		glDisable(GL_DEPTH_TEST);
	}

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'y':
	case 'Y':
		if (rc.rotate) {
			rc.rotate = false;
		}
		else {
			rc.rotate = true;
		}
		break;
	case 'h':
	case 'H':
		if (rc.hidden_surface) {
			rc.hidden_surface = false;
		}
		else {
			rc.hidden_surface = true;
		}
		break;
	case 't':
	case 'T':
		rc.drawHexa = true;
		if (rc.hexaTopLoop) {
			rc.hexaTopLoop = false;
		}
		else {
			rc.hexaTopLoop = true;
		}
		break;
	case 'f':
	case 'F':
		rc.drawHexa = true;
		if (rc.hexaFrontOpen) {
			rc.hexaFrontOpen = false;
		}
		else {
			rc.hexaFrontOpen = true;
		}
		break;
	case '1':
		rc.drawHexa = true;
		rc.hexaSideOpen = true;
		break;
	case '2':
		rc.hexaSideOpen = false;
		break;
	case 'o':
	case 'O':
		rc.drawHexa = false;
		if (rc.quadSideOpen) {
			rc.quadSideOpen = false;
		}
		else {
			rc.quadSideOpen = true;
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
	if (rc.rotate) {
		rc.rotatePos += 0.5f;
	}

	if (rc.hexaTopLoop) {
		rc.hexaTopLoopPos += 0.5f;
	}
	else if (!rc.hexaTopLoop && rc.hexaTopLoopPos != 0.0f) {
		rc.hexaTopLoopPos = 0.0f;
	}

	if (rc.hexaFrontOpen) {
		if (rc.hexaFrontOpenPos + 1.0f > 90.0f) {
			rc.hexaFrontOpenPos = 90.0f;
		}
		else {
			rc.hexaFrontOpenPos += 1.0f;
		}
	}
	else if (!rc.hexaFrontOpen) {
		if (rc.hexaFrontOpenPos - 1.0f < 0.0f) {
			rc.hexaFrontOpenPos = 0.0f;
		}
		else {
			rc.hexaFrontOpenPos -= 1.0f;
		}
	}

	if (rc.hexaSideOpen) {
		if (rc.hexaSideOpenPos + 0.02f > 0.6f) {
			rc.hexaSideOpenPos = 0.6f;
		}
		else {
			rc.hexaSideOpenPos += 0.02f;
		}
	}
	else if (!rc.hexaSideOpen) {
		if (rc.hexaSideOpenPos - 0.02f < 0.0f) {
			rc.hexaSideOpenPos = 0.0f;
		}
		else {
			rc.hexaSideOpenPos -= 0.02f;
		}
	}

	if (rc.quadSideOpen) {
		if (rc.quadSideOpenPos + 1.0f > 233.14f) {
			rc.quadSideOpenPos = 233.14f;
		}
		else {
			rc.quadSideOpenPos += 0.5f;
		}
	}
	else if (!rc.quadSideOpen) {
		if (rc.quadSideOpenPos - 0.5f < 0.0f) {
			rc.quadSideOpenPos = 0.0f;
		}
		else {
			rc.quadSideOpenPos -= 0.5f;
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
