#pragma once
#include "make_vertexShaders.h"
#include "make_fragmentShaders.h"
#include "make_shaderProgram.h"
#include "stdafx.h"

#include "Light.h"
#include "Field.h"
#include "Crane_Bottom.h"
#include "Crane_Mid.h"
#include "Crane_Lefthand.h"
#include "Crane_Righthand.h"

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
	GLfloat x, z;
	bool rotation, revolve;
	GLfloat rotationPos, revolvePos;
	bool Cameraset;
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
	}
};
RunControl rc;

struct ObjectManager {
	Light light;
	Field field;
	Crane_Bottom bottom;
	Crane_Mid mid;
	Crane_Lefthand left;
	Crane_Righthand right;


	void initMyBuffer(GLuint s_program) {
		light.initBuffer(s_program);
		field.initBuffer(s_program);
		bottom.initBuffer(s_program);
		mid.initBuffer(s_program);
		left.initBuffer(s_program);
		right.initBuffer(s_program);
	}

	void allStop() {
		light.rotate = false;
		bottom.zMove = false;
		mid.rMove = false;
		left.rMove = false;
		right.rMove = false;
	}

	void allReset() {
		light.allReset();
		bottom.allReset();
		mid.allReset();
		left.allReset();
		right.allReset();
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
	glutCreateWindow("practice 26");

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

	glm::vec3 cameraPos = glm::vec3(rc.x + 4.0 * cos(2 * M_PI / 360.0f * rc.rotationPos), 1.5f, rc.z + 4.0 * sin(2 * M_PI / 360.0f * rc.rotationPos)); //--- ī�޶� ��ġ
	glm::vec3 cameraDirection = glm::vec3(100 * cos(2 * M_PI / 360.0f * rc.revolvePos), 0.0f, 100 * sin(2 * M_PI / 360.0f * rc.revolvePos)); //--- ī�޶� �ٶ󺸴� ����
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- ���� ��ȯ ����
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	unsigned int viewPos = glGetUniformLocation(s_program, "viewPos"); //--- �ٶ󺸴� ���� �����׸�Ʈ ���̴��� ����
	glUniform3f(viewPos, rc.x + 3.4 * cos(2 * M_PI / 360.0f * rc.rotationPos), 1.5f, rc.z + 3.4 * sin(2 * M_PI / 360.0f * rc.rotationPos));

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
	glutPostRedisplay();
	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case '1':
		om.light.lightOn = true;
		break;
	case '2':
		om.light.lightOn = false;
		break;
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
	case 'b':	// ũ������ �Ʒ� ��ü�� z�� �������� ��/�� �������� �̵��Ѵ�.
	case 'B':
		if (om.bottom.zMove == -1 || om.bottom.zMove == 0) {
			om.bottom.zMove += 2;
		}
		else {
			om.bottom.zMove -= 2;
		}
		break;
	case 'm':	// ũ������ �߾� ��ü�� y�࿡ ���Ͽ� �� �������� ȸ���Ѵ�.
	case 'M':
		if (om.mid.rMove == 1) {
			om.mid.rMove = 0;
		}
		else {
			om.mid.rMove = 1;
		}
		break;
	case 'n':	// ũ������ �߾� ��ü�� y�࿡ ���Ͽ� �� �������� ȸ���Ѵ�.
	case 'N':
		if (om.mid.rMove == 2) {
			om.mid.rMove = 0;
		}
		else {
			om.mid.rMove = 2;
		}
		break;
	case 't':	// ũ������ �� �� 2���� ���� x�࿡ ���Ͽ� ��/�� �������� ���� �ݴ�������� ȸ���Ѵ�.
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
	case 'z':	// ī�޶� z�� ��/�� �������� �̵�
		rc.z += 0.1f;
		break;
	case 'Z':
		rc.z -= 0.1f;
		break;
	case 'x':	// ī�޶� x�� ��/�� �������� �̵�
		rc.x += 0.1f;
		break;
	case 'X':
		rc.x -= 0.1f;
		break;
	case 'y':	// ī�޶� ���� y�࿡ ���ؼ� ȸ��
	case 'Y':
		if (rc.revolve) {
			rc.revolve = false;
		}
		else {
			rc.revolve = true;
		}
		break;
	case 'a':	// r ��ɾ�� ���� ȭ���� �߽��� �࿡ ���Ͽ� ī�޶� ȸ���ϴ� �ִϸ��̼��� �����Ѵ�/�����
	case 'A':
		if (rc.rotation) {
			rc.rotation = false;
		}
		else {
			rc.rotation = true;
		}
		break;
	case 's':	// ��� ������ ���߱�
	case 'S':
		rc.rotation = false;
		rc.revolve = false;
		om.allStop();
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
	om.bottom.update();
	om.mid.update();
	om.left.update();
	om.right.update();
	if (rc.rotation) {
		rc.rotationPos += 1.0f;
		rc.revolvePos += 1.0f;
	}
	if (rc.revolve) {
		rc.revolvePos += 1.0f;
	}
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, value);
	return;
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}
