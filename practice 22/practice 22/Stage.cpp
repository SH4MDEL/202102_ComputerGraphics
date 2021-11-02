#include "Stage.h"

Stage::Stage()
{
	allReset();

	GLfloat linear = 1.0f;	// ������ü�� ����� ���� �� ���ϴ� ������ ������ �Է����ݴϴ�.
	HeightFromGround = linear;
	//GLfloat front_left_down_x = -linear, front_left_down_y = -linear, front_left_down_z = linear;		// ������ü�� ����� ���� �� �ּ� �����մϴ�.
	//GLfloat front_left_top_x = -linear, front_left_top_y = linear, front_left_top_z = linear;
	//GLfloat front_right_down_x = linear, front_right_down_y = -linear, front_right_down_z = linear;
	//GLfloat front_right_top_x = linear, front_right_top_y = linear, front_right_top_z = linear;
	//GLfloat back_left_down_x = -linear, back_left_down_y = -linear, back_left_down_z = -linear;
	//GLfloat back_left_top_x = -linear, back_left_top_y = linear, back_left_top_z = -linear;
	//GLfloat back_right_down_x = linear, back_right_down_y = -linear, back_right_down_z = -linear;
	//GLfloat back_right_top_x = linear, back_right_top_y = linear, back_right_top_z = -linear;

	GLfloat front_left_down_x = -linear, front_left_down_y = -linear, front_left_down_z = linear;		// ������ü�� ����� ���� �� ������ �������ݴϴ�.
	GLfloat front_left_top_x = -linear, front_left_top_y = linear, front_left_top_z = linear;
	GLfloat front_right_down_x = linear, front_right_down_y = -linear, front_right_down_z = linear;
	GLfloat front_right_top_x = linear, front_right_top_y = linear, front_right_top_z = linear;
	GLfloat back_left_down_x = -linear, back_left_down_y = -linear, back_left_down_z = -linear;
	GLfloat back_left_top_x = -linear, back_left_top_y = linear, back_left_top_z = -linear;
	GLfloat back_right_down_x = linear, back_right_down_y = -linear, back_right_down_z = -linear;
	GLfloat back_right_top_x = linear, back_right_top_y = linear, back_right_top_z = -linear;

	GLfloat back_color_r = 0.1f, back_color_g = 0.1f, back_color_b = 0.1f;
	GLfloat front_color_r = 0.15f, front_color_g = 0.15f, front_color_b = 0.15f;
	GLfloat bottom_color_r = 0.2f, bottom_color_g = 0.2f, bottom_color_b = 0.2f;
	GLfloat up_color_r = 0.25f, up_color_g = 0.25f, up_color_b = 0.25f;
	GLfloat left_color_r = 0.3f, left_color_g = 0.3f, left_color_b = 0.3f;
	GLfloat right_color_r = 0.35f, right_color_g = 0.35f, right_color_b = 0.35f;

	// ���� ��ǥ
	data[0][0][0][0][0] = front_left_down_x, data[0][0][0][0][1] = front_left_down_y, data[0][0][0][0][2] = front_left_down_z;
	data[0][0][0][1][0] = front_right_down_x, data[0][0][0][1][1] = front_right_down_y, data[0][0][0][1][2] = front_right_down_z;
	data[0][0][0][2][0] = front_left_top_x, data[0][0][0][2][1] = front_left_top_y, data[0][0][0][2][2] = front_left_top_z;

	data[0][0][1][0][0] = front_left_top_x, data[0][0][1][0][1] = front_left_top_y, data[0][0][1][0][2] = front_left_top_z;
	data[0][0][1][1][0] = front_right_down_x, data[0][0][1][1][1] = front_right_down_y, data[0][0][1][1][2] = front_right_down_z;
	data[0][0][1][2][0] = front_right_top_x, data[0][0][1][2][1] = front_right_top_y, data[0][0][1][2][2] = front_right_top_z;

	// ���� ����
	data[0][1][0][0][0] = front_color_r, data[0][1][0][0][1] = front_color_g, data[0][1][0][0][2] = front_color_b;
	data[0][1][0][1][0] = front_color_r, data[0][1][0][1][1] = front_color_g, data[0][1][0][1][2] = front_color_b;
	data[0][1][0][2][0] = front_color_r, data[0][1][0][2][1] = front_color_g, data[0][1][0][2][2] = front_color_b;

	data[0][1][1][0][0] = front_color_r, data[0][1][1][0][1] = front_color_g, data[0][1][1][0][2] = front_color_b;
	data[0][1][1][1][0] = front_color_r, data[0][1][1][1][1] = front_color_g, data[0][1][1][1][2] = front_color_b;
	data[0][1][1][2][0] = front_color_r, data[0][1][1][2][1] = front_color_g, data[0][1][1][2][2] = front_color_b;


	// ��� ��ǥ
	data[1][0][0][0][0] = front_right_top_x, data[1][0][0][0][1] = front_right_top_y, data[1][0][0][0][2] = front_right_top_z;
	data[1][0][0][1][0] = back_right_top_x, data[1][0][0][1][1] = back_right_top_y, data[1][0][0][1][2] = back_right_top_z;
	data[1][0][0][2][0] = front_left_top_x, data[1][0][0][2][1] = front_left_top_y, data[1][0][0][2][2] = front_left_top_z;

	data[1][0][1][0][0] = front_left_top_x, data[1][0][1][0][1] = front_left_top_y, data[1][0][1][0][2] = front_left_top_z;
	data[1][0][1][1][0] = back_right_top_x, data[1][0][1][1][1] = back_right_top_y, data[1][0][1][1][2] = back_right_top_z;
	data[1][0][1][2][0] = back_left_top_x, data[1][0][1][2][1] = back_left_top_y, data[1][0][1][2][2] = back_left_top_z;

	// ��� ����
	data[1][1][0][0][0] = up_color_r, data[1][1][0][0][1] = up_color_g, data[1][1][0][0][2] = up_color_b;
	data[1][1][0][1][0] = up_color_r, data[1][1][0][1][1] = up_color_g, data[1][1][0][1][2] = up_color_b;
	data[1][1][0][2][0] = up_color_r, data[1][1][0][2][1] = up_color_g, data[1][1][0][2][2] = up_color_b;

	data[1][1][1][0][0] = up_color_r, data[1][1][1][0][1] = up_color_g, data[1][1][1][0][2] = up_color_b;
	data[1][1][1][1][0] = up_color_r, data[1][1][1][1][1] = up_color_g, data[1][1][1][1][2] = up_color_b;
	data[1][1][1][2][0] = up_color_r, data[1][1][1][2][1] = up_color_g, data[1][1][1][2][2] = up_color_b;

	// ���� ��ǥ
	data[2][0][0][0][0] = back_left_top_x, data[2][0][0][0][1] = back_left_top_y, data[2][0][0][0][2] = back_left_top_z;
	data[2][0][0][1][0] = back_left_down_x, data[2][0][0][1][1] = back_left_down_y, data[2][0][0][1][2] = back_left_down_z;
	data[2][0][0][2][0] = front_left_down_x, data[2][0][0][2][1] = front_left_down_y, data[2][0][0][2][2] = front_left_down_z;

	data[2][0][1][0][0] = front_left_down_x, data[2][0][1][0][1] = front_left_down_y, data[2][0][1][0][2] = front_left_down_z;
	data[2][0][1][1][0] = front_left_top_x, data[2][0][1][1][1] = front_left_top_y, data[2][0][1][1][2] = front_left_top_z;
	data[2][0][1][2][0] = back_left_top_x, data[2][0][1][2][1] = back_left_top_y, data[2][0][1][2][2] = back_left_top_z;

	// ���� ����
	data[2][1][0][0][0] = left_color_r, data[2][1][0][0][1] = left_color_g, data[2][1][0][0][2] = left_color_b;
	data[2][1][0][1][0] = left_color_r, data[2][1][0][1][1] = left_color_g, data[2][1][0][1][2] = left_color_b;
	data[2][1][0][2][0] = left_color_r, data[2][1][0][2][1] = left_color_g, data[2][1][0][2][2] = left_color_b;

	data[2][1][1][0][0] = left_color_r, data[2][1][1][0][1] = left_color_g, data[2][1][1][0][2] = left_color_b;
	data[2][1][1][1][0] = left_color_r, data[2][1][1][1][1] = left_color_g, data[2][1][1][1][2] = left_color_b;
	data[2][1][1][2][0] = left_color_r, data[2][1][1][2][1] = left_color_g, data[2][1][1][2][2] = left_color_b;

	// �ĸ� ��ǥ
	data[3][0][0][0][0] = back_left_top_x, data[3][0][0][0][1] = back_left_top_y, data[3][0][0][0][2] = back_left_top_z;
	data[3][0][0][1][0] = back_left_down_x, data[3][0][0][1][1] = back_left_down_y, data[3][0][0][1][2] = back_left_down_z;
	data[3][0][0][2][0] = back_right_top_x, data[3][0][0][2][1] = back_right_top_y, data[3][0][0][2][2] = back_right_top_z;

	data[3][0][1][0][0] = back_right_top_x, data[3][0][1][0][1] = back_right_top_y, data[3][0][1][0][2] = back_right_top_z;
	data[3][0][1][1][0] = back_left_down_x, data[3][0][1][1][1] = back_left_down_y, data[3][0][1][1][2] = back_left_down_z;
	data[3][0][1][2][0] = back_right_down_x, data[3][0][1][2][1] = back_right_down_y, data[3][0][1][2][2] = back_right_down_z;

	// �ĸ� ����
	data[3][1][0][0][0] = back_color_r, data[3][1][0][0][1] = back_color_g, data[3][1][0][0][2] = back_color_b;
	data[3][1][0][1][0] = back_color_r, data[3][1][0][1][1] = back_color_g, data[3][1][0][1][2] = back_color_b;
	data[3][1][0][2][0] = back_color_r, data[3][1][0][2][1] = back_color_g, data[3][1][0][2][2] = back_color_b;

	data[3][1][1][0][0] = back_color_r, data[3][1][1][0][1] = back_color_g, data[3][1][1][0][2] = back_color_b;
	data[3][1][1][1][0] = back_color_r, data[3][1][1][1][1] = back_color_g, data[3][1][1][1][2] = back_color_b;
	data[3][1][1][2][0] = back_color_r, data[3][1][1][2][1] = back_color_g, data[3][1][1][2][2] = back_color_b;

	// �ϴ� ��ǥ
	data[4][0][0][0][0] = back_right_down_x, data[4][0][0][0][1] = back_right_down_y, data[4][0][0][0][2] = back_right_down_z;
	data[4][0][0][1][0] = front_right_down_x, data[4][0][0][1][1] = front_right_down_y, data[4][0][0][1][2] = front_right_down_z;
	data[4][0][0][2][0] = front_left_down_x, data[4][0][0][2][1] = front_left_down_y, data[4][0][0][2][2] = front_left_down_z;

	data[4][0][1][0][0] = front_left_down_x, data[4][0][1][0][1] = front_left_down_y, data[4][0][1][0][2] = front_left_down_z;
	data[4][0][1][1][0] = back_left_down_x, data[4][0][1][1][1] = back_left_down_y, data[4][0][1][1][2] = back_left_down_z;
	data[4][0][1][2][0] = back_right_down_x, data[4][0][1][2][1] = back_right_down_y, data[4][0][1][2][2] = back_right_down_z;

	// �ϴ� ����
	data[4][1][0][0][0] = bottom_color_r, data[4][1][0][0][1] = bottom_color_g, data[4][1][0][0][2] = bottom_color_b;
	data[4][1][0][1][0] = bottom_color_r, data[4][1][0][1][1] = bottom_color_g, data[4][1][0][1][2] = bottom_color_b;
	data[4][1][0][2][0] = bottom_color_r, data[4][1][0][2][1] = bottom_color_g, data[4][1][0][2][2] = bottom_color_b;

	data[4][1][1][0][0] = bottom_color_r, data[4][1][1][0][1] = bottom_color_g, data[4][1][1][0][2] = bottom_color_b;
	data[4][1][1][1][0] = bottom_color_r, data[4][1][1][1][1] = bottom_color_g, data[4][1][1][1][2] = bottom_color_b;
	data[4][1][1][2][0] = bottom_color_r, data[4][1][1][2][1] = bottom_color_g, data[4][1][1][2][2] = bottom_color_b;

	// ���� ��ǥ
	data[5][0][0][0][0] = back_right_down_x, data[5][0][0][0][1] = back_right_down_y, data[5][0][0][0][2] = back_right_down_z;
	data[5][0][0][1][0] = back_right_top_x, data[5][0][0][1][1] = back_right_top_y, data[5][0][0][1][2] = back_right_top_z;
	data[5][0][0][2][0] = front_right_down_x, data[5][0][0][2][1] = front_right_down_y, data[5][0][0][2][2] = front_right_down_z;

	data[5][0][1][0][0] = front_right_down_x, data[5][0][1][0][1] = front_right_down_y, data[5][0][1][0][2] = front_right_down_z;
	data[5][0][1][1][0] = back_right_top_x, data[5][0][1][1][1] = back_right_top_y, data[5][0][1][1][2] = back_right_top_z;
	data[5][0][1][2][0] = front_right_top_x, data[5][0][1][2][1] = front_right_top_y, data[5][0][1][2][2] = front_right_top_z;

	// ���� ����
	data[5][1][0][0][0] = right_color_r, data[5][1][0][0][1] = right_color_g, data[5][1][0][0][2] = right_color_b;
	data[5][1][0][1][0] = right_color_r, data[5][1][0][1][1] = right_color_g, data[5][1][0][1][2] = right_color_b;
	data[5][1][0][2][0] = right_color_r, data[5][1][0][2][1] = right_color_g, data[5][1][0][2][2] = right_color_b;

	data[5][1][1][0][0] = right_color_r, data[5][1][1][0][1] = right_color_g, data[5][1][1][0][2] = right_color_b;
	data[5][1][1][1][0] = right_color_r, data[5][1][1][1][1] = right_color_g, data[5][1][1][1][2] = right_color_b;
	data[5][1][1][2][0] = right_color_r, data[5][1][1][2][1] = right_color_g, data[5][1][1][2][2] = right_color_b;
}

void Stage::initBuffer()
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

void Stage::draw()
{
	for (int i = 0; i < 3; i++) {
		glBindVertexArray(vao[i]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	for (int i = 4; i < 6; i++) {
		glBindVertexArray(vao[i]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void Stage::allReset()
{
	opendoor = false;
	opendoorPos = 0.0f;
}

void Stage::update()
{
	if (opendoor) {
		if (opendoorPos < 90.0f) {
			opendoorPos += 1.0f;
		}
	}
	else {
		if (opendoorPos > 0.0f) {
			opendoorPos -= 1.0f;
		}
	}
}

void Stage::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::translate(myFactor, glm::vec3(0.0f, HeightFromGround, 0.0f));	// �⺻���� ������ ��ü�� ��ġ
}

glm::mat4 Stage::getFactor()
{
	return myFactor;
}

void Stage::putDoorFactor(glm::mat4 inputFactor)
{
	myDoorFactor = inputFactor;
	myDoorFactor = glm::translate(myDoorFactor, glm::vec3(0.0f, 1.0f, -1.0f));
	myDoorFactor = glm::rotate(myDoorFactor, glm::radians(opendoorPos), glm::vec3(1.0f, 0.0f, 0.0f));
	myDoorFactor = glm::translate(myDoorFactor, glm::vec3(0.0f, -1.0f, 1.0f));
}

glm::mat4 Stage::getDoorFactor()
{
	return myDoorFactor;
}

void Stage::drawDoor()
{
	glBindVertexArray(vao[3]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
