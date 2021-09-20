#pragma once
#include "shader.h"
#include "stdafx.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 10);

void initShader();
GLuint make_shaderProgram();
GLvoid drawScene();
GLvoid mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char inputKey, int x, int y);
GLvoid Reshape(int w, int h);

void sizeset();

GLchar* vertexSource, *fragmentSource; //--- �ҽ��ڵ� ���� ����
GLuint vertexShader, fragmentShader; //--- ���̴� ��ü

struct Triangle {
	GLfloat data[2][3][3];		// 0�� : ��ġ, 1�� : ����
	GLuint vao, vbo[2];
	Triangle* next;
	GLfloat size = 0.0;

	Triangle(GLfloat mx, GLfloat my, GLfloat size) {
		this->size = size;
		data[0][0][0] = mx - (GLfloat)0.1 - size,	data[0][0][1] = my - (GLfloat)0.1 - size,	data[0][0][2] = 0.0,
		data[0][1][0] = mx + (GLfloat)0.1 + size,	data[0][1][1] = my - (GLfloat)0.1 - size,	data[0][1][2] = 0.0,
		data[0][2][0] = mx,							data[0][2][1] = my + (GLfloat)0.1 + size,	data[0][2][2] = 0.0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				data[1][i][j] = (GLclampf)dis(gen) / (GLclampf)10.0;
			}
		}

		glGenVertexArrays(1, &vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
		glBindVertexArray(vao);

		glGenBuffers(2, vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�

		vertexArraySet();
	}
	void vertexArraySet()
	{
		for (int i = 0; i < 2; i++) {
			//--- i��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
			glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
			//--- ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
			//--- triShape �迭�� ������: 9 * float
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), data[i], GL_STATIC_DRAW);
			//--- ��ǥ���� attribute �ε��� i���� ����Ѵ�: ���ؽ� �� 3* float
			glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
			//--- attribute �ε��� i���� ��밡���ϰ� ��
			glEnableVertexAttribArray(i);
			//std::cout << "set vbo\n";
		}
	}
	Triangle* getNextAddress() { return next; }
	GLvoid putNextAddress(Triangle* nextTriangle) { this->next = nextTriangle; }
};

struct Triangle_Manager {
	Triangle* head;
	Triangle* now;
	int data_num;
	bool drawtype;

	Triangle_Manager() { data_num = 0, drawtype = false; }
	void add_triangle(Triangle* triangle) {
		if (data_num == 0) {
			triangle->putNextAddress(triangle);
			head = triangle;
			now = triangle;
			triangle->putNextAddress(triangle);
			data_num++;
		}
		else if (data_num == 4) {
			triangle->putNextAddress(head->getNextAddress());
			now->putNextAddress(triangle);
			now = triangle;
			delete head;
			head = now->getNextAddress();
		}
		else {
			triangle->putNextAddress(head);
			now->putNextAddress(triangle);
			now = triangle;
			triangle->putNextAddress(head);
			data_num++;
		}
		sizeset();
	}
};

Triangle_Manager tm;
GLclampf xPos = 0, yPos = 0;
GLfloat size = 0.0;
bool settype = false;

int main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("practice 5");

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

	tm.add_triangle(new Triangle(-0.5, 0.5, size));
	tm.add_triangle(new Triangle(0.5, 0.5, size));
	tm.add_triangle(new Triangle(-0.5, -0.5, size));
	tm.add_triangle(new Triangle(0.5, -0.5, size));

	glutDisplayFunc(drawScene);
	glutMouseFunc(mouse);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLuint s_program;
void initShader()
{
	make_vertexShaders(); //--- ���ؽ� ���̴� �����
	make_fragmentShaders(); //--- �����׸�Ʈ ���̴� �����

	//-- shader Program
	s_program = glCreateProgram();
	glAttachShader(s_program, vertexShader);
	glAttachShader(s_program, fragmentShader);
	glLinkProgram(s_program);

	//checkCompileErrors(s_program, "PROGRAM");

	//--- ���̴� �����ϱ�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//--- Shader Program ����ϱ�
	glUseProgram(s_program);
}

GLuint make_shaderProgram()
{
	GLuint ShaderProgramID;
	ShaderProgramID = glCreateProgram(); //--- ���̴� ���α׷� �����

	glAttachShader(ShaderProgramID, vertexShader); //--- ���̴� ���α׷��� ���ؽ� ���̴� ���̱�
	glAttachShader(ShaderProgramID, fragmentShader); //--- ���̴� ���α׷��� �����׸�Ʈ ���̴� ���̱�

	glLinkProgram(ShaderProgramID); //--- ���̴� ���α׷� ��ũ�ϱ�

	glDeleteShader(vertexShader); //--- ���̴� ��ü�� ���̴� ���α׷��� ��ũ��������, ���̴� ��ü ��ü�� ���� ����
	glDeleteShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result); // ---���̴��� �� ����Ǿ����� üũ�ϱ�
	if (!result) {
		glGetProgramInfoLog(ShaderProgramID, 512, NULL, errorLog);
		std::cerr << "ERROR: shader program ���� ����\n" << errorLog << std::endl;
		return false;
	}
	glUseProgram(ShaderProgramID); //--- ������� ���̴� ���α׷� ����ϱ�
	//--- ���� ���� ���̴����α׷� ���� �� �ְ�, �� �� �Ѱ��� ���α׷��� ����Ϸ���
	//--- glUseProgram �Լ��� ȣ���Ͽ� ��� �� Ư�� ���α׷��� �����Ѵ�.
	//--- ����ϱ� ������ ȣ���� �� �ִ�.
	return ShaderProgramID;
}

GLvoid drawScene()
{
	//--- ����� ���� ����
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- ������ ���������ο� ���̴� �ҷ�����
	glUseProgram(s_program);
	for (int i = 0; i < tm.data_num; i++) {
		tm.now = tm.now->next;
		//--- ����� VAO �ҷ�����
		glBindVertexArray(tm.now->vao);
		//--- �ﰢ�� �׸���
		if (tm.drawtype == false) {
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		else {
			glDrawArrays(GL_LINE_LOOP, 0, 3);
		}
	}
	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid mouse(int button, int state, int x, int y) {

	y = -(y - glutGet(GLUT_WINDOW_HEIGHT));
	xPos = (((GLclampf)x - ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0));
	yPos = (((GLclampf)y - ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0));
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		tm.add_triangle(new Triangle(xPos, yPos, size));
	}
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'A':
	case 'a':
		tm.drawtype = false;
		break;
	case 'B':
	case 'b':
		tm.drawtype = true;
		break;
	case 'Q':
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

void sizeset() {
	if (settype == false) {
		if (size >= 0.1) {
			size -= (GLfloat)0.01;
			settype = true;
		}
		else {
			size += (GLfloat)0.01;
		}
	}
	else {
		if (size <= 0.0) {
			size += (GLfloat)0.01;
			settype = false;
		}
		else {
			size -= (GLfloat)0.01;
		}
	}
}