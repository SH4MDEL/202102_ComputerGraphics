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

GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체
GLuint s_program;
bool initiation = false, timer = false, reverse = false, stitch = false;
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
	GLfloat Tx, Ty, weight;
	GLfloat data[2][3][3];		// 0번 : 위치, 1번 : 색상
	GLuint vao, vbo[2];
	int position;
	int moveStack;

	Triangle(GLfloat Tx, GLfloat Ty, GLfloat weight) : Tx(Tx), Ty(Ty), weight(weight), position(TriangleStatus::GoingLeft), moveStack(0) {
		data[0][0][0] = Tx - (GLfloat)0.05, data[0][0][1] = Ty - (GLfloat)0.05, data[0][0][2] = 0.0;
		data[0][1][0] = Tx + (GLfloat)0.05, data[0][1][1] = Ty - (GLfloat)0.05, data[0][1][2] = 0.0;
		data[0][2][0] = Tx,					data[0][2][1] = Ty + (GLfloat)0.05, data[0][2][2] = 0.0;

		data[1][0][0] = 0.5, data[1][0][1] = 0.5, data[1][0][2] = 0.5;
		data[1][1][0] = 0.5, data[1][1][1] = 0.5, data[1][1][2] = 0.5;
		data[1][2][0] = 0.5, data[1][2][1] = 0.5, data[1][2][2] = 0.5;
	}
	void setthis(GLfloat x, GLfloat y, int position, int moveStack) {
		this->Tx = x, this->Ty = y, this->position = position, this->moveStack = moveStack;
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
		if (stitch == true) {
			if ((position == TriangleStatus::GoingLeft && reverse == false) || (position == TriangleStatus::GoingRight && reverse == true)) {
				data[0][0][0] = Tx - (GLfloat)0.05 - weight, data[0][0][1] = Ty - (GLfloat)0.05, data[0][0][2] = 0.0;
				data[0][1][0] = Tx + (GLfloat)0.05 - weight, data[0][1][1] = Ty - (GLfloat)0.05, data[0][1][2] = 0.0;
				data[0][2][0] = Tx - weight,				 data[0][2][1] = Ty + (GLfloat)0.05, data[0][2][2] = 0.0;
			}
			else if ((position == TriangleStatus::GoingRight && reverse == false) || (position == TriangleStatus::GoingLeft && reverse == true)) {
				data[0][0][0] = Tx - (GLfloat)0.05 + weight, data[0][0][1] = Ty - (GLfloat)0.05, data[0][0][2] = 0.0;
				data[0][1][0] = Tx + (GLfloat)0.05 + weight, data[0][1][1] = Ty - (GLfloat)0.05, data[0][1][2] = 0.0;
				data[0][2][0] = Tx + weight, data[0][2][1] = Ty + (GLfloat)0.05, data[0][2][2] = 0.0;
			}
			else if ((position == TriangleStatus::GoingDown && reverse == false) || (position == TriangleStatus::GoingUp && reverse == true)) {
				data[0][0][0] = Tx - (GLfloat)0.05, data[0][0][1] = Ty - (GLfloat)0.05 - weight, data[0][0][2] = 0.0;
				data[0][1][0] = Tx + (GLfloat)0.05, data[0][1][1] = Ty - (GLfloat)0.05 - weight, data[0][1][2] = 0.0;
				data[0][2][0] = Tx,					data[0][2][1] = Ty + (GLfloat)0.05 - weight, data[0][2][2] = 0.0;
			}
			else {
				data[0][0][0] = Tx - (GLfloat)0.05, data[0][0][1] = Ty - (GLfloat)0.05 + weight, data[0][0][2] = 0.0;
				data[0][1][0] = Tx + (GLfloat)0.05, data[0][1][1] = Ty - (GLfloat)0.05 + weight, data[0][1][2] = 0.0;
				data[0][2][0] = Tx,					data[0][2][1] = Ty + (GLfloat)0.05 + weight, data[0][2][2] = 0.0;
			}
		}
		else {
			data[0][0][0] = Tx - (GLfloat)0.05, data[0][0][1] = Ty - (GLfloat)0.05, data[0][0][2] = 0.0;
			data[0][1][0] = Tx + (GLfloat)0.05, data[0][1][1] = Ty - (GLfloat)0.05, data[0][1][2] = 0.0;
			data[0][2][0] = Tx,					data[0][2][1] = Ty + (GLfloat)0.05, data[0][2][2] = 0.0;
		}
	}
};
struct Snake {
	Triangle tri[6] = { Triangle((GLfloat)-0.2, (GLfloat)0.0, -0.01f), Triangle((GLfloat)-0.1, (GLfloat)0.0, 0.01f), Triangle((GLfloat)0.0, (GLfloat)0.0, -0.01f),
						Triangle((GLfloat)0.1, (GLfloat)0.0, 0.01f), Triangle((GLfloat)0.2, (GLfloat)0.0, -0.01f), Triangle((GLfloat)0.3, (GLfloat)0.0, 0.01f) };
	int position;
	Snake() : position(SnakeStatus::LeftDown) {}
	
	void moveit() {
		if (reverse == false) {
			if (position == SnakeStatus::LeftDown) {
				if (tri[5].position == TriangleStatus::GoingRight) {
					if (tri[5].Ty < -0.95) {
						this->position = SnakeStatus::RightUp;
						for (int i = 0; i < 6; i++) {
							if (tri[i].moveStack == 0) {
								tri[i].moveStack = 10;
							}
							else if (tri[i].moveStack == 10) {
								tri[i].moveStack = 0;
							}
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
							if (tri[i].moveStack == 0) {
								tri[i].moveStack = 10;
							}
							else if (tri[i].moveStack == 10) {
								tri[i].moveStack = 0;
							}
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
							if (tri[i].moveStack == 0) {
								tri[i].moveStack = 10;
							}
							else if (tri[i].moveStack == 10) {
								tri[i].moveStack = 0;
							}
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
							if (tri[i].moveStack == 0) {
								tri[i].moveStack = 10;
							}
							else if (tri[i].moveStack == 10) {
								tri[i].moveStack = 0;
							}
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
							if (tri[i].moveStack == 0) {
								tri[i].moveStack = 10;
							}
							else if (tri[i].moveStack == 10) {
								tri[i].moveStack = 0;
							}
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
							if (tri[i].moveStack == 0) {
								tri[i].moveStack = 10;
							}
							else if (tri[i].moveStack == 10) {
								tri[i].moveStack = 0;
							}
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
							if (tri[i].moveStack == 0) {
								tri[i].moveStack = 10;
							}
							else if (tri[i].moveStack == 10) {
								tri[i].moveStack = 0;
							}
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
							if (tri[i].moveStack == 0) {
								tri[i].moveStack = 10;
							}
							else if (tri[i].moveStack == 10) {
								tri[i].moveStack = 0;
							}
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

int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("practice 8");

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
	//--- 변경된 배경색 설정
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(s_program);
	if (initiation == true) {
		for (int i = 0; i < 6; i++) {
			glBindVertexArray(va.vao[i]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}

	glutSwapBuffers(); //--- 화면에 출력하기
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
		// 이동 시작
		if (initiation == true) {
			timer = true;
		}
		break;
	case 'N':
	case 'n':
		//이동방향 전환
		if ((snake.tri[0].position != TriangleStatus::GoingDown && snake.tri[0].position != TriangleStatus::GoingUp) &&
			(snake.tri[5].position != TriangleStatus::GoingDown && snake.tri[5].position != TriangleStatus::GoingUp)) {
			if (snake.position == SnakeStatus::LeftDown) {
				for (int i = 0; i < 6; i++) {
					if (snake.tri[i].position == TriangleStatus::GoingRight) {
						snake.tri[i].position = TriangleStatus::GoingLeft;
							if (snake.tri[i].moveStack == 0) { snake.tri[i].moveStack = 10; }
							else if (snake.tri[i].moveStack == 10) { snake.tri[i].moveStack = 0; }
					}
					else if (snake.tri[i].position == TriangleStatus::GoingLeft) {
						snake.tri[i].position = TriangleStatus::GoingRight;
							if (snake.tri[i].moveStack == 0) { snake.tri[i].moveStack = 10; }
							else if (snake.tri[i].moveStack == 10) { snake.tri[i].moveStack = 0; }
					}
					else if (snake.tri[i].position == TriangleStatus::GoingUp) {
						snake.tri[i].position = TriangleStatus::GoingDown;
					}
					else {
						snake.tri[i].position = TriangleStatus::GoingUp;
					}
				}
				snake.position = SnakeStatus::RightUp;
			}
			else if (snake.position == SnakeStatus::RightUp) {
				for (int i = 0; i < 6; i++) {
					if (snake.tri[i].position == TriangleStatus::GoingRight) {
						snake.tri[i].position = TriangleStatus::GoingLeft;
						if (snake.tri[i].moveStack == 0) { snake.tri[i].moveStack = 10; }
						else if (snake.tri[i].moveStack == 10) { snake.tri[i].moveStack = 0; }
					}
					else if (snake.tri[i].position == TriangleStatus::GoingLeft) {
						snake.tri[i].position = TriangleStatus::GoingRight;
						if (snake.tri[i].moveStack == 0) { snake.tri[i].moveStack = 10; }
						else if (snake.tri[i].moveStack == 10) { snake.tri[i].moveStack = 0; }
					}
					else if (snake.tri[i].position == TriangleStatus::GoingUp) {
						snake.tri[i].position = TriangleStatus::GoingDown;
					}
					else {
						snake.tri[i].position = TriangleStatus::GoingUp;
					}
				}
				snake.position = SnakeStatus::LeftDown;
			}
			else if (snake.position == SnakeStatus::RightDown) {
				for (int i = 0; i < 6; i++) {
					if (snake.tri[i].position == TriangleStatus::GoingRight) {
						snake.tri[i].position = TriangleStatus::GoingLeft;
						if (snake.tri[i].moveStack == 0) { snake.tri[i].moveStack = 10; }
						else if (snake.tri[i].moveStack == 10) { snake.tri[i].moveStack = 0; }
					}
					else if (snake.tri[i].position == TriangleStatus::GoingLeft) {
						snake.tri[i].position = TriangleStatus::GoingRight;
						if (snake.tri[i].moveStack == 0) { snake.tri[i].moveStack = 10; }
						else if (snake.tri[i].moveStack == 10) { snake.tri[i].moveStack = 0; }
					}
					else if (snake.tri[i].position == TriangleStatus::GoingUp) {
						snake.tri[i].position = TriangleStatus::GoingDown;
					}
					else {
						snake.tri[i].position = TriangleStatus::GoingUp;
					}
				}
				snake.position = SnakeStatus::LeftUp;
			}
			else {
				for (int i = 0; i < 6; i++) {
					if (snake.tri[i].position == TriangleStatus::GoingRight) {
						snake.tri[i].position = TriangleStatus::GoingLeft;
						if (snake.tri[i].moveStack == 0) { snake.tri[i].moveStack = 10; }
						else if (snake.tri[i].moveStack == 10) { snake.tri[i].moveStack = 0; }
					}
					else if (snake.tri[i].position == TriangleStatus::GoingLeft) {
						snake.tri[i].position = TriangleStatus::GoingRight;
						if (snake.tri[i].moveStack == 0) { snake.tri[i].moveStack = 10; }
						else if (snake.tri[i].moveStack == 10) { snake.tri[i].moveStack = 0; }
					}
					else if (snake.tri[i].position == TriangleStatus::GoingUp) {
						snake.tri[i].position = TriangleStatus::GoingDown;
					}
					else {
						snake.tri[i].position = TriangleStatus::GoingUp;
					}
				}
				snake.position = SnakeStatus::RightDown;
			}
			if (reverse == false) { reverse = true; }
			else { reverse = false; }
		}
		break;
	case '+':
	case '=':
		// 이동속도 증가
		if (delay > 5) {
			delay -= 2;
		}
		break;
	case '-':
	case '_':
		// 이동속도 감소
		if (delay < 25) {
			delay += 2;
		}
		break;
	case 'A':
	case 'a':
		// 두개씩 연결되어 같이 이동
		stitch = true;
		break;
	case 'B':
	case 'b':
		// 분리되어 같이 이동
		stitch = false;
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

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

void initBuffer()
{
	glGenVertexArrays(6, va.vao); //--- VAO 를 지정하고 할당하기
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(va.vao[i]);

		glGenBuffers(2, va.vbo[i]); //--- 2개의 VBO를 지정하고 할당하기
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
