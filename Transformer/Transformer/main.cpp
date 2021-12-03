#pragma once
#include "make_vertexShaders.h"
#include "make_fragmentShaders.h"
#include "make_shaderProgram.h"
#include "stdafx.h"

#include "Field.h"
#include "Obstacle.h"
#include "Item.h"
#include "Robot.h"
#include "Light.h"


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
	GLint rotation;
	GLfloat rotationPos;
	RunControl() {
		reset();

	}
	void reset() {
		cx = 0.0f, cz = 0.0f;
		rotation = 0;
		rotationPos = 270.0f;
	}
};
RunControl rc;

struct ObjectManager {
	Field field;
	Obstacle obs[8];
	float obsx[8];
	float obsz[8];
	Item item[5];
	float itemx[5];
	float itemz[5];

	Robot rb;
	Light light;

	void initMyBuffer(GLint s_program) {
		field.initBuffer(s_program);
		for (int i = 0; i < 8; i++) {
			obs[i].initBuffer(s_program);
			obsx[i] = obs[i].xPos;
			obsz[i] = obs[i].zPos;
		}
		for (int i = 0; i < 5; i++) {
			item[i].initBuffer(s_program);
			itemx[i] = item[i].xPos;
			itemz[i] = item[i].zPos;
		}
		rb.initBuffer(s_program);
		light.initBuffer(s_program);
	}

	void allReset() {
		for (int i = 0; i < 8; i++) {
			obs[i].allReset();
		}
		for (int i = 0; i < 5; i++) {
			item[i].allReset();
		}
		rb.allReset();
		for (int i = 0; i < 8; i++) {
			obs[i].initBuffer(s_program);
			obsx[i] = obs[i].xPos;
			obsz[i] = obs[i].zPos;
		}
		for (int i = 0; i < 5; i++) {
			item[i].initBuffer(s_program);
			itemx[i] = item[i].xPos;
			itemz[i] = item[i].zPos;
		}
		light.allReset();
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
	glutCreateWindow("Transformer");

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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- ������ ���������ο� ���̴� �ҷ�����
	glUseProgram(s_program);

	glm::vec3 cameraPos = glm::vec3((rc.cx + 6.0) * cos(2 * M_PI / 360.0f * rc.rotationPos), 4.0f, (rc.cz + 6.0) * sin(2 * M_PI / 360.0f * rc.rotationPos)); //--- ī�޶� ��ġ
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- ���� ��ȯ ����
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	unsigned int viewPos = glGetUniformLocation(s_program, "viewPos"); //--- �ٶ󺸴� ���� �����׸�Ʈ ���̴��� ����
	glUniform3f(viewPos, (rc.cx + 6.0f) * (GLfloat)cos(2 * M_PI / 360.0f * rc.rotationPos), 4.0f, (rc.cz + 6.0f) * (GLfloat)sin(2 * M_PI / 360.0f * rc.rotationPos));


	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 200.0f);
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform"); //--- ���� ��ȯ �� ����
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	unsigned int modelLocation = glGetUniformLocation(s_program, "ModelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������

	glm::mat4 basicSet = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);

	om.field.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.field.getFactor()));
	om.field.draw();

	for (int i = 0; i < 8; i++) {
		om.obs[i].putFactor(om.field.getFactor());
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.obs[i].getFactor()));
		om.obs[i].draw();
	}

	for (int i = 0; i < 5; i++) {
		if (!om.rb.picked[i]) {
			om.item[i].putFactor(om.field.getFactor());
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.item[i].getFactor()));
			om.item[i].draw();
		}
	}

	om.rb.putFactor(om.field.getFactor());

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rb.getbodyFactor()));
	om.rb.body_draw();

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rb.getheadFactor()));
	om.rb.head_draw();

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rb.getleftarmFactor()));
	om.rb.leftarm_draw();

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rb.getleftlegFactor()));
	om.rb.leftleg_draw();

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rb.getrightarmFactor()));
	om.rb.rightarm_draw();

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rb.getrightlegFactor()));
	om.rb.rightleg_draw();

	for (int i = 0; i < om.rb.partnercount; i++) {
		om.rb.putsubFactor(om.field.getFactor(), i);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rb.getbodyFactor()));
		om.rb.body_draw();

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rb.getheadFactor()));
		om.rb.head_draw();

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rb.getleftarmFactor()));
		om.rb.leftarm_draw();

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rb.getleftlegFactor()));
		om.rb.leftleg_draw();

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rb.getrightarmFactor()));
		om.rb.rightarm_draw();

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.rb.getrightlegFactor()));
		om.rb.rightleg_draw();
	}

	om.light.putFactor(basicSet);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(om.light.getFactor()));
	om.light.draw();

	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'i':
	case 'I':
		printf("�κ� �� �̵�\n");
		om.rb.movement = 2;
		om.rb.rotation = 0.0f;
		break;
	case 'k':
	case 'K':
		printf("�κ� �� �̵�\n");
		om.rb.movement = 3;
		om.rb.rotation = 180.0f;
		break;
	case 'j':
	case 'J':
		printf("�κ� �� �̵�\n");
		om.rb.movement = 0;
		om.rb.rotation = 90.0f;
		break;
	case 'l':	
	case 'L':
		printf("�κ� �� �̵�\n");
		om.rb.movement = 1;
		om.rb.rotation = 270.0f;
		break;
	case 'w':
	case 'W':
		printf("ī�޶� �� �̵�\n");
		rc.cz -= 0.1f;
		break;
	case 's':
	case 'S':
		printf("ī�޶� �� �̵�\n");
		rc.cz += 0.1f;
		break;
	case 'a':
	case 'A':
		printf("ī�޶� �� �̵�\n");
		rc.cx -= 0.1f;
		break;
	case 'd':
	case 'D':
		printf("ī�޶� �� �̵�\n");
		rc.cx += 0.1f;
		break;
	case 'c':
		if (rc.rotation != 1) {
			printf("ī�޶� �� ȸ��\n");
			rc.cx = 0.0f, rc.cz = 0.0f;
			rc.rotation = 1;
		}
		else {
			printf("ī�޶� ȸ�� �ߴ�\n");
			rc.rotation = 0;
		}
		break;
	case 'C':
		if (rc.rotation != 2) {
			printf("ī�޶� �� ȸ��\n");
			rc.cx = 0.0f, rc.cz = 0.0f;
			rc.rotation = 2;
		}
		else {
			printf("ī�޶� ȸ�� �ߴ�\n");
			rc.rotation = 0;
		}
		break;
	case 32:	// SPACE
		if (om.rb.jump == 0) {
			printf("ĳ���� ����\n");
			om.rb.jump = 1;
		}
		break;
	case 27:	// ESCAPE
		printf("��� �� �ʱ�ȭ\n");
		om.allReset();
		rc.reset();
		break;
	case 't':
	case 'T':
		if (om.light.lightOn) {
			printf("���� ����\n");
			om.light.lightOn = false;
		}
		else {
			printf("���� �ѱ�\n");
			om.light.lightOn = true;
		}
		break;
	case 'q':	// ���α׷� ����
	case 'Q':
		printf("���α׷� ����\n");
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	if (rc.rotation == 1) {
		rc.rotationPos += 1.0f;
	}
	if (rc.rotation == 2) {
		rc.rotationPos -= 1.0f;
	}
	for (int i = 0; i < 5; i++) {
		om.item[i].update();
	}
	om.rb.update(om.obsx, om.obsz, 8, om.itemx, om.itemz, 5);
	om.light.update();
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, value);
	return;
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}
