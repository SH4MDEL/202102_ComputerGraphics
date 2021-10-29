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

GLvoid drawScene();
GLvoid Keyboard(unsigned char inputKey, int x, int y);
GLvoid TimerFunction(int value);
GLvoid Reshape(int w, int h);

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> colors(0, 10);

GLchar *vertexSource, *fragmentSource; //--- �ҽ��ڵ� ���� ����
GLuint vertexShader, fragmentShader; //--- ���̴� ��ü
GLuint s_program;

struct RunControl {

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
	
};
ObjectManager om;


int main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("practice 19");

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {					// glew �ʱ�ȭ
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
	//--- ����� ���� ����
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- ������ ���������ο� ���̴� �ҷ�����
	glUseProgram(s_program);

	//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.0f); //--- ī�޶� ��ġ
	//glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
	//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����
	//glm::mat4 view = glm::mat4(1.0f);
	//view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	//unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- ���� ��ȯ ����
	//glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


	//glm::mat4 projection = glm::mat4(1.0f);
	//if (rc.proj) {
	//	projection = glm::perspective(glm::radians(45.0f), 700.0f / 700.0f, 0.1f, 50.0f);
	//}
	//else {
	//	projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
	//}
	//projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.2)); //--- ������ �ణ �ڷ� �̷���
	//unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform"); //--- ���� ��ȯ �� ����
	//glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);


	unsigned int modelLocation = glGetUniformLocation(s_program, "ModelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������

	glm::mat4 basicSet = glm::mat4(1.0f);
	basicSet = glm::rotate(basicSet, glm::radians(-30.0f), glm::vec3(1.0, 0.0, 0.0));
	basicSet = glm::rotate(basicSet, glm::radians(30.0f), glm::vec3(0.0, 1.0, 0.0));

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(basicSet));

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

	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'b':	// ũ������ �Ʒ� ��ü�� z�� �������� ��/�� �������� �̵��Ѵ�.
	case 'B':
		
		break;
	case 'm':	// ũ������ �߾� ��ü�� y�࿡ ���Ͽ� ��/�� �������� ȸ���Ѵ�.
	case 'M':
		
		break;
	case 't':	// ũ������ �� �� 2���� ���� x�࿡ ���Ͽ� ��/�� �������� ���� �ݴ�������� ȸ���Ѵ�.
	case 'T':
		
		break;
	case 'z':	// ī�޶� z�� ��/�� �������� �̵�
	case 'Z':
		
		break;
	case 'x':	// ī�޶� x�� ��/�� �������� �̵�
	case 'X':
		
		break;
	case 'y':	// ī�޶� ���� y�࿡ ���ؼ� ȸ��
	case 'Y':
		
		break;
	case 'r':	// ȭ���� �߽��� y�࿡ ���Ͽ� ī�޶� ȸ��(�߽ɿ� ���Ͽ� ����)
	case 'R':
		
		break;
	case 'a':	// r ��ɾ�� ���� ȭ���� �߽��� �࿡ ���Ͽ� ī�޶� ȸ���ϴ� �ִϸ��̼��� �����Ѵ�/�����
	case 'A':
		
		break;
	case 's':	// ��� ������ ���߱�
	case 'S':
		
		break;
	case 'c':	// ��� ������ �ʱ�ȭ
	case 'C':

		break;
	case 'q':	// ���α׷� ����
	case 'Q':
		
		break;
	}
	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	

	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, value);
	return;
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}
