#include <iostream>
#include <random>
#include <gl/glew.h>								//--- 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#define WINDOWSWIDTH 1000
#define WINDOWSHEIGHT 1000

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 10);

GLvoid drawScene();
GLvoid Reshape(int w, int h);

class Object {
protected:
	GLclampf Rtype, Gtype, Btype;
public:
	Object() {};
	GLclampf getR() { return Rtype; }
	GLclampf getG() { return Gtype; }
	GLclampf getB() { return Btype; }
	GLvoid randomColor() {
		Rtype = (GLclampf)dis(gen) / (GLclampf)10.0;
		Gtype = (GLclampf)dis(gen) / (GLclampf)10.0;
		Btype = (GLclampf)dis(gen) / (GLclampf)10.0;
	}
	~Object() {};
};

class BackgroundManage : public Object {
public:
	BackgroundManage(GLclampf Rtype, GLclampf Gtype, GLclampf Btype) {
		this->Rtype = Rtype;
		this->Gtype = Gtype;
		this->Btype = Btype;
	}
	~BackgroundManage() {};
};

class Square : public Object {
	GLclampf x, y, size;
public:
	Square(GLclampf Rtype, GLclampf Gtype, GLclampf Btype, GLclampf x, GLclampf y) : x(x), y(y) {
		this->Rtype = Rtype;
		this->Gtype = Gtype;
		this->Btype = Btype;
		size = (GLclampf)0.5;
	}
	GLclampf getX() { return x; }
	GLclampf getY() { return y; }
	GLclampf getSize() { return size; }
	~Square() {};
};

BackgroundManage bgm(0.0f, 0.0f, 0.0f);
Square square(1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
GLclampf xPos = 0, yPos = 0;

GLvoid myGlutInitiate(int argc, char** argv)
{
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(0, 0);					// 윈도우의 위치 지정
	glutInitWindowSize(WINDOWSHEIGHT, WINDOWSWIDTH);	// 윈도우의 크기 지정
	glutCreateWindow("Practice 2");					// 윈도우 생성(윈도우 이름)
}

GLvoid drawScene() {								//--- 콜백 함수: 그리기 콜백 함수 
	glClearColor(bgm.getR(), bgm.getG(), bgm.getB(), 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);					// 설정된 색으로 전체를 칠하기

	glColor3f(square.getR(), square.getG(), square.getB());
	glRectf(square.getX() - square.getSize(), square.getY() - square.getSize(), 
		square.getX() + square.getSize(), square.getY() + square.getSize());

	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다.
	glutSwapBuffers();								// 화면에 출력하기
}

GLvoid mouse(int button, int state, int x, int y) {
	y = -(y - glutGet(GLUT_WINDOW_HEIGHT));
	xPos = (((GLclampf)x - ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0));
	yPos = (((GLclampf)y - ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0));
	if (button == GLUT_LEFT_BUTTON) {
		if (square.getX() - square.getSize() < xPos && square.getX() + square.getSize() > xPos &&
			square.getY() - square.getSize() < yPos && square.getY() + square.getSize() > yPos) {
			square.randomColor();
		}
		else {
			bgm.randomColor();
		}
	}
	if (button == GLUT_RIGHT_BUTTON) {
		glutLeaveMainLoop();
	}
}

GLvoid Reshape(int w, int h) {						//--- 콜백 함수: 다시 그리기 콜백 함수

	glViewport(0, 0, w, h);
}

int main(int argc, char** argv)					//--- 윈도우 출력하고 콜백함수 설정 
{
	//--- 윈도우 생성하기
	myGlutInitiate(argc, argv);

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {					// glew 초기화
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initialized\n";
	}
	glutDisplayFunc(drawScene);						// 출력 함수의 지정
	glutMouseFunc(mouse);
	glutReshapeFunc(Reshape);						// 다시 그리기 함수 지정
	glutMainLoop();									// 이벤트 처리 시작 
}