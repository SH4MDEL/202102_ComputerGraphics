#include <iostream>
#include <random>
#include <gl/glew.h>								//--- 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 10);

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char inputKey, int x, int y);
GLvoid TimerFunction(int value);

class BackgroundManage {
	GLclampf Rtype, Gtype, Btype;
	bool timer;
public:
	BackgroundManage(GLclampf Rtype, GLclampf Gtype, GLclampf Btype) :
		Rtype(Rtype), Gtype(Gtype), Btype(Btype), timer(false) {}
	GLclampf getR() { return Rtype; }
	GLclampf getG() { return Gtype; }
	GLclampf getB() { return Btype; }
	GLvoid setR() { Rtype = 1.0, Gtype = 0.0, Btype = 0.0; }
	GLvoid setG() { Rtype = 0.0, Gtype = 1.0, Btype = 0.0; }
	GLvoid setB() { Rtype = 0.0, Gtype = 0.0, Btype = 1.0; }
	GLvoid setW() { Rtype = 1.0, Gtype = 1.0, Btype = 1.0; }
	GLvoid setK() { Rtype = 0.0, Gtype = 0.0, Btype = 0.0; }
	bool getTimer() { return timer; }
	GLvoid timerOn() { timer = true; }
	GLvoid timerOff() { timer = false; }

	GLvoid randomColor() {
		Rtype = (GLclampf)dis(gen) / (GLclampf)10.0;
		Gtype = (GLclampf)dis(gen) / (GLclampf)10.0;
		Btype = (GLclampf)dis(gen) / (GLclampf)10.0;
	}
	~BackgroundManage() {};
};

BackgroundManage bgm(0.0f, 0.0f, 0.0f);

GLvoid myGlutInitiate(int argc, char** argv)
{
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(0, 0);					// 윈도우의 위치 지정
	glutInitWindowSize(800, 600);					// 윈도우의 크기 지정
	glutCreateWindow("Practice 1");					// 윈도우 생성(윈도우 이름)
}

GLvoid drawScene() {								//--- 콜백 함수: 그리기 콜백 함수 
	glClearColor(bgm.getR(), bgm.getG(), bgm.getB(), 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);					// 설정된 색으로 전체를 칠하기

	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다.
	glutSwapBuffers();								// 화면에 출력하기
}

GLvoid Reshape(int w, int h) {						//--- 콜백 함수: 다시 그리기 콜백 함수
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'R':
	case 'r':
		bgm.setR();
		break;
	case 'G':
	case 'g':
		bgm.setG();
		break;
	case 'B':
	case 'b':
		bgm.setB();
		break;
	case 'A':
	case 'a':
		bgm.randomColor();
		break;
	case 'W':
	case 'w':
		bgm.setW();
		break;
	case 'K':
	case 'k':
		bgm.setK();
		break;
	case 'T':
	case 't':
		bgm.timerOn();
		break;
	case 'S':
	case 's':
		bgm.timerOff();
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
	if (bgm.getTimer() == true) {
		bgm.randomColor();
		glutPostRedisplay();
		glutTimerFunc(200, TimerFunction, value);
	}
	else {
		glutPostRedisplay();
		glutTimerFunc(200, TimerFunction, value);
	}
	return;
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
	glutReshapeFunc(Reshape);						// 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(200, TimerFunction, 1);
	glutMainLoop();									// 이벤트 처리 시작 
}