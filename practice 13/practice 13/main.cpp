#pragma once
#include "shader.h"
#include "initShader.h"
#include "make_shaderProgram.h"
#include "stdafx.h"
void initBuffer();

GLvoid drawScene();
GLvoid Keyboard(unsigned char inputKey, int x, int y);
GLvoid motion(int x, int y);
GLvoid Reshape(int w, int h);

GLchar* vertexSource, * fragmentSource; //--- �ҽ��ڵ� ���� ����
GLuint vertexShader, fragmentShader; //--- ���̴� ��ü
GLuint s_program;

struct VectexArray {
	GLuint line_vao[2], line_vbo[2][2];
	GLuint hexahedron_vao[6], hexahedron_vbo[6][2];
	GLuint tetrahedron_vao[6], tetrahedron_vbo[6][2];
};
VectexArray va;

struct _Line {
	GLfloat data[2][2][2][3];
	_Line() {
		data[0][0][0][0] = 1.0f, data[0][0][0][1] = 0.0f, data[0][0][0][2] = 0.0f;		// ��ġ
		data[0][0][1][0] = -1.0f, data[0][0][1][1] = 0.0f, data[0][0][1][2] = 0.0f;

		data[0][1][0][0] = 0.0f, data[0][1][0][1] = 0.0f, data[0][1][0][2] = 0.0f;		// ����
		data[0][1][1][0] = 0.0f, data[0][1][1][1] = 0.0f, data[0][1][1][2] = 0.0f;

		data[1][0][0][0] = 0.0f, data[1][0][0][1] = 1.0f, data[1][0][0][2] = 0.0f;		// ��ġ
		data[1][0][1][0] = 0.0f, data[1][0][1][1] = -1.0f, data[1][0][1][2] = 0.0f;

		data[1][1][0][0] = 0.0f, data[1][1][0][1] = 0.0f, data[1][1][0][2] = 0.0f;		// ����
		data[1][1][1][0] = 0.0f, data[1][1][1][1] = 0.0f, data[1][1][1][2] = 0.0f;
	}
};
_Line line;

struct Hexahedron {
	GLfloat data[6][2][2][3][3];
	bool drawed[6];
	Hexahedron() {

		// ���� ��ǥ
		data[0][0][0][0][0] = -0.5f, data[0][0][0][0][1] = -0.5f, data[0][0][0][0][2] = 0.5f;
		data[0][0][0][1][0] = 0.5f, data[0][0][0][1][1] = -0.5f, data[0][0][0][1][2] = 0.5f;
		data[0][0][0][2][0] = -0.5f, data[0][0][0][2][1] = 0.5f, data[0][0][0][2][2] = 0.5f;

		data[0][0][1][0][0] = -0.5f, data[0][0][1][0][1] = 0.5f, data[0][0][1][0][2] = 0.5f;
		data[0][0][1][1][0] = 0.5f, data[0][0][1][1][1] = -0.5f, data[0][0][1][1][2] = 0.5f;
		data[0][0][1][2][0] = 0.5f, data[0][0][1][2][1] = 0.5f, data[0][0][1][2][2] = 0.5f;

		// ���� ����
		data[0][1][0][0][0] = 1.0f, data[0][1][0][0][1] = 0.0f, data[0][1][0][0][2] = 0.0f;
		data[0][1][0][1][0] = 1.0f, data[0][1][0][1][1] = 0.0f, data[0][1][0][1][2] = 0.0f;
		data[0][1][0][2][0] = 1.0f, data[0][1][0][2][1] = 0.0f, data[0][1][0][2][2] = 0.0f;

		data[0][1][1][0][0] = 1.0f, data[0][1][1][0][1] = 0.0f, data[0][1][1][0][2] = 0.0f;
		data[0][1][1][1][0] = 1.0f, data[0][1][1][1][1] = 0.0f, data[0][1][1][1][2] = 0.0f;
		data[0][1][1][2][0] = 1.0f, data[0][1][1][2][1] = 0.0f, data[0][1][1][2][2] = 0.0f;


		// ��� ��ǥ
		data[1][0][0][0][0] = 0.5f, data[1][0][0][0][1] = 0.5f, data[1][0][0][0][2] = 0.5f;
		data[1][0][0][1][0] = 0.5f, data[1][0][0][1][1] = 0.5f, data[1][0][0][1][2] = -0.5f;
		data[1][0][0][2][0] = -0.5f, data[1][0][0][2][1] = 0.5f, data[1][0][0][2][2] = 0.5f;

		data[1][0][1][0][0] = -0.5f, data[1][0][1][0][1] = 0.5f, data[1][0][1][0][2] = 0.5f;
		data[1][0][1][1][0] = 0.5f, data[1][0][1][1][1] = 0.5f, data[1][0][1][1][2] = -0.5f;
		data[1][0][1][2][0] = -0.5f, data[1][0][1][2][1] = 0.5f, data[1][0][1][2][2] = -0.5f;

		// ��� ����
		data[1][1][0][0][0] = 0.0f, data[1][1][0][0][1] = 1.0f, data[1][1][0][0][2] = 0.0f;
		data[1][1][0][1][0] = 0.0f, data[1][1][0][1][1] = 1.0f, data[1][1][0][1][2] = 0.0f;
		data[1][1][0][2][0] = 0.0f, data[1][1][0][2][1] = 1.0f, data[1][1][0][2][2] = 0.0f;

		data[1][1][1][0][0] = 0.0f, data[1][1][1][0][1] = 1.0f, data[1][1][1][0][2] = 0.0f;
		data[1][1][1][1][0] = 0.0f, data[1][1][1][1][1] = 1.0f, data[1][1][1][1][2] = 0.0f;
		data[1][1][1][2][0] = 0.0f, data[1][1][1][2][1] = 1.0f, data[1][1][1][2][2] = 0.0f;

		// ���� ��ǥ
		data[2][0][0][0][0] = -0.5f, data[2][0][0][0][1] = 0.5f, data[2][0][0][0][2] = -0.5f;
		data[2][0][0][1][0] = -0.5f, data[2][0][0][1][1] = -0.5f, data[2][0][0][1][2] = -0.5f;
		data[2][0][0][2][0] = -0.5f, data[2][0][0][2][1] = -0.5f, data[2][0][0][2][2] = 0.5f;

		data[2][0][1][0][0] = -0.5f, data[2][0][1][0][1] = -0.5f, data[2][0][1][0][2] = 0.5f;
		data[2][0][1][1][0] = -0.5f, data[2][0][1][1][1] = 0.5f, data[2][0][1][1][2] = 0.5f;
		data[2][0][1][2][0] = -0.5f, data[2][0][1][2][1] = 0.5f, data[2][0][1][2][2] = -0.5f;

		// ���� ����
		data[2][1][0][0][0] = 0.0f, data[2][1][0][0][1] = 0.0f, data[2][1][0][0][2] = 1.0f;
		data[2][1][0][1][0] = 0.0f, data[2][1][0][1][1] = 0.0f, data[2][1][0][1][2] = 1.0f;
		data[2][1][0][2][0] = 0.0f, data[2][1][0][2][1] = 0.0f, data[2][1][0][2][2] = 1.0f;

		data[2][1][1][0][0] = 0.0f, data[2][1][1][0][1] = 0.0f, data[2][1][1][0][2] = 1.0f;
		data[2][1][1][1][0] = 0.0f, data[2][1][1][1][1] = 0.0f, data[2][1][1][1][2] = 1.0f;
		data[2][1][1][2][0] = 0.0f, data[2][1][1][2][1] = 0.0f, data[2][1][1][2][2] = 1.0f;

		// �ĸ� ��ǥ
		data[3][0][0][0][0] = -0.5f, data[3][0][0][0][1] = 0.5f, data[3][0][0][0][2] = -0.5f;
		data[3][0][0][1][0] = -0.5f, data[3][0][0][1][1] = -0.5f, data[3][0][0][1][2] = -0.5f;
		data[3][0][0][2][0] = 0.5f, data[3][0][0][2][1] = 0.5f, data[3][0][0][2][2] = -0.5f;

		data[3][0][1][0][0] = 0.5f, data[3][0][1][0][1] = 0.5f, data[3][0][1][0][2] = -0.5f;
		data[3][0][1][1][0] = -0.5f, data[3][0][1][1][1] = -0.5f, data[3][0][1][1][2] = -0.5f;
		data[3][0][1][2][0] = 0.5f, data[3][0][1][2][1] = -0.5f, data[3][0][1][2][2] = -0.5f;

		// �ĸ� ����
		data[3][1][0][0][0] = 0.0f, data[3][1][0][0][1] = 1.0f, data[3][1][0][0][2] = 1.0f;
		data[3][1][0][1][0] = 0.0f, data[3][1][0][1][1] = 1.0f, data[3][1][0][1][2] = 1.0f;
		data[3][1][0][2][0] = 0.0f, data[3][1][0][2][1] = 1.0f, data[3][1][0][2][2] = 1.0f;

		data[3][1][1][0][0] = 0.0f, data[3][1][1][0][1] = 1.0f, data[3][1][1][0][2] = 1.0f;
		data[3][1][1][1][0] = 0.0f, data[3][1][1][1][1] = 1.0f, data[3][1][1][1][2] = 1.0f;
		data[3][1][1][2][0] = 0.0f, data[3][1][1][2][1] = 1.0f, data[3][1][1][2][2] = 1.0f;

		// �ϴ� ��ǥ
		data[4][0][0][0][0] = 0.5f, data[4][0][0][0][1] = -0.5f, data[4][0][0][0][2] = -0.5f;
		data[4][0][0][1][0] = 0.5f, data[4][0][0][1][1] = -0.5f, data[4][0][0][1][2] = 0.5f;
		data[4][0][0][2][0] = -0.5f, data[4][0][0][2][1] = -0.5f, data[4][0][0][2][2] = 0.5f;

		data[4][0][1][0][0] = -0.5f, data[4][0][1][0][1] = -0.5f, data[4][0][1][0][2] = 0.5f;
		data[4][0][1][1][0] = -0.5f, data[4][0][1][1][1] = -0.5f, data[4][0][1][1][2] = -0.5f;
		data[4][0][1][2][0] = 0.5f, data[4][0][1][2][1] = -0.5f, data[4][0][1][2][2] = -0.5f;

		// �ϴ� ����
		data[4][1][0][0][0] = 1.0f, data[4][1][0][0][1] = 0.0f, data[4][1][0][0][2] = 1.0f;
		data[4][1][0][1][0] = 1.0f, data[4][1][0][1][1] = 0.0f, data[4][1][0][1][2] = 1.0f;
		data[4][1][0][2][0] = 1.0f, data[4][1][0][2][1] = 0.0f, data[4][1][0][2][2] = 1.0f;

		data[4][1][1][0][0] = 1.0f, data[4][1][1][0][1] = 0.0f, data[4][1][1][0][2] = 1.0f;
		data[4][1][1][1][0] = 1.0f, data[4][1][1][1][1] = 0.0f, data[4][1][1][1][2] = 1.0f;
		data[4][1][1][2][0] = 1.0f, data[4][1][1][2][1] = 0.0f, data[4][1][1][2][2] = 1.0f;

		// ���� ��ǥ
		data[5][0][0][0][0] = 0.5f, data[5][0][0][0][1] = -0.5f, data[5][0][0][0][2] = -0.5f;
		data[5][0][0][1][0] = 0.5f, data[5][0][0][1][1] = 0.5f, data[5][0][0][1][2] = -0.5f;
		data[5][0][0][2][0] = 0.5f, data[5][0][0][2][1] = -0.5f, data[5][0][0][2][2] = 0.5f;

		data[5][0][1][0][0] = 0.5f, data[5][0][1][0][1] = -0.5f, data[5][0][1][0][2] = 0.5f;
		data[5][0][1][1][0] = 0.5f, data[5][0][1][1][1] = 0.5f, data[5][0][1][1][2] = -0.5f;
		data[5][0][1][2][0] = 0.5f, data[5][0][1][2][1] = 0.5f, data[5][0][1][2][2] = 0.5f;
		
		// ���� ����
		data[5][1][0][0][0] = 1.0f, data[5][1][0][0][1] = 1.0f, data[5][1][0][0][2] = 0.0f;
		data[5][1][0][1][0] = 1.0f, data[5][1][0][1][1] = 1.0f, data[5][1][0][1][2] = 0.0f;
		data[5][1][0][2][0] = 1.0f, data[5][1][0][2][1] = 1.0f, data[5][1][0][2][2] = 0.0f;

		data[5][1][1][0][0] = 1.0f, data[5][1][1][0][1] = 1.0f, data[5][1][1][0][2] = 0.0f;
		data[5][1][1][1][0] = 1.0f, data[5][1][1][1][1] = 1.0f, data[5][1][1][1][2] = 0.0f;
		data[5][1][1][2][0] = 1.0f, data[5][1][1][2][1] = 1.0f, data[5][1][1][2][2] = 0.0f;

		drawed_reset();
	}
	void drawed_reset() {
		for (int i = 0; i < 6; i++) {
			drawed[i] = false;
		}
	}
};
Hexahedron hexa;

struct Tetrahedron {
	GLfloat data[6][2][3][3];
	bool drawed[6];
	Tetrahedron() {

		// �ϴ� �簢�� ��ǥ
		data[0][0][0][0] = -0.5f, data[0][0][0][1] = -0.5f, data[0][0][0][2] = 0.5f;
		data[0][0][1][0] = -0.5f, data[0][0][1][1] = -0.5f, data[0][0][1][2] = -0.5f;
		data[0][0][2][0] = 0.5f, data[0][0][2][1] = -0.5f, data[0][0][2][2] = 0.5f;

		data[1][0][0][0] = 0.5f, data[1][0][0][1] = -0.5f, data[1][0][0][2] = 0.5f;
		data[1][0][1][0] = -0.5f, data[1][0][1][1] = -0.5f, data[1][0][1][2] = -0.5f;
		data[1][0][2][0] = 0.5f, data[1][0][2][1] = -0.5f, data[1][0][2][2] = -0.5f;

		// �ϴ� �簢�� ����
		data[0][1][0][0] = 1.0f, data[0][1][0][1] = 0.0f, data[0][1][0][2] = 0.0f;
		data[0][1][1][0] = 1.0f, data[0][1][1][1] = 0.0f, data[0][1][1][2] = 0.0f;
		data[0][1][2][0] = 1.0f, data[0][1][2][1] = 0.0f, data[0][1][2][2] = 0.0f;

		data[1][1][0][0] = 1.0f, data[1][1][0][1] = 0.0f, data[1][1][0][2] = 0.0f;
		data[1][1][1][0] = 1.0f, data[1][1][1][1] = 0.0f, data[1][1][1][2] = 0.0f;
		data[1][1][2][0] = 1.0f, data[1][1][2][1] = 0.0f, data[1][1][2][2] = 0.0f;

		// ���� �ﰢ�� ��ǥ
		data[2][0][0][0] = 0.5f, data[2][0][0][1] = -0.5f, data[2][0][0][2] = -0.5f;
		data[2][0][1][0] = 0.0f, data[2][0][1][1] = 0.5f, data[2][0][1][2] = 0.0f;
		data[2][0][2][0] = 0.5f, data[2][0][2][1] = -0.5f, data[2][0][2][2] = 0.5f;

		// ���� �ﰢ�� ����
		data[2][1][0][0] = 0.0f, data[2][1][0][1] = 1.0f, data[2][1][0][2] = 0.0f;
		data[2][1][1][0] = 0.0f, data[2][1][1][1] = 1.0f, data[2][1][1][2] = 0.0f;
		data[2][1][2][0] = 0.0f, data[2][1][2][1] = 1.0f, data[2][1][2][2] = 0.0f;

		// ���� �ﰢ�� ��ǥ
		data[3][0][0][0] = 0.5f, data[3][0][0][1] = -0.5f, data[3][0][0][2] = 0.5f;
		data[3][0][1][0] = 0.0f, data[3][0][1][1] = 0.5f, data[3][0][1][2] = 0.0f;
		data[3][0][2][0] = -0.5f, data[3][0][2][1] = -0.5f, data[3][0][2][2] = 0.5f;

		// ���� �ﰢ�� ����
		data[3][1][0][0] = 0.0f, data[3][1][0][1] = 0.0f, data[3][1][0][2] = 1.0f;
		data[3][1][1][0] = 0.0f, data[3][1][1][1] = 0.0f, data[3][1][1][2] = 1.0f;
		data[3][1][2][0] = 0.0f, data[3][1][2][1] = 0.0f, data[3][1][2][2] = 1.0f;

		// ���� �ﰢ�� ��ǥ
		data[4][0][0][0] = -0.5f, data[4][0][0][1] = -0.5f, data[4][0][0][2] = 0.5f;
		data[4][0][1][0] = 0.0f, data[4][0][1][1] = 0.5f, data[4][0][1][2] = 0.0f;
		data[4][0][2][0] = -0.5f, data[4][0][2][1] = -0.5f, data[4][0][2][2] = -0.5f;

		// ���� �ﰢ�� ����
		data[4][1][0][0] = 0.0f, data[4][1][0][1] = 1.0f, data[4][1][0][2] = 1.0f;
		data[4][1][1][0] = 0.0f, data[4][1][1][1] = 1.0f, data[4][1][1][2] = 1.0f;
		data[4][1][2][0] = 0.0f, data[4][1][2][1] = 1.0f, data[4][1][2][2] = 1.0f;

		// �ĸ� �ﰢ�� ��ǥ
		data[5][0][0][0] = -0.5f, data[5][0][0][1] = -0.5f, data[5][0][0][2] = -0.5f;
		data[5][0][1][0] = 0.0f, data[5][0][1][1] = 0.5f, data[5][0][1][2] = 0.0f;
		data[5][0][2][0] = 0.5f, data[5][0][2][1] = -0.5f, data[5][0][2][2] = -0.5f;

		// �ĸ� �ﰢ�� ����
		data[5][1][0][0] = 1.0f, data[5][1][0][1] = 0.0f, data[5][1][0][2] = 1.0f;
		data[5][1][1][0] = 1.0f, data[5][1][1][1] = 0.0f, data[5][1][1][2] = 1.0f;
		data[5][1][2][0] = 1.0f, data[5][1][2][1] = 0.0f, data[5][1][2][2] = 1.0f;

		drawed_reset();
	}
	void drawed_reset() {
		for (int i = 0; i < 6; i++) {
			drawed[i] = false;
		}
	}
};
Tetrahedron tetra;

int main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("practice 13");

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
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(Keyboard);
	glutMotionFunc(motion);
	glDisable(GL_DEPTH_TEST);
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

	for (int i = 0; i < 2; i++) {
		glBindVertexArray(va.line_vao[i]);
		glDrawArrays(GL_LINES, 0, 2);
	}

	glm::mat4 OBJECT = glm::mat4(1.0f);
	OBJECT = glm::rotate(OBJECT, (float)glm::radians(30.0), glm::vec3(1.0, 0.0, 0.0));
	OBJECT = glm::rotate(OBJECT, (float)glm::radians(-30.0), glm::vec3(0.0, 1.0, 0.0));
	unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(OBJECT)); //--- modelTransform ������ ��ȯ �� �����ϱ�

	for (int i = 0; i < 6; i++) {
		//glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		if (hexa.drawed[i] == true) {
			glBindVertexArray(va.hexahedron_vao[i]);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		if (tetra.drawed[i] == true) {
			glBindVertexArray(va.tetrahedron_vao[i]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		//glDisable(GL_DEPTH_TEST);
		//glDisable(GL_CULL_FACE);
	}
	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	// ������ ���Ͽ�
	switch (inputKey) {
	case '1':
		hexa.drawed_reset();
		tetra.drawed_reset();
		hexa.drawed[0] = true;
		break;
	case '2':
		hexa.drawed_reset();
		tetra.drawed_reset();
		hexa.drawed[1] = true;
		break;
	case '3':
		hexa.drawed_reset();
		tetra.drawed_reset();
		hexa.drawed[2] = true;
		break;
	case '4':
		hexa.drawed_reset();
		tetra.drawed_reset();
		hexa.drawed[3] = true;
		break;
	case '5':
		hexa.drawed_reset();
		tetra.drawed_reset();
		hexa.drawed[4] = true;
		break;
	case '6':
		hexa.drawed_reset();
		tetra.drawed_reset();
		hexa.drawed[5] = true;
		break;
	case '7':
		hexa.drawed_reset();
		tetra.drawed_reset();
		tetra.drawed[2] = true;
		break;
	case '8':
		hexa.drawed_reset();
		tetra.drawed_reset();
		tetra.drawed[3] = true;
		break;
	case '9':
		hexa.drawed_reset();
		tetra.drawed_reset();
		tetra.drawed[4] = true;
		break;
	case '0':
		hexa.drawed_reset();
		tetra.drawed_reset();
		tetra.drawed[5] = true;
		break;
	case 'P':
	case 'p':
		hexa.drawed_reset();
		tetra.drawed_reset();
		tetra.drawed[0] = true;
		tetra.drawed[1] = true;
		break;
	case 'A':
	case 'a':
		hexa.drawed_reset();
		tetra.drawed_reset();
		hexa.drawed[0] = true;
		hexa.drawed[3] = true;
		break;
	case 'B':
	case 'b':
		hexa.drawed_reset();
		tetra.drawed_reset();
		hexa.drawed[2] = true;
		hexa.drawed[5] = true;
		break;
	case 'C':
	case 'c':
		hexa.drawed_reset();
		tetra.drawed_reset();
		hexa.drawed[1] = true;
		hexa.drawed[4] = true;
		break;
	case 'D':
	case 'd':
		hexa.drawed_reset();
		tetra.drawed_reset();
		tetra.drawed[0] = true;
		tetra.drawed[1] = true;
		tetra.drawed[2] = true;
		break;
	case 'E':
	case 'e':
		hexa.drawed_reset();
		tetra.drawed_reset();
		tetra.drawed[0] = true;
		tetra.drawed[1] = true;
		tetra.drawed[3] = true;
		break;
	case 'F':
	case 'f':
		hexa.drawed_reset();
		tetra.drawed_reset();
		tetra.drawed[0] = true;
		tetra.drawed[1] = true;
		tetra.drawed[4] = true;
		break;
	case 'G':
	case 'g':
		hexa.drawed_reset();
		tetra.drawed_reset();
		tetra.drawed[0] = true;
		tetra.drawed[1] = true;
		tetra.drawed[5] = true;
		break;
	case 'Q':
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

GLvoid motion(int x, int y)
{
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

void initBuffer()
{
	glGenVertexArrays(2, va.line_vao);
	for (int i = 0; i < 2; i++) {
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

	glGenVertexArrays(6, va.tetrahedron_vao);
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(va.tetrahedron_vao[i]);
		glGenBuffers(2, va.tetrahedron_vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, va.tetrahedron_vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), tetra.data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}
}

