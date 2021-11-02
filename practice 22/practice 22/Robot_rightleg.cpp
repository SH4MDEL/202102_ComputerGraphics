#include "Robot_rightleg.h"

Robot_rightleg::Robot_rightleg()
{
	allReset();

	//GLfloat linear = size(gen) / 100.0f;	// 정육면체를 만들고 싶을 때 원하는 길이의 절반을 입력해줍니다.
	//HeightFromGround = linear;
	//GLfloat front_left_down_x = -linear, front_left_down_y = -linear, front_left_down_z = linear;		// 정육면체를 만들고 싶을 때 주석 해제합니다.
	//GLfloat front_left_top_x = -linear, front_left_top_y = linear, front_left_top_z = linear;
	//GLfloat front_right_down_x = linear, front_right_down_y = -linear, front_right_down_z = linear;
	//GLfloat front_right_top_x = linear, front_right_top_y = linear, front_right_top_z = linear;
	//GLfloat back_left_down_x = -linear, back_left_down_y = -linear, back_left_down_z = -linear;
	//GLfloat back_left_top_x = -linear, back_left_top_y = linear, back_left_top_z = -linear;
	//GLfloat back_right_down_x = linear, back_right_down_y = -linear, back_right_down_z = -linear;
	//GLfloat back_right_top_x = linear, back_right_top_y = linear, back_right_top_z = -linear;

	GLfloat front_left_down_x = -0.05f, front_left_down_y = -0.2f, front_left_down_z = 0.05f;		// 직육면체를 만들고 싶을 때 적절히 수정해줍니다.
	GLfloat front_left_top_x = -0.05f, front_left_top_y = 0.2f, front_left_top_z = 0.05f;
	GLfloat front_right_down_x = 0.05f, front_right_down_y = -0.2f, front_right_down_z = 0.05f;
	GLfloat front_right_top_x = 0.05f, front_right_top_y = 0.2f, front_right_top_z = 0.05f;
	GLfloat back_left_down_x = -0.05f, back_left_down_y = -0.2f, back_left_down_z = -0.05f;
	GLfloat back_left_top_x = -0.05f, back_left_top_y = 0.2f, back_left_top_z = -0.05f;
	GLfloat back_right_down_x = 0.05f, back_right_down_y = -0.2f, back_right_down_z = -0.05f;
	GLfloat back_right_top_x = 0.05f, back_right_top_y = 0.2f, back_right_top_z = -0.05f;

	GLfloat back_color_r = 1.0f, back_color_g = 1.0f, back_color_b = 0.0f;
	GLfloat front_color_r = back_color_r, front_color_g = back_color_g, front_color_b = back_color_b;
	GLfloat bottom_color_r = back_color_r, bottom_color_g = back_color_g, bottom_color_b = back_color_b;
	GLfloat up_color_r = back_color_r, up_color_g = back_color_g, up_color_b = back_color_b;
	GLfloat left_color_r = back_color_r, left_color_g = back_color_g, left_color_b = back_color_b;
	GLfloat right_color_r = back_color_r, right_color_g = back_color_g, right_color_b = back_color_b;

	//printf("%d\n", color(gen));

	// 전면 좌표
	data[0][0][0][0][0] = front_left_down_x, data[0][0][0][0][1] = front_left_down_y, data[0][0][0][0][2] = front_left_down_z;
	data[0][0][0][1][0] = front_right_down_x, data[0][0][0][1][1] = front_right_down_y, data[0][0][0][1][2] = front_right_down_z;
	data[0][0][0][2][0] = front_left_top_x, data[0][0][0][2][1] = front_left_top_y, data[0][0][0][2][2] = front_left_top_z;

	data[0][0][1][0][0] = front_left_top_x, data[0][0][1][0][1] = front_left_top_y, data[0][0][1][0][2] = front_left_top_z;
	data[0][0][1][1][0] = front_right_down_x, data[0][0][1][1][1] = front_right_down_y, data[0][0][1][1][2] = front_right_down_z;
	data[0][0][1][2][0] = front_right_top_x, data[0][0][1][2][1] = front_right_top_y, data[0][0][1][2][2] = front_right_top_z;

	// 전면 색상
	data[0][1][0][0][0] = front_color_r, data[0][1][0][0][1] = front_color_g, data[0][1][0][0][2] = front_color_b;
	data[0][1][0][1][0] = front_color_r, data[0][1][0][1][1] = front_color_g, data[0][1][0][1][2] = front_color_b;
	data[0][1][0][2][0] = front_color_r, data[0][1][0][2][1] = front_color_g, data[0][1][0][2][2] = front_color_b;

	data[0][1][1][0][0] = front_color_r, data[0][1][1][0][1] = front_color_g, data[0][1][1][0][2] = front_color_b;
	data[0][1][1][1][0] = front_color_r, data[0][1][1][1][1] = front_color_g, data[0][1][1][1][2] = front_color_b;
	data[0][1][1][2][0] = front_color_r, data[0][1][1][2][1] = front_color_g, data[0][1][1][2][2] = front_color_b;


	// 상단 좌표
	data[1][0][0][0][0] = front_right_top_x, data[1][0][0][0][1] = front_right_top_y, data[1][0][0][0][2] = front_right_top_z;
	data[1][0][0][1][0] = back_right_top_x, data[1][0][0][1][1] = back_right_top_y, data[1][0][0][1][2] = back_right_top_z;
	data[1][0][0][2][0] = front_left_top_x, data[1][0][0][2][1] = front_left_top_y, data[1][0][0][2][2] = front_left_top_z;

	data[1][0][1][0][0] = front_left_top_x, data[1][0][1][0][1] = front_left_top_y, data[1][0][1][0][2] = front_left_top_z;
	data[1][0][1][1][0] = back_right_top_x, data[1][0][1][1][1] = back_right_top_y, data[1][0][1][1][2] = back_right_top_z;
	data[1][0][1][2][0] = back_left_top_x, data[1][0][1][2][1] = back_left_top_y, data[1][0][1][2][2] = back_left_top_z;

	// 상단 색상
	data[1][1][0][0][0] = up_color_r, data[1][1][0][0][1] = up_color_g, data[1][1][0][0][2] = up_color_b;
	data[1][1][0][1][0] = up_color_r, data[1][1][0][1][1] = up_color_g, data[1][1][0][1][2] = up_color_b;
	data[1][1][0][2][0] = up_color_r, data[1][1][0][2][1] = up_color_g, data[1][1][0][2][2] = up_color_b;

	data[1][1][1][0][0] = up_color_r, data[1][1][1][0][1] = up_color_g, data[1][1][1][0][2] = up_color_b;
	data[1][1][1][1][0] = up_color_r, data[1][1][1][1][1] = up_color_g, data[1][1][1][1][2] = up_color_b;
	data[1][1][1][2][0] = up_color_r, data[1][1][1][2][1] = up_color_g, data[1][1][1][2][2] = up_color_b;

	// 좌측 좌표
	data[2][0][0][0][0] = back_left_top_x, data[2][0][0][0][1] = back_left_top_y, data[2][0][0][0][2] = back_left_top_z;
	data[2][0][0][1][0] = back_left_down_x, data[2][0][0][1][1] = back_left_down_y, data[2][0][0][1][2] = back_left_down_z;
	data[2][0][0][2][0] = front_left_down_x, data[2][0][0][2][1] = front_left_down_y, data[2][0][0][2][2] = front_left_down_z;

	data[2][0][1][0][0] = front_left_down_x, data[2][0][1][0][1] = front_left_down_y, data[2][0][1][0][2] = front_left_down_z;
	data[2][0][1][1][0] = front_left_top_x, data[2][0][1][1][1] = front_left_top_y, data[2][0][1][1][2] = front_left_top_z;
	data[2][0][1][2][0] = back_left_top_x, data[2][0][1][2][1] = back_left_top_y, data[2][0][1][2][2] = back_left_top_z;

	// 좌측 색상
	data[2][1][0][0][0] = left_color_r, data[2][1][0][0][1] = left_color_g, data[2][1][0][0][2] = left_color_b;
	data[2][1][0][1][0] = left_color_r, data[2][1][0][1][1] = left_color_g, data[2][1][0][1][2] = left_color_b;
	data[2][1][0][2][0] = left_color_r, data[2][1][0][2][1] = left_color_g, data[2][1][0][2][2] = left_color_b;

	data[2][1][1][0][0] = left_color_r, data[2][1][1][0][1] = left_color_g, data[2][1][1][0][2] = left_color_b;
	data[2][1][1][1][0] = left_color_r, data[2][1][1][1][1] = left_color_g, data[2][1][1][1][2] = left_color_b;
	data[2][1][1][2][0] = left_color_r, data[2][1][1][2][1] = left_color_g, data[2][1][1][2][2] = left_color_b;

	// 후면 좌표
	data[3][0][0][0][0] = back_left_top_x, data[3][0][0][0][1] = back_left_top_y, data[3][0][0][0][2] = back_left_top_z;
	data[3][0][0][1][0] = back_left_down_x, data[3][0][0][1][1] = back_left_down_y, data[3][0][0][1][2] = back_left_down_z;
	data[3][0][0][2][0] = back_right_top_x, data[3][0][0][2][1] = back_right_top_y, data[3][0][0][2][2] = back_right_top_z;

	data[3][0][1][0][0] = back_right_top_x, data[3][0][1][0][1] = back_right_top_y, data[3][0][1][0][2] = back_right_top_z;
	data[3][0][1][1][0] = back_left_down_x, data[3][0][1][1][1] = back_left_down_y, data[3][0][1][1][2] = back_left_down_z;
	data[3][0][1][2][0] = back_right_down_x, data[3][0][1][2][1] = back_right_down_y, data[3][0][1][2][2] = back_right_down_z;

	// 후면 색상
	data[3][1][0][0][0] = back_color_r, data[3][1][0][0][1] = back_color_g, data[3][1][0][0][2] = back_color_b;
	data[3][1][0][1][0] = back_color_r, data[3][1][0][1][1] = back_color_g, data[3][1][0][1][2] = back_color_b;
	data[3][1][0][2][0] = back_color_r, data[3][1][0][2][1] = back_color_g, data[3][1][0][2][2] = back_color_b;

	data[3][1][1][0][0] = back_color_r, data[3][1][1][0][1] = back_color_g, data[3][1][1][0][2] = back_color_b;
	data[3][1][1][1][0] = back_color_r, data[3][1][1][1][1] = back_color_g, data[3][1][1][1][2] = back_color_b;
	data[3][1][1][2][0] = back_color_r, data[3][1][1][2][1] = back_color_g, data[3][1][1][2][2] = back_color_b;

	// 하단 좌표
	data[4][0][0][0][0] = back_right_down_x, data[4][0][0][0][1] = back_right_down_y, data[4][0][0][0][2] = back_right_down_z;
	data[4][0][0][1][0] = front_right_down_x, data[4][0][0][1][1] = front_right_down_y, data[4][0][0][1][2] = front_right_down_z;
	data[4][0][0][2][0] = front_left_down_x, data[4][0][0][2][1] = front_left_down_y, data[4][0][0][2][2] = front_left_down_z;

	data[4][0][1][0][0] = front_left_down_x, data[4][0][1][0][1] = front_left_down_y, data[4][0][1][0][2] = front_left_down_z;
	data[4][0][1][1][0] = back_left_down_x, data[4][0][1][1][1] = back_left_down_y, data[4][0][1][1][2] = back_left_down_z;
	data[4][0][1][2][0] = back_right_down_x, data[4][0][1][2][1] = back_right_down_y, data[4][0][1][2][2] = back_right_down_z;

	// 하단 색상
	data[4][1][0][0][0] = bottom_color_r, data[4][1][0][0][1] = bottom_color_g, data[4][1][0][0][2] = bottom_color_b;
	data[4][1][0][1][0] = bottom_color_r, data[4][1][0][1][1] = bottom_color_g, data[4][1][0][1][2] = bottom_color_b;
	data[4][1][0][2][0] = bottom_color_r, data[4][1][0][2][1] = bottom_color_g, data[4][1][0][2][2] = bottom_color_b;

	data[4][1][1][0][0] = bottom_color_r, data[4][1][1][0][1] = bottom_color_g, data[4][1][1][0][2] = bottom_color_b;
	data[4][1][1][1][0] = bottom_color_r, data[4][1][1][1][1] = bottom_color_g, data[4][1][1][1][2] = bottom_color_b;
	data[4][1][1][2][0] = bottom_color_r, data[4][1][1][2][1] = bottom_color_g, data[4][1][1][2][2] = bottom_color_b;

	// 우측 좌표
	data[5][0][0][0][0] = back_right_down_x, data[5][0][0][0][1] = back_right_down_y, data[5][0][0][0][2] = back_right_down_z;
	data[5][0][0][1][0] = back_right_top_x, data[5][0][0][1][1] = back_right_top_y, data[5][0][0][1][2] = back_right_top_z;
	data[5][0][0][2][0] = front_right_down_x, data[5][0][0][2][1] = front_right_down_y, data[5][0][0][2][2] = front_right_down_z;

	data[5][0][1][0][0] = front_right_down_x, data[5][0][1][0][1] = front_right_down_y, data[5][0][1][0][2] = front_right_down_z;
	data[5][0][1][1][0] = back_right_top_x, data[5][0][1][1][1] = back_right_top_y, data[5][0][1][1][2] = back_right_top_z;
	data[5][0][1][2][0] = front_right_top_x, data[5][0][1][2][1] = front_right_top_y, data[5][0][1][2][2] = front_right_top_z;

	// 우측 색상
	data[5][1][0][0][0] = right_color_r, data[5][1][0][0][1] = right_color_g, data[5][1][0][0][2] = right_color_b;
	data[5][1][0][1][0] = right_color_r, data[5][1][0][1][1] = right_color_g, data[5][1][0][1][2] = right_color_b;
	data[5][1][0][2][0] = right_color_r, data[5][1][0][2][1] = right_color_g, data[5][1][0][2][2] = right_color_b;

	data[5][1][1][0][0] = right_color_r, data[5][1][1][0][1] = right_color_g, data[5][1][1][0][2] = right_color_b;
	data[5][1][1][1][0] = right_color_r, data[5][1][1][1][1] = right_color_g, data[5][1][1][1][2] = right_color_b;
	data[5][1][1][2][0] = right_color_r, data[5][1][1][2][1] = right_color_g, data[5][1][1][2][2] = right_color_b;
}

void Robot_rightleg::initBuffer()
{
	glGenVertexArrays(6, vao);
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(vao[i]);
		glGenBuffers(2, vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}
}

void Robot_rightleg::draw()
{
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(vao[i]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void Robot_rightleg::allReset()
{
	HeightFromGround = -0.4f;
	hanging = true;
	hangingPos = -45.0f;
}

void Robot_rightleg::update()
{
	if (hanging) {
		if (hangingPos >= 45.0f) {
			hangingPos = 44.0f;
			hanging = false;
		}
		else {
			hangingPos += 1.0f;
		}
	}
	else {
		if (hangingPos <= -45.0f) {
			hangingPos = -44.0f;
			hanging = true;
		}
		else {
			hangingPos -= 1.0f;
		}
	}
}

void Robot_rightleg::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::translate(myFactor, glm::vec3(0.1f, HeightFromGround, 0.0f));	// 기본으로 세팅할 객체의 위치
	myFactor = glm::translate(myFactor, glm::vec3(0.0f, 0.2f, 0.0f));
	myFactor = glm::rotate(myFactor, glm::radians(hangingPos), glm::vec3(1.0f, 0.0f, 0.0f));
	myFactor = glm::translate(myFactor, glm::vec3(0.0f, -0.2f, 0.0f));
}

glm::mat4 Robot_rightleg::getFactor()
{
	return myFactor;
}

