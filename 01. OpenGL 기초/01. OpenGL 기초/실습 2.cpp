#include <iostream>
#include <random>
#include <gl/glew.h>								//--- �ʿ��� ������� include
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
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(0, 0);					// �������� ��ġ ����
	glutInitWindowSize(WINDOWSHEIGHT, WINDOWSWIDTH);	// �������� ũ�� ����
	glutCreateWindow("Practice 2");					// ������ ����(������ �̸�)
}

GLvoid drawScene() {								//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
	glClearColor(bgm.getR(), bgm.getG(), bgm.getB(), 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);					// ������ ������ ��ü�� ĥ�ϱ�

	glColor3f(square.getR(), square.getG(), square.getB());
	glRectf(square.getX() - square.getSize(), square.getY() - square.getSize(), 
		square.getX() + square.getSize(), square.getY() + square.getSize());

	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�.
	glutSwapBuffers();								// ȭ�鿡 ����ϱ�
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

GLvoid Reshape(int w, int h) {						//--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�

	glViewport(0, 0, w, h);
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
	glutMouseFunc(mouse);
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutMainLoop();									// �̺�Ʈ ó�� ���� 
}