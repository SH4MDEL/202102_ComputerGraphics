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

GLchar *vertexSource, *fragmentSource; //--- �ҽ��ڵ� ���� ����
GLuint vertexShader, fragmentShader; //--- ���̴� ��ü
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

int main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	printf("������ ������ �Է��Ͻÿ� (5 �̻� 20 ����): ");
	scanf("%d", &mm.horizontal);
	printf("������ ������ �Է��Ͻÿ� (5 �̻� 20 ����): ");
	scanf("%d", &mm.vertical);
	mm.CreatField();

	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(M_WINDOWX, M_WINDOWY);
	glutCreateWindow("Moving Mountain & Maze");

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {					// glew �ʱ�ȭ
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
	//--- ����� ���� ����
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- ������ ���������ο� ���̴� �ҷ�����
	glUseProgram(s_program);

	glViewport(0, 0, 900, 900);

	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
	if (rc.quarterview) {
		cameraPos = glm::vec3(
			(3.0f + rc.perspectiveZPos) * sin(2 * M_PI / 360.0f * rc.rotationYPos) * cos(2 * M_PI / 360.0f * rc.rotationXPos),
			(3.0f + rc.perspectiveZPos) * cos(2 * M_PI / 360.0f * rc.rotationYPos),
			(3.0f + rc.perspectiveZPos) * sin(2 * M_PI / 360.0f * rc.rotationYPos) * sin(2 * M_PI / 360.0f * rc.rotationXPos)); //--- ī�޶� ��ġ
		cameraDirection = glm::vec3((GLfloat)mm.vertical / 20.0f, 0.0f, (GLfloat)mm.horizontal / 20.0f); //--- ī�޶� �ٶ󺸴� ����
	}
	else {
		if (rm.robot.movement == 0 || rm.robot.movement == 1) {
			cameraPos = glm::vec3(rm.robot.xPos, 0.1f, rm.robot.zPos); //--- ī�޶� ��ġ
			cameraDirection = glm::vec3(20.0f, 1.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
		}
		else if (rm.robot.movement == 2) {
			cameraPos = glm::vec3(rm.robot.xPos, 0.1f, rm.robot.zPos); //--- ī�޶� ��ġ
			cameraDirection = glm::vec3(-20.0f, 1.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
		}
		else if (rm.robot.movement == 3) {
			cameraPos = glm::vec3(rm.robot.xPos, 0.1f, rm.robot.zPos); //--- ī�޶� ��ġ
			cameraDirection = glm::vec3(0.0f, 1.0f, -20.0f); //--- ī�޶� �ٶ󺸴� ����
		}
		else if (rm.robot.movement == 4) {
			cameraPos = glm::vec3(rm.robot.xPos, 0.1f, rm.robot.zPos); //--- ī�޶� ��ġ
			cameraDirection = glm::vec3(0.0f, 1.0f, 20.0f); //--- ī�޶� �ٶ󺸴� ����
		}
	}
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- ���� ��ȯ ����
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


	glm::mat4 projection = glm::mat4(1.0f);
	if (!rc.quarterview) {
		projection = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 10.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, -0.05)); //--- ������ �ణ �ڷ� �о���
	}
	else if (rc.perspective) {
		projection = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 200.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.2)); //--- ������ �ణ �ڷ� �о���
	}
	else {
		projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -3.0f, 3.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.2)); //--- ������ �ణ �ڷ� �о���
	}
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform"); //--- ���� ��ȯ �� ����
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	glEnable(GL_DEPTH_TEST);

	unsigned int modelLocation = glGetUniformLocation(s_program, "ModelTransform"); //--- ���ؽ� ���̴����� �𵨸� ��ȯ ��ġ ��������

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

	glm::vec3 cameraPos2 = glm::vec3(0.0f, 8.0f, 0.0f); //--- ī�޶� ��ġ
	glm::vec3 cameraDirection2 = glm::vec3(0.0f, 0.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
	glm::vec3 cameraUp2 = glm::vec3(1.0f, 0.0f, 0.0f); //--- ī�޶� ���� ����
	glm::mat4 view2 = glm::mat4(1.0f);
	view2 = glm::lookAt(cameraPos2, cameraDirection2, cameraUp2);
	unsigned int viewLocation3 = glGetUniformLocation(s_program, "viewTransform"); //--- ���� ��ȯ ����
	glUniformMatrix4fv(viewLocation3, 1, GL_FALSE, &view2[0][0]);


	glm::mat4 projection2 = glm::mat4(1.0f);
	//projection3 = glm::perspective(glm::radians(60.0f), (float)700.0 / (float)700.0, 0.1f, 200.0f);
	projection2 = glm::ortho(0.0f, (float)mm.vertical / 10.0f, 0.0f, (float)mm.horizontal / 10.0f, 0.0f, 10.0f);
	projection2 = glm::translate(projection2, glm::vec3(0.0f, 0.0f, 0.0f)); //--- ������ �ణ �ڷ� �̷���
	unsigned int projectionLocation3 = glGetUniformLocation(s_program, "projectionTransform"); //--- ���� ��ȯ �� ����
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

	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid Keyboard(unsigned char inputKey, int x, int y)
{
	switch (inputKey) {
	case 'o':	// ���� ���� ����
	case 'O':
		printf("o : ���� ���� ����\n");
		rc.perspective = false;
		break;
	case 'p':	// ���� ���� ����
	case 'P':	
		printf("p : ���� ���� ����\n");
		rc.perspective = true;
		break;
	case 'z':	// ���� ���� �� �𵨸��� �ְ� ���̸� z������ �̵��� �� �ְ� �Ѵ�.
		printf("z : z�� ���� ���� �̵�\n");
		if (rc.perspective) {
			rc.perspectiveZPos += 0.1f;
		}
		break;
	case 'Z':
		printf("Z : z�� ���� ���� �̵�\n");
		if (rc.perspective) {
			rc.perspectiveZPos -= 0.1f;
		}
		break;
	case 'm':	// ����ü���� �� �Ʒ��� �����δ� / �����.
		printf("m : ����ü �� �Ʒ��� �̵�\n");
		for (int i = 0; i < mm.vertical; i++) {
			for (int j = 0; j < mm.horizontal; j++) {
				mm.mountain_list[i][j].start_wave();
			}
		}
		break;
	case 'M':
		printf("M : ����ü ����\n");
		for (int i = 0; i < mm.vertical; i++) {
			for (int j = 0; j < mm.horizontal; j++) {
				mm.mountain_list[i][j].stop_wave();
			}
		}
		break;
	case 'x':	// ī�޶� �ٴ��� x���� �������� �� �������� ȸ���Ѵ�.
		if (rc.rotationX != 1) {
			printf("x : x�� ���� ���� �̵�\n");
			rc.rotationX = 1;
		}
		else {
			printf("x : x�� �̵� ����\n");
			rc.rotationX = 0;
		}
		break;
	case 'X':	// ī�޶� �ٴ��� x���� �������� �� �������� ȸ���Ѵ�.
		if (rc.rotationX != 2) {
			printf("X : x�� ���� ���� �̵�\n");
			rc.rotationX = 2;
		}
		else {
			printf("X : x�� �̵� ����\n");
			rc.rotationX = 0;
		}
		break;
	case 'y':	// ī�޶� �ٴ��� y���� �������� �� �������� ȸ���Ѵ�.
		if (rc.rotationY != 1) {
			printf("y : y�� ���� ���� �̵�\n");
			rc.rotationY = 1;
		}
		else {
			printf("y : y�� �̵� ����\n");
			rc.rotationY = 0;
		}
		break;
	case 'Y':	// ī�޶� �ٴ��� y���� �������� �� �������� ȸ���Ѵ�.
		if (rc.rotationY != 2) {
			printf("Y : y�� ���� ���� �̵�\n");
			rc.rotationY = 2;
		}
		else {
			printf("Y : y�� �̵� ����\n");
			rc.rotationY = 0;
		}
		break;
	case 'r':	// �̷θ� �����Ѵ�.
	case 'R':
		printf("r : �̷� ����\n");
		if (!rc.maze) {
			mm.makeMaze();
			rc.maze = true;
			rm.drawed = true;
		}
		break;
	case 'S':	// �̷ο��� ��ü�� �����̱� �����Ѵ�.
		if (!rc.maze) {
			printf("S : ���� �̷θ� �����Ͻʽÿ�. \n");
		}
		else {
			printf("S : ��ü ������ ����. \n");
			rm.robot.movement = 1;
		}
		break;
	case 'v':	// ����ü�� �������� ���߰� ���� ���̷� ���Ѵ�.
	case 'V':
		if (!rc.maze) {
			printf("v : ���� �̷θ� �����Ͻʽÿ�. \n");
		}
		else {
			printf("v : ���� ���̷� ��ȯ. \n");
			for (int i = 0; i < mm.vertical; i++) {
				for (int j = 0; j < mm.horizontal; j++) {
					mm.mountain_list[i][j].low_height();
				}
			}
		}
		break;
	case 'w':	// ��ü �� �̵�
		if (rm.robot.movement != 0) {
			printf("w : ��ü �� �̵�. \n");
			rm.robot.movement = 1;
		}
		break;
	case 's':	// ��ü �� �̵�
		if (rm.robot.movement != 0) {
			printf("s : ��ü �� �̵�. \n");
			rm.robot.movement = 2;
		}
		break;
	case 'a':	// ��ü �� �̵�
		if (rm.robot.movement != 0) {
			printf("a : ��ü �� �̵�. \n");
			rm.robot.movement = 3;
		}
		break;
	case 'd':	// ��ü �� �̵�
		if (rm.robot.movement != 0) {
			printf("d : ��ü �� �̵�. \n");
			rm.robot.movement = 4;
		}
		break;
	case '-':	// ����ü �̵��ϴ� �ӵ� ����
	case '_':
		printf("- : ����ü �̵��ӵ� ����. \n");
		for (int i = 0; i < mm.vertical; i++) {
			for (int j = 0; j < mm.horizontal; j++) {
				mm.mountain_list[i][j].speeddown();
			}
		}
		break;
	case '=':	// ����ü �̵��ϴ� �ӵ� ����
	case '+':
		printf("+ : ����ü �̵��ӵ� ����. \n");
		for (int i = 0; i < mm.vertical; i++) {
			for (int j = 0; j < mm.horizontal; j++) {
				mm.mountain_list[i][j].speedup();
			}
		}
		break;
	case '1':	// 1��Ī ��ü ����
		printf("1 : 1��Ī ��ü ���� \n");
		rc.quarterview = false;
		break;
	case '3':	// 3��Ī ���ͺ� ����
		printf("1 : 3��Ī ���ͺ� ���� \n");
		rc.quarterview = true;
		break;
	case 'c':	// ��� �� �ʱ�ȭ
	case 'C':
		printf("c : �ʱ�ȭ \n");
		rc.reset();
		rm.reset();
		mm.reset();
		break;
	case 'q':	// ���α׷� ����
	case 'Q':
		printf("q : ���α׷� ���� \n");
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

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}
