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

GLchar* vertexSource, *fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체

struct Triangle {
	GLfloat data[2][3][3];		// 0번 : 위치, 1번 : 색상
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

		glGenVertexArrays(1, &vao); //--- VAO 를 지정하고 할당하기
		glBindVertexArray(vao);

		glGenBuffers(2, vbo); //--- 2개의 VBO를 지정하고 할당하기

		vertexArraySet();
	}
	void vertexArraySet()
	{
		for (int i = 0; i < 2; i++) {
			//--- i번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
			glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
			//--- 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
			//--- triShape 배열의 사이즈: 9 * float
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), data[i], GL_STATIC_DRAW);
			//--- 좌표값을 attribute 인덱스 i번에 명시한다: 버텍스 당 3* float
			glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
			//--- attribute 인덱스 i번을 사용가능하게 함
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

int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("practice 5");

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {					// glew 초기화
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
	make_vertexShaders(); //--- 버텍스 세이더 만들기
	make_fragmentShaders(); //--- 프래그먼트 세이더 만들기

	//-- shader Program
	s_program = glCreateProgram();
	glAttachShader(s_program, vertexShader);
	glAttachShader(s_program, fragmentShader);
	glLinkProgram(s_program);

	//checkCompileErrors(s_program, "PROGRAM");

	//--- 세이더 삭제하기
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//--- Shader Program 사용하기
	glUseProgram(s_program);
}

GLuint make_shaderProgram()
{
	GLuint ShaderProgramID;
	ShaderProgramID = glCreateProgram(); //--- 세이더 프로그램 만들기

	glAttachShader(ShaderProgramID, vertexShader); //--- 세이더 프로그램에 버텍스 세이더 붙이기
	glAttachShader(ShaderProgramID, fragmentShader); //--- 세이더 프로그램에 프래그먼트 세이더 붙이기

	glLinkProgram(ShaderProgramID); //--- 세이더 프로그램 링크하기

	glDeleteShader(vertexShader); //--- 세이더 객체를 세이더 프로그램에 링크했음으로, 세이더 객체 자체는 삭제 가능
	glDeleteShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &result); // ---세이더가 잘 연결되었는지 체크하기
	if (!result) {
		glGetProgramInfoLog(ShaderProgramID, 512, NULL, errorLog);
		std::cerr << "ERROR: shader program 연결 실패\n" << errorLog << std::endl;
		return false;
	}
	glUseProgram(ShaderProgramID); //--- 만들어진 세이더 프로그램 사용하기
	//--- 여러 개의 세이더프로그램 만들 수 있고, 그 중 한개의 프로그램을 사용하려면
	//--- glUseProgram 함수를 호출하여 사용 할 특정 프로그램을 지정한다.
	//--- 사용하기 직전에 호출할 수 있다.
	return ShaderProgramID;
}

GLvoid drawScene()
{
	//--- 변경된 배경색 설정
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(s_program);
	for (int i = 0; i < tm.data_num; i++) {
		tm.now = tm.now->next;
		//--- 사용할 VAO 불러오기
		glBindVertexArray(tm.now->vao);
		//--- 삼각형 그리기
		if (tm.drawtype == false) {
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		else {
			glDrawArrays(GL_LINE_LOOP, 0, 3);
		}
	}
	glutSwapBuffers(); //--- 화면에 출력하기
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

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
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