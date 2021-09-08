#include <iostream>
#include <gl/glew.h>								//--- �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

class Square {
	GLclampf Rtype, Gtype, Btype;
	int x, y;
public:
	Square(GLclampf Rtype, GLclampf Gtype, GLclampf Btype, int x, int y) :
		Rtype(Rtype), Gtype(Gtype), Btype(Btype), x(x), y(y) {}
	GLvoid reColoring(GLclampf Rtype, GLclampf Gtype, GLclampf Btype) {
		this->Rtype = Rtype;
		this->Gtype = Gtype;
		this->Btype = Btype;
	}
	GLvoid reMove(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int getX() { return x; }
	int getY() { return y; }
	~Square() {};
};

GLvoid myGlutInitiate(int argc, char** argv)
{
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(0, 0);					// �������� ��ġ ����
	glutInitWindowSize(800, 600);					// �������� ũ�� ����
	glutCreateWindow("Practice 1");					// ������ ����(������ �̸�)
}

GLvoid drawScene() {								//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			// �������� ��blue�� �� ����
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
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glutDisplayFunc(drawScene);
		break;
	case 'G':
		break;
	case 'B':
		break;
	case 'A':
		break;
	case 'W':
		break;
	case 'K':
		break;
	case 'T':
		break;
	case 'S':
		break;
	case 'Q':
		break;
	}
	glutPostRedisplay();
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
	glutMainLoop();									// �̺�Ʈ ó�� ���� 
}