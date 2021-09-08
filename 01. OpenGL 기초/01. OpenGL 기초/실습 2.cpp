#include <iostream>
#include <gl/glew.h>								//--- 필요한 헤더파일 include
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
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(0, 0);					// 윈도우의 위치 지정
	glutInitWindowSize(800, 600);					// 윈도우의 크기 지정
	glutCreateWindow("Practice 1");					// 윈도우 생성(윈도우 이름)
}

GLvoid drawScene() {								//--- 콜백 함수: 그리기 콜백 함수 
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			// 바탕색을 ‘blue’ 로 지정
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
	glutMainLoop();									// 이벤트 처리 시작 
}