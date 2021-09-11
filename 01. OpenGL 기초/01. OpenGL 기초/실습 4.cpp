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
std::uniform_int_distribution<int> boool(0, 1);

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

struct Square : public Object {
	GLclampf originx, originy, x, y;
	GLclampf wsize, hsize;
	Square* next;
	bool rightOn, upOn;
	bool wsizeOn, hsizeOn;

	Square(GLclampf x, GLclampf y) : originx(x), originy(y), x(x), y(y) {
		Rtype = (GLclampf)dis(gen) / (GLclampf)10.0;
		Gtype = (GLclampf)dis(gen) / (GLclampf)10.0;
		Btype = (GLclampf)dis(gen) / (GLclampf)10.0;
		wsize = (GLclampf)0.1;
		hsize = (GLclampf)0.1;
		rightOn = boool(gen);
		upOn = boool(gen);
		wsizeOn = boool(gen);
		hsizeOn = boool(gen);
	}
	GLclampf getX() { return x; }
	GLclampf getY() { return y; }
	GLvoid putX(GLclampf x) { this->x = x; }
	GLvoid putY(GLclampf y) { this->y = y; }

	GLclampf getHSize() { return hsize; }
	GLvoid putHsize(GLclampf size) { this->hsize = size; }
	GLclampf getWSize() { return wsize; }
	GLvoid putWsize(GLclampf size) { this->wsize = size; }

	Square* getNextAddress() { return next; }
	GLvoid putNextAddress(Square* nextSquare) { this->next = nextSquare; }

	~Square() {};
};

struct Square_Manager {
	Square* head;
	Square* now;
	int num;
	bool timer;
	bool size;

	Square_Manager() { num = 0, timer = false, size = false; }
	void add_square(Square* square) {
		if (num == 0) {
			square->putNextAddress(square);
			head = square;
			now = square;
			square->putNextAddress(square);
			num++;
		}
		else if (num == 5) {
			square->putNextAddress(head->getNextAddress());
			now->putNextAddress(square);
			now = square;
			delete head;
			head = now->getNextAddress();
		}
		else {
			square->putNextAddress(head);
			now->putNextAddress(square);
			now = square;
			square->putNextAddress(head);
			num++;
		}
	}
	void all_delete() {
		for (int i = 0; i < num; i++) {
			head = now->next->next;
			delete now->next;
			now->next = head;
		}
		num = 0;
		timer = false;
		size = false;
	}
	void reset() {
		for (int i = 0; i < num; i++) {
			now = now->next;
			now->putX(now->originx);
			now->putY(now->originy);
		}
	}
	void sizeset() {
		for (int i = 0; i < num; i++) {
			if (now->wsizeOn == true && now->hsizeOn == true) {
				if (now->wsize >= (GLclampf)0.5) {
					now->hsizeOn = false;
				}
				else {
					now->wsize += (GLclampf)0.005;
				}
			}
			else if (now->wsizeOn == true && now->hsizeOn == false) {
				if (now->wsize <= (GLclampf)0.1) {
					now->wsizeOn = false;
					now->hsizeOn = true;
				}
				else {
					now->wsize -= (GLclampf)0.005;
				}
			}
			else if (now->wsizeOn == false && now->hsizeOn == true) {
				if (now->hsize >= (GLclampf)0.5) {
					now->hsizeOn = false;
				}
				else {
					now->hsize += (GLclampf)0.005;
				}
			}
			else if (now->wsizeOn == false && now->hsizeOn == false) {
				if (now->hsize <= (GLclampf)0.1) {
					now->wsizeOn = true;
					now->hsizeOn = true;
				}
				else {
					now->hsize -= (GLclampf)0.005;
				}
			}
		}
	}
};

BackgroundManage bgm(0.1f, 0.1f, 0.1f);
Square_Manager sm;
GLclampf xPos = 0, yPos = 0;

GLvoid myGlutInitiate(int argc, char** argv)
{
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(0, 0);					// 윈도우의 위치 지정
	glutInitWindowSize(WINDOWSHEIGHT, WINDOWSWIDTH);	// 윈도우의 크기 지정
	glutCreateWindow("Practice 3");					// 윈도우 생성(윈도우 이름)
}

GLvoid drawScene() {								//--- 콜백 함수: 그리기 콜백 함수 
	glClearColor(bgm.getR(), bgm.getG(), bgm.getB(), 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);					// 설정된 색으로 전체를 칠하기

	for (int i = 0; i < sm.num; i++) {
		sm.now = sm.now->next;
		glColor3f(sm.now->getR(), sm.now->getG(), sm.now->getB());
		glRectf(sm.now->getX() - sm.now->getWSize(), sm.now->getY() - sm.now->getHSize(),
			sm.now->getX() + sm.now->getWSize(), sm.now->getY() + sm.now->getHSize());
	}

	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다.
	glutSwapBuffers();								// 화면에 출력하기
}

GLvoid mouse(int button, int state, int x, int y) {
	y = -(y - glutGet(GLUT_WINDOW_HEIGHT));
	xPos = (((GLclampf)x - ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_WIDTH) / (GLclampf)2.0));
	yPos = (((GLclampf)y - ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0)) / ((GLclampf)glutGet(GLUT_WINDOW_HEIGHT) / (GLclampf)2.0));
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		sm.add_square(new Square(xPos, yPos));
	}
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'A':
	case 'a':
		sm.timer = true;
		break;
	case 'C':
	case 'c':
		if (sm.size == true) {
			sm.size = false;
		}
		else {
			sm.size = true;
		}
		break;
	case 'S':
	case 's':
		sm.timer = false;
		break;
	case 'M':
	case 'm':
		sm.reset();
		break;
	case 'R':
	case 'r':
		sm.all_delete();
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
	if (sm.timer == true) {
		for (int i = 0; i < sm.num; i++) {
			sm.now = sm.now->next;
			if (sm.now->rightOn == true) {
				if (sm.now->getX() + (GLclampf)0.01 <= 1) {
					sm.now->x += (GLclampf)0.01;
				}
				else {
					sm.now->x -= (GLclampf)0.01;
					sm.now->rightOn = false;
				}
			}
			else {
				if (sm.now->getX() - (GLclampf)0.01 >= -1) {
					sm.now->x -= (GLclampf)0.01;
				}
				else {
					sm.now->x += (GLclampf)0.01;
					sm.now->rightOn = true;
				}
			}
			if (sm.now->upOn == true) {
				if (sm.now->getY() + (GLclampf)0.01 <= 1) {
					sm.now->y += (GLclampf)0.01;
				}
				else {
					sm.now->y -= (GLclampf)0.01;
					sm.now->upOn = false;
				}
			}
			else {
				if (sm.now->getY() - (GLclampf)0.01 >= -1) {
					sm.now->y -= (GLclampf)0.01;
				}
				else {
					sm.now->y += (GLclampf)0.01;
					sm.now->upOn = true;
				}
			}
			if (sm.size == true) {
				sm.sizeset();
			}
		}
		glutPostRedisplay();
		glutTimerFunc(10, TimerFunction, value);
	}
	else {
		glutPostRedisplay();
		glutTimerFunc(10, TimerFunction, value);
	}
	return;
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
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, TimerFunction, 1);
	glutReshapeFunc(Reshape);						// 다시 그리기 함수 지정
	glutMainLoop();									// 이벤트 처리 시작 
}