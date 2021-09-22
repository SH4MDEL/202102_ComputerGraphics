#pragma once
#include "shader.h"
#include "initShader.h"
#include "make_shaderProgram.h"
#include "stdafx.h"
void initBuffer();
void reinitBuffer();

GLvoid drawScene();
GLvoid mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char inputKey, int x, int y);
GLvoid TimerFunction(int value);
GLvoid Reshape(int w, int h);

GLchar* vertexSource, * fragmentSource; //--- �ҽ��ڵ� ���� ����
GLuint vertexShader, fragmentShader; //--- ���̴� ��ü
GLuint s_program;
bool initiation = false, timer = false, reverse = false;
int delay = 15;

enum TriangleStatus {
	GoingUp,
	GoingDown,
	GoingLeft,
	GoingRight
};

enum SnakeStatus {
	LeftDown,
	RightDown,
	LeftUp,
	RightUp
};

struct VecterArray {
	GLuint vao[6], vbo[6][2];
};
VecterArray va;

struct Triangle {
	GLfloat Tx, Ty;
	GLfloat data[2][3][3];		// 0�� : ��ġ, 1�� : ����
	GLuint vao, vbo[2];
	int position;
	int moveStack;

	Triangle(GLfloat Tx, GLfloat Ty) : Tx(Tx), Ty(Ty), position(TriangleStatus::GoingLeft), moveStack(0) {
		data[0][0][0] = Tx - (GLfloat)0.05, data[0][0][1] = Ty - (GLfloat)0.05, data[0][0][2] = 0.0;
		data[0][1][0] = Tx + (GLfloat)0.05, data[0][1][1] = Ty - (GLfloat)0.05, data[0][1][2] = 0.0;
		data[0][2][0] = Tx,					data[0][2][1] = Ty + (GLfloat)0.05, data[0][2][2] = 0.0;

		data[1][0][0] = 0.5, data[1][0][1] = 0.5, data[1][0][2] = 0.5;
		data[1][1][0] = 0.5, data[1][1][1] = 0.5, data[1][1][2] = 0.5;
		data[1][2][0] = 0.5, data[1][2][1] = 0.5, data[1][2][2] = 0.5;
	}
	void moveit(int lineStatus) {
		if (lineStatus == SnakeStatus::LeftDown) {
			if (position == TriangleStatus::GoingLeft) {
				if (Tx < (GLfloat)-0.95) {
					position = TriangleStatus::GoingDown;
					Ty -= (GLfloat)0.01;
					moveStack++;
				}
				else {
					Tx -= (GLfloat)0.01;
				}
			}
			else if (position == TriangleStatus::GoingDown) {
				if (moveStack == 10) {
					position = TriangleStatus::GoingRight;
					Tx += (GLfloat)0.01;
					moveStack = 0;
				}
				else {
					Ty -= (GLfloat)0.01;
					moveStack++;
				}
			}
			else if (position == TriangleStatus::GoingRight) {
				Tx += (GLfloat)0.01;
			}
		}
		else if (lineStatus == SnakeStatus::RightDown) {
			if (position == TriangleStatus::GoingRight) {
				if (Tx > (GLfloat)0.95) {
					position = TriangleStatus::GoingDown;
					Ty -= (GLfloat)0.01;
					moveStack++;
				}
				else {
					Tx += (GLfloat)0.01;
				}
			}
			else if (position == TriangleStatus::GoingDown) {
				if (moveStack == 10) {
					position = TriangleStatus::GoingLeft;
					Tx -= (GLfloat)0.01;
					moveStack = 0;
				}
				else {
					Ty -= (GLfloat)0.01;
					moveStack++;
				}
			}
			else if (position == TriangleStatus::GoingLeft) {
				Tx -= (GLfloat)0.01;
			}
		}
		else if (lineStatus == SnakeStatus::LeftUp) {
			if (position == TriangleStatus::GoingLeft) {
				if (Tx < (GLfloat)-0.95) {
					position = TriangleStatus::GoingUp;
					Ty += (GLfloat)0.01;
					moveStack--;
				}
				else {
					Tx -= (GLfloat)0.01;
				}
			}
			else if (position == TriangleStatus::GoingUp) {
				if (moveStack == 0) {
					position = TriangleStatus::GoingRight;
					Tx += (GLfloat)0.01;
					moveStack = 10;
				}
				else {
					Ty += (GLfloat)0.01;
					moveStack--;
				}
			}
			else if (position == TriangleStatus::GoingRight) {
				Tx += (GLfloat)0.01;
			}
		}
		else if (lineStatus == SnakeStatus::RightUp) {
			if (position == TriangleStatus::GoingRight) {
				if (Tx > (GLfloat)0.95) {
					position = TriangleStatus::GoingUp;
					Ty += (GLfloat)0.01;
					moveStack--;
				}
				else {
					Tx += (GLfloat)0.01;
				}
			}
			else if (position == TriangleStatus::GoingUp) {
				if (moveStack == 0) {
					position = TriangleStatus::GoingLeft;
					Tx -= (GLfloat)0.01;
					moveStack = 10;
				}
				else {
					Ty += (GLfloat)0.01;
					moveStack--;
				}
			}
			else if (position == TriangleStatus::GoingLeft) {
				Tx -= (GLfloat)0.01;
			}
		}
		data[0][0][0] = Tx - (GLfloat)0.05, data[0][0][1] = Ty - (GLfloat)0.05, data[0][0][2] = 0.0;
		data[0][1][0] = Tx + (GLfloat)0.05, data[0][1][1] = Ty - (GLfloat)0.05, data[0][1][2] = 0.0;
		data[0][2][0] = Tx,					data[0][2][1] = Ty + (GLfloat)0.05, data[0][2][2] = 0.0;
	}
};
struct Snake {
	Triangle tri[6] = { Triangle((GLfloat)-0.2, (GLfloat)0.0), Triangle((GLfloat)-0.1, (GLfloat)0.0), Triangle((GLfloat)0.0, (GLfloat)0.0),
						Triangle((GLfloat)0.1, (GLfloat)0.0), Triangle((GLfloat)0.2, (GLfloat)0.0), Triangle((GLfloat)0.3, (GLfloat)0.0) };
	int position;
	Snake() : position(SnakeStatus::LeftDown) {}
	
	void moveit() {
		if (reverse == false) {
			if (position == SnakeStatus::LeftDown) {
				if (tri[5].position == TriangleStatus::GoingRight) {
					if (tri[5].Ty < -0.95) {
						this->position = SnakeStatus::RightUp;
						for (int i = 0; i < 6; i++) {
							tri[i].moveStack = abs(tri[i].moveStack - 10);
						}
					}
					else {
						this->position = SnakeStatus::RightDown;
					}
				}
			}
			else if (position == SnakeStatus::RightDown) {
				if (tri[5].position == TriangleStatus::GoingLeft) {
					if (tri[5].Ty < -0.95) {
						this->position = SnakeStatus::LeftUp;
						for (int i = 0; i < 6; i++) {
							tri[i].moveStack = abs(tri[i].moveStack - 10);
						}
					}
					else {
						this->position = SnakeStatus::LeftDown;
					}
				}
			}
			else if (position == SnakeStatus::LeftUp) {
				if (tri[5].position == TriangleStatus::GoingRight) {
					if (tri[5].Ty > 0.95) {
						this->position = SnakeStatus::RightDown;
						for (int i = 0; i < 6; i++) {
							tri[i].moveStack = abs(tri[i].moveStack - 10);
						}
					}
					else {
						this->position = SnakeStatus::RightUp;
					}
				}
			}
			else if (position == SnakeStatus::RightUp) {
				if (tri[5].position == TriangleStatus::GoingLeft) {
					if (tri[5].Ty > 0.95) {
						this->position = SnakeStatus::LeftDown;
						for (int i = 0; i < 6; i++) {
							tri[i].moveStack = abs(tri[i].moveStack - 10);
						}
					}
					else {
						this->position = SnakeStatus::LeftUp;
					}
				}
			}
		}
		else {
			if (position == SnakeStatus::LeftDown) {
				if (tri[0].position == TriangleStatus::GoingRight) {
					if (tri[0].Ty < -0.95) {
						this->position = SnakeStatus::RightUp;
						for (int i = 0; i < 6; i++) {
							tri[i].moveStack = abs(tri[i].moveStack - 10);
						}
					}
					else {
						this->position = SnakeStatus::RightDown;
					}
				}
			}
			else if (position == SnakeStatus::RightDown) {
				if (tri[0].position == TriangleStatus::GoingLeft) {
					if (tri[0].Ty < -0.95) {
						this->position = SnakeStatus::LeftUp;
						for (int i = 0; i < 6; i++) {
							tri[i].moveStack = abs(tri[i].moveStack - 10);
						}
					}
					else {
						this->position = SnakeStatus::LeftDown;
					}
				}
			}
			else if (position == SnakeStatus::LeftUp) {
				if (tri[0].position == TriangleStatus::GoingRight) {
					if (tri[0].Ty > 0.95) {
						this->position = SnakeStatus::RightDown;
						for (int i = 0; i < 6; i++) {
							tri[i].moveStack = abs(tri[i].moveStack - 10);
						}
					}
					else {
						this->position = SnakeStatus::RightUp;
					}
				}
			}
			else if (position == SnakeStatus::RightUp) {
				if (tri[0].position == TriangleStatus::GoingLeft) {
					if (tri[0].Ty > 0.95) {
						this->position = SnakeStatus::LeftDown;
						for (int i = 0; i < 6; i++) {
							tri[i].moveStack = abs(tri[i].moveStack - 10);
						}
					}
					else {
						this->position = SnakeStatus::LeftUp;
					}
				}
			}
		}
		for (int i = 0; i < 6; i++) {
			tri[i].moveit(this->position);
		}
	}
};
Snake snake;

int main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("practice 8");

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
	initBuffer();

	glutDisplayFunc(drawScene);
	glutMouseFunc(mouse);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(delay, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	//--- ����� ���� ����
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- ������ ���������ο� ���̴� �ҷ�����
	glUseProgram(s_program);
	if (initiation == true) {
		for (int i = 0; i < 6; i++) {
			glBindVertexArray(va.vao[i]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}

	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid mouse(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		initiation = true;
	}

}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'M':
	case 'm':
		// �̵� ����
		if (initiation == true) {
			timer = true;
		}
		break;
	case 'N':
	case 'n':
		//�̵����� ��ȯ

		if (snake.position == SnakeStatus::LeftDown) {
			snake.position = SnakeStatus::RightUp;
			for (int i = 0; i < 6; i++) {
				if (snake.tri[i].position == TriangleStatus::GoingRight) {
					snake.tri[i].position = TriangleStatus::GoingLeft;
				}
				else if (snake.tri[i].position == TriangleStatus::GoingLeft) {
					snake.tri[i].position = TriangleStatus::GoingRight;
				}
				else if (snake.tri[i].position == TriangleStatus::GoingUp) {
					snake.tri[i].position = TriangleStatus::GoingDown;
				}
				else {
					snake.tri[i].position = TriangleStatus::GoingUp;
				}
			}
		}
		else if (snake.position == SnakeStatus::RightUp) {
			snake.position = SnakeStatus::LeftDown;
			for (int i = 0; i < 6; i++) {
				if (snake.tri[i].position == TriangleStatus::GoingRight) {
					snake.tri[i].position = TriangleStatus::GoingLeft;
				}
				else if (snake.tri[i].position == TriangleStatus::GoingLeft) {
					snake.tri[i].position = TriangleStatus::GoingRight;
				}
				else if (snake.tri[i].position == TriangleStatus::GoingUp) {
					snake.tri[i].position = TriangleStatus::GoingDown;
				}
				else {
					snake.tri[i].position = TriangleStatus::GoingUp;
				}
			}
		}
		else if (snake.position == SnakeStatus::RightDown) {
			snake.position = SnakeStatus::LeftUp;
			for (int i = 0; i < 6; i++) {
				if (snake.tri[i].position == TriangleStatus::GoingRight) {
					snake.tri[i].position = TriangleStatus::GoingLeft;
				}
				else if (snake.tri[i].position == TriangleStatus::GoingLeft) {
					snake.tri[i].position = TriangleStatus::GoingRight;
				}
				else if (snake.tri[i].position == TriangleStatus::GoingUp) {
					snake.tri[i].position = TriangleStatus::GoingDown;
				}
				else {
					snake.tri[i].position = TriangleStatus::GoingUp;
				}
			}
		}
		else {
			snake.position = SnakeStatus::RightDown;
			for (int i = 0; i < 6; i++) {
				if (snake.tri[i].position == TriangleStatus::GoingRight) {
					snake.tri[i].position = TriangleStatus::GoingLeft;
				}
				else if (snake.tri[i].position == TriangleStatus::GoingLeft) {
					snake.tri[i].position = TriangleStatus::GoingRight;
				}
				else if (snake.tri[i].position == TriangleStatus::GoingUp) {
					snake.tri[i].position = TriangleStatus::GoingDown;
				}
				else {
					snake.tri[i].position = TriangleStatus::GoingUp;
				}
			}
		}
		for (int i = 0; i < 6; i++) {
			if (snake.tri[i].moveStack == 0) { snake.tri[i].moveStack = 10; }
			else if (snake.tri[i].moveStack == 10) { snake.tri[i].moveStack = 0; }
		}
		if (reverse == false) { reverse = true; }
		else { reverse = false; }
		break;
	case '+':
	case '=':
		// �̵��ӵ� ����
		if (delay > 5) {
			delay -= 2;
		}
		break;
	case '-':
	case '_':
		// �̵��ӵ� ����
		if (delay < 25) {
			delay += 2;
		}
		break;
	case 'A':
	case 'a':
		// �ΰ��� ����Ǿ� ���� �̵�
		break;
	case 'B':
	case 'b':
		// �ΰ��� ����Ǿ� ���� �̵�
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
	if (timer == true) {
		snake.moveit();
		reinitBuffer();
		glutPostRedisplay();
		glutTimerFunc(delay, TimerFunction, value);
	}
	else {
		glutPostRedisplay();
		glutTimerFunc(delay, TimerFunction, value);
	}
	return;
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

void initBuffer()
{
	glGenVertexArrays(6, va.vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(va.vao[i]);

		glGenBuffers(2, va.vbo[i]); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, va.vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), snake.tri[i].data[j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}
}

void reinitBuffer()
{
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(va.vao[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, va.vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), snake.tri[i].data[j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}
}
