#pragma once
#include "make_vertexShaders.h"
#include "make_fragmentShaders.h"
#include "make_shaderProgram.h"
#include "stdafx.h"

#include "Stage.h"
#include "Obstacle.h"

#include "Robot_body.h"
#include "Robot_head.h"
#include "Robot_leftarm.h"
#include "Robot_leftleg.h"
#include "Robot_rightarm.h"
#include "Robot_rightleg.h"

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
	GLfloat cx, cz;
	bool rotation;
	GLfloat rotationPos;
	RunControl() {
		reset();

	}
	void reset() {
		cx = 0.0f, cz = 0.0f;
		rotation = false;
		rotationPos = 270.0f;
	}
};
RunControl rc;

struct ObjectManager {
	Stage stage;
	Obstacle obs;
	Robot_body rb;
	Robot_head rh;
	Robot_leftarm rla;
	Robot_leftleg rll;
	Robot_rightarm rra;
	Robot_rightleg rrl;

	void initMyBuffer() {
		stage.initBuffer();
		obs.initBuffer();
		rb.initBuffer();
		rh.initBuffer();
		rla.initBuffer();
		rll.initBuffer();
		rra.initBuffer();
		rrl.initBuffer();
	}

	void allReset() {
		stage.allReset();
		obs.allReset();
		rb.allReset();
		rh.allReset();
		rla.allReset();
		rll.allReset();
		rra.allReset();
		rrl.allReset();
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
	glutCreateWindow("practice 21");

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

	glm::vec3 cameraPos = glm::vec3(rc.cx + 4.0 * cos(2 * M_PI / 360.0f * rc.rotationPos), 2.0f, rc.cz + 4.0 * sin(2 * M_PI / 360.0f * rc.rotationPos)); //--- ī�޶� ��ġ
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- ���� ��ȯ ����
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 200.0f);
	// projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.2)); //--- ������ �ణ �ڷ� �̷���
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform"); //--- ���� ��ȯ �� ����
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	unsigned int modelLocation = glGetUniformLocation(s_program, "ModelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������

	glm::mat4 basicSet = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);

	om.stage.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.stage.getFactor()));
	om.stage.draw();

	om.stage.putDoorFactor(om.stage.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.stage.getDoorFactor()));
	om.stage.drawDoor();

	om.obs.putFactor(om.stage.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.obs.getFactor()));
	om.obs.draw();

	om.rb.putFactor(om.stage.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rb.getFactor()));
	om.rb.draw();

	om.rh.putFactor(om.rb.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rh.getFactor()));
	om.rh.draw();

	om.rla.putFactor(om.rb.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rla.getFactor()));
	om.rla.draw();

	om.rll.putFactor(om.rb.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rll.getFactor()));
	om.rll.draw();

	om.rra.putFactor(om.rb.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rra.getFactor()));
	om.rra.draw();

	om.rrl.putFactor(om.rb.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rrl.getFactor()));
	om.rrl.draw();

	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'w':
	case 'W':
		om.rb.rotation = 0.0f;
		om.rb.movement = 2;
		break;
	case 's':
	case 'S':
		om.rb.movement = 3;
		om.rb.rotation = 180.0f;
		break;
	case 'a':
	case 'A':
		om.rb.movement = 0;
		om.rb.rotation = 90.0f;
		break;
	case 'd':	
	case 'D':
		om.rb.movement = 1;
		om.rb.rotation = 270.0f;
		break;
	case 'j':
	case 'J':
		if (om.rb.jump == 0) {
			om.rb.jump = 1;
		}
		break;
	case 'z':
		rc.cz += 0.1f;
		break;
	case 'Z':
		rc.cz -= 0.1f;
		break;
	case 'x':
		rc.cx += 0.1f;
		break;
	case 'X':
		rc.cx -= 0.1f;
		break;
	case 'o':
	case 'O':
		if (om.stage.opendoor) {
			om.stage.opendoor = false;
		}
		else {
			om.stage.opendoor = true;
		}
		break;
	case 'r':	// r ��ɾ�� ���� ȭ���� �߽��� �࿡ ���Ͽ� ī�޶� ȸ���ϴ� �ִϸ��̼��� �����Ѵ�/�����
	case 'R':
		if (rc.rotation) {
			rc.rotation = false;
		}
		else {
			rc.rotation = true;
		}
		break;
	case 'i':	// ��� ������ �ʱ�ȭ
	case 'I':
		om.allReset();
		rc.reset();
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
	if (rc.rotation) {
		rc.rotationPos += 1.0f;
	}
	om.stage.update();
	om.rb.update(om.obs.xPos, om.obs.zPos);
	om.rla.update();
	om.rll.update();
	om.rra.update();
	om.rrl.update();
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, value);
	return;
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}
