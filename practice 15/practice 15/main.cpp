#pragma once
#include "shader.h"
#include "initShader.h"
#include "make_shaderProgram.h"
#include "stdafx.h"
void initBuffer();

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

struct VectexArray {
	GLuint line_vao[3], line_vbo[3][2];
	GLuint hexahedron_vao[6], hexahedron_vbo[6][2];
	GLuint tetrahedron_vao[6], tetrahedron_vbo[6][2];
};
VectexArray va;

struct RunControl {
	bool xRotate, yRotate;
	float xRotatePos, yRotatePos;
	bool aRotate, bRotate;
	float aRotatePos, bRotatePos;
	bool rRotate, changed;
	float rRotatePos;
	RunControl() {
		reset();
	}
	void reset() {
		xRotate = false, yRotate = false;
		xRotatePos = 30.0f, yRotatePos = -30.0f;
		aRotate = false, bRotate = false;
		aRotatePos = 30.0f, bRotatePos = -30.0f;
		rRotate = false, changed = false;
		rRotatePos = -30.0f;
	}
};
RunControl rc;

struct _Line {
	GLfloat data[3][2][2][3];
	_Line() {
		data[0][0][0][0] = 1.0f, data[0][0][0][1] = 0.0f, data[0][0][0][2] = 0.0f;		// ��ġ
		data[0][0][1][0] = -1.0f, data[0][0][1][1] = 0.0f, data[0][0][1][2] = 0.0f;

		data[0][1][0][0] = 0.0f, data[0][1][0][1] = 0.0f, data[0][1][0][2] = 0.0f;		// ����
		data[0][1][1][0] = 0.0f, data[0][1][1][1] = 0.0f, data[0][1][1][2] = 0.0f;

		data[1][0][0][0] = 0.0f, data[1][0][0][1] = 1.0f, data[1][0][0][2] = 0.0f;		// ��ġ
		data[1][0][1][0] = 0.0f, data[1][0][1][1] = -1.0f, data[1][0][1][2] = 0.0f;

		data[1][1][0][0] = 0.0f, data[1][1][0][1] = 0.0f, data[1][1][0][2] = 0.0f;		// ����
		data[1][1][1][0] = 0.0f, data[1][1][1][1] = 0.0f, data[1][1][1][2] = 0.0f;

		data[2][0][0][0] = 0.0f, data[2][0][0][1] = 0.0f, data[2][0][0][2] = 1.0f;		// ��ġ
		data[2][0][1][0] = 0.0f, data[2][0][1][1] = 0.0f, data[2][0][1][2] = -1.0f;

		data[2][1][0][0] = 0.0f, data[2][1][0][1] = 0.0f, data[2][1][0][2] = 0.0f;		// ����
		data[2][1][1][0] = 0.0f, data[2][1][1][1] = 0.0f, data[2][1][1][2] = 0.0f;
	}
};
_Line line;

struct Hexahedron {
	GLfloat data[6][2][2][3][3];
	bool drawed;
	Hexahedron() {

		// ���� ��ǥ
		data[0][0][0][0][0] = -0.15f, data[0][0][0][0][1] = -0.15f, data[0][0][0][0][2] = 0.15f;
		data[0][0][0][1][0] = 0.15f, data[0][0][0][1][1] = -0.15f, data[0][0][0][1][2] = 0.15f;
		data[0][0][0][2][0] = -0.15f, data[0][0][0][2][1] = 0.15f, data[0][0][0][2][2] = 0.15f;

		data[0][0][1][0][0] = -0.15f, data[0][0][1][0][1] = 0.15f, data[0][0][1][0][2] = 0.15f;
		data[0][0][1][1][0] = 0.15f, data[0][0][1][1][1] = -0.15f, data[0][0][1][1][2] = 0.15f;
		data[0][0][1][2][0] = 0.15f, data[0][0][1][2][1] = 0.15f, data[0][0][1][2][2] = 0.15f;

		// ���� ����
		data[0][1][0][0][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][0][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][0][2] = (GLfloat)colors(gen) / 10.0f;
		data[0][1][0][1][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][1][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][1][2] = (GLfloat)colors(gen) / 10.0f;
		data[0][1][0][2][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][2][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][0][2][2] = (GLfloat)colors(gen) / 10.0f;

		data[0][1][1][0][0] = data[0][1][0][2][0], data[0][1][1][0][1] = data[0][1][0][2][1], data[0][1][1][0][2] = data[0][1][0][2][2];
		data[0][1][1][1][0] = data[0][1][0][1][0], data[0][1][1][1][1] = data[0][1][0][1][1], data[0][1][1][1][2] = data[0][1][0][1][2];
		data[0][1][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[0][1][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[0][1][1][2][2] = (GLfloat)colors(gen) / 10.0f;


		// ��� ��ǥ
		data[1][0][0][0][0] = 0.15f, data[1][0][0][0][1] = 0.15f, data[1][0][0][0][2] = 0.15f;
		data[1][0][0][1][0] = 0.15f, data[1][0][0][1][1] = 0.15f, data[1][0][0][1][2] = -0.15f;
		data[1][0][0][2][0] = -0.15f, data[1][0][0][2][1] = 0.15f, data[1][0][0][2][2] = 0.15f;

		data[1][0][1][0][0] = -0.15f, data[1][0][1][0][1] = 0.15f, data[1][0][1][0][2] = 0.15f;
		data[1][0][1][1][0] = 0.15f, data[1][0][1][1][1] = 0.15f, data[1][0][1][1][2] = -0.15f;
		data[1][0][1][2][0] = -0.15f, data[1][0][1][2][1] = 0.15f, data[1][0][1][2][2] = -0.15f;

		// ��� ����
		data[1][1][0][0][0] = data[0][1][1][2][0], data[1][1][0][0][1] = data[0][1][1][2][1], data[1][1][0][0][2] = data[0][1][1][2][2];
		data[1][1][0][1][0] = (GLfloat)colors(gen) / 10.0f, data[1][1][0][1][1] = (GLfloat)colors(gen) / 10.0f, data[1][1][0][1][2] = (GLfloat)colors(gen) / 10.0f;
		data[1][1][0][2][0] = data[0][1][0][2][0], data[1][1][0][2][1] = data[0][1][0][2][1], data[1][1][0][2][2] = data[0][1][0][2][2];

		data[1][1][1][0][0] = data[0][1][0][2][0], data[1][1][1][0][1] = data[0][1][0][2][1], data[1][1][1][0][2] = data[0][1][0][2][2];
		data[1][1][1][1][0] = data[1][1][0][1][0], data[1][1][1][1][1] = data[1][1][0][1][1], data[1][1][1][1][2] = data[1][1][0][1][2];
		data[1][1][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[1][1][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[1][1][1][2][2] = (GLfloat)colors(gen) / 10.0f;

		// ���� ��ǥ
		data[2][0][0][0][0] = -0.15f, data[2][0][0][0][1] = 0.15f, data[2][0][0][0][2] = -0.15f;
		data[2][0][0][1][0] = -0.15f, data[2][0][0][1][1] = -0.15f, data[2][0][0][1][2] = -0.15f;
		data[2][0][0][2][0] = -0.15f, data[2][0][0][2][1] = -0.15f, data[2][0][0][2][2] = 0.15f;

		data[2][0][1][0][0] = -0.15f, data[2][0][1][0][1] = -0.15f, data[2][0][1][0][2] = 0.15f;
		data[2][0][1][1][0] = -0.15f, data[2][0][1][1][1] = 0.15f, data[2][0][1][1][2] = 0.15f;
		data[2][0][1][2][0] = -0.15f, data[2][0][1][2][1] = 0.15f, data[2][0][1][2][2] = -0.15f;

		// ���� ����
		data[2][1][0][0][0] = data[1][1][1][2][0], data[2][1][0][0][1] = data[1][1][1][2][1], data[2][1][0][0][2] = data[1][1][1][2][2];
		data[2][1][0][1][0] = (GLfloat)colors(gen) / 10.0f, data[2][1][0][1][1] = (GLfloat)colors(gen) / 10.0f, data[2][1][0][1][2] = (GLfloat)colors(gen) / 10.0f;
		data[2][1][0][2][0] = data[0][1][0][0][0], data[2][1][0][2][1] = data[0][1][0][0][1], data[2][1][0][2][2] = data[0][1][0][0][2];

		data[2][1][1][0][0] = data[0][1][0][0][0], data[2][1][1][0][1] = data[0][1][0][0][1], data[2][1][1][0][2] = data[0][1][0][0][2];
		data[2][1][1][1][0] = data[0][1][0][2][0], data[2][1][1][1][1] = data[0][1][0][2][1], data[2][1][1][1][2] = data[0][1][0][2][2];
		data[2][1][1][2][0] = data[1][1][1][2][0], data[2][1][1][2][1] = data[1][1][1][2][1], data[2][1][1][2][2] = data[1][1][1][2][2];

		// �ĸ� ��ǥ
		data[3][0][0][0][0] = -0.15f, data[3][0][0][0][1] = 0.15f, data[3][0][0][0][2] = -0.15f;
		data[3][0][0][1][0] = -0.15f, data[3][0][0][1][1] = -0.15f, data[3][0][0][1][2] = -0.15f;
		data[3][0][0][2][0] = 0.15f, data[3][0][0][2][1] = 0.15f, data[3][0][0][2][2] = -0.15f;

		data[3][0][1][0][0] = 0.15f, data[3][0][1][0][1] = 0.15f, data[3][0][1][0][2] = -0.15f;
		data[3][0][1][1][0] = -0.15f, data[3][0][1][1][1] = -0.15f, data[3][0][1][1][2] = -0.15f;
		data[3][0][1][2][0] = 0.15f, data[3][0][1][2][1] = -0.15f, data[3][0][1][2][2] = -0.15f;

		// �ĸ� ����
		data[3][1][0][0][0] = data[1][1][1][2][0], data[3][1][0][0][1] = data[1][1][1][2][1], data[3][1][0][0][2] = data[1][1][1][2][2];
		data[3][1][0][1][0] = data[2][1][0][1][0], data[3][1][0][1][1] = data[2][1][0][1][1], data[3][1][0][1][2] = data[2][1][0][1][2];
		data[3][1][0][2][0] = data[1][1][0][1][0], data[3][1][0][2][1] = data[1][1][0][1][1], data[3][1][0][2][2] = data[1][1][0][1][2];

		data[3][1][1][0][0] = data[1][1][0][1][0], data[3][1][1][0][1] = data[1][1][0][1][1], data[3][1][1][0][2] = data[1][1][0][1][2];
		data[3][1][1][1][0] = data[2][1][0][1][0], data[3][1][1][1][1] = data[2][1][0][1][1], data[3][1][1][1][2] = data[2][1][0][1][2];
		data[3][1][1][2][0] = (GLfloat)colors(gen) / 10.0f, data[3][1][1][2][1] = (GLfloat)colors(gen) / 10.0f, data[3][1][1][2][2] = (GLfloat)colors(gen) / 10.0f;

		// �ϴ� ��ǥ
		data[4][0][0][0][0] = 0.15f, data[4][0][0][0][1] = -0.15f, data[4][0][0][0][2] = -0.15f;
		data[4][0][0][1][0] = 0.15f, data[4][0][0][1][1] = -0.15f, data[4][0][0][1][2] = 0.15f;
		data[4][0][0][2][0] = -0.15f, data[4][0][0][2][1] = -0.15f, data[4][0][0][2][2] = 0.15f;

		data[4][0][1][0][0] = -0.15f, data[4][0][1][0][1] = -0.15f, data[4][0][1][0][2] = 0.15f;
		data[4][0][1][1][0] = -0.15f, data[4][0][1][1][1] = -0.15f, data[4][0][1][1][2] = -0.15f;
		data[4][0][1][2][0] = 0.15f, data[4][0][1][2][1] = -0.15f, data[4][0][1][2][2] = -0.15f;

		// �ϴ� ����
		data[4][1][0][0][0] = data[3][1][1][2][0], data[4][1][0][0][1] = data[3][1][1][2][1], data[4][1][0][0][2] = data[3][1][1][2][2];
		data[4][1][0][1][0] = data[0][1][0][1][0], data[4][1][0][1][1] = data[0][1][0][1][1], data[4][1][0][1][2] = data[0][1][0][1][2];
		data[4][1][0][2][0] = data[0][1][0][0][0], data[4][1][0][2][1] = data[0][1][0][0][1], data[4][1][0][2][2] = data[0][1][0][0][2];

		data[4][1][1][0][0] = data[0][1][0][0][0], data[4][1][1][0][1] = data[0][1][0][0][1], data[4][1][1][0][2] = data[0][1][0][0][2];
		data[4][1][1][1][0] = data[2][1][0][1][0], data[4][1][1][1][1] = data[2][1][0][1][1], data[4][1][1][1][2] = data[2][1][0][1][2];
		data[4][1][1][2][0] = data[3][1][1][2][0], data[4][1][1][2][1] = data[3][1][1][2][1], data[4][1][1][2][2] = data[3][1][1][2][2];

		// ���� ��ǥ
		data[5][0][0][0][0] = 0.15f, data[5][0][0][0][1] = -0.15f, data[5][0][0][0][2] = -0.15f;
		data[5][0][0][1][0] = 0.15f, data[5][0][0][1][1] = 0.15f, data[5][0][0][1][2] = -0.15f;
		data[5][0][0][2][0] = 0.15f, data[5][0][0][2][1] = -0.15f, data[5][0][0][2][2] = 0.15f;

		data[5][0][1][0][0] = 0.15f, data[5][0][1][0][1] = -0.15f, data[5][0][1][0][2] = 0.15f;
		data[5][0][1][1][0] = 0.15f, data[5][0][1][1][1] = 0.15f, data[5][0][1][1][2] = -0.15f;
		data[5][0][1][2][0] = 0.15f, data[5][0][1][2][1] = 0.15f, data[5][0][1][2][2] = 0.15f;
		
		// ���� ����
		data[5][1][0][0][0] = data[3][1][1][2][0], data[5][1][0][0][1] = data[3][1][1][2][1], data[5][1][0][0][2] = data[3][1][1][2][2];
		data[5][1][0][1][0] = data[1][1][0][1][0], data[5][1][0][1][1] = data[1][1][0][1][1], data[5][1][0][1][2] = data[1][1][0][1][2];
		data[5][1][0][2][0] = data[0][1][0][1][0], data[5][1][0][2][1] = data[0][1][0][1][1], data[5][1][0][2][2] = data[0][1][0][1][2];

		data[5][1][1][0][0] = data[0][1][0][1][0], data[5][1][1][0][1] = data[0][1][0][1][1], data[5][1][1][0][2] = data[0][1][0][1][2];
		data[5][1][1][1][0] = data[1][1][0][1][0], data[5][1][1][1][1] = data[1][1][0][1][1], data[5][1][1][1][2] = data[1][1][0][1][2];
		data[5][1][1][2][0] = data[0][1][1][2][0], data[5][1][1][2][1] = data[0][1][1][2][1], data[5][1][1][2][2] = data[0][1][1][2][2];

		drawed_reset();
	}
	void drawed_reset() {
		drawed = false;
	}
};
Hexahedron hexa;

GLUquadricObj* qobjSphere, *qobjCylinder1, *qobjCylinder2;

int main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("practice 15");

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
	initShader();
	initBuffer();

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

	unsigned int modelSelected = glGetUniformLocation(s_program, "modelSelect"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniform1i(modelSelected, 0);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 firstModel = glm::mat4(1.0f);
	glm::mat4 secondModel = glm::mat4(1.0f);

	model = glm::rotate(model, (float)glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0));
	model = glm::rotate(model, (float)glm::radians(rc.rRotatePos), glm::vec3(0.0, 1.0, 0.0));
	unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model)); //--- modelTransform ������ ��ȯ �� �����ϱ�

	for (int i = 0; i < 3; i++) {
		glBindVertexArray(va.line_vao[i]);
		glDrawArrays(GL_LINES, 0, 2);
	}


	glUniform1i(modelSelected, 1);

	firstModel = glm::rotate(firstModel, (float)glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0));
	firstModel = glm::rotate(firstModel, (float)glm::radians(rc.rRotatePos), glm::vec3(0.0, 1.0, 0.0));
	firstModel = glm::translate(firstModel, glm::vec3(-0.5, 0.0, 0.0));
	firstModel = glm::rotate(firstModel, (float)glm::radians(rc.xRotatePos), glm::vec3(1.0, 0.0, 0.0));
	firstModel = glm::rotate(firstModel, (float)glm::radians(rc.yRotatePos), glm::vec3(0.0, 1.0, 0.0));
	unsigned int firstModelLocation = glGetUniformLocation(s_program, "firstModelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniformMatrix4fv(firstModelLocation, 1, GL_FALSE, glm::value_ptr(firstModel)); //--- modelTransform ������ ��ȯ �� �����ϱ�
	if (rc.changed == false) {
		for (int i = 0; i < 6; i++) {
			glEnable(GL_DEPTH_TEST);

			glBindVertexArray(va.hexahedron_vao[i]);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			glDisable(GL_DEPTH_TEST);
		}
	}
	else {
		qobjCylinder1 = gluNewQuadric(); // ��ü �����ϱ�
		gluQuadricDrawStyle(qobjCylinder1, GLU_LINE);
		gluQuadricNormals(qobjCylinder1, GLU_SMOOTH); // ���� ����
		gluQuadricOrientation(qobjCylinder1, GLU_OUTSIDE); // ���� ����
		gluCylinder(qobjCylinder1, 0.2, 0.0, 0.4, 20, 8);
	}


	glUniform1i(modelSelected, 2);

	secondModel = glm::rotate(secondModel, (float)glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0));
	secondModel = glm::rotate(secondModel, (float)glm::radians(rc.rRotatePos), glm::vec3(0.0, 1.0, 0.0));
	secondModel = glm::translate(secondModel, glm::vec3(0.5, 0.0, 0.0));
	secondModel = glm::rotate(secondModel, (float)glm::radians(rc.aRotatePos), glm::vec3(1.0, 0.0, 0.0));
	secondModel = glm::rotate(secondModel, (float)glm::radians(rc.bRotatePos), glm::vec3(0.0, 1.0, 0.0));
	unsigned int secondModelLocation = glGetUniformLocation(s_program, "secondModelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniformMatrix4fv(secondModelLocation, 1, GL_FALSE, glm::value_ptr(secondModel)); //--- modelTransform ������ ��ȯ �� �����ϱ�
	if (rc.changed == false) {
		qobjSphere = gluNewQuadric(); // ��ü �����ϱ�
		gluQuadricDrawStyle(qobjSphere, GLU_LINE); // ���� ��Ÿ��
		gluQuadricNormals(qobjSphere, GLU_SMOOTH); // ���� ����
		gluQuadricOrientation(qobjSphere, GLU_OUTSIDE); // ���� ����
		gluSphere(qobjSphere, 0.2, 50, 50); // ��ü �����
	}
	else {
		qobjCylinder2 = gluNewQuadric(); // ��ü �����ϱ�
		gluQuadricDrawStyle(qobjCylinder2, GLU_LINE);
		gluQuadricNormals(qobjCylinder2, GLU_SMOOTH); // ���� ����
		gluQuadricOrientation(qobjCylinder2, GLU_OUTSIDE); // ���� ����
		gluCylinder(qobjCylinder2, 0.2, 0.2, 0.4, 20, 8);
	}
	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'X':
	case 'x':
		if (rc.xRotate) {
			rc.xRotate = false;
		}
		else {
			rc.xRotate = true;
		}
		break;
	case 'Y':
	case 'y':
		if (rc.yRotate) {
			rc.yRotate = false;
		}
		else {
			rc.yRotate = true;
		}
		break;
	case 'A':
	case 'a':
		if (rc.aRotate) {
			rc.aRotate = false;
		}
		else {
			rc.aRotate = true;
		}
		break;
	case 'B':
	case 'b':
		if (rc.bRotate) {
			rc.bRotate = false;
		}
		else {
			rc.bRotate = true;
		}
		break;
	case 'R':
	case 'r':
		if (rc.rRotate) {
			rc.rRotate = false;
		}
		else {
			rc.rRotate = true;
		}
		break;
	case 'C':
	case 'c':
		if (rc.changed) {
			rc.changed = false;
		}
		else {
			rc.changed = true;
		}
		break;
	case 'S':
	case 's':
		rc.reset();
		break;
	case 'Q':
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	if (rc.xRotate) {
		rc.xRotatePos += 0.5f;
	}
	if (rc.yRotate) {
		rc.yRotatePos += 0.5f;
	}
	if (rc.aRotate ) {
		rc.aRotatePos += 0.5f;
	}
	if (rc.bRotate) {
		rc.bRotatePos += 0.5f;
	}
	if (rc.rRotate) {
		rc.rRotatePos += 0.5f;
	}
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, value);
	return;
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

void initBuffer()
{
	glGenVertexArrays(3, va.line_vao);
	for (int i = 0; i < 3; i++) {
		glBindVertexArray(va.line_vao[i]);
		glGenBuffers(2, va.line_vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, va.line_vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), line.data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}

	glGenVertexArrays(6, va.hexahedron_vao);
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(va.hexahedron_vao[i]);
		glGenBuffers(2, va.hexahedron_vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, va.hexahedron_vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), hexa.data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}
}

