#pragma once
#include "make_vertexShaders.h"
#include "make_fragmentShaders.h"
#include "make_shaderProgram.h"
#include "stdafx.h"

#include "Field.h"
#include "Mountain.h"
#include "Robot.h"

#include "random_only.h"

#define M_PI 3.1415926535897932384626433832795
#define M_WINDOWX 1200
#define M_WINDOWY 900

GLvoid drawScene();
GLvoid Keyboard(unsigned char inputKey, int x, int y);
GLvoid TimerFunction(int value);
GLvoid Reshape(int w, int h);

GLchar *vertexSource, *fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체
GLuint s_program;

struct RunControl {
	GLint rotationX, rotationY;
	bool rotationYup;
	GLfloat rotationXPos, rotationYPos, perspectiveZPos;
	bool perspective;
	bool maze;
	bool quarterview;
	RunControl() {
		reset();

	}
	void reset() {
		rotationX = 0;
		rotationY = 0;
		rotationXPos = 180.0f;
		rotationYPos = 30.0f;
		rotationYup = true;
		perspective = true;
		maze = false;
		perspectiveZPos = 0.0f;
		quarterview = true;
	}
};
RunControl rc;

struct RobotManager {
	bool drawed;
	Robot robot;
	bool up, down, left, right;
	void initMyBuffer() {
		robot.initBuffer();
	}
	void reset() {
		robot.allReset();
		drawed = false;
		up = false, down = false, left = false, right = false;
	}
};
RobotManager rm;

struct MountainManager {
	GLint horizontal, vertical;
	Field field;
	Mountain** mountain_list;
	random_only ro;

	MountainManager() {
		horizontal = 0;
		vertical = 0;
	}
	void reset() {
		for (int i = 0; i < vertical; i++) {
			for (int j = 0; j < horizontal; j++) {
				mountain_list[i][j].allReset();
			}
		}
	}
	void CreatField() {
		field.add_data(vertical, horizontal);
		mountain_list = new Mountain*[vertical];
		for (int i = 0; i < vertical; i++) {
			mountain_list[i] = new Mountain[horizontal] ();
		}
		for (int i = 0; i < vertical; i++) {
			for (int j = 0; j < horizontal; j++) {
				mountain_list[i][j].add_data(i, j);
			}
		}
	}
	void initMyBuffer() {
		field.initBuffer();
		for (int i = 0; i < vertical; i++) {
			for (int j = 0; j < horizontal; j++) {
				mountain_list[i][j].initBuffer();
			}
		}
	}
	void makeMaze() {
		int maze = ro.get_mazing();
		int n = 0, m = 0;
		mountain_list[0][0].make_road();
		while (n + 1 != vertical || m + 1 != horizontal) {
			maze = ro.get_mazing();
			if (maze >= 1 && maze <= 3 && n != 0) {
				n -= 1;
			}
			else if (maze >= 4 && maze <= 6 && m != 0) {
				m -= 1;
			}
			else if (maze >= 7 && maze <= 11 && n + 1 != vertical) {
				n += 1;
			}
			else if (maze >= 12 && maze <= 16 && m + 1 != horizontal) {
				m += 1;
			}
			mountain_list[n][m].make_road();
		}
	}
};
MountainManager mm;

void collid()
{
	rm.up = false, rm.down = false, rm.left = false, rm.right = false;
	if (rm.robot.xPos - 0.01f - 0.001f < 0.0f) {
		rm.left = true;
	}
	if (rm.robot.xPos + 0.01f + 0.001f > (float)mm.vertical / 10.0f) {
		rm.right = true;
	}
	if (rm.robot.zPos - 0.01f - 0.001f < 0.0f) {
		rm.down = true;
	}
	if (rm.robot.zPos + 0.01f + 0.001f > (float)mm.horizontal / 10.0f) {
		rm.up = true;
	}
	for (int i = 0; i < mm.vertical; i++) {
		for (int j = 0; j < mm.horizontal; j++) {
			if (mm.mountain_list[i][j].status != 0) {
				if (rm.robot.xPos + 0.01f + 0.001f > (GLfloat)mm.mountain_list[i][j].xPos / 10.0f && rm.robot.xPos - 0.01f < (GLfloat)mm.mountain_list[i][j].xPos / 10.0f + 0.1f &&
					rm.robot.zPos + 0.01f > (GLfloat)mm.mountain_list[i][j].zPos / 10.0f && rm.robot.zPos - 0.01f < (GLfloat)mm.mountain_list[i][j].zPos / 10.0f + 0.1f) {
					rm.right = true;
				}
				if (rm.robot.xPos + 0.001f > (GLfloat)mm.mountain_list[i][j].xPos / 10.0f && rm.robot.xPos - 0.01f - 0.001f < (GLfloat)mm.mountain_list[i][j].xPos / 10.0f + 0.1f &&
					rm.robot.zPos + 0.01f > (GLfloat)mm.mountain_list[i][j].zPos / 10.0f && rm.robot.zPos - 0.01f < (GLfloat)mm.mountain_list[i][j].zPos / 10.0f + 0.1f) {
					rm.left = true;
				}
				if (rm.robot.xPos + 0.01f > (GLfloat)mm.mountain_list[i][j].xPos / 10.0f && rm.robot.xPos - 0.01f < (GLfloat)mm.mountain_list[i][j].xPos / 10.0f + 0.1f &&
					rm.robot.zPos + 0.01f + 0.001f > (GLfloat)mm.mountain_list[i][j].zPos / 10.0f && rm.robot.zPos - 0.01f < (GLfloat)mm.mountain_list[i][j].zPos / 10.0f + 0.1f) {
					rm.up = true;
				}
				if (rm.robot.xPos + 0.01f > (GLfloat)mm.mountain_list[i][j].xPos / 10.0f && rm.robot.xPos - 0.01f < (GLfloat)mm.mountain_list[i][j].xPos / 10.0f + 0.1f &&
					rm.robot.zPos + 0.01f > (GLfloat)mm.mountain_list[i][j].zPos / 10.0f && rm.robot.zPos - 0.01f - 0.001f< (GLfloat)mm.mountain_list[i][j].zPos / 10.0f + 0.1f) {
					rm.down = true;
				}
			}
		}
	}
}

int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	printf("가로의 개수를 입력하시오 (5 이상 20 이하): ");
	scanf("%d", &mm.horizontal);
	printf("세로의 개수를 입력하시오 (5 이상 20 이하): ");
	scanf("%d", &mm.vertical);
	mm.CreatField();

	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(M_WINDOWX, M_WINDOWY);
	glutCreateWindow("Moving Mountain & Maze");

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {					// glew 초기화
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initialized\n";
	}
	mm.initMyBuffer();
	rm.initMyBuffer();

	glewInit();
	make_vertexShaders(vertexSource, vertexShader);
	make_fragmentShaders(fragmentSource, fragmentShader);
	s_program = make_shaderProgram(vertexShader, fragmentShader);

	glutDisplayFunc(drawScene);

	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, TimerFunction, 1);

	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	//--- 변경된 배경색 설정
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(s_program);

	glViewport(0, 0, 900, 900);

	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
	if (rc.quarterview) {
		cameraPos = glm::vec3(
			(3.0f + rc.perspectiveZPos) * sin(2 * M_PI / 360.0f * rc.rotationYPos) * cos(2 * M_PI / 360.0f * rc.rotationXPos),
			(3.0f + rc.perspectiveZPos) * cos(2 * M_PI / 360.0f * rc.rotationYPos),
			(3.0f + rc.perspectiveZPos) * sin(2 * M_PI / 360.0f * rc.rotationYPos) * sin(2 * M_PI / 360.0f * rc.rotationXPos)); //--- 카메라 위치
		cameraDirection = glm::vec3((GLfloat)mm.vertical / 20.0f, 0.0f, (GLfloat)mm.horizontal / 20.0f); //--- 카메라 바라보는 방향
	}
	else {
		if (rm.robot.movement == 0 || rm.robot.movement == 1) {
			cameraPos = glm::vec3(rm.robot.xPos, 0.1f, rm.robot.zPos); //--- 카메라 위치
			cameraDirection = glm::vec3(20.0f, 1.0f, 0.0f); //--- 카메라 바라보는 방향
		}
		else if (rm.robot.movement == 2) {
			cameraPos = glm::vec3(rm.robot.xPos, 0.1f, rm.robot.zPos); //--- 카메라 위치
			cameraDirection = glm::vec3(-20.0f, 1.0f, 0.0f); //--- 카메라 바라보는 방향
		}
		else if (rm.robot.movement == 3) {
			cameraPos = glm::vec3(rm.robot.xPos, 0.1f, rm.robot.zPos); //--- 카메라 위치
			cameraDirection = glm::vec3(0.0f, 1.0f, -20.0f); //--- 카메라 바라보는 방향
		}
		else if (rm.robot.movement == 4) {
			cameraPos = glm::vec3(rm.robot.xPos, 0.1f, rm.robot.zPos); //--- 카메라 위치
			cameraDirection = glm::vec3(0.0f, 1.0f, 20.0f); //--- 카메라 바라보는 방향
		}
	}
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


	glm::mat4 projection = glm::mat4(1.0f);
	if (!rc.quarterview) {
		projection = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 10.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, -0.05)); //--- 공간을 약간 뒤로 밀어줌
	}
	else if (rc.perspective) {
		projection = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 200.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.2)); //--- 공간을 약간 뒤로 밀어줌
	}
	else {
		projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -3.0f, 3.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.2)); //--- 공간을 약간 뒤로 밀어줌
	}
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	glEnable(GL_DEPTH_TEST);

	unsigned int modelLocation = glGetUniformLocation(s_program, "ModelTransform"); //--- 버텍스 세이더에서 모델링 변환 위치 가져오기

	mm.field.putFactor(glm::mat4(1.0f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(mm.field.getFactor()));
	mm.field.draw();

	for (int i = 0; i < mm.vertical; i++) {
		for (int j = 0; j < mm.horizontal; j++) {
			mm.mountain_list[i][j].putFactor(mm.field.getFactor());
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(mm.mountain_list[i][j].getFactor()));
			mm.mountain_list[i][j].draw();
		}
	}

	if (rm.drawed) {
		rm.robot.putFactor(mm.field.getFactor());

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rm.robot.getbodyFactor()));
		rm.robot.body_draw();

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rm.robot.getheadFactor()));
		rm.robot.head_draw();

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rm.robot.getleftarmFactor()));
		rm.robot.leftarm_draw();

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rm.robot.getleftlegFactor()));
		rm.robot.leftleg_draw();

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rm.robot.getrightarmFactor()));
		rm.robot.rightarm_draw();

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rm.robot.getrightlegFactor()));
		rm.robot.rightleg_draw();
	}
	glDisable(GL_DEPTH_TEST);


	glViewport(900, 300, 300, 300);

	glm::vec3 cameraPos2 = glm::vec3(0.0f, 8.0f, 0.0f); //--- 카메라 위치
	glm::vec3 cameraDirection2 = glm::vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
	glm::vec3 cameraUp2 = glm::vec3(1.0f, 0.0f, 0.0f); //--- 카메라 위쪽 방향
	glm::mat4 view2 = glm::mat4(1.0f);
	view2 = glm::lookAt(cameraPos2, cameraDirection2, cameraUp2);
	unsigned int viewLocation3 = glGetUniformLocation(s_program, "viewTransform"); //--- 뷰잉 변환 설정
	glUniformMatrix4fv(viewLocation3, 1, GL_FALSE, &view2[0][0]);


	glm::mat4 projection2 = glm::mat4(1.0f);
	//projection3 = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 200.0f);
	projection2 = glm::ortho(0.0f, (float)mm.vertical / 10.0f, 0.0f, (float)mm.horizontal / 10.0f, 0.0f, 10.0f);
	projection2 = glm::translate(projection2, glm::vec3(0.0f, 0.0f, 0.0f)); //--- 공간을 약간 뒤로 미뤄줌
	unsigned int projectionLocation3 = glGetUniformLocation(s_program, "projectionTransform"); //--- 투영 변환 값 설정
	glUniformMatrix4fv(projectionLocation3, 1, GL_FALSE, &projection2[0][0]);

	glEnable(GL_DEPTH_TEST);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(mm.field.getFactor()));
	mm.field.draw();

	for (int i = 0; i < mm.vertical; i++) {
		for (int j = 0; j < mm.horizontal; j++) {
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(mm.mountain_list[i][j].getFactor()));
			mm.mountain_list[i][j].draw();
		}
	}

	if (rm.drawed) {

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rm.robot.getbodyFactor()));
		rm.robot.body_draw();

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rm.robot.getheadFactor()));
		rm.robot.head_draw();

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rm.robot.getleftarmFactor()));
		rm.robot.leftarm_draw();

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rm.robot.getleftlegFactor()));
		rm.robot.leftleg_draw();

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rm.robot.getrightarmFactor()));
		rm.robot.rightarm_draw();

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(rm.robot.getrightlegFactor()));
		rm.robot.rightleg_draw();
	}

	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers(); //--- 화면에 출력하기
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'o':	// 직각 투영 설정
	case 'O':
		printf("o : 직각 투영 설정\n");
		rc.perspective = false;
		break;
	case 'p':	// 원근 투영 설정
	case 'P':	
		printf("p : 원근 투영 설정\n");
		rc.perspective = true;
		break;
	case 'z':	// 원근 투영 시 모델링이 멀게 보이면 z축으로 이동할 수 있게 한다.
		printf("z : z축 양의 방향 이동\n");
		if (rc.perspective) {
			rc.perspectiveZPos += 0.1f;
		}
		break;
	case 'Z':
		printf("Z : z축 음의 방향 이동\n");
		if (rc.perspective) {
			rc.perspectiveZPos -= 0.1f;
		}
		break;
	case 'm':	// 육면체들이 위 아래로 움직인다 / 멈춘다.
		printf("m : 육면체 위 아래로 이동\n");
		for (int i = 0; i < mm.vertical; i++) {
			for (int j = 0; j < mm.horizontal; j++) {
				mm.mountain_list[i][j].start_wave();
			}
		}
		break;
	case 'M':
		printf("M : 육면체 정지\n");
		for (int i = 0; i < mm.vertical; i++) {
			for (int j = 0; j < mm.horizontal; j++) {
				mm.mountain_list[i][j].stop_wave();
			}
		}
		break;
	case 'x':	// 카메라가 바닥의 x축을 기준으로 양 방향으로 회전한다.
		if (rc.rotationX != 1) {
			printf("x : x축 양의 방향 이동\n");
			rc.rotationX = 1;
		}
		else {
			printf("x : x축 이동 정지\n");
			rc.rotationX = 0;
		}
		break;
	case 'X':	// 카메라가 바닥의 x축을 기준으로 음 방향으로 회전한다.
		if (rc.rotationX != 2) {
			printf("X : x축 음의 방향 이동\n");
			rc.rotationX = 2;
		}
		else {
			printf("X : x축 이동 정지\n");
			rc.rotationX = 0;
		}
		break;
	case 'y':	// 카메라가 바닥의 y축을 기준으로 양 방향으로 회전한다.
		if (rc.rotationY != 1) {
			printf("y : y축 양의 방향 이동\n");
			rc.rotationY = 1;
		}
		else {
			printf("y : y축 이동 정지\n");
			rc.rotationY = 0;
		}
		break;
	case 'Y':	// 카메라가 바닥의 y축을 기준으로 음 방향으로 회전한다.
		if (rc.rotationY != 2) {
			printf("Y : y축 음의 방향 이동\n");
			rc.rotationY = 2;
		}
		else {
			printf("Y : y축 이동 정지\n");
			rc.rotationY = 0;
		}
		break;
	case 'r':	// 미로를 제작한다.
	case 'R':
		printf("r : 미로 제작\n");
		if (!rc.maze) {
			mm.makeMaze();
			rc.maze = true;
			rm.drawed = true;
		}
		break;
	case 'S':	// 미로에서 객체가 움직이기 시작한다.
		if (!rc.maze) {
			printf("S : 먼저 미로를 생성하십시오. \n");
		}
		else {
			printf("S : 객체 움직임 시작. \n");
			rm.robot.movement = 1;
		}
		break;
	case 'v':	// 육면체들 움직임이 멈추고 낮은 높이로 변한다.
	case 'V':
		if (!rc.maze) {
			printf("v : 먼저 미로를 생성하십시오. \n");
		}
		else {
			printf("v : 낮은 높이로 변환. \n");
			for (int i = 0; i < mm.vertical; i++) {
				for (int j = 0; j < mm.horizontal; j++) {
					mm.mountain_list[i][j].low_height();
				}
			}
		}
		break;
	case 'w':	// 객체 앞 이동
		if (rm.robot.movement != 0) {
			printf("w : 객체 앞 이동. \n");
			rm.robot.movement = 1;
		}
		break;
	case 's':	// 객체 뒤 이동
		if (rm.robot.movement != 0) {
			printf("s : 객체 뒤 이동. \n");
			rm.robot.movement = 2;
		}
		break;
	case 'a':	// 객체 좌 이동
		if (rm.robot.movement != 0) {
			printf("a : 객체 좌 이동. \n");
			rm.robot.movement = 3;
		}
		break;
	case 'd':	// 객체 우 이동
		if (rm.robot.movement != 0) {
			printf("d : 객체 우 이동. \n");
			rm.robot.movement = 4;
		}
		break;
	case '-':	// 육면체 이동하는 속도 감소
	case '_':
		printf("- : 육면체 이동속도 감소. \n");
		for (int i = 0; i < mm.vertical; i++) {
			for (int j = 0; j < mm.horizontal; j++) {
				mm.mountain_list[i][j].speeddown();
			}
		}
		break;
	case '=':	// 육면체 이동하는 속도 증가
	case '+':
		printf("+ : 육면체 이동속도 증가. \n");
		for (int i = 0; i < mm.vertical; i++) {
			for (int j = 0; j < mm.horizontal; j++) {
				mm.mountain_list[i][j].speedup();
			}
		}
		break;
	case '1':	// 1인칭 객체 시점
		printf("1 : 1인칭 객체 시점 \n");
		rc.quarterview = false;
		break;
	case '3':	// 3인칭 쿼터뷰 시점
		printf("1 : 3인칭 쿼터뷰 시점 \n");
		rc.quarterview = true;
		break;
	case 'c':	// 모든 값 초기화
	case 'C':
		printf("c : 초기화 \n");
		rc.reset();
		rm.reset();
		mm.reset();
		break;
	case 'q':	// 프로그램 종료
	case 'Q':
		printf("q : 프로그램 종료 \n");
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	if (rc.rotationX == 1) {
		rc.rotationXPos += 1.0f;
	}
	else if (rc.rotationX == 2) {
		rc.rotationXPos -= 1.0f;
	}
	if (rc.rotationY == 1) {
		if (rc.rotationYup) {
			if (rc.rotationYPos + 1.0f >= 180.0f) {
				rc.rotationYPos = 179.0f;
				rc.rotationXPos += 180.0f;
				rc.rotationYup = false;
			}
			else {
				rc.rotationYPos += 1.0f;
			}
		}
		else {
			if (rc.rotationYPos - 1.0f <= 0.0f) {
				rc.rotationYPos = 1.0f;
				rc.rotationXPos += 180.0f;
				rc.rotationYup = true;
			}
			else {
				rc.rotationYPos -= 1.0f;
			}
		}
	}
	else if (rc.rotationY == 2) {
		if (rc.rotationYup) {
			if (rc.rotationYPos - 1.0f <= 0.0f) {
				rc.rotationYPos = 1.0f;
				rc.rotationXPos -= 180.0f;
				rc.rotationYup = false;
			}
			else {
				rc.rotationYPos -= 1.0f;
			}
		}
		else {
			if (rc.rotationYPos + 1.0f >= 180.0f) {
				rc.rotationYPos = 179.0f;
				rc.rotationXPos -= 180.0f;
				rc.rotationYup = true;
			}
			else {
				rc.rotationYPos += 1.0f;
			}
		}
	}
	for (int i = 0; i < mm.vertical; i++) {
		for (int j = 0; j < mm.horizontal; j++) {
			mm.mountain_list[i][j].update();
		}
	}
	collid();
	rm.robot.update(rm.up, rm.down, rm.left, rm.right);

	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, value);
	return;
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}
