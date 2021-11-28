#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "make_vertexShaders.h"
#include "make_fragmentShaders.h"
#include "make_shaderProgram.h"
#include "stdafx.h"

#include "Light.h"
#include "Sun.h"
#include "Earth.h"
#include "Moon.h"

#define M_PI 3.1415926535897932384626433832795
#define M_WINDOWX 700
#define M_WINDOWY 700

GLvoid drawScene();
GLvoid Keyboard(unsigned char inputKey, int x, int y);
GLvoid TimerFunction(int value);
GLvoid Reshape(int w, int h);

GLchar *vertexSource, *fragmentSource; //--- �ҽ��ڵ� ���� ����
GLuint vertexShader, fragmentShader; //--- ���̴� ��ü
GLuint s_program;

struct RunControl {
	

	RunControl() {
		reset();

	}
	void reset() {
		
	}
};
RunControl rc;

struct ObjectManager {
	Light light;
	Sun sun;
	Earth earth;
	Moon moon;

	void initMyBuffer(GLuint s_program) {
		sun.initBuffer(s_program);
		light.initBuffer(s_program);
		earth.initBuffer(s_program);
		moon.initBuffer(s_program);
	}

	void allReset() {
		sun.allReset();
		light.allReset();
		earth.allReset();
		moon.allReset();
	}
};
ObjectManager om;


int main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(M_WINDOWX, M_WINDOWY);
	glutCreateWindow("practice 25");

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {					// glew �ʱ�ȭ
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
	//--- ����� ���� ����
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- ������ ���������ο� ���̴� �ҷ�����
	glUseProgram(s_program);

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 7.0f); //--- ī�޶� ��ġ
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- ���� ��ȯ ����
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	unsigned int viewPos = glGetUniformLocation(s_program, "viewPos"); //--- �ٶ󺸴� ���� �����׸�Ʈ ���̴��� ����
	glUniform3f(viewPos, -2.0f, 2.0f, 2.0f);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 200.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.2)); //--- ������ �ణ �ڷ� �̷���
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform"); //--- ���� ��ȯ �� ����
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	unsigned int modelLocation = glGetUniformLocation(s_program, "ModelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������

	glm::mat4 basicSet = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);

	om.light.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.light.getFactor()));
	om.light.draw();

	om.sun.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.sun.getFactor()));
	om.sun.draw();

	om.earth.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.earth.getFactor()));
	om.earth.draw();

	om.moon.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.moon.getFactor()));
	om.moon.draw();

	glDisable(GL_DEPTH_TEST);
	glutPostRedisplay();
	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'c':
	case 'C':
		if (om.light.colorType == 1) {
			om.light.colorType++;
			om.light.rCol = 0.3f, om.light.gCol = 1.0f, om.light.bCol = 0.3f;
		}
		else if (om.light.colorType == 2) {
			om.light.colorType++;
			om.light.rCol = 0.3f, om.light.gCol = 0.3f, om.light.bCol = 1.0f;
		}
		else {
			om.light.colorType = 1;
			om.light.rCol = 1.0f, om.light.gCol = 0.3f, om.light.bCol = 0.3f;
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
	case 'q':	// ���α׷� ����
	case 'Q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	om.light.update();
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, value);
	return;
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}
