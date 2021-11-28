#pragma once
#include "make_vertexShaders.h"
#include "make_fragmentShaders.h"
#include "make_shaderProgram.h"
#include "stdafx.h"

#include "Hexahedron.h"
#include "Quadrangular.h"
#include "Line.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

struct ObjectManager {
	Hexahedron hexa;
	Quadrangular quad;
	Line line;


	void initMyBuffer(GLuint s_program) {
		hexa.initBuffer(s_program);
		quad.initBuffer(s_program);
		line.initBuffer();
	}

	void initTexture(GLuint s_program) {
		glGenTextures(6, hexa.texture); //--- 텍스처 생성
		for (int i = 0; i < 6; i++) {
			char Text[100];
			int widthImage, heightImage, numberOfChannel;
			stbi_set_flip_vertically_on_load(true);
			glBindTexture(GL_TEXTURE_2D, hexa.texture[i]); //--- 텍스처 바인딩
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			sprintf(Text, "mol_ru\\molru%d.jpg", i);
			hexa.image[i] = stbi_load(Text, &widthImage, &heightImage, &numberOfChannel, 0); //--- 텍스처로 사용할 비트맵 이미지 로드하기
			glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, hexa.image[i]); //---텍스처 이미지 정의

			stbi_image_free(hexa.image[i]);
		}
		hexa.initTexture(s_program);

		glGenTextures(6, quad.texture); //--- 텍스처 생성
		for (int i = 0; i < 6; i++) {
			char Text[100];
			int widthImage, heightImage, numberOfChannel;
			stbi_set_flip_vertically_on_load(true);
			glBindTexture(GL_TEXTURE_2D, quad.texture[i]); //--- 텍스처 바인딩
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			sprintf(Text, "mol_ru\\molru%d.jpg", i);
			quad.image[i] = stbi_load(Text, &widthImage, &heightImage, &numberOfChannel, 0); //--- 텍스처로 사용할 비트맵 이미지 로드하기
			glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, quad.image[i]); //---텍스처 이미지 정의

			stbi_image_free(quad.image[i]);
		}
		quad.initTexture(s_program);
	}

	void allReset() {
		hexa.allReset();
		quad.allReset();
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
	glutCreateWindow("practice 28");

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
	om.initTexture(s_program);

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

	glm::vec3 cameraPos = glm::vec3(3.0f, 1.5f, 3.0f); //--- 카메라 위치
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	unsigned int viewPos = glGetUniformLocation(s_program, "viewPos"); //--- 바라보는 방향 프래그먼트 셰이더로 전달
	glUniform3f(viewPos, 3.0f, 1.5f, 3.0f);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 200.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.2)); //--- 공간을 약간 뒤로 미뤄줌
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	unsigned int modelLocation = glGetUniformLocation(s_program, "ModelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	glm::mat4 basicSet = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(basicSet));
	om.line.draw();

	om.hexa.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.hexa.getFactor()));
	om.hexa.draw();

	om.quad.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.quad.getFactor()));
	om.quad.draw();

	glDisable(GL_DEPTH_TEST);
	glutPostRedisplay();
	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'c':
	case 'C':
		om.hexa.drawed = true;
		om.quad.drawed = false;
		break;
	case 'p':
	case 'P':
		om.hexa.drawed = false;
		om.quad.drawed = true;
		break;
	case 'x':
	case 'X':
		if (om.hexa.Xrotate) {
			om.hexa.Xrotate = false;
		}
		else {
			om.hexa.Xrotate = true;
		}
		if (om.quad.Xrotate) {
			om.quad.Xrotate = false;
		}
		else {
			om.quad.Xrotate = true;
		}
		break;
	case 'y':
	case 'Y':
		if (om.hexa.Yrotate) {
			om.hexa.Yrotate = false;
		}
		else {
			om.hexa.Yrotate = true;
		}
		if (om.quad.Yrotate) {
			om.quad.Yrotate = false;
		}
		else {
			om.quad.Yrotate = true;
		}
		break;
	case 's':
	case 'S':
		om.allReset();
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
	om.hexa.update();
	om.quad.update();
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, value);
	return;
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}
