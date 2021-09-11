#include <iostream>
#include <random>
#include <gl/glew.h>								//--- �ʿ��� ������� include
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
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(0, 0);					// �������� ��ġ ����
	glutInitWindowSize(800, 600);					// �������� ũ�� ����
	glutCreateWindow("Practice 1");					// ������ ����(������ �̸�)
}

GLvoid drawScene() {								//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
	glClearColor(bgm.getR(), bgm.getG(), bgm.getB(), 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);					// ������ ������ ��ü�� ĥ�ϱ�

	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�.
	glutSwapBuffers();								// ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) {						//--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
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

int main(int argc, char** argv)					//--- ������ ����ϰ� �ݹ��Լ� ���� 
{
	//--- ������ �����ϱ�
	myGlutInitiate(argc, argv);

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {					// glew �ʱ�ȭ
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initialized\n";
	}
	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(200, TimerFunction, 1);
	glutMainLoop();									// �̺�Ʈ ó�� ���� 
}