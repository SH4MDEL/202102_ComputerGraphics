#pragma once
#include "make_vertexShaders.h"
#include "make_fragmentShaders.h"
#include "make_shaderProgram.h"
#include "stdafx.h"

#include "Stage.h"
#include "Hexahedron_bottom.h"
#include "Hexahedron_mid.h"
#include "Hexahedron_top.h"
#include "Ball.h"

#define M_PI 3.1415926535897932384626433832795
#define M_WINDOWX 700
#define M_WINDOWY 700

GLvoid drawScene();
GLvoid motion(int x, int y);
GLvoid Keyboard(unsigned char inputKey, int x, int y);
GLvoid TimerFunction(int value);
GLvoid Reshape(int w, int h);

GLchar *vertexSource, *fragmentSource; //--- �ҽ��ڵ� ���� ����
GLuint vertexShader, fragmentShader; //--- ���̴� ��ü
GLuint s_program;

struct RunControl {
	GLfloat mPos, premPos, cy;
	bool rotation;
	GLfloat rotationPos;
	int nextBall;
	RunControl() {
		reset();

	}
	void reset() {
		mPos = 0.0f, premPos = 0.0f;
		cy = 0.0f;
		rotation = false;
		rotationPos = 90.0f;
		nextBall = 0;
	}
};
RunControl rc;

struct ObjectManager {
	Stage stage;
	Hexahedron_bottom hb;
	Hexahedron_mid hm;
	Hexahedron_top ht;
	Ball ball[5];

	void initMyBuffer() {
		stage.initBuffer();
		hb.initBuffer();
		hm.initBuffer();
		ht.initBuffer();
	}

	void allReset() {
		stage.allReset();
		hb.allReset();
		hm.allReset();
		ht.allReset();
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
	glutCreateWindow("practice 23");

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

	glutPassiveMotionFunc(motion);
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

	//glm::vec3 cameraPos = glm::vec3(rc.cx + 4.0 * cos(2 * M_PI / 360.0f * rc.rotationPos), 5.0f, rc.cz + 4.0 * sin(2 * M_PI / 360.0f * rc.rotationPos)); //--- ī�޶� ��ġ
	glm::vec3 cameraPos = glm::vec3(5.0f * cos(2 * M_PI / 360.0f * rc.rotationPos), 5.0f * sin(2 * M_PI / 360.0f * rc.rotationPos) + rc.cy, 0.0f); //--- ī�޶� ��ġ
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
	glm::vec3 cameraUp = glm::vec3(0.0f, 0.0f, -1.0f); //--- ī�޶� ���� ����
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

	for (int i = 0; i < 5; i++) {
		om.ball[i].putFactor(om.stage.getFactor());
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.ball[i].getFactor()));
		om.ball[i].draw();
	}

	om.hb.putFactor(om.stage.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.hb.getFactor()));
	om.hb.draw();

	om.hm.putFactor(om.hb.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.hm.getFactor()));
	om.hm.draw();

	om.ht.putFactor(om.hm.getFactor());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.ht.getFactor()));
	om.ht.draw();

	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid motion(int x, int y)
{
	//y = -(y - glutGet(GLUT_WINDOW_HEIGHT));
	rc.mPos = (((GLclampf)x - ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0));
	//yPos = (((GLclampf)y - ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0));
	if (rc.mPos - rc.premPos > 0.0f) {
		om.stage.rPos += (rc.mPos - rc.premPos) * 50.0f;
	}
	else if (rc.mPos - rc.premPos < 0.0f) {
		om.stage.rPos += (rc.mPos - rc.premPos) * 50.0f;
	}
	rc.premPos = rc.mPos;
	glutPostRedisplay();
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'z':
		rc.cy -= 0.1f;
		break;
	case 'Z':
		rc.cy += 0.1f;
		break;
	case 'b':
	case 'B':
		om.ball[rc.nextBall].allReset();
		if (rc.nextBall == 4) {
			rc.nextBall = 0;
		}
		else {
			rc.nextBall++;
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
	for (int i = 0; i < 5; i++) {
		om.ball[i].update();
	}
	
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, value);
	return;
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}
