#pragma once
#include "shader.h"
#include "stdafx.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 10);
std::uniform_int_distribution<int> boool(0, 1);

void initShader();
GLuint make_shaderProgram();
GLvoid drawScene();
GLvoid mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char inputKey, int x, int y);
GLvoid TimerFunction(int value);
GLvoid Reshape(int w, int h);

void sizeset();

GLchar* vertexSource, * fragmentSource; //--- �ҽ��ڵ� ���� ����
GLuint vertexShader, fragmentShader; //--- ���̴� ��ü

struct _Rectangle {
	GLfloat x, y;
	GLfloat data[2][6][3];		// 0�� : ��ġ, 1�� : ����

	GLuint vao, vbo[2];

	_Rectangle() : _Rectangle(0.0, 0.0) {}

	_Rectangle(GLfloat mx, GLfloat my) : x(mx), y(my) {
		data[0][0][0] = x - (GLfloat)0.3, data[0][0][1] = y - (GLfloat)0.25, data[0][0][2] = 0.0;
		data[0][1][0] = x + (GLfloat)0.3, data[0][1][1] = y - (GLfloat)0.25, data[0][1][2] = 0.0;
		data[0][2][0] = x - (GLfloat)0.3, data[0][2][1] = y + (GLfloat)0.25, data[0][2][2] = 0.0;

		data[0][3][0] = x - (GLfloat)0.3, data[0][3][1] = y + (GLfloat)0.25, data[0][3][2] = 0.0;
		data[0][4][0] = x + (GLfloat)0.3, data[0][4][1] = y - (GLfloat)0.25, data[0][4][2] = 0.0;
		data[0][5][0] = x + (GLfloat)0.3, data[0][5][1] = y + (GLfloat)0.25, data[0][5][2] = 0.0;

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 3; j++) {
				data[1][i][j] = (GLclampf)dis(gen) / (GLclampf)10.0;
			}
		}
		data[1][2][0] = data[1][3][0], data[1][2][1] = data[1][3][1], data[1][2][2] = data[1][3][2];
		data[1][1][0] = data[1][4][0], data[1][1][1] = data[1][4][1], data[1][1][2] = data[1][4][2];

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
			glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), data[i], GL_STATIC_DRAW);
			//--- ��ǥ���� attribute �ε��� i���� ����Ѵ�: ���ؽ� �� 3* float
			glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
			//--- attribute �ε��� i���� ��밡���ϰ� ��
			glEnableVertexAttribArray(i);
			//std::cout << "set vbo\n";
		}
	}
	bool isin(GLfloat x, GLfloat y) {
		if (this->x - (GLfloat)0.3 <= x && this->x + (GLfloat)0.3 >= x &&
			this->y - (GLfloat)0.25 <= y && this->y + (GLfloat)0.25 >= y) {
			return true;
		}
		return false;
	}
};
struct Rectangle_Manager {
	_Rectangle* rect;

	Rectangle_Manager() {}
	void add_rectangle(_Rectangle* rectangle) {
		delete rect;
		rect = rectangle;
	}
};
Rectangle_Manager rm;

struct Triangle {
	GLfloat x, y;
	GLfloat data[2][3][3];		// 0�� : ��ġ, 1�� : ����

	GLuint vao, vbo[2];

	Triangle(GLfloat mx, GLfloat my) : x(mx), y(my) {
		data[0][0][0] = x - (GLfloat)0.1, data[0][0][1] = y - (GLfloat)0.1, data[0][0][2] = 0.0,
		data[0][1][0] = x + (GLfloat)0.1, data[0][1][1] = y - (GLfloat)0.1, data[0][1][2] = 0.0,
		data[0][2][0] = x,				  data[0][2][1] = y + (GLfloat)0.15, data[0][2][2] = 0.0;
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
		}
	}
	void colorSet() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				data[1][i][j] = (GLclampf)dis(gen) / (GLclampf)10.0;
			}
		}
		vertexArraySet();
	}
	virtual void moveit() = 0;
};

struct Outer : public Triangle {
	Outer* next;
	GLfloat size = 0.0;
	bool lookup, lookright;
	GLint status = 0;

	Outer(GLfloat mx, GLfloat my, GLfloat size) : Triangle(mx, my), size(size) {
		lookup = boool(gen);
		lookright = boool(gen);
		if (lookup == true) {
			status = 0;
		}
		else {
			status = 1;
		}
	}
	void moveit() override {
		if (lookright == true) {
			if (x >= 1) {
				x -= (GLclampf)0.01;
				lookright = false;
				status = 2;
				colorSet();
			}
			else if (x + 0.1 + size >= -0.3 && x + 0.1 + size <= 0.3 && y >= -0.25 && y <= 0.25) {
				x -= (GLclampf)0.01;
				lookright = false;
				status = 2;
				colorSet();
			}
			else {
				x += (GLclampf)0.01;
			}
		}
		else {
			if (x <= -1) {
				x += (GLclampf)0.01;
				lookright = true;
				status = 3;
				colorSet();
			}
			else if (x - 0.1 - size >= -0.3 && x - 0.1 - size <= 0.3 && y >= -0.25 && y <= 0.25) {
				x -= (GLclampf)0.01;
				lookright = true;
				status = 3;
				colorSet();
			}
			else {
				x -= (GLclampf)0.01;
			}
		}
		if (lookup == true) {
			if (y >= 1) {
				y -= (GLclampf)0.01;
				lookup = false;
				status = 1;
				colorSet();
			}
			else if (y + 0.1 + size >= -0.25 && y + 0.1 + size <= 0.25 && x >= -0.3 && x <= 0.3) {
				x -= (GLclampf)0.01;
				lookup = false;
				status = 1;
				colorSet();
			}
			else {
				y += (GLclampf)0.01;
			}
		}
		else {
			if (y <= -1) {
				y += (GLclampf)0.01;
				lookup = true;
				status = 0;
				colorSet();
			}
			else if (y - 0.1 - size >= -0.25 && y - 0.1 - size <= 0.25 && x >= -0.3 && x <= 0.3) {
				x -= (GLclampf)0.01;
				lookup = true;
				status = 0;
				colorSet();
			}
			else {
				y -= (GLclampf)0.01;
			}
		}
		if (status == 0) {
			putCoordinatesLookUp(x, y);
		}
		else if (status == 1) {
			putCoordinatesLookDown(x, y);
		}
		else if (status == 2) {
			putCoordinatesLookLeft(x, y);
		}
		else {
			putCoordinatesLookRight(x, y);
		}
	}
	void putCoordinatesLookUp(GLfloat x, GLfloat y) {
		data[0][0][0] = x - (GLfloat)0.1 - size, data[0][0][1] = y - (GLfloat)0.1 - size, data[0][0][2] = 0.0,
		data[0][1][0] = x + (GLfloat)0.1 + size, data[0][1][1] = y - (GLfloat)0.1 - size, data[0][1][2] = 0.0,
		data[0][2][0] = x,						 data[0][2][1] = y + (GLfloat)0.15 + size, data[0][2][2] = 0.0;
		vertexArraySet();
	}
	void putCoordinatesLookDown(GLfloat x, GLfloat y) {
		data[0][0][0] = x - (GLfloat)0.1 - size, data[0][0][1] = y + (GLfloat)0.1 + size, data[0][0][2] = 0.0,
		data[0][1][0] = x + (GLfloat)0.1 + size, data[0][1][1] = y + (GLfloat)0.1 + size, data[0][1][2] = 0.0,
		data[0][2][0] = x,						 data[0][2][1] = y - (GLfloat)0.15 - size, data[0][2][2] = 0.0;
		vertexArraySet();
	}
	void putCoordinatesLookLeft(GLfloat x, GLfloat y) {
		data[0][0][0] = x + (GLfloat)0.1 + size, data[0][0][1] = y - (GLfloat)0.1 - size, data[0][0][2] = 0.0,
		data[0][1][0] = x + (GLfloat)0.1 + size, data[0][1][1] = y + (GLfloat)0.1 + size, data[0][1][2] = 0.0,
		data[0][2][0] = x - (GLfloat)0.15 - size, data[0][2][1] = y,					  data[0][2][2] = 0.0;
		vertexArraySet();
	}
	void putCoordinatesLookRight(GLfloat x, GLfloat y) {
		data[0][0][0] = x - (GLfloat)0.1 - size, data[0][0][1] = y - (GLfloat)0.1 - size, data[0][0][2] = 0.0,
		data[0][1][0] = x - (GLfloat)0.1 - size, data[0][1][1] = y + (GLfloat)0.1 + size, data[0][1][2] = 0.0,
		data[0][2][0] = x + (GLfloat)0.15 + size, data[0][2][1] = y,					  data[0][2][2] = 0.0;
		vertexArraySet();
	}
	Outer* getNextAddress() { return next; }
	GLvoid putNextAddress(Outer* nextTriangle) { this->next = nextTriangle; }
};

struct Inner : public Triangle {
	Inner* next;

	bool lookright;
	GLint status;

	Inner(GLfloat mx, GLfloat my, GLint status) : Triangle(mx, my), status(status) {
		if (status == 0) {
			lookright = false;
		}
		else {
			lookright = true;
		}
	}
	Inner(GLfloat mx, GLfloat my, GLint status, bool lookright) : Triangle(mx, my), status(status), lookright(lookright) {};
	void moveit() override {
		if (lookright == true) {
			if (x <= 0.2) {
				x += (GLclampf)0.01;
			}
			else {
				x -= (GLclampf)0.01;
				lookright = false;
				colorSet();
			}
		}
		else {
			if (x - (GLclampf)0.01 >= -0.2) {
				x -= (GLclampf)0.01;
			}
			else {
				x += (GLclampf)0.01;
				lookright = true;
				colorSet();
			}
		}
		if (status == 0) {
			putCoordinatesLookUp(x, y);
		}
		else if (status == 1) {
			putCoordinatesLookDown(x, y);
		}
	}
	void putCoordinatesLookUp(GLfloat x, GLfloat y) {
		data[0][0][0] = x - (GLfloat)0.1, data[0][0][1] = y - (GLfloat)0.1, data[0][0][2] = 0.0,
			data[0][1][0] = x + (GLfloat)0.1, data[0][1][1] = y - (GLfloat)0.1, data[0][1][2] = 0.0,
			data[0][2][0] = x, data[0][2][1] = y + (GLfloat)0.15, data[0][2][2] = 0.0;
		vertexArraySet();
	}
	void putCoordinatesLookDown(GLfloat x, GLfloat y) {
		data[0][0][0] = x - (GLfloat)0.1, data[0][0][1] = y + (GLfloat)0.1, data[0][0][2] = 0.0,
			data[0][1][0] = x + (GLfloat)0.1, data[0][1][1] = y + (GLfloat)0.1, data[0][1][2] = 0.0,
			data[0][2][0] = x, data[0][2][1] = y - (GLfloat)0.15, data[0][2][2] = 0.0;
		vertexArraySet();
	}
	Inner* getNextAddress() { return next; }
	GLvoid putNextAddress(Inner* nextTriangle) { this->next = nextTriangle; }
	GLfloat getX() { return x; }
	GLfloat getY() { return y; }
	GLint getStat() { return status; }
	bool getlook() { return lookright; }
};

struct Outer_Manager {
	Outer* head;
	Outer* now;
	int data_num;
	bool drawtype;

	Outer_Manager() { data_num = 0, drawtype = false; }
	void add_triangle(Outer* triangle) {
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

struct Inner_Manager {
	Inner* head;
	Inner* now;
	int data_num;

	Inner_Manager() { data_num = 0; }
	void add_triangle(Inner* triangle) {
		if (data_num == 0) {
			triangle->putNextAddress(triangle);
			head = triangle;
			now = triangle;
			triangle->putNextAddress(triangle);
			data_num++;
		}
		else if (data_num == 2) {
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
	}
};

Outer_Manager om;
Inner_Manager im;
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
	glutCreateWindow("practice 7");

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

	rm.add_rectangle(new _Rectangle());

	im.add_triangle(new Inner((GLfloat)0.15, (GLfloat)0.15, 1));
	im.add_triangle(new Inner((GLfloat)-0.15, (GLfloat)-0.15, 0));

	om.add_triangle(new Outer((GLfloat)-0.7, (GLfloat)0.5, size));
	om.add_triangle(new Outer((GLfloat)0.7, (GLfloat)0.5, size));
	om.add_triangle(new Outer((GLfloat)-0.7, (GLfloat)-0.5, size));
	om.add_triangle(new Outer((GLfloat)0.7, (GLfloat)-0.5, size));

	glutDisplayFunc(drawScene);
	glutMouseFunc(mouse);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, TimerFunction, 1);
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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- ������ ���������ο� ���̴� �ҷ�����
	glUseProgram(s_program);

	glBindVertexArray(rm.rect->vao);
	//--- �ﰢ�� �׸���
	glDrawArrays(GL_TRIANGLES, 0, 6);

	for (int i = 0; i < om.data_num; i++) {
		om.now = om.now->next;
		//--- ����� VAO �ҷ�����
		glBindVertexArray(om.now->vao);
		//--- �ﰢ�� �׸���
		if (om.drawtype == false) {
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		else {
			glDrawArrays(GL_LINE_LOOP, 0, 3);
		}
	}
	for (int i = 0; i < im.data_num; i++) {
		im.now = im.now->next;
		//--- ����� VAO �ҷ�����
		glBindVertexArray(im.now->vao);
		//--- �ﰢ�� �׸���
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid mouse(int button, int state, int x, int y) {

	y = -(y - glutGet(GLUT_WINDOW_HEIGHT));
	xPos = (((GLclampf)x - ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0));
	yPos = (((GLclampf)y - ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0));
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !rm.rect->isin(xPos, yPos)) {
		om.add_triangle(new Outer(xPos, yPos, size));
		im.add_triangle(new Inner(im.now->next->getX(), im.now->next->getY(), im.now->next->getStat(), im.now->next->getlook()));
		im.add_triangle(new Inner(im.now->next->getX(), im.now->next->getY(), im.now->next->getStat(), im.now->next->getlook()));
	}
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'A':
	case 'a':
		om.drawtype = false;
		break;
	case 'B':
	case 'b':
		om.drawtype = true;
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
	for (int i = 0; i < om.data_num; i++) {
		om.now = om.now->next;
		om.now->moveit();
	}
	for (int i = 0; i < im.data_num; i++) {
		im.now = im.now->next;
		im.now->moveit();
	}
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, value);
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