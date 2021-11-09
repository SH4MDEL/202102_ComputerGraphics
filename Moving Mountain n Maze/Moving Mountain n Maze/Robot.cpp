#include "robot.h"

Robot::Robot()
{
	allReset();

	// body

	GLfloat front_left_down_x = -0.02f, front_left_down_y = -0.02f, front_left_down_z = 0.01f;		// 직육면체를 만들고 싶을 때 적절히 수정해줍니다.
	GLfloat front_left_top_x = -0.02f, front_left_top_y = 0.02f, front_left_top_z = 0.01f;
	GLfloat front_right_down_x = 0.02f, front_right_down_y = -0.02f, front_right_down_z = 0.01f;
	GLfloat front_right_top_x = 0.02f, front_right_top_y = 0.02f, front_right_top_z = 0.01f;
	GLfloat back_left_down_x = -0.02f, back_left_down_y = -0.02f, back_left_down_z = -0.01f;
	GLfloat back_left_top_x = -0.02f, back_left_top_y = 0.02f, back_left_top_z = -0.01f;
	GLfloat back_right_down_x = 0.02f, back_right_down_y = -0.02f, back_right_down_z = -0.01f;
	GLfloat back_right_top_x = 0.02f, back_right_top_y = 0.02f, back_right_top_z = -0.01f;

	GLfloat back_color_r = 0.0f, back_color_g = 0.0f, back_color_b = 1.0f;
	GLfloat front_color_r = back_color_r, front_color_g = back_color_g, front_color_b = back_color_b;
	GLfloat bottom_color_r = back_color_r, bottom_color_g = back_color_g, bottom_color_b = back_color_b;
	GLfloat up_color_r = back_color_r, up_color_g = back_color_g, up_color_b = back_color_b;
	GLfloat left_color_r = back_color_r, left_color_g = back_color_g, left_color_b = back_color_b;
	GLfloat right_color_r = back_color_r, right_color_g = back_color_g, right_color_b = back_color_b;

	//printf("%d\n", color(gen));

	// 전면 좌표
	body[0][0][0][0][0] = front_left_down_x, body[0][0][0][0][1] = front_left_down_y, body[0][0][0][0][2] = front_left_down_z;
	body[0][0][0][1][0] = front_right_down_x, body[0][0][0][1][1] = front_right_down_y, body[0][0][0][1][2] = front_right_down_z;
	body[0][0][0][2][0] = front_left_top_x, body[0][0][0][2][1] = front_left_top_y, body[0][0][0][2][2] = front_left_top_z;

	body[0][0][1][0][0] = front_left_top_x, body[0][0][1][0][1] = front_left_top_y, body[0][0][1][0][2] = front_left_top_z;
	body[0][0][1][1][0] = front_right_down_x, body[0][0][1][1][1] = front_right_down_y, body[0][0][1][1][2] = front_right_down_z;
	body[0][0][1][2][0] = front_right_top_x, body[0][0][1][2][1] = front_right_top_y, body[0][0][1][2][2] = front_right_top_z;

	// 전면 색상
	body[0][1][0][0][0] = front_color_r, body[0][1][0][0][1] = front_color_g, body[0][1][0][0][2] = front_color_b;
	body[0][1][0][1][0] = front_color_r, body[0][1][0][1][1] = front_color_g, body[0][1][0][1][2] = front_color_b;
	body[0][1][0][2][0] = front_color_r, body[0][1][0][2][1] = front_color_g, body[0][1][0][2][2] = front_color_b;

	body[0][1][1][0][0] = front_color_r, body[0][1][1][0][1] = front_color_g, body[0][1][1][0][2] = front_color_b;
	body[0][1][1][1][0] = front_color_r, body[0][1][1][1][1] = front_color_g, body[0][1][1][1][2] = front_color_b;
	body[0][1][1][2][0] = front_color_r, body[0][1][1][2][1] = front_color_g, body[0][1][1][2][2] = front_color_b;


	// 상단 좌표
	body[1][0][0][0][0] = front_right_top_x, body[1][0][0][0][1] = front_right_top_y, body[1][0][0][0][2] = front_right_top_z;
	body[1][0][0][1][0] = back_right_top_x, body[1][0][0][1][1] = back_right_top_y, body[1][0][0][1][2] = back_right_top_z;
	body[1][0][0][2][0] = front_left_top_x, body[1][0][0][2][1] = front_left_top_y, body[1][0][0][2][2] = front_left_top_z;

	body[1][0][1][0][0] = front_left_top_x, body[1][0][1][0][1] = front_left_top_y, body[1][0][1][0][2] = front_left_top_z;
	body[1][0][1][1][0] = back_right_top_x, body[1][0][1][1][1] = back_right_top_y, body[1][0][1][1][2] = back_right_top_z;
	body[1][0][1][2][0] = back_left_top_x, body[1][0][1][2][1] = back_left_top_y, body[1][0][1][2][2] = back_left_top_z;

	// 상단 색상
	body[1][1][0][0][0] = up_color_r, body[1][1][0][0][1] = up_color_g, body[1][1][0][0][2] = up_color_b;
	body[1][1][0][1][0] = up_color_r, body[1][1][0][1][1] = up_color_g, body[1][1][0][1][2] = up_color_b;
	body[1][1][0][2][0] = up_color_r, body[1][1][0][2][1] = up_color_g, body[1][1][0][2][2] = up_color_b;

	body[1][1][1][0][0] = up_color_r, body[1][1][1][0][1] = up_color_g, body[1][1][1][0][2] = up_color_b;
	body[1][1][1][1][0] = up_color_r, body[1][1][1][1][1] = up_color_g, body[1][1][1][1][2] = up_color_b;
	body[1][1][1][2][0] = up_color_r, body[1][1][1][2][1] = up_color_g, body[1][1][1][2][2] = up_color_b;

	// 좌측 좌표
	body[2][0][0][0][0] = back_left_top_x, body[2][0][0][0][1] = back_left_top_y, body[2][0][0][0][2] = back_left_top_z;
	body[2][0][0][1][0] = back_left_down_x, body[2][0][0][1][1] = back_left_down_y, body[2][0][0][1][2] = back_left_down_z;
	body[2][0][0][2][0] = front_left_down_x, body[2][0][0][2][1] = front_left_down_y, body[2][0][0][2][2] = front_left_down_z;

	body[2][0][1][0][0] = front_left_down_x, body[2][0][1][0][1] = front_left_down_y, body[2][0][1][0][2] = front_left_down_z;
	body[2][0][1][1][0] = front_left_top_x, body[2][0][1][1][1] = front_left_top_y, body[2][0][1][1][2] = front_left_top_z;
	body[2][0][1][2][0] = back_left_top_x, body[2][0][1][2][1] = back_left_top_y, body[2][0][1][2][2] = back_left_top_z;

	// 좌측 색상
	body[2][1][0][0][0] = left_color_r, body[2][1][0][0][1] = left_color_g, body[2][1][0][0][2] = left_color_b;
	body[2][1][0][1][0] = left_color_r, body[2][1][0][1][1] = left_color_g, body[2][1][0][1][2] = left_color_b;
	body[2][1][0][2][0] = left_color_r, body[2][1][0][2][1] = left_color_g, body[2][1][0][2][2] = left_color_b;

	body[2][1][1][0][0] = left_color_r, body[2][1][1][0][1] = left_color_g, body[2][1][1][0][2] = left_color_b;
	body[2][1][1][1][0] = left_color_r, body[2][1][1][1][1] = left_color_g, body[2][1][1][1][2] = left_color_b;
	body[2][1][1][2][0] = left_color_r, body[2][1][1][2][1] = left_color_g, body[2][1][1][2][2] = left_color_b;

	// 후면 좌표
	body[3][0][0][0][0] = back_left_top_x, body[3][0][0][0][1] = back_left_top_y, body[3][0][0][0][2] = back_left_top_z;
	body[3][0][0][1][0] = back_left_down_x, body[3][0][0][1][1] = back_left_down_y, body[3][0][0][1][2] = back_left_down_z;
	body[3][0][0][2][0] = back_right_top_x, body[3][0][0][2][1] = back_right_top_y, body[3][0][0][2][2] = back_right_top_z;

	body[3][0][1][0][0] = back_right_top_x, body[3][0][1][0][1] = back_right_top_y, body[3][0][1][0][2] = back_right_top_z;
	body[3][0][1][1][0] = back_left_down_x, body[3][0][1][1][1] = back_left_down_y, body[3][0][1][1][2] = back_left_down_z;
	body[3][0][1][2][0] = back_right_down_x, body[3][0][1][2][1] = back_right_down_y, body[3][0][1][2][2] = back_right_down_z;

	// 후면 색상
	body[3][1][0][0][0] = back_color_r, body[3][1][0][0][1] = back_color_g, body[3][1][0][0][2] = back_color_b;
	body[3][1][0][1][0] = back_color_r, body[3][1][0][1][1] = back_color_g, body[3][1][0][1][2] = back_color_b;
	body[3][1][0][2][0] = back_color_r, body[3][1][0][2][1] = back_color_g, body[3][1][0][2][2] = back_color_b;

	body[3][1][1][0][0] = back_color_r, body[3][1][1][0][1] = back_color_g, body[3][1][1][0][2] = back_color_b;
	body[3][1][1][1][0] = back_color_r, body[3][1][1][1][1] = back_color_g, body[3][1][1][1][2] = back_color_b;
	body[3][1][1][2][0] = back_color_r, body[3][1][1][2][1] = back_color_g, body[3][1][1][2][2] = back_color_b;

	// 하단 좌표
	body[4][0][0][0][0] = back_right_down_x, body[4][0][0][0][1] = back_right_down_y, body[4][0][0][0][2] = back_right_down_z;
	body[4][0][0][1][0] = front_right_down_x, body[4][0][0][1][1] = front_right_down_y, body[4][0][0][1][2] = front_right_down_z;
	body[4][0][0][2][0] = front_left_down_x, body[4][0][0][2][1] = front_left_down_y, body[4][0][0][2][2] = front_left_down_z;

	body[4][0][1][0][0] = front_left_down_x, body[4][0][1][0][1] = front_left_down_y, body[4][0][1][0][2] = front_left_down_z;
	body[4][0][1][1][0] = back_left_down_x, body[4][0][1][1][1] = back_left_down_y, body[4][0][1][1][2] = back_left_down_z;
	body[4][0][1][2][0] = back_right_down_x, body[4][0][1][2][1] = back_right_down_y, body[4][0][1][2][2] = back_right_down_z;

	// 하단 색상
	body[4][1][0][0][0] = bottom_color_r, body[4][1][0][0][1] = bottom_color_g, body[4][1][0][0][2] = bottom_color_b;
	body[4][1][0][1][0] = bottom_color_r, body[4][1][0][1][1] = bottom_color_g, body[4][1][0][1][2] = bottom_color_b;
	body[4][1][0][2][0] = bottom_color_r, body[4][1][0][2][1] = bottom_color_g, body[4][1][0][2][2] = bottom_color_b;

	body[4][1][1][0][0] = bottom_color_r, body[4][1][1][0][1] = bottom_color_g, body[4][1][1][0][2] = bottom_color_b;
	body[4][1][1][1][0] = bottom_color_r, body[4][1][1][1][1] = bottom_color_g, body[4][1][1][1][2] = bottom_color_b;
	body[4][1][1][2][0] = bottom_color_r, body[4][1][1][2][1] = bottom_color_g, body[4][1][1][2][2] = bottom_color_b;

	// 우측 좌표
	body[5][0][0][0][0] = back_right_down_x, body[5][0][0][0][1] = back_right_down_y, body[5][0][0][0][2] = back_right_down_z;
	body[5][0][0][1][0] = back_right_top_x, body[5][0][0][1][1] = back_right_top_y, body[5][0][0][1][2] = back_right_top_z;
	body[5][0][0][2][0] = front_right_down_x, body[5][0][0][2][1] = front_right_down_y, body[5][0][0][2][2] = front_right_down_z;

	body[5][0][1][0][0] = front_right_down_x, body[5][0][1][0][1] = front_right_down_y, body[5][0][1][0][2] = front_right_down_z;
	body[5][0][1][1][0] = back_right_top_x, body[5][0][1][1][1] = back_right_top_y, body[5][0][1][1][2] = back_right_top_z;
	body[5][0][1][2][0] = front_right_top_x, body[5][0][1][2][1] = front_right_top_y, body[5][0][1][2][2] = front_right_top_z;

	// 우측 색상
	body[5][1][0][0][0] = right_color_r, body[5][1][0][0][1] = right_color_g, body[5][1][0][0][2] = right_color_b;
	body[5][1][0][1][0] = right_color_r, body[5][1][0][1][1] = right_color_g, body[5][1][0][1][2] = right_color_b;
	body[5][1][0][2][0] = right_color_r, body[5][1][0][2][1] = right_color_g, body[5][1][0][2][2] = right_color_b;

	body[5][1][1][0][0] = right_color_r, body[5][1][1][0][1] = right_color_g, body[5][1][1][0][2] = right_color_b;
	body[5][1][1][1][0] = right_color_r, body[5][1][1][1][1] = right_color_g, body[5][1][1][1][2] = right_color_b;
	body[5][1][1][2][0] = right_color_r, body[5][1][1][2][1] = right_color_g, body[5][1][1][2][2] = right_color_b;

	// head

	front_left_down_x = -0.01f, front_left_down_y = -0.01f, front_left_down_z = 0.01f;		// 직육면체를 만들고 싶을 때 적절히 수정해줍니다.
	front_left_top_x = -0.01f, front_left_top_y = 0.01f, front_left_top_z = 0.01f;
	front_right_down_x = 0.01f, front_right_down_y = -0.01f, front_right_down_z = 0.01f;
	front_right_top_x = 0.01f, front_right_top_y = 0.01f, front_right_top_z = 0.01f;
	back_left_down_x = -0.01f, back_left_down_y = -0.01f, back_left_down_z = -0.01f;
	back_left_top_x = -0.01f, back_left_top_y = 0.01f, back_left_top_z = -0.01f;
	back_right_down_x = 0.01f, back_right_down_y = -0.01f, back_right_down_z = -0.01f;
	back_right_top_x = 0.01f, back_right_top_y = 0.01f, back_right_top_z = -0.01f;

	back_color_r = 1.0f, back_color_g = 0.0f, back_color_b = 0.0f;
	front_color_r = back_color_r, front_color_g = back_color_g, front_color_b = back_color_b;
	bottom_color_r = back_color_r, bottom_color_g = back_color_g, bottom_color_b = back_color_b;
	up_color_r = back_color_r, up_color_g = back_color_g, up_color_b = back_color_b;
	left_color_r = back_color_r, left_color_g = back_color_g, left_color_b = back_color_b;
	right_color_r = back_color_r, right_color_g = back_color_g, right_color_b = back_color_b;

	// 전면 좌표
	head[0][0][0][0][0] = front_left_down_x, head[0][0][0][0][1] = front_left_down_y, head[0][0][0][0][2] = front_left_down_z;
	head[0][0][0][1][0] = front_right_down_x, head[0][0][0][1][1] = front_right_down_y, head[0][0][0][1][2] = front_right_down_z;
	head[0][0][0][2][0] = front_left_top_x, head[0][0][0][2][1] = front_left_top_y, head[0][0][0][2][2] = front_left_top_z;

	head[0][0][1][0][0] = front_left_top_x, head[0][0][1][0][1] = front_left_top_y, head[0][0][1][0][2] = front_left_top_z;
	head[0][0][1][1][0] = front_right_down_x, head[0][0][1][1][1] = front_right_down_y, head[0][0][1][1][2] = front_right_down_z;
	head[0][0][1][2][0] = front_right_top_x, head[0][0][1][2][1] = front_right_top_y, head[0][0][1][2][2] = front_right_top_z;

	// 전면 색상
	head[0][1][0][0][0] = front_color_r, head[0][1][0][0][1] = front_color_g, head[0][1][0][0][2] = front_color_b;
	head[0][1][0][1][0] = front_color_r, head[0][1][0][1][1] = front_color_g, head[0][1][0][1][2] = front_color_b;
	head[0][1][0][2][0] = front_color_r, head[0][1][0][2][1] = front_color_g, head[0][1][0][2][2] = front_color_b;

	head[0][1][1][0][0] = front_color_r, head[0][1][1][0][1] = front_color_g, head[0][1][1][0][2] = front_color_b;
	head[0][1][1][1][0] = front_color_r, head[0][1][1][1][1] = front_color_g, head[0][1][1][1][2] = front_color_b;
	head[0][1][1][2][0] = front_color_r, head[0][1][1][2][1] = front_color_g, head[0][1][1][2][2] = front_color_b;


	// 상단 좌표
	head[1][0][0][0][0] = front_right_top_x, head[1][0][0][0][1] = front_right_top_y, head[1][0][0][0][2] = front_right_top_z;
	head[1][0][0][1][0] = back_right_top_x, head[1][0][0][1][1] = back_right_top_y, head[1][0][0][1][2] = back_right_top_z;
	head[1][0][0][2][0] = front_left_top_x, head[1][0][0][2][1] = front_left_top_y, head[1][0][0][2][2] = front_left_top_z;

	head[1][0][1][0][0] = front_left_top_x, head[1][0][1][0][1] = front_left_top_y, head[1][0][1][0][2] = front_left_top_z;
	head[1][0][1][1][0] = back_right_top_x, head[1][0][1][1][1] = back_right_top_y, head[1][0][1][1][2] = back_right_top_z;
	head[1][0][1][2][0] = back_left_top_x, head[1][0][1][2][1] = back_left_top_y, head[1][0][1][2][2] = back_left_top_z;

	// 상단 색상
	head[1][1][0][0][0] = up_color_r, head[1][1][0][0][1] = up_color_g, head[1][1][0][0][2] = up_color_b;
	head[1][1][0][1][0] = up_color_r, head[1][1][0][1][1] = up_color_g, head[1][1][0][1][2] = up_color_b;
	head[1][1][0][2][0] = up_color_r, head[1][1][0][2][1] = up_color_g, head[1][1][0][2][2] = up_color_b;

	head[1][1][1][0][0] = up_color_r, head[1][1][1][0][1] = up_color_g, head[1][1][1][0][2] = up_color_b;
	head[1][1][1][1][0] = up_color_r, head[1][1][1][1][1] = up_color_g, head[1][1][1][1][2] = up_color_b;
	head[1][1][1][2][0] = up_color_r, head[1][1][1][2][1] = up_color_g, head[1][1][1][2][2] = up_color_b;

	// 좌측 좌표
	head[2][0][0][0][0] = back_left_top_x, head[2][0][0][0][1] = back_left_top_y, head[2][0][0][0][2] = back_left_top_z;
	head[2][0][0][1][0] = back_left_down_x, head[2][0][0][1][1] = back_left_down_y, head[2][0][0][1][2] = back_left_down_z;
	head[2][0][0][2][0] = front_left_down_x, head[2][0][0][2][1] = front_left_down_y, head[2][0][0][2][2] = front_left_down_z;

	head[2][0][1][0][0] = front_left_down_x, head[2][0][1][0][1] = front_left_down_y, head[2][0][1][0][2] = front_left_down_z;
	head[2][0][1][1][0] = front_left_top_x, head[2][0][1][1][1] = front_left_top_y, head[2][0][1][1][2] = front_left_top_z;
	head[2][0][1][2][0] = back_left_top_x, head[2][0][1][2][1] = back_left_top_y, head[2][0][1][2][2] = back_left_top_z;

	// 좌측 색상
	head[2][1][0][0][0] = left_color_r, head[2][1][0][0][1] = left_color_g, head[2][1][0][0][2] = left_color_b;
	head[2][1][0][1][0] = left_color_r, head[2][1][0][1][1] = left_color_g, head[2][1][0][1][2] = left_color_b;
	head[2][1][0][2][0] = left_color_r, head[2][1][0][2][1] = left_color_g, head[2][1][0][2][2] = left_color_b;

	head[2][1][1][0][0] = left_color_r, head[2][1][1][0][1] = left_color_g, head[2][1][1][0][2] = left_color_b;
	head[2][1][1][1][0] = left_color_r, head[2][1][1][1][1] = left_color_g, head[2][1][1][1][2] = left_color_b;
	head[2][1][1][2][0] = left_color_r, head[2][1][1][2][1] = left_color_g, head[2][1][1][2][2] = left_color_b;

	// 후면 좌표
	head[3][0][0][0][0] = back_left_top_x, head[3][0][0][0][1] = back_left_top_y, head[3][0][0][0][2] = back_left_top_z;
	head[3][0][0][1][0] = back_left_down_x, head[3][0][0][1][1] = back_left_down_y, head[3][0][0][1][2] = back_left_down_z;
	head[3][0][0][2][0] = back_right_top_x, head[3][0][0][2][1] = back_right_top_y, head[3][0][0][2][2] = back_right_top_z;

	head[3][0][1][0][0] = back_right_top_x, head[3][0][1][0][1] = back_right_top_y, head[3][0][1][0][2] = back_right_top_z;
	head[3][0][1][1][0] = back_left_down_x, head[3][0][1][1][1] = back_left_down_y, head[3][0][1][1][2] = back_left_down_z;
	head[3][0][1][2][0] = back_right_down_x, head[3][0][1][2][1] = back_right_down_y, head[3][0][1][2][2] = back_right_down_z;

	// 후면 색상
	head[3][1][0][0][0] = back_color_r, head[3][1][0][0][1] = back_color_g, head[3][1][0][0][2] = back_color_b;
	head[3][1][0][1][0] = back_color_r, head[3][1][0][1][1] = back_color_g, head[3][1][0][1][2] = back_color_b;
	head[3][1][0][2][0] = back_color_r, head[3][1][0][2][1] = back_color_g, head[3][1][0][2][2] = back_color_b;

	head[3][1][1][0][0] = back_color_r, head[3][1][1][0][1] = back_color_g, head[3][1][1][0][2] = back_color_b;
	head[3][1][1][1][0] = back_color_r, head[3][1][1][1][1] = back_color_g, head[3][1][1][1][2] = back_color_b;
	head[3][1][1][2][0] = back_color_r, head[3][1][1][2][1] = back_color_g, head[3][1][1][2][2] = back_color_b;

	// 하단 좌표
	head[4][0][0][0][0] = back_right_down_x, head[4][0][0][0][1] = back_right_down_y, head[4][0][0][0][2] = back_right_down_z;
	head[4][0][0][1][0] = front_right_down_x, head[4][0][0][1][1] = front_right_down_y, head[4][0][0][1][2] = front_right_down_z;
	head[4][0][0][2][0] = front_left_down_x, head[4][0][0][2][1] = front_left_down_y, head[4][0][0][2][2] = front_left_down_z;

	head[4][0][1][0][0] = front_left_down_x, head[4][0][1][0][1] = front_left_down_y, head[4][0][1][0][2] = front_left_down_z;
	head[4][0][1][1][0] = back_left_down_x, head[4][0][1][1][1] = back_left_down_y, head[4][0][1][1][2] = back_left_down_z;
	head[4][0][1][2][0] = back_right_down_x, head[4][0][1][2][1] = back_right_down_y, head[4][0][1][2][2] = back_right_down_z;

	// 하단 색상
	head[4][1][0][0][0] = bottom_color_r, head[4][1][0][0][1] = bottom_color_g, head[4][1][0][0][2] = bottom_color_b;
	head[4][1][0][1][0] = bottom_color_r, head[4][1][0][1][1] = bottom_color_g, head[4][1][0][1][2] = bottom_color_b;
	head[4][1][0][2][0] = bottom_color_r, head[4][1][0][2][1] = bottom_color_g, head[4][1][0][2][2] = bottom_color_b;

	head[4][1][1][0][0] = bottom_color_r, head[4][1][1][0][1] = bottom_color_g, head[4][1][1][0][2] = bottom_color_b;
	head[4][1][1][1][0] = bottom_color_r, head[4][1][1][1][1] = bottom_color_g, head[4][1][1][1][2] = bottom_color_b;
	head[4][1][1][2][0] = bottom_color_r, head[4][1][1][2][1] = bottom_color_g, head[4][1][1][2][2] = bottom_color_b;

	// 우측 좌표
	head[5][0][0][0][0] = back_right_down_x, head[5][0][0][0][1] = back_right_down_y, head[5][0][0][0][2] = back_right_down_z;
	head[5][0][0][1][0] = back_right_top_x, head[5][0][0][1][1] = back_right_top_y, head[5][0][0][1][2] = back_right_top_z;
	head[5][0][0][2][0] = front_right_down_x, head[5][0][0][2][1] = front_right_down_y, head[5][0][0][2][2] = front_right_down_z;

	head[5][0][1][0][0] = front_right_down_x, head[5][0][1][0][1] = front_right_down_y, head[5][0][1][0][2] = front_right_down_z;
	head[5][0][1][1][0] = back_right_top_x, head[5][0][1][1][1] = back_right_top_y, head[5][0][1][1][2] = back_right_top_z;
	head[5][0][1][2][0] = front_right_top_x, head[5][0][1][2][1] = front_right_top_y, head[5][0][1][2][2] = front_right_top_z;

	// 우측 색상
	head[5][1][0][0][0] = right_color_r, head[5][1][0][0][1] = right_color_g, head[5][1][0][0][2] = right_color_b;
	head[5][1][0][1][0] = right_color_r, head[5][1][0][1][1] = right_color_g, head[5][1][0][1][2] = right_color_b;
	head[5][1][0][2][0] = right_color_r, head[5][1][0][2][1] = right_color_g, head[5][1][0][2][2] = right_color_b;

	head[5][1][1][0][0] = right_color_r, head[5][1][1][0][1] = right_color_g, head[5][1][1][0][2] = right_color_b;
	head[5][1][1][1][0] = right_color_r, head[5][1][1][1][1] = right_color_g, head[5][1][1][1][2] = right_color_b;
	head[5][1][1][2][0] = right_color_r, head[5][1][1][2][1] = right_color_g, head[5][1][1][2][2] = right_color_b;


	// 코 좌표
	head[6][0][0][0][0] = -0.001f, head[6][0][0][0][1] = -0.001f, head[6][0][0][0][2] = 0.011f;
	head[6][0][0][1][0] = 0.001f, head[6][0][0][1][1] = -0.001f, head[6][0][0][1][2] = 0.011f;
	head[6][0][0][2][0] = -0.001f, head[6][0][0][2][1] = 0.001f, head[6][0][0][2][2] = 0.011f;

	head[6][0][1][0][0] = -0.001f, head[6][0][1][0][1] = -0.001f, head[6][0][1][0][2] = 0.011f;
	head[6][0][1][1][0] = 0.001f, head[6][0][1][1][1] = -0.001f, head[6][0][1][1][2] = 0.011f;
	head[6][0][1][2][0] = 0.001f, head[6][0][1][2][1] = 0.001f, head[6][0][1][2][2] = 0.011f;

	// 코 색상
	head[6][1][0][0][0] = 0.9f, head[6][1][0][0][1] = 0.9f, head[6][1][0][0][2] = 0.9f;
	head[6][1][0][1][0] = 0.9f, head[6][1][0][1][1] = 0.9f, head[6][1][0][1][2] = 0.9f;
	head[6][1][0][2][0] = 0.9f, head[6][1][0][2][1] = 0.9f, head[6][1][0][2][2] = 0.9f;

	head[6][1][1][0][0] = 0.9f, head[6][1][1][0][1] = 0.9f, head[6][1][1][0][2] = 0.9f;
	head[6][1][1][1][0] = 0.9f, head[6][1][1][1][1] = 0.9f, head[6][1][1][1][2] = 0.9f;
	head[6][1][1][2][0] = 0.9f, head[6][1][1][2][1] = 0.9f, head[6][1][1][2][2] = 0.9f;

	// leftarm

	front_left_down_x = -0.005f, front_left_down_y = -0.02f, front_left_down_z = 0.005f;		// 직육면체를 만들고 싶을 때 적절히 수정해줍니다.
	front_left_top_x = -0.005f, front_left_top_y = 0.02f, front_left_top_z = 0.005f;
	front_right_down_x = 0.005f, front_right_down_y = -0.02f, front_right_down_z = 0.005f;
	front_right_top_x = 0.005f, front_right_top_y = 0.02f, front_right_top_z = 0.005f;
	back_left_down_x = -0.005f, back_left_down_y = -0.02f, back_left_down_z = -0.005f;
	back_left_top_x = -0.005f, back_left_top_y = 0.02f, back_left_top_z = -0.005f;
	back_right_down_x = 0.005f, back_right_down_y = -0.02f, back_right_down_z = -0.005f;
	back_right_top_x = 0.005f, back_right_top_y = 0.02f, back_right_top_z = -0.005f;

	back_color_r = 0.0f, back_color_g = 1.0f, back_color_b = 0.0f;
	front_color_r = back_color_r, front_color_g = back_color_g, front_color_b = back_color_b;
	bottom_color_r = back_color_r, bottom_color_g = back_color_g, bottom_color_b = back_color_b;
	up_color_r = back_color_r, up_color_g = back_color_g, up_color_b = back_color_b;
	left_color_r = back_color_r, left_color_g = back_color_g, left_color_b = back_color_b;
	right_color_r = back_color_r, right_color_g = back_color_g, right_color_b = back_color_b;

	// 전면 좌표
	leftarm[0][0][0][0][0] = front_left_down_x, leftarm[0][0][0][0][1] = front_left_down_y, leftarm[0][0][0][0][2] = front_left_down_z;
	leftarm[0][0][0][1][0] = front_right_down_x, leftarm[0][0][0][1][1] = front_right_down_y, leftarm[0][0][0][1][2] = front_right_down_z;
	leftarm[0][0][0][2][0] = front_left_top_x, leftarm[0][0][0][2][1] = front_left_top_y, leftarm[0][0][0][2][2] = front_left_top_z;

	leftarm[0][0][1][0][0] = front_left_top_x, leftarm[0][0][1][0][1] = front_left_top_y, leftarm[0][0][1][0][2] = front_left_top_z;
	leftarm[0][0][1][1][0] = front_right_down_x, leftarm[0][0][1][1][1] = front_right_down_y, leftarm[0][0][1][1][2] = front_right_down_z;
	leftarm[0][0][1][2][0] = front_right_top_x, leftarm[0][0][1][2][1] = front_right_top_y, leftarm[0][0][1][2][2] = front_right_top_z;

	// 전면 색상
	leftarm[0][1][0][0][0] = front_color_r, leftarm[0][1][0][0][1] = front_color_g, leftarm[0][1][0][0][2] = front_color_b;
	leftarm[0][1][0][1][0] = front_color_r, leftarm[0][1][0][1][1] = front_color_g, leftarm[0][1][0][1][2] = front_color_b;
	leftarm[0][1][0][2][0] = front_color_r, leftarm[0][1][0][2][1] = front_color_g, leftarm[0][1][0][2][2] = front_color_b;

	leftarm[0][1][1][0][0] = front_color_r, leftarm[0][1][1][0][1] = front_color_g, leftarm[0][1][1][0][2] = front_color_b;
	leftarm[0][1][1][1][0] = front_color_r, leftarm[0][1][1][1][1] = front_color_g, leftarm[0][1][1][1][2] = front_color_b;
	leftarm[0][1][1][2][0] = front_color_r, leftarm[0][1][1][2][1] = front_color_g, leftarm[0][1][1][2][2] = front_color_b;


	// 상단 좌표
	leftarm[1][0][0][0][0] = front_right_top_x, leftarm[1][0][0][0][1] = front_right_top_y, leftarm[1][0][0][0][2] = front_right_top_z;
	leftarm[1][0][0][1][0] = back_right_top_x, leftarm[1][0][0][1][1] = back_right_top_y, leftarm[1][0][0][1][2] = back_right_top_z;
	leftarm[1][0][0][2][0] = front_left_top_x, leftarm[1][0][0][2][1] = front_left_top_y, leftarm[1][0][0][2][2] = front_left_top_z;

	leftarm[1][0][1][0][0] = front_left_top_x, leftarm[1][0][1][0][1] = front_left_top_y, leftarm[1][0][1][0][2] = front_left_top_z;
	leftarm[1][0][1][1][0] = back_right_top_x, leftarm[1][0][1][1][1] = back_right_top_y, leftarm[1][0][1][1][2] = back_right_top_z;
	leftarm[1][0][1][2][0] = back_left_top_x, leftarm[1][0][1][2][1] = back_left_top_y, leftarm[1][0][1][2][2] = back_left_top_z;

	// 상단 색상
	leftarm[1][1][0][0][0] = up_color_r, leftarm[1][1][0][0][1] = up_color_g, leftarm[1][1][0][0][2] = up_color_b;
	leftarm[1][1][0][1][0] = up_color_r, leftarm[1][1][0][1][1] = up_color_g, leftarm[1][1][0][1][2] = up_color_b;
	leftarm[1][1][0][2][0] = up_color_r, leftarm[1][1][0][2][1] = up_color_g, leftarm[1][1][0][2][2] = up_color_b;

	leftarm[1][1][1][0][0] = up_color_r, leftarm[1][1][1][0][1] = up_color_g, leftarm[1][1][1][0][2] = up_color_b;
	leftarm[1][1][1][1][0] = up_color_r, leftarm[1][1][1][1][1] = up_color_g, leftarm[1][1][1][1][2] = up_color_b;
	leftarm[1][1][1][2][0] = up_color_r, leftarm[1][1][1][2][1] = up_color_g, leftarm[1][1][1][2][2] = up_color_b;

	// 좌측 좌표
	leftarm[2][0][0][0][0] = back_left_top_x, leftarm[2][0][0][0][1] = back_left_top_y, leftarm[2][0][0][0][2] = back_left_top_z;
	leftarm[2][0][0][1][0] = back_left_down_x, leftarm[2][0][0][1][1] = back_left_down_y, leftarm[2][0][0][1][2] = back_left_down_z;
	leftarm[2][0][0][2][0] = front_left_down_x, leftarm[2][0][0][2][1] = front_left_down_y, leftarm[2][0][0][2][2] = front_left_down_z;

	leftarm[2][0][1][0][0] = front_left_down_x, leftarm[2][0][1][0][1] = front_left_down_y, leftarm[2][0][1][0][2] = front_left_down_z;
	leftarm[2][0][1][1][0] = front_left_top_x, leftarm[2][0][1][1][1] = front_left_top_y, leftarm[2][0][1][1][2] = front_left_top_z;
	leftarm[2][0][1][2][0] = back_left_top_x, leftarm[2][0][1][2][1] = back_left_top_y, leftarm[2][0][1][2][2] = back_left_top_z;

	// 좌측 색상
	leftarm[2][1][0][0][0] = left_color_r, leftarm[2][1][0][0][1] = left_color_g, leftarm[2][1][0][0][2] = left_color_b;
	leftarm[2][1][0][1][0] = left_color_r, leftarm[2][1][0][1][1] = left_color_g, leftarm[2][1][0][1][2] = left_color_b;
	leftarm[2][1][0][2][0] = left_color_r, leftarm[2][1][0][2][1] = left_color_g, leftarm[2][1][0][2][2] = left_color_b;

	leftarm[2][1][1][0][0] = left_color_r, leftarm[2][1][1][0][1] = left_color_g, leftarm[2][1][1][0][2] = left_color_b;
	leftarm[2][1][1][1][0] = left_color_r, leftarm[2][1][1][1][1] = left_color_g, leftarm[2][1][1][1][2] = left_color_b;
	leftarm[2][1][1][2][0] = left_color_r, leftarm[2][1][1][2][1] = left_color_g, leftarm[2][1][1][2][2] = left_color_b;

	// 후면 좌표
	leftarm[3][0][0][0][0] = back_left_top_x, leftarm[3][0][0][0][1] = back_left_top_y, leftarm[3][0][0][0][2] = back_left_top_z;
	leftarm[3][0][0][1][0] = back_left_down_x, leftarm[3][0][0][1][1] = back_left_down_y, leftarm[3][0][0][1][2] = back_left_down_z;
	leftarm[3][0][0][2][0] = back_right_top_x, leftarm[3][0][0][2][1] = back_right_top_y, leftarm[3][0][0][2][2] = back_right_top_z;

	leftarm[3][0][1][0][0] = back_right_top_x, leftarm[3][0][1][0][1] = back_right_top_y, leftarm[3][0][1][0][2] = back_right_top_z;
	leftarm[3][0][1][1][0] = back_left_down_x, leftarm[3][0][1][1][1] = back_left_down_y, leftarm[3][0][1][1][2] = back_left_down_z;
	leftarm[3][0][1][2][0] = back_right_down_x, leftarm[3][0][1][2][1] = back_right_down_y, leftarm[3][0][1][2][2] = back_right_down_z;

	// 후면 색상
	leftarm[3][1][0][0][0] = back_color_r, leftarm[3][1][0][0][1] = back_color_g, leftarm[3][1][0][0][2] = back_color_b;
	leftarm[3][1][0][1][0] = back_color_r, leftarm[3][1][0][1][1] = back_color_g, leftarm[3][1][0][1][2] = back_color_b;
	leftarm[3][1][0][2][0] = back_color_r, leftarm[3][1][0][2][1] = back_color_g, leftarm[3][1][0][2][2] = back_color_b;

	leftarm[3][1][1][0][0] = back_color_r, leftarm[3][1][1][0][1] = back_color_g, leftarm[3][1][1][0][2] = back_color_b;
	leftarm[3][1][1][1][0] = back_color_r, leftarm[3][1][1][1][1] = back_color_g, leftarm[3][1][1][1][2] = back_color_b;
	leftarm[3][1][1][2][0] = back_color_r, leftarm[3][1][1][2][1] = back_color_g, leftarm[3][1][1][2][2] = back_color_b;

	// 하단 좌표
	leftarm[4][0][0][0][0] = back_right_down_x, leftarm[4][0][0][0][1] = back_right_down_y, leftarm[4][0][0][0][2] = back_right_down_z;
	leftarm[4][0][0][1][0] = front_right_down_x, leftarm[4][0][0][1][1] = front_right_down_y, leftarm[4][0][0][1][2] = front_right_down_z;
	leftarm[4][0][0][2][0] = front_left_down_x, leftarm[4][0][0][2][1] = front_left_down_y, leftarm[4][0][0][2][2] = front_left_down_z;

	leftarm[4][0][1][0][0] = front_left_down_x, leftarm[4][0][1][0][1] = front_left_down_y, leftarm[4][0][1][0][2] = front_left_down_z;
	leftarm[4][0][1][1][0] = back_left_down_x, leftarm[4][0][1][1][1] = back_left_down_y, leftarm[4][0][1][1][2] = back_left_down_z;
	leftarm[4][0][1][2][0] = back_right_down_x, leftarm[4][0][1][2][1] = back_right_down_y, leftarm[4][0][1][2][2] = back_right_down_z;

	// 하단 색상
	leftarm[4][1][0][0][0] = bottom_color_r, leftarm[4][1][0][0][1] = bottom_color_g, leftarm[4][1][0][0][2] = bottom_color_b;
	leftarm[4][1][0][1][0] = bottom_color_r, leftarm[4][1][0][1][1] = bottom_color_g, leftarm[4][1][0][1][2] = bottom_color_b;
	leftarm[4][1][0][2][0] = bottom_color_r, leftarm[4][1][0][2][1] = bottom_color_g, leftarm[4][1][0][2][2] = bottom_color_b;

	leftarm[4][1][1][0][0] = bottom_color_r, leftarm[4][1][1][0][1] = bottom_color_g, leftarm[4][1][1][0][2] = bottom_color_b;
	leftarm[4][1][1][1][0] = bottom_color_r, leftarm[4][1][1][1][1] = bottom_color_g, leftarm[4][1][1][1][2] = bottom_color_b;
	leftarm[4][1][1][2][0] = bottom_color_r, leftarm[4][1][1][2][1] = bottom_color_g, leftarm[4][1][1][2][2] = bottom_color_b;

	// 우측 좌표
	leftarm[5][0][0][0][0] = back_right_down_x, leftarm[5][0][0][0][1] = back_right_down_y, leftarm[5][0][0][0][2] = back_right_down_z;
	leftarm[5][0][0][1][0] = back_right_top_x, leftarm[5][0][0][1][1] = back_right_top_y, leftarm[5][0][0][1][2] = back_right_top_z;
	leftarm[5][0][0][2][0] = front_right_down_x, leftarm[5][0][0][2][1] = front_right_down_y, leftarm[5][0][0][2][2] = front_right_down_z;

	leftarm[5][0][1][0][0] = front_right_down_x, leftarm[5][0][1][0][1] = front_right_down_y, leftarm[5][0][1][0][2] = front_right_down_z;
	leftarm[5][0][1][1][0] = back_right_top_x, leftarm[5][0][1][1][1] = back_right_top_y, leftarm[5][0][1][1][2] = back_right_top_z;
	leftarm[5][0][1][2][0] = front_right_top_x, leftarm[5][0][1][2][1] = front_right_top_y, leftarm[5][0][1][2][2] = front_right_top_z;

	// 우측 색상
	leftarm[5][1][0][0][0] = right_color_r, leftarm[5][1][0][0][1] = right_color_g, leftarm[5][1][0][0][2] = right_color_b;
	leftarm[5][1][0][1][0] = right_color_r, leftarm[5][1][0][1][1] = right_color_g, leftarm[5][1][0][1][2] = right_color_b;
	leftarm[5][1][0][2][0] = right_color_r, leftarm[5][1][0][2][1] = right_color_g, leftarm[5][1][0][2][2] = right_color_b;

	leftarm[5][1][1][0][0] = right_color_r, leftarm[5][1][1][0][1] = right_color_g, leftarm[5][1][1][0][2] = right_color_b;
	leftarm[5][1][1][1][0] = right_color_r, leftarm[5][1][1][1][1] = right_color_g, leftarm[5][1][1][1][2] = right_color_b;
	leftarm[5][1][1][2][0] = right_color_r, leftarm[5][1][1][2][1] = right_color_g, leftarm[5][1][1][2][2] = right_color_b;

	// leftleg

	front_left_down_x = -0.005f, front_left_down_y = -0.02f, front_left_down_z = 0.005f;		// 직육면체를 만들고 싶을 때 적절히 수정해줍니다.
	front_left_top_x = -0.005f, front_left_top_y = 0.02f, front_left_top_z = 0.005f;
	front_right_down_x = 0.005f, front_right_down_y = -0.02f, front_right_down_z = 0.005f;
	front_right_top_x = 0.005f, front_right_top_y = 0.02f, front_right_top_z = 0.005f;
	back_left_down_x = -0.005f, back_left_down_y = -0.02f, back_left_down_z = -0.005f;
	back_left_top_x = -0.005f, back_left_top_y = 0.02f, back_left_top_z = -0.005f;
	back_right_down_x = 0.005f, back_right_down_y = -0.02f, back_right_down_z = -0.005f;
	back_right_top_x = 0.005f, back_right_top_y = 0.02f, back_right_top_z = -0.005f;

	back_color_r = 0.8f, back_color_g = 0.8f, back_color_b = 0.3f;
	front_color_r = back_color_r, front_color_g = back_color_g, front_color_b = back_color_b;
	bottom_color_r = back_color_r, bottom_color_g = back_color_g, bottom_color_b = back_color_b;
	up_color_r = back_color_r, up_color_g = back_color_g, up_color_b = back_color_b;
	left_color_r = back_color_r, left_color_g = back_color_g, left_color_b = back_color_b;
	right_color_r = back_color_r, right_color_g = back_color_g, right_color_b = back_color_b;

	// 전면 좌표
	leftleg[0][0][0][0][0] = front_left_down_x, leftleg[0][0][0][0][1] = front_left_down_y, leftleg[0][0][0][0][2] = front_left_down_z;
	leftleg[0][0][0][1][0] = front_right_down_x, leftleg[0][0][0][1][1] = front_right_down_y, leftleg[0][0][0][1][2] = front_right_down_z;
	leftleg[0][0][0][2][0] = front_left_top_x, leftleg[0][0][0][2][1] = front_left_top_y, leftleg[0][0][0][2][2] = front_left_top_z;

	leftleg[0][0][1][0][0] = front_left_top_x, leftleg[0][0][1][0][1] = front_left_top_y, leftleg[0][0][1][0][2] = front_left_top_z;
	leftleg[0][0][1][1][0] = front_right_down_x, leftleg[0][0][1][1][1] = front_right_down_y, leftleg[0][0][1][1][2] = front_right_down_z;
	leftleg[0][0][1][2][0] = front_right_top_x, leftleg[0][0][1][2][1] = front_right_top_y, leftleg[0][0][1][2][2] = front_right_top_z;

	// 전면 색상
	leftleg[0][1][0][0][0] = front_color_r, leftleg[0][1][0][0][1] = front_color_g, leftleg[0][1][0][0][2] = front_color_b;
	leftleg[0][1][0][1][0] = front_color_r, leftleg[0][1][0][1][1] = front_color_g, leftleg[0][1][0][1][2] = front_color_b;
	leftleg[0][1][0][2][0] = front_color_r, leftleg[0][1][0][2][1] = front_color_g, leftleg[0][1][0][2][2] = front_color_b;

	leftleg[0][1][1][0][0] = front_color_r, leftleg[0][1][1][0][1] = front_color_g, leftleg[0][1][1][0][2] = front_color_b;
	leftleg[0][1][1][1][0] = front_color_r, leftleg[0][1][1][1][1] = front_color_g, leftleg[0][1][1][1][2] = front_color_b;
	leftleg[0][1][1][2][0] = front_color_r, leftleg[0][1][1][2][1] = front_color_g, leftleg[0][1][1][2][2] = front_color_b;


	// 상단 좌표
	leftleg[1][0][0][0][0] = front_right_top_x, leftleg[1][0][0][0][1] = front_right_top_y, leftleg[1][0][0][0][2] = front_right_top_z;
	leftleg[1][0][0][1][0] = back_right_top_x, leftleg[1][0][0][1][1] = back_right_top_y, leftleg[1][0][0][1][2] = back_right_top_z;
	leftleg[1][0][0][2][0] = front_left_top_x, leftleg[1][0][0][2][1] = front_left_top_y, leftleg[1][0][0][2][2] = front_left_top_z;

	leftleg[1][0][1][0][0] = front_left_top_x, leftleg[1][0][1][0][1] = front_left_top_y, leftleg[1][0][1][0][2] = front_left_top_z;
	leftleg[1][0][1][1][0] = back_right_top_x, leftleg[1][0][1][1][1] = back_right_top_y, leftleg[1][0][1][1][2] = back_right_top_z;
	leftleg[1][0][1][2][0] = back_left_top_x, leftleg[1][0][1][2][1] = back_left_top_y, leftleg[1][0][1][2][2] = back_left_top_z;

	// 상단 색상
	leftleg[1][1][0][0][0] = up_color_r, leftleg[1][1][0][0][1] = up_color_g, leftleg[1][1][0][0][2] = up_color_b;
	leftleg[1][1][0][1][0] = up_color_r, leftleg[1][1][0][1][1] = up_color_g, leftleg[1][1][0][1][2] = up_color_b;
	leftleg[1][1][0][2][0] = up_color_r, leftleg[1][1][0][2][1] = up_color_g, leftleg[1][1][0][2][2] = up_color_b;

	leftleg[1][1][1][0][0] = up_color_r, leftleg[1][1][1][0][1] = up_color_g, leftleg[1][1][1][0][2] = up_color_b;
	leftleg[1][1][1][1][0] = up_color_r, leftleg[1][1][1][1][1] = up_color_g, leftleg[1][1][1][1][2] = up_color_b;
	leftleg[1][1][1][2][0] = up_color_r, leftleg[1][1][1][2][1] = up_color_g, leftleg[1][1][1][2][2] = up_color_b;

	// 좌측 좌표
	leftleg[2][0][0][0][0] = back_left_top_x, leftleg[2][0][0][0][1] = back_left_top_y, leftleg[2][0][0][0][2] = back_left_top_z;
	leftleg[2][0][0][1][0] = back_left_down_x, leftleg[2][0][0][1][1] = back_left_down_y, leftleg[2][0][0][1][2] = back_left_down_z;
	leftleg[2][0][0][2][0] = front_left_down_x, leftleg[2][0][0][2][1] = front_left_down_y, leftleg[2][0][0][2][2] = front_left_down_z;

	leftleg[2][0][1][0][0] = front_left_down_x, leftleg[2][0][1][0][1] = front_left_down_y, leftleg[2][0][1][0][2] = front_left_down_z;
	leftleg[2][0][1][1][0] = front_left_top_x, leftleg[2][0][1][1][1] = front_left_top_y, leftleg[2][0][1][1][2] = front_left_top_z;
	leftleg[2][0][1][2][0] = back_left_top_x, leftleg[2][0][1][2][1] = back_left_top_y, leftleg[2][0][1][2][2] = back_left_top_z;

	// 좌측 색상
	leftleg[2][1][0][0][0] = left_color_r, leftleg[2][1][0][0][1] = left_color_g, leftleg[2][1][0][0][2] = left_color_b;
	leftleg[2][1][0][1][0] = left_color_r, leftleg[2][1][0][1][1] = left_color_g, leftleg[2][1][0][1][2] = left_color_b;
	leftleg[2][1][0][2][0] = left_color_r, leftleg[2][1][0][2][1] = left_color_g, leftleg[2][1][0][2][2] = left_color_b;

	leftleg[2][1][1][0][0] = left_color_r, leftleg[2][1][1][0][1] = left_color_g, leftleg[2][1][1][0][2] = left_color_b;
	leftleg[2][1][1][1][0] = left_color_r, leftleg[2][1][1][1][1] = left_color_g, leftleg[2][1][1][1][2] = left_color_b;
	leftleg[2][1][1][2][0] = left_color_r, leftleg[2][1][1][2][1] = left_color_g, leftleg[2][1][1][2][2] = left_color_b;

	// 후면 좌표
	leftleg[3][0][0][0][0] = back_left_top_x, leftleg[3][0][0][0][1] = back_left_top_y, leftleg[3][0][0][0][2] = back_left_top_z;
	leftleg[3][0][0][1][0] = back_left_down_x, leftleg[3][0][0][1][1] = back_left_down_y, leftleg[3][0][0][1][2] = back_left_down_z;
	leftleg[3][0][0][2][0] = back_right_top_x, leftleg[3][0][0][2][1] = back_right_top_y, leftleg[3][0][0][2][2] = back_right_top_z;

	leftleg[3][0][1][0][0] = back_right_top_x, leftleg[3][0][1][0][1] = back_right_top_y, leftleg[3][0][1][0][2] = back_right_top_z;
	leftleg[3][0][1][1][0] = back_left_down_x, leftleg[3][0][1][1][1] = back_left_down_y, leftleg[3][0][1][1][2] = back_left_down_z;
	leftleg[3][0][1][2][0] = back_right_down_x, leftleg[3][0][1][2][1] = back_right_down_y, leftleg[3][0][1][2][2] = back_right_down_z;

	// 후면 색상
	leftleg[3][1][0][0][0] = back_color_r, leftleg[3][1][0][0][1] = back_color_g, leftleg[3][1][0][0][2] = back_color_b;
	leftleg[3][1][0][1][0] = back_color_r, leftleg[3][1][0][1][1] = back_color_g, leftleg[3][1][0][1][2] = back_color_b;
	leftleg[3][1][0][2][0] = back_color_r, leftleg[3][1][0][2][1] = back_color_g, leftleg[3][1][0][2][2] = back_color_b;

	leftleg[3][1][1][0][0] = back_color_r, leftleg[3][1][1][0][1] = back_color_g, leftleg[3][1][1][0][2] = back_color_b;
	leftleg[3][1][1][1][0] = back_color_r, leftleg[3][1][1][1][1] = back_color_g, leftleg[3][1][1][1][2] = back_color_b;
	leftleg[3][1][1][2][0] = back_color_r, leftleg[3][1][1][2][1] = back_color_g, leftleg[3][1][1][2][2] = back_color_b;

	// 하단 좌표
	leftleg[4][0][0][0][0] = back_right_down_x, leftleg[4][0][0][0][1] = back_right_down_y, leftleg[4][0][0][0][2] = back_right_down_z;
	leftleg[4][0][0][1][0] = front_right_down_x, leftleg[4][0][0][1][1] = front_right_down_y, leftleg[4][0][0][1][2] = front_right_down_z;
	leftleg[4][0][0][2][0] = front_left_down_x, leftleg[4][0][0][2][1] = front_left_down_y, leftleg[4][0][0][2][2] = front_left_down_z;

	leftleg[4][0][1][0][0] = front_left_down_x, leftleg[4][0][1][0][1] = front_left_down_y, leftleg[4][0][1][0][2] = front_left_down_z;
	leftleg[4][0][1][1][0] = back_left_down_x, leftleg[4][0][1][1][1] = back_left_down_y, leftleg[4][0][1][1][2] = back_left_down_z;
	leftleg[4][0][1][2][0] = back_right_down_x, leftleg[4][0][1][2][1] = back_right_down_y, leftleg[4][0][1][2][2] = back_right_down_z;

	// 하단 색상
	leftleg[4][1][0][0][0] = bottom_color_r, leftleg[4][1][0][0][1] = bottom_color_g, leftleg[4][1][0][0][2] = bottom_color_b;
	leftleg[4][1][0][1][0] = bottom_color_r, leftleg[4][1][0][1][1] = bottom_color_g, leftleg[4][1][0][1][2] = bottom_color_b;
	leftleg[4][1][0][2][0] = bottom_color_r, leftleg[4][1][0][2][1] = bottom_color_g, leftleg[4][1][0][2][2] = bottom_color_b;

	leftleg[4][1][1][0][0] = bottom_color_r, leftleg[4][1][1][0][1] = bottom_color_g, leftleg[4][1][1][0][2] = bottom_color_b;
	leftleg[4][1][1][1][0] = bottom_color_r, leftleg[4][1][1][1][1] = bottom_color_g, leftleg[4][1][1][1][2] = bottom_color_b;
	leftleg[4][1][1][2][0] = bottom_color_r, leftleg[4][1][1][2][1] = bottom_color_g, leftleg[4][1][1][2][2] = bottom_color_b;

	// 우측 좌표
	leftleg[5][0][0][0][0] = back_right_down_x, leftleg[5][0][0][0][1] = back_right_down_y, leftleg[5][0][0][0][2] = back_right_down_z;
	leftleg[5][0][0][1][0] = back_right_top_x, leftleg[5][0][0][1][1] = back_right_top_y, leftleg[5][0][0][1][2] = back_right_top_z;
	leftleg[5][0][0][2][0] = front_right_down_x, leftleg[5][0][0][2][1] = front_right_down_y, leftleg[5][0][0][2][2] = front_right_down_z;

	leftleg[5][0][1][0][0] = front_right_down_x, leftleg[5][0][1][0][1] = front_right_down_y, leftleg[5][0][1][0][2] = front_right_down_z;
	leftleg[5][0][1][1][0] = back_right_top_x, leftleg[5][0][1][1][1] = back_right_top_y, leftleg[5][0][1][1][2] = back_right_top_z;
	leftleg[5][0][1][2][0] = front_right_top_x, leftleg[5][0][1][2][1] = front_right_top_y, leftleg[5][0][1][2][2] = front_right_top_z;

	// 우측 색상
	leftleg[5][1][0][0][0] = right_color_r, leftleg[5][1][0][0][1] = right_color_g, leftleg[5][1][0][0][2] = right_color_b;
	leftleg[5][1][0][1][0] = right_color_r, leftleg[5][1][0][1][1] = right_color_g, leftleg[5][1][0][1][2] = right_color_b;
	leftleg[5][1][0][2][0] = right_color_r, leftleg[5][1][0][2][1] = right_color_g, leftleg[5][1][0][2][2] = right_color_b;

	leftleg[5][1][1][0][0] = right_color_r, leftleg[5][1][1][0][1] = right_color_g, leftleg[5][1][1][0][2] = right_color_b;
	leftleg[5][1][1][1][0] = right_color_r, leftleg[5][1][1][1][1] = right_color_g, leftleg[5][1][1][1][2] = right_color_b;
	leftleg[5][1][1][2][0] = right_color_r, leftleg[5][1][1][2][1] = right_color_g, leftleg[5][1][1][2][2] = right_color_b;

	// rightarm

	front_left_down_x = -0.005f, front_left_down_y = -0.02f, front_left_down_z = 0.005f;		// 직육면체를 만들고 싶을 때 적절히 수정해줍니다.
	front_left_top_x = -0.005f, front_left_top_y = 0.02f, front_left_top_z = 0.005f;
	front_right_down_x = 0.005f, front_right_down_y = -0.02f, front_right_down_z = 0.005f;
	front_right_top_x = 0.005f, front_right_top_y = 0.02f, front_right_top_z = 0.005f;
	back_left_down_x = -0.005f, back_left_down_y = -0.02f, back_left_down_z = -0.005f;
	back_left_top_x = -0.005f, back_left_top_y = 0.02f, back_left_top_z = -0.005f;
	back_right_down_x = 0.005f, back_right_down_y = -0.02f, back_right_down_z = -0.005f;
	back_right_top_x = 0.005f, back_right_top_y = 0.02f, back_right_top_z = -0.005f;

	back_color_r = 0.5f, back_color_g = 0.9f, back_color_b = 0.5f;
	front_color_r = back_color_r, front_color_g = back_color_g, front_color_b = back_color_b;
	bottom_color_r = back_color_r, bottom_color_g = back_color_g, bottom_color_b = back_color_b;
	up_color_r = back_color_r, up_color_g = back_color_g, up_color_b = back_color_b;
	left_color_r = back_color_r, left_color_g = back_color_g, left_color_b = back_color_b;
	right_color_r = back_color_r, right_color_g = back_color_g, right_color_b = back_color_b;

	// 전면 좌표
	rightarm[0][0][0][0][0] = front_left_down_x, rightarm[0][0][0][0][1] = front_left_down_y, rightarm[0][0][0][0][2] = front_left_down_z;
	rightarm[0][0][0][1][0] = front_right_down_x, rightarm[0][0][0][1][1] = front_right_down_y, rightarm[0][0][0][1][2] = front_right_down_z;
	rightarm[0][0][0][2][0] = front_left_top_x, rightarm[0][0][0][2][1] = front_left_top_y, rightarm[0][0][0][2][2] = front_left_top_z;

	rightarm[0][0][1][0][0] = front_left_top_x, rightarm[0][0][1][0][1] = front_left_top_y, rightarm[0][0][1][0][2] = front_left_top_z;
	rightarm[0][0][1][1][0] = front_right_down_x, rightarm[0][0][1][1][1] = front_right_down_y, rightarm[0][0][1][1][2] = front_right_down_z;
	rightarm[0][0][1][2][0] = front_right_top_x, rightarm[0][0][1][2][1] = front_right_top_y, rightarm[0][0][1][2][2] = front_right_top_z;

	// 전면 색상
	rightarm[0][1][0][0][0] = front_color_r, rightarm[0][1][0][0][1] = front_color_g, rightarm[0][1][0][0][2] = front_color_b;
	rightarm[0][1][0][1][0] = front_color_r, rightarm[0][1][0][1][1] = front_color_g, rightarm[0][1][0][1][2] = front_color_b;
	rightarm[0][1][0][2][0] = front_color_r, rightarm[0][1][0][2][1] = front_color_g, rightarm[0][1][0][2][2] = front_color_b;

	rightarm[0][1][1][0][0] = front_color_r, rightarm[0][1][1][0][1] = front_color_g, rightarm[0][1][1][0][2] = front_color_b;
	rightarm[0][1][1][1][0] = front_color_r, rightarm[0][1][1][1][1] = front_color_g, rightarm[0][1][1][1][2] = front_color_b;
	rightarm[0][1][1][2][0] = front_color_r, rightarm[0][1][1][2][1] = front_color_g, rightarm[0][1][1][2][2] = front_color_b;


	// 상단 좌표
	rightarm[1][0][0][0][0] = front_right_top_x, rightarm[1][0][0][0][1] = front_right_top_y, rightarm[1][0][0][0][2] = front_right_top_z;
	rightarm[1][0][0][1][0] = back_right_top_x, rightarm[1][0][0][1][1] = back_right_top_y, rightarm[1][0][0][1][2] = back_right_top_z;
	rightarm[1][0][0][2][0] = front_left_top_x, rightarm[1][0][0][2][1] = front_left_top_y, rightarm[1][0][0][2][2] = front_left_top_z;

	rightarm[1][0][1][0][0] = front_left_top_x, rightarm[1][0][1][0][1] = front_left_top_y, rightarm[1][0][1][0][2] = front_left_top_z;
	rightarm[1][0][1][1][0] = back_right_top_x, rightarm[1][0][1][1][1] = back_right_top_y, rightarm[1][0][1][1][2] = back_right_top_z;
	rightarm[1][0][1][2][0] = back_left_top_x, rightarm[1][0][1][2][1] = back_left_top_y, rightarm[1][0][1][2][2] = back_left_top_z;

	// 상단 색상
	rightarm[1][1][0][0][0] = up_color_r, rightarm[1][1][0][0][1] = up_color_g, rightarm[1][1][0][0][2] = up_color_b;
	rightarm[1][1][0][1][0] = up_color_r, rightarm[1][1][0][1][1] = up_color_g, rightarm[1][1][0][1][2] = up_color_b;
	rightarm[1][1][0][2][0] = up_color_r, rightarm[1][1][0][2][1] = up_color_g, rightarm[1][1][0][2][2] = up_color_b;

	rightarm[1][1][1][0][0] = up_color_r, rightarm[1][1][1][0][1] = up_color_g, rightarm[1][1][1][0][2] = up_color_b;
	rightarm[1][1][1][1][0] = up_color_r, rightarm[1][1][1][1][1] = up_color_g, rightarm[1][1][1][1][2] = up_color_b;
	rightarm[1][1][1][2][0] = up_color_r, rightarm[1][1][1][2][1] = up_color_g, rightarm[1][1][1][2][2] = up_color_b;

	// 좌측 좌표
	rightarm[2][0][0][0][0] = back_left_top_x, rightarm[2][0][0][0][1] = back_left_top_y, rightarm[2][0][0][0][2] = back_left_top_z;
	rightarm[2][0][0][1][0] = back_left_down_x, rightarm[2][0][0][1][1] = back_left_down_y, rightarm[2][0][0][1][2] = back_left_down_z;
	rightarm[2][0][0][2][0] = front_left_down_x, rightarm[2][0][0][2][1] = front_left_down_y, rightarm[2][0][0][2][2] = front_left_down_z;

	rightarm[2][0][1][0][0] = front_left_down_x, rightarm[2][0][1][0][1] = front_left_down_y, rightarm[2][0][1][0][2] = front_left_down_z;
	rightarm[2][0][1][1][0] = front_left_top_x, rightarm[2][0][1][1][1] = front_left_top_y, rightarm[2][0][1][1][2] = front_left_top_z;
	rightarm[2][0][1][2][0] = back_left_top_x, rightarm[2][0][1][2][1] = back_left_top_y, rightarm[2][0][1][2][2] = back_left_top_z;

	// 좌측 색상
	rightarm[2][1][0][0][0] = left_color_r, rightarm[2][1][0][0][1] = left_color_g, rightarm[2][1][0][0][2] = left_color_b;
	rightarm[2][1][0][1][0] = left_color_r, rightarm[2][1][0][1][1] = left_color_g, rightarm[2][1][0][1][2] = left_color_b;
	rightarm[2][1][0][2][0] = left_color_r, rightarm[2][1][0][2][1] = left_color_g, rightarm[2][1][0][2][2] = left_color_b;

	rightarm[2][1][1][0][0] = left_color_r, rightarm[2][1][1][0][1] = left_color_g, rightarm[2][1][1][0][2] = left_color_b;
	rightarm[2][1][1][1][0] = left_color_r, rightarm[2][1][1][1][1] = left_color_g, rightarm[2][1][1][1][2] = left_color_b;
	rightarm[2][1][1][2][0] = left_color_r, rightarm[2][1][1][2][1] = left_color_g, rightarm[2][1][1][2][2] = left_color_b;

	// 후면 좌표
	rightarm[3][0][0][0][0] = back_left_top_x, rightarm[3][0][0][0][1] = back_left_top_y, rightarm[3][0][0][0][2] = back_left_top_z;
	rightarm[3][0][0][1][0] = back_left_down_x, rightarm[3][0][0][1][1] = back_left_down_y, rightarm[3][0][0][1][2] = back_left_down_z;
	rightarm[3][0][0][2][0] = back_right_top_x, rightarm[3][0][0][2][1] = back_right_top_y, rightarm[3][0][0][2][2] = back_right_top_z;

	rightarm[3][0][1][0][0] = back_right_top_x, rightarm[3][0][1][0][1] = back_right_top_y, rightarm[3][0][1][0][2] = back_right_top_z;
	rightarm[3][0][1][1][0] = back_left_down_x, rightarm[3][0][1][1][1] = back_left_down_y, rightarm[3][0][1][1][2] = back_left_down_z;
	rightarm[3][0][1][2][0] = back_right_down_x, rightarm[3][0][1][2][1] = back_right_down_y, rightarm[3][0][1][2][2] = back_right_down_z;

	// 후면 색상
	rightarm[3][1][0][0][0] = back_color_r, rightarm[3][1][0][0][1] = back_color_g, rightarm[3][1][0][0][2] = back_color_b;
	rightarm[3][1][0][1][0] = back_color_r, rightarm[3][1][0][1][1] = back_color_g, rightarm[3][1][0][1][2] = back_color_b;
	rightarm[3][1][0][2][0] = back_color_r, rightarm[3][1][0][2][1] = back_color_g, rightarm[3][1][0][2][2] = back_color_b;

	rightarm[3][1][1][0][0] = back_color_r, rightarm[3][1][1][0][1] = back_color_g, rightarm[3][1][1][0][2] = back_color_b;
	rightarm[3][1][1][1][0] = back_color_r, rightarm[3][1][1][1][1] = back_color_g, rightarm[3][1][1][1][2] = back_color_b;
	rightarm[3][1][1][2][0] = back_color_r, rightarm[3][1][1][2][1] = back_color_g, rightarm[3][1][1][2][2] = back_color_b;

	// 하단 좌표
	rightarm[4][0][0][0][0] = back_right_down_x, rightarm[4][0][0][0][1] = back_right_down_y, rightarm[4][0][0][0][2] = back_right_down_z;
	rightarm[4][0][0][1][0] = front_right_down_x, rightarm[4][0][0][1][1] = front_right_down_y, rightarm[4][0][0][1][2] = front_right_down_z;
	rightarm[4][0][0][2][0] = front_left_down_x, rightarm[4][0][0][2][1] = front_left_down_y, rightarm[4][0][0][2][2] = front_left_down_z;

	rightarm[4][0][1][0][0] = front_left_down_x, rightarm[4][0][1][0][1] = front_left_down_y, rightarm[4][0][1][0][2] = front_left_down_z;
	rightarm[4][0][1][1][0] = back_left_down_x, rightarm[4][0][1][1][1] = back_left_down_y, rightarm[4][0][1][1][2] = back_left_down_z;
	rightarm[4][0][1][2][0] = back_right_down_x, rightarm[4][0][1][2][1] = back_right_down_y, rightarm[4][0][1][2][2] = back_right_down_z;

	// 하단 색상
	rightarm[4][1][0][0][0] = bottom_color_r, rightarm[4][1][0][0][1] = bottom_color_g, rightarm[4][1][0][0][2] = bottom_color_b;
	rightarm[4][1][0][1][0] = bottom_color_r, rightarm[4][1][0][1][1] = bottom_color_g, rightarm[4][1][0][1][2] = bottom_color_b;
	rightarm[4][1][0][2][0] = bottom_color_r, rightarm[4][1][0][2][1] = bottom_color_g, rightarm[4][1][0][2][2] = bottom_color_b;

	rightarm[4][1][1][0][0] = bottom_color_r, rightarm[4][1][1][0][1] = bottom_color_g, rightarm[4][1][1][0][2] = bottom_color_b;
	rightarm[4][1][1][1][0] = bottom_color_r, rightarm[4][1][1][1][1] = bottom_color_g, rightarm[4][1][1][1][2] = bottom_color_b;
	rightarm[4][1][1][2][0] = bottom_color_r, rightarm[4][1][1][2][1] = bottom_color_g, rightarm[4][1][1][2][2] = bottom_color_b;

	// 우측 좌표
	rightarm[5][0][0][0][0] = back_right_down_x, rightarm[5][0][0][0][1] = back_right_down_y, rightarm[5][0][0][0][2] = back_right_down_z;
	rightarm[5][0][0][1][0] = back_right_top_x, rightarm[5][0][0][1][1] = back_right_top_y, rightarm[5][0][0][1][2] = back_right_top_z;
	rightarm[5][0][0][2][0] = front_right_down_x, rightarm[5][0][0][2][1] = front_right_down_y, rightarm[5][0][0][2][2] = front_right_down_z;

	rightarm[5][0][1][0][0] = front_right_down_x, rightarm[5][0][1][0][1] = front_right_down_y, rightarm[5][0][1][0][2] = front_right_down_z;
	rightarm[5][0][1][1][0] = back_right_top_x, rightarm[5][0][1][1][1] = back_right_top_y, rightarm[5][0][1][1][2] = back_right_top_z;
	rightarm[5][0][1][2][0] = front_right_top_x, rightarm[5][0][1][2][1] = front_right_top_y, rightarm[5][0][1][2][2] = front_right_top_z;

	// 우측 색상
	rightarm[5][1][0][0][0] = right_color_r, rightarm[5][1][0][0][1] = right_color_g, rightarm[5][1][0][0][2] = right_color_b;
	rightarm[5][1][0][1][0] = right_color_r, rightarm[5][1][0][1][1] = right_color_g, rightarm[5][1][0][1][2] = right_color_b;
	rightarm[5][1][0][2][0] = right_color_r, rightarm[5][1][0][2][1] = right_color_g, rightarm[5][1][0][2][2] = right_color_b;

	rightarm[5][1][1][0][0] = right_color_r, rightarm[5][1][1][0][1] = right_color_g, rightarm[5][1][1][0][2] = right_color_b;
	rightarm[5][1][1][1][0] = right_color_r, rightarm[5][1][1][1][1] = right_color_g, rightarm[5][1][1][1][2] = right_color_b;
	rightarm[5][1][1][2][0] = right_color_r, rightarm[5][1][1][2][1] = right_color_g, rightarm[5][1][1][2][2] = right_color_b;

	//rightleg

	front_left_down_x = -0.005f, front_left_down_y = -0.02f, front_left_down_z = 0.005f;		// 직육면체를 만들고 싶을 때 적절히 수정해줍니다.
	front_left_top_x = -0.005f, front_left_top_y = 0.02f, front_left_top_z = 0.005f;
	front_right_down_x = 0.005f, front_right_down_y = -0.02f, front_right_down_z = 0.005f;
	front_right_top_x = 0.005f, front_right_top_y = 0.02f, front_right_top_z = 0.005f;
	back_left_down_x = -0.005f, back_left_down_y = -0.02f, back_left_down_z = -0.005f;
	back_left_top_x = -0.005f, back_left_top_y = 0.02f, back_left_top_z = -0.005f;
	back_right_down_x = 0.005f, back_right_down_y = -0.02f, back_right_down_z = -0.005f;
	back_right_top_x = 0.005f, back_right_top_y = 0.02f, back_right_top_z = -0.005f;

	back_color_r = 1.0f, back_color_g = 1.0f, back_color_b = 0.0f;
	front_color_r = back_color_r, front_color_g = back_color_g, front_color_b = back_color_b;
	bottom_color_r = back_color_r, bottom_color_g = back_color_g, bottom_color_b = back_color_b;
	up_color_r = back_color_r, up_color_g = back_color_g, up_color_b = back_color_b;
	left_color_r = back_color_r, left_color_g = back_color_g, left_color_b = back_color_b;
	right_color_r = back_color_r, right_color_g = back_color_g, right_color_b = back_color_b;


	// 전면 좌표
	rightleg[0][0][0][0][0] = front_left_down_x, rightleg[0][0][0][0][1] = front_left_down_y, rightleg[0][0][0][0][2] = front_left_down_z;
	rightleg[0][0][0][1][0] = front_right_down_x, rightleg[0][0][0][1][1] = front_right_down_y, rightleg[0][0][0][1][2] = front_right_down_z;
	rightleg[0][0][0][2][0] = front_left_top_x, rightleg[0][0][0][2][1] = front_left_top_y, rightleg[0][0][0][2][2] = front_left_top_z;

	rightleg[0][0][1][0][0] = front_left_top_x, rightleg[0][0][1][0][1] = front_left_top_y, rightleg[0][0][1][0][2] = front_left_top_z;
	rightleg[0][0][1][1][0] = front_right_down_x, rightleg[0][0][1][1][1] = front_right_down_y, rightleg[0][0][1][1][2] = front_right_down_z;
	rightleg[0][0][1][2][0] = front_right_top_x, rightleg[0][0][1][2][1] = front_right_top_y, rightleg[0][0][1][2][2] = front_right_top_z;

	// 전면 색상
	rightleg[0][1][0][0][0] = front_color_r, rightleg[0][1][0][0][1] = front_color_g, rightleg[0][1][0][0][2] = front_color_b;
	rightleg[0][1][0][1][0] = front_color_r, rightleg[0][1][0][1][1] = front_color_g, rightleg[0][1][0][1][2] = front_color_b;
	rightleg[0][1][0][2][0] = front_color_r, rightleg[0][1][0][2][1] = front_color_g, rightleg[0][1][0][2][2] = front_color_b;

	rightleg[0][1][1][0][0] = front_color_r, rightleg[0][1][1][0][1] = front_color_g, rightleg[0][1][1][0][2] = front_color_b;
	rightleg[0][1][1][1][0] = front_color_r, rightleg[0][1][1][1][1] = front_color_g, rightleg[0][1][1][1][2] = front_color_b;
	rightleg[0][1][1][2][0] = front_color_r, rightleg[0][1][1][2][1] = front_color_g, rightleg[0][1][1][2][2] = front_color_b;


	// 상단 좌표
	rightleg[1][0][0][0][0] = front_right_top_x, rightleg[1][0][0][0][1] = front_right_top_y, rightleg[1][0][0][0][2] = front_right_top_z;
	rightleg[1][0][0][1][0] = back_right_top_x, rightleg[1][0][0][1][1] = back_right_top_y, rightleg[1][0][0][1][2] = back_right_top_z;
	rightleg[1][0][0][2][0] = front_left_top_x, rightleg[1][0][0][2][1] = front_left_top_y, rightleg[1][0][0][2][2] = front_left_top_z;

	rightleg[1][0][1][0][0] = front_left_top_x, rightleg[1][0][1][0][1] = front_left_top_y, rightleg[1][0][1][0][2] = front_left_top_z;
	rightleg[1][0][1][1][0] = back_right_top_x, rightleg[1][0][1][1][1] = back_right_top_y, rightleg[1][0][1][1][2] = back_right_top_z;
	rightleg[1][0][1][2][0] = back_left_top_x, rightleg[1][0][1][2][1] = back_left_top_y, rightleg[1][0][1][2][2] = back_left_top_z;

	// 상단 색상
	rightleg[1][1][0][0][0] = up_color_r, rightleg[1][1][0][0][1] = up_color_g, rightleg[1][1][0][0][2] = up_color_b;
	rightleg[1][1][0][1][0] = up_color_r, rightleg[1][1][0][1][1] = up_color_g, rightleg[1][1][0][1][2] = up_color_b;
	rightleg[1][1][0][2][0] = up_color_r, rightleg[1][1][0][2][1] = up_color_g, rightleg[1][1][0][2][2] = up_color_b;

	rightleg[1][1][1][0][0] = up_color_r, rightleg[1][1][1][0][1] = up_color_g, rightleg[1][1][1][0][2] = up_color_b;
	rightleg[1][1][1][1][0] = up_color_r, rightleg[1][1][1][1][1] = up_color_g, rightleg[1][1][1][1][2] = up_color_b;
	rightleg[1][1][1][2][0] = up_color_r, rightleg[1][1][1][2][1] = up_color_g, rightleg[1][1][1][2][2] = up_color_b;

	// 좌측 좌표
	rightleg[2][0][0][0][0] = back_left_top_x, rightleg[2][0][0][0][1] = back_left_top_y, rightleg[2][0][0][0][2] = back_left_top_z;
	rightleg[2][0][0][1][0] = back_left_down_x, rightleg[2][0][0][1][1] = back_left_down_y, rightleg[2][0][0][1][2] = back_left_down_z;
	rightleg[2][0][0][2][0] = front_left_down_x, rightleg[2][0][0][2][1] = front_left_down_y, rightleg[2][0][0][2][2] = front_left_down_z;

	rightleg[2][0][1][0][0] = front_left_down_x, rightleg[2][0][1][0][1] = front_left_down_y, rightleg[2][0][1][0][2] = front_left_down_z;
	rightleg[2][0][1][1][0] = front_left_top_x, rightleg[2][0][1][1][1] = front_left_top_y, rightleg[2][0][1][1][2] = front_left_top_z;
	rightleg[2][0][1][2][0] = back_left_top_x, rightleg[2][0][1][2][1] = back_left_top_y, rightleg[2][0][1][2][2] = back_left_top_z;

	// 좌측 색상
	rightleg[2][1][0][0][0] = left_color_r, rightleg[2][1][0][0][1] = left_color_g, rightleg[2][1][0][0][2] = left_color_b;
	rightleg[2][1][0][1][0] = left_color_r, rightleg[2][1][0][1][1] = left_color_g, rightleg[2][1][0][1][2] = left_color_b;
	rightleg[2][1][0][2][0] = left_color_r, rightleg[2][1][0][2][1] = left_color_g, rightleg[2][1][0][2][2] = left_color_b;

	rightleg[2][1][1][0][0] = left_color_r, rightleg[2][1][1][0][1] = left_color_g, rightleg[2][1][1][0][2] = left_color_b;
	rightleg[2][1][1][1][0] = left_color_r, rightleg[2][1][1][1][1] = left_color_g, rightleg[2][1][1][1][2] = left_color_b;
	rightleg[2][1][1][2][0] = left_color_r, rightleg[2][1][1][2][1] = left_color_g, rightleg[2][1][1][2][2] = left_color_b;

	// 후면 좌표
	rightleg[3][0][0][0][0] = back_left_top_x, rightleg[3][0][0][0][1] = back_left_top_y, rightleg[3][0][0][0][2] = back_left_top_z;
	rightleg[3][0][0][1][0] = back_left_down_x, rightleg[3][0][0][1][1] = back_left_down_y, rightleg[3][0][0][1][2] = back_left_down_z;
	rightleg[3][0][0][2][0] = back_right_top_x, rightleg[3][0][0][2][1] = back_right_top_y, rightleg[3][0][0][2][2] = back_right_top_z;

	rightleg[3][0][1][0][0] = back_right_top_x, rightleg[3][0][1][0][1] = back_right_top_y, rightleg[3][0][1][0][2] = back_right_top_z;
	rightleg[3][0][1][1][0] = back_left_down_x, rightleg[3][0][1][1][1] = back_left_down_y, rightleg[3][0][1][1][2] = back_left_down_z;
	rightleg[3][0][1][2][0] = back_right_down_x, rightleg[3][0][1][2][1] = back_right_down_y, rightleg[3][0][1][2][2] = back_right_down_z;

	// 후면 색상
	rightleg[3][1][0][0][0] = back_color_r, rightleg[3][1][0][0][1] = back_color_g, rightleg[3][1][0][0][2] = back_color_b;
	rightleg[3][1][0][1][0] = back_color_r, rightleg[3][1][0][1][1] = back_color_g, rightleg[3][1][0][1][2] = back_color_b;
	rightleg[3][1][0][2][0] = back_color_r, rightleg[3][1][0][2][1] = back_color_g, rightleg[3][1][0][2][2] = back_color_b;

	rightleg[3][1][1][0][0] = back_color_r, rightleg[3][1][1][0][1] = back_color_g, rightleg[3][1][1][0][2] = back_color_b;
	rightleg[3][1][1][1][0] = back_color_r, rightleg[3][1][1][1][1] = back_color_g, rightleg[3][1][1][1][2] = back_color_b;
	rightleg[3][1][1][2][0] = back_color_r, rightleg[3][1][1][2][1] = back_color_g, rightleg[3][1][1][2][2] = back_color_b;

	// 하단 좌표
	rightleg[4][0][0][0][0] = back_right_down_x, rightleg[4][0][0][0][1] = back_right_down_y, rightleg[4][0][0][0][2] = back_right_down_z;
	rightleg[4][0][0][1][0] = front_right_down_x, rightleg[4][0][0][1][1] = front_right_down_y, rightleg[4][0][0][1][2] = front_right_down_z;
	rightleg[4][0][0][2][0] = front_left_down_x, rightleg[4][0][0][2][1] = front_left_down_y, rightleg[4][0][0][2][2] = front_left_down_z;

	rightleg[4][0][1][0][0] = front_left_down_x, rightleg[4][0][1][0][1] = front_left_down_y, rightleg[4][0][1][0][2] = front_left_down_z;
	rightleg[4][0][1][1][0] = back_left_down_x, rightleg[4][0][1][1][1] = back_left_down_y, rightleg[4][0][1][1][2] = back_left_down_z;
	rightleg[4][0][1][2][0] = back_right_down_x, rightleg[4][0][1][2][1] = back_right_down_y, rightleg[4][0][1][2][2] = back_right_down_z;

	// 하단 색상
	rightleg[4][1][0][0][0] = bottom_color_r, rightleg[4][1][0][0][1] = bottom_color_g, rightleg[4][1][0][0][2] = bottom_color_b;
	rightleg[4][1][0][1][0] = bottom_color_r, rightleg[4][1][0][1][1] = bottom_color_g, rightleg[4][1][0][1][2] = bottom_color_b;
	rightleg[4][1][0][2][0] = bottom_color_r, rightleg[4][1][0][2][1] = bottom_color_g, rightleg[4][1][0][2][2] = bottom_color_b;

	rightleg[4][1][1][0][0] = bottom_color_r, rightleg[4][1][1][0][1] = bottom_color_g, rightleg[4][1][1][0][2] = bottom_color_b;
	rightleg[4][1][1][1][0] = bottom_color_r, rightleg[4][1][1][1][1] = bottom_color_g, rightleg[4][1][1][1][2] = bottom_color_b;
	rightleg[4][1][1][2][0] = bottom_color_r, rightleg[4][1][1][2][1] = bottom_color_g, rightleg[4][1][1][2][2] = bottom_color_b;

	// 우측 좌표
	rightleg[5][0][0][0][0] = back_right_down_x, rightleg[5][0][0][0][1] = back_right_down_y, rightleg[5][0][0][0][2] = back_right_down_z;
	rightleg[5][0][0][1][0] = back_right_top_x, rightleg[5][0][0][1][1] = back_right_top_y, rightleg[5][0][0][1][2] = back_right_top_z;
	rightleg[5][0][0][2][0] = front_right_down_x, rightleg[5][0][0][2][1] = front_right_down_y, rightleg[5][0][0][2][2] = front_right_down_z;

	rightleg[5][0][1][0][0] = front_right_down_x, rightleg[5][0][1][0][1] = front_right_down_y, rightleg[5][0][1][0][2] = front_right_down_z;
	rightleg[5][0][1][1][0] = back_right_top_x, rightleg[5][0][1][1][1] = back_right_top_y, rightleg[5][0][1][1][2] = back_right_top_z;
	rightleg[5][0][1][2][0] = front_right_top_x, rightleg[5][0][1][2][1] = front_right_top_y, rightleg[5][0][1][2][2] = front_right_top_z;

	// 우측 색상
	rightleg[5][1][0][0][0] = right_color_r, rightleg[5][1][0][0][1] = right_color_g, rightleg[5][1][0][0][2] = right_color_b;
	rightleg[5][1][0][1][0] = right_color_r, rightleg[5][1][0][1][1] = right_color_g, rightleg[5][1][0][1][2] = right_color_b;
	rightleg[5][1][0][2][0] = right_color_r, rightleg[5][1][0][2][1] = right_color_g, rightleg[5][1][0][2][2] = right_color_b;

	rightleg[5][1][1][0][0] = right_color_r, rightleg[5][1][1][0][1] = right_color_g, rightleg[5][1][1][0][2] = right_color_b;
	rightleg[5][1][1][1][0] = right_color_r, rightleg[5][1][1][1][1] = right_color_g, rightleg[5][1][1][1][2] = right_color_b;
	rightleg[5][1][1][2][0] = right_color_r, rightleg[5][1][1][2][1] = right_color_g, rightleg[5][1][1][2][2] = right_color_b;
}

void Robot::allReset()
{
	movement = 0;
	xPos = 0.05f, zPos = 0.05f, rotation = 90.0f;
	HeightFromGround[0] = 0.05f;
	HeightFromGround[1] = 0.03f;
	HeightFromGround[2] = 0.0f;
	HeightFromGround[3] = -0.04f;
	HeightFromGround[4] = 0.0f;
	HeightFromGround[5] = -0.04f;
	hanging = true;
}

void Robot::initBuffer()
{
	glGenVertexArrays(6, body_vao);
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(body_vao[i]);
		glGenBuffers(2, body_vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, body_vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), body[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}

	glGenVertexArrays(7, head_vao);
	for (int i = 0; i < 7; i++) {
		glBindVertexArray(head_vao[i]);
		glGenBuffers(2, head_vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, head_vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), head[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}

	glGenVertexArrays(6, leftarm_vao);
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(leftarm_vao[i]);
		glGenBuffers(2, leftarm_vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, leftarm_vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), leftarm[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}

	glGenVertexArrays(6, leftleg_vao);
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(leftleg_vao[i]);
		glGenBuffers(2, leftleg_vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, leftleg_vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), leftleg[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}

	glGenVertexArrays(6, rightarm_vao);
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(rightarm_vao[i]);
		glGenBuffers(2, rightarm_vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, rightarm_vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), rightarm[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}

	glGenVertexArrays(6, rightleg_vao);
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(rightleg_vao[i]);
		glGenBuffers(2, rightleg_vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, rightleg_vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), rightleg[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}
}

void Robot::body_draw()
{
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(body_vao[i]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void Robot::head_draw()
{
	for (int i = 0; i < 7; i++) {
		glBindVertexArray(head_vao[i]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void Robot::leftarm_draw()
{
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(leftarm_vao[i]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void Robot::leftleg_draw()
{
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(leftleg_vao[i]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void Robot::rightarm_draw()
{
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(rightarm_vao[i]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void Robot::rightleg_draw()
{
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(rightleg_vao[i]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void Robot::update(bool up, bool down, bool left, bool right)
{
	if (movement == 1) {
		rotation = 90.0f;
		if (!right) {
			xPos += 0.001f;
		}
	}
	else if (movement == 2) {
		rotation = 270.0f;
		if (!left) {
			xPos -= 0.001f;
		}
	}
	else if (movement == 3) {
		rotation = 180.0f;
		if (!down) {
			zPos -= 0.001f;
		}
	}
	else if (movement == 4) {
		rotation = 0.0f;
		if (!up) {
			zPos += 0.001f;
		}
	}
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

void Robot::putFactor(glm::mat4 inputFactor)
{
	bodyFactor = inputFactor;
	bodyFactor = glm::translate(bodyFactor, glm::vec3(xPos, 0.0f, zPos));
	bodyFactor = glm::translate(bodyFactor, glm::vec3(0.0f, HeightFromGround[0], 0.0f));	// 기본으로 세팅할 객체의 위치
	bodyFactor = glm::rotate(bodyFactor, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

	headFactor = bodyFactor;
	headFactor = glm::translate(headFactor, glm::vec3(0.0f, HeightFromGround[1], 0.0f));	// 기본으로 세팅할 객체의 위치

	leftarmFactor = bodyFactor;
	leftarmFactor = glm::translate(leftarmFactor, glm::vec3(-0.025f, HeightFromGround[2], 0.0f));	// 기본으로 세팅할 객체의 위치
	leftarmFactor = glm::translate(leftarmFactor, glm::vec3(0.0f, 0.02f, 0.0f));
	leftarmFactor = glm::rotate(leftarmFactor, glm::radians(hangingPos), glm::vec3(1.0f, 0.0f, 0.0f));
	leftarmFactor = glm::translate(leftarmFactor, glm::vec3(0.0f, -0.02f, 0.0f));

	leftlegFactor = bodyFactor;
	leftlegFactor = glm::translate(leftlegFactor, glm::vec3(-0.01f, HeightFromGround[3], 0.0f));	// 기본으로 세팅할 객체의 위치
	leftlegFactor = glm::translate(leftlegFactor, glm::vec3(0.0f, 0.02f, 0.0f));
	leftlegFactor = glm::rotate(leftlegFactor, glm::radians(-hangingPos), glm::vec3(1.0f, 0.0f, 0.0f));
	leftlegFactor = glm::translate(leftlegFactor, glm::vec3(0.0f, -0.02f, 0.0f));

	rightarmFactor = bodyFactor;
	rightarmFactor = glm::translate(rightarmFactor, glm::vec3(0.025f, HeightFromGround[4], 0.0f));	// 기본으로 세팅할 객체의 위치
	rightarmFactor = glm::translate(rightarmFactor, glm::vec3(0.0f, 0.02f, 0.0f));
	rightarmFactor = glm::rotate(rightarmFactor, glm::radians(-hangingPos), glm::vec3(1.0f, 0.0f, 0.0f));
	rightarmFactor = glm::translate(rightarmFactor, glm::vec3(0.0f, -0.02f, 0.0f));

	rightlegFactor = bodyFactor;
	rightlegFactor = glm::translate(rightlegFactor, glm::vec3(0.01f, HeightFromGround[5], 0.0f));	// 기본으로 세팅할 객체의 위치
	rightlegFactor = glm::translate(rightlegFactor, glm::vec3(0.0f, 0.02f, 0.0f));
	rightlegFactor = glm::rotate(rightlegFactor, glm::radians(hangingPos), glm::vec3(1.0f, 0.0f, 0.0f));
	rightlegFactor = glm::translate(rightlegFactor, glm::vec3(0.0f, -0.02f, 0.0f));
}

glm::mat4 Robot::getbodyFactor()
{
	return bodyFactor;
}

glm::mat4 Robot::getheadFactor()
{
	return headFactor;
}

glm::mat4 Robot::getleftarmFactor()
{
	return leftarmFactor;
}

glm::mat4 Robot::getleftlegFactor()
{
	return leftlegFactor;
}

glm::mat4 Robot::getrightarmFactor()
{
	return rightarmFactor;
}

glm::mat4 Robot::getrightlegFactor()
{
	return rightlegFactor;
}