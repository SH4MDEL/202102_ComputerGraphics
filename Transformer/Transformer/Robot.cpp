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

	//printf("%d\n", color(gen));

	// 전면 좌표
	body[0][0][0][0][0] = front_left_down_x, body[0][0][0][0][1] = front_left_down_y, body[0][0][0][0][2] = front_left_down_z;
	body[0][0][0][1][0] = front_right_down_x, body[0][0][0][1][1] = front_right_down_y, body[0][0][0][1][2] = front_right_down_z;
	body[0][0][0][2][0] = front_left_top_x, body[0][0][0][2][1] = front_left_top_y, body[0][0][0][2][2] = front_left_top_z;

	body[0][0][1][0][0] = front_left_top_x, body[0][0][1][0][1] = front_left_top_y, body[0][0][1][0][2] = front_left_top_z;
	body[0][0][1][1][0] = front_right_down_x, body[0][0][1][1][1] = front_right_down_y, body[0][0][1][1][2] = front_right_down_z;
	body[0][0][1][2][0] = front_right_top_x, body[0][0][1][2][1] = front_right_top_y, body[0][0][1][2][2] = front_right_top_z;

	// 전면 색상
	body[0][1][0][0][0] = 0.0f, body[0][1][0][0][1] = 0.0f, body[0][1][0][0][2] = 1.0f;
	body[0][1][0][1][0] = 0.0f, body[0][1][0][1][1] = 0.0f, body[0][1][0][1][2] = 1.0f;
	body[0][1][0][2][0] = 0.0f, body[0][1][0][2][1] = 0.0f, body[0][1][0][2][2] = 1.0f;

	body[0][1][1][0][0] = 0.0f, body[0][1][1][0][1] = 0.0f, body[0][1][1][0][2] = 1.0f;
	body[0][1][1][1][0] = 0.0f, body[0][1][1][1][1] = 0.0f, body[0][1][1][1][2] = 1.0f;
	body[0][1][1][2][0] = 0.0f, body[0][1][1][2][1] = 0.0f, body[0][1][1][2][2] = 1.0f;


	// 상단 좌표
	body[1][0][0][0][0] = front_right_top_x, body[1][0][0][0][1] = front_right_top_y, body[1][0][0][0][2] = front_right_top_z;
	body[1][0][0][1][0] = back_right_top_x, body[1][0][0][1][1] = back_right_top_y, body[1][0][0][1][2] = back_right_top_z;
	body[1][0][0][2][0] = front_left_top_x, body[1][0][0][2][1] = front_left_top_y, body[1][0][0][2][2] = front_left_top_z;

	body[1][0][1][0][0] = front_left_top_x, body[1][0][1][0][1] = front_left_top_y, body[1][0][1][0][2] = front_left_top_z;
	body[1][0][1][1][0] = back_right_top_x, body[1][0][1][1][1] = back_right_top_y, body[1][0][1][1][2] = back_right_top_z;
	body[1][0][1][2][0] = back_left_top_x, body[1][0][1][2][1] = back_left_top_y, body[1][0][1][2][2] = back_left_top_z;

	// 상단 색상
	body[1][1][0][0][0] = 0.0f, body[1][1][0][0][1] = 1.0f, body[1][1][0][0][2] = 0.0f;
	body[1][1][0][1][0] = 0.0f, body[1][1][0][1][1] = 1.0f, body[1][1][0][1][2] = 0.0f;
	body[1][1][0][2][0] = 0.0f, body[1][1][0][2][1] = 1.0f, body[1][1][0][2][2] = 0.0f;

	body[1][1][1][0][0] = 0.0f, body[1][1][1][0][1] = 1.0f, body[1][1][1][0][2] = 0.0f;
	body[1][1][1][1][0] = 0.0f, body[1][1][1][1][1] = 1.0f, body[1][1][1][1][2] = 0.0f;
	body[1][1][1][2][0] = 0.0f, body[1][1][1][2][1] = 1.0f, body[1][1][1][2][2] = 0.0f;

	// 좌측 좌표
	body[2][0][0][0][0] = back_left_top_x, body[2][0][0][0][1] = back_left_top_y, body[2][0][0][0][2] = back_left_top_z;
	body[2][0][0][1][0] = back_left_down_x, body[2][0][0][1][1] = back_left_down_y, body[2][0][0][1][2] = back_left_down_z;
	body[2][0][0][2][0] = front_left_down_x, body[2][0][0][2][1] = front_left_down_y, body[2][0][0][2][2] = front_left_down_z;

	body[2][0][1][0][0] = front_left_down_x, body[2][0][1][0][1] = front_left_down_y, body[2][0][1][0][2] = front_left_down_z;
	body[2][0][1][1][0] = front_left_top_x, body[2][0][1][1][1] = front_left_top_y, body[2][0][1][1][2] = front_left_top_z;
	body[2][0][1][2][0] = back_left_top_x, body[2][0][1][2][1] = back_left_top_y, body[2][0][1][2][2] = back_left_top_z;

	// 좌측 색상
	body[2][1][0][0][0] = -1.0f, body[2][1][0][0][1] = 0.0f, body[2][1][0][0][2] = 0.0f;
	body[2][1][0][1][0] = -1.0f, body[2][1][0][1][1] = 0.0f, body[2][1][0][1][2] = 0.0f;
	body[2][1][0][2][0] = -1.0f, body[2][1][0][2][1] = 0.0f, body[2][1][0][2][2] = 0.0f;

	body[2][1][1][0][0] = -1.0f, body[2][1][1][0][1] = 0.0f, body[2][1][1][0][2] = 0.0f;
	body[2][1][1][1][0] = -1.0f, body[2][1][1][1][1] = 0.0f, body[2][1][1][1][2] = 0.0f;
	body[2][1][1][2][0] = -1.0f, body[2][1][1][2][1] = 0.0f, body[2][1][1][2][2] = 0.0f;

	// 후면 좌표
	body[3][0][0][0][0] = back_left_top_x, body[3][0][0][0][1] = back_left_top_y, body[3][0][0][0][2] = back_left_top_z;
	body[3][0][0][1][0] = back_left_down_x, body[3][0][0][1][1] = back_left_down_y, body[3][0][0][1][2] = back_left_down_z;
	body[3][0][0][2][0] = back_right_top_x, body[3][0][0][2][1] = back_right_top_y, body[3][0][0][2][2] = back_right_top_z;

	body[3][0][1][0][0] = back_right_top_x, body[3][0][1][0][1] = back_right_top_y, body[3][0][1][0][2] = back_right_top_z;
	body[3][0][1][1][0] = back_left_down_x, body[3][0][1][1][1] = back_left_down_y, body[3][0][1][1][2] = back_left_down_z;
	body[3][0][1][2][0] = back_right_down_x, body[3][0][1][2][1] = back_right_down_y, body[3][0][1][2][2] = back_right_down_z;

	// 후면 색상
	body[3][1][0][0][0] = 0.0f, body[3][1][0][0][1] = 0.0f, body[3][1][0][0][2] = -1.0f;
	body[3][1][0][1][0] = 0.0f, body[3][1][0][1][1] = 0.0f, body[3][1][0][1][2] = -1.0f;
	body[3][1][0][2][0] = 0.0f, body[3][1][0][2][1] = 0.0f, body[3][1][0][2][2] = -1.0f;

	body[3][1][1][0][0] = 0.0f, body[3][1][1][0][1] = 0.0f, body[3][1][1][0][2] = -1.0f;
	body[3][1][1][1][0] = 0.0f, body[3][1][1][1][1] = 0.0f, body[3][1][1][1][2] = -1.0f;
	body[3][1][1][2][0] = 0.0f, body[3][1][1][2][1] = 0.0f, body[3][1][1][2][2] = -1.0f;

	// 하단 좌표
	body[4][0][0][0][0] = back_right_down_x, body[4][0][0][0][1] = back_right_down_y, body[4][0][0][0][2] = back_right_down_z;
	body[4][0][0][1][0] = front_right_down_x, body[4][0][0][1][1] = front_right_down_y, body[4][0][0][1][2] = front_right_down_z;
	body[4][0][0][2][0] = front_left_down_x, body[4][0][0][2][1] = front_left_down_y, body[4][0][0][2][2] = front_left_down_z;

	body[4][0][1][0][0] = front_left_down_x, body[4][0][1][0][1] = front_left_down_y, body[4][0][1][0][2] = front_left_down_z;
	body[4][0][1][1][0] = back_left_down_x, body[4][0][1][1][1] = back_left_down_y, body[4][0][1][1][2] = back_left_down_z;
	body[4][0][1][2][0] = back_right_down_x, body[4][0][1][2][1] = back_right_down_y, body[4][0][1][2][2] = back_right_down_z;

	// 하단 색상
	body[4][1][0][0][0] = 0.0f, body[4][1][0][0][1] = -1.0f, body[4][1][0][0][2] = 0.0f;
	body[4][1][0][1][0] = 0.0f, body[4][1][0][1][1] = -1.0f, body[4][1][0][1][2] = 0.0f;
	body[4][1][0][2][0] = 0.0f, body[4][1][0][2][1] = -1.0f, body[4][1][0][2][2] = 0.0f;

	body[4][1][1][0][0] = 0.0f, body[4][1][1][0][1] = -1.0f, body[4][1][1][0][2] = 0.0f;
	body[4][1][1][1][0] = 0.0f, body[4][1][1][1][1] = -1.0f, body[4][1][1][1][2] = 0.0f;
	body[4][1][1][2][0] = 0.0f, body[4][1][1][2][1] = -1.0f, body[4][1][1][2][2] = 0.0f;

	// 우측 좌표
	body[5][0][0][0][0] = back_right_down_x, body[5][0][0][0][1] = back_right_down_y, body[5][0][0][0][2] = back_right_down_z;
	body[5][0][0][1][0] = back_right_top_x, body[5][0][0][1][1] = back_right_top_y, body[5][0][0][1][2] = back_right_top_z;
	body[5][0][0][2][0] = front_right_down_x, body[5][0][0][2][1] = front_right_down_y, body[5][0][0][2][2] = front_right_down_z;

	body[5][0][1][0][0] = front_right_down_x, body[5][0][1][0][1] = front_right_down_y, body[5][0][1][0][2] = front_right_down_z;
	body[5][0][1][1][0] = back_right_top_x, body[5][0][1][1][1] = back_right_top_y, body[5][0][1][1][2] = back_right_top_z;
	body[5][0][1][2][0] = front_right_top_x, body[5][0][1][2][1] = front_right_top_y, body[5][0][1][2][2] = front_right_top_z;

	// 우측 색상
	body[5][1][0][0][0] = 1.0f, body[5][1][0][0][1] = 0.0f, body[5][1][0][0][2] = 0.0f;
	body[5][1][0][1][0] = 1.0f, body[5][1][0][1][1] = 0.0f, body[5][1][0][1][2] = 0.0f;
	body[5][1][0][2][0] = 1.0f, body[5][1][0][2][1] = 0.0f, body[5][1][0][2][2] = 0.0f;

	body[5][1][1][0][0] = 1.0f, body[5][1][1][0][1] = 0.0f, body[5][1][1][0][2] = 0.0f;
	body[5][1][1][1][0] = 1.0f, body[5][1][1][1][1] = 0.0f, body[5][1][1][1][2] = 0.0f;
	body[5][1][1][2][0] = 1.0f, body[5][1][1][2][1] = 0.0f, body[5][1][1][2][2] = 0.0f;

	// head

	front_left_down_x = -0.01f, front_left_down_y = -0.01f, front_left_down_z = 0.01f;		// 직육면체를 만들고 싶을 때 적절히 수정해줍니다.
	front_left_top_x = -0.01f, front_left_top_y = 0.01f, front_left_top_z = 0.01f;
	front_right_down_x = 0.01f, front_right_down_y = -0.01f, front_right_down_z = 0.01f;
	front_right_top_x = 0.01f, front_right_top_y = 0.01f, front_right_top_z = 0.01f;
	back_left_down_x = -0.01f, back_left_down_y = -0.01f, back_left_down_z = -0.01f;
	back_left_top_x = -0.01f, back_left_top_y = 0.01f, back_left_top_z = -0.01f;
	back_right_down_x = 0.01f, back_right_down_y = -0.01f, back_right_down_z = -0.01f;
	back_right_top_x = 0.01f, back_right_top_y = 0.01f, back_right_top_z = -0.01f;

	// 전면 좌표
	head[0][0][0][0][0] = front_left_down_x, head[0][0][0][0][1] = front_left_down_y, head[0][0][0][0][2] = front_left_down_z;
	head[0][0][0][1][0] = front_right_down_x, head[0][0][0][1][1] = front_right_down_y, head[0][0][0][1][2] = front_right_down_z;
	head[0][0][0][2][0] = front_left_top_x, head[0][0][0][2][1] = front_left_top_y, head[0][0][0][2][2] = front_left_top_z;

	head[0][0][1][0][0] = front_left_top_x, head[0][0][1][0][1] = front_left_top_y, head[0][0][1][0][2] = front_left_top_z;
	head[0][0][1][1][0] = front_right_down_x, head[0][0][1][1][1] = front_right_down_y, head[0][0][1][1][2] = front_right_down_z;
	head[0][0][1][2][0] = front_right_top_x, head[0][0][1][2][1] = front_right_top_y, head[0][0][1][2][2] = front_right_top_z;

	// 전면 색상
	head[0][1][0][0][0] = 0.0f, head[0][1][0][0][1] = 0.0f, head[0][1][0][0][2] = 1.0f;
	head[0][1][0][1][0] = 0.0f, head[0][1][0][1][1] = 0.0f, head[0][1][0][1][2] = 1.0f;
	head[0][1][0][2][0] = 0.0f, head[0][1][0][2][1] = 0.0f, head[0][1][0][2][2] = 1.0f;
																				  
	head[0][1][1][0][0] = 0.0f, head[0][1][1][0][1] = 0.0f, head[0][1][1][0][2] = 1.0f;
	head[0][1][1][1][0] = 0.0f, head[0][1][1][1][1] = 0.0f, head[0][1][1][1][2] = 1.0f;
	head[0][1][1][2][0] = 0.0f, head[0][1][1][2][1] = 0.0f, head[0][1][1][2][2] = 1.0f;


	// 상단 좌표
	head[1][0][0][0][0] = front_right_top_x, head[1][0][0][0][1] = front_right_top_y, head[1][0][0][0][2] = front_right_top_z;
	head[1][0][0][1][0] = back_right_top_x, head[1][0][0][1][1] = back_right_top_y, head[1][0][0][1][2] = back_right_top_z;
	head[1][0][0][2][0] = front_left_top_x, head[1][0][0][2][1] = front_left_top_y, head[1][0][0][2][2] = front_left_top_z;

	head[1][0][1][0][0] = front_left_top_x, head[1][0][1][0][1] = front_left_top_y, head[1][0][1][0][2] = front_left_top_z;
	head[1][0][1][1][0] = back_right_top_x, head[1][0][1][1][1] = back_right_top_y, head[1][0][1][1][2] = back_right_top_z;
	head[1][0][1][2][0] = back_left_top_x, head[1][0][1][2][1] = back_left_top_y, head[1][0][1][2][2] = back_left_top_z;

	// 상단 색상
	head[1][1][0][0][0] = 0.0f, head[1][1][0][0][1] = 1.0f, head[1][1][0][0][2] = 0.0f;
	head[1][1][0][1][0] = 0.0f, head[1][1][0][1][1] = 1.0f, head[1][1][0][1][2] = 0.0f;
	head[1][1][0][2][0] = 0.0f, head[1][1][0][2][1] = 1.0f, head[1][1][0][2][2] = 0.0f;
													  
	head[1][1][1][0][0] = 0.0f, head[1][1][1][0][1] = 1.0f, head[1][1][1][0][2] = 0.0f;
	head[1][1][1][1][0] = 0.0f, head[1][1][1][1][1] = 1.0f, head[1][1][1][1][2] = 0.0f;
	head[1][1][1][2][0] = 0.0f, head[1][1][1][2][1] = 1.0f, head[1][1][1][2][2] = 0.0f;

	// 좌측 좌표
	head[2][0][0][0][0] = back_left_top_x, head[2][0][0][0][1] = back_left_top_y, head[2][0][0][0][2] = back_left_top_z;
	head[2][0][0][1][0] = back_left_down_x, head[2][0][0][1][1] = back_left_down_y, head[2][0][0][1][2] = back_left_down_z;
	head[2][0][0][2][0] = front_left_down_x, head[2][0][0][2][1] = front_left_down_y, head[2][0][0][2][2] = front_left_down_z;

	head[2][0][1][0][0] = front_left_down_x, head[2][0][1][0][1] = front_left_down_y, head[2][0][1][0][2] = front_left_down_z;
	head[2][0][1][1][0] = front_left_top_x, head[2][0][1][1][1] = front_left_top_y, head[2][0][1][1][2] = front_left_top_z;
	head[2][0][1][2][0] = back_left_top_x, head[2][0][1][2][1] = back_left_top_y, head[2][0][1][2][2] = back_left_top_z;

	// 좌측 색상
	head[2][1][0][0][0] = -1.0f, head[2][1][0][0][1] = 0.0f, head[2][1][0][0][2] = 0.0f;
	head[2][1][0][1][0] = -1.0f, head[2][1][0][1][1] = 0.0f, head[2][1][0][1][2] = 0.0f;
	head[2][1][0][2][0] = -1.0f, head[2][1][0][2][1] = 0.0f, head[2][1][0][2][2] = 0.0f;
						  
	head[2][1][1][0][0] = -1.0f, head[2][1][1][0][1] = 0.0f, head[2][1][1][0][2] = 0.0f;
	head[2][1][1][1][0] = -1.0f, head[2][1][1][1][1] = 0.0f, head[2][1][1][1][2] = 0.0f;
	head[2][1][1][2][0] = -1.0f, head[2][1][1][2][1] = 0.0f, head[2][1][1][2][2] = 0.0f;

	// 후면 좌표
	head[3][0][0][0][0] = back_left_top_x, head[3][0][0][0][1] = back_left_top_y, head[3][0][0][0][2] = back_left_top_z;
	head[3][0][0][1][0] = back_left_down_x, head[3][0][0][1][1] = back_left_down_y, head[3][0][0][1][2] = back_left_down_z;
	head[3][0][0][2][0] = back_right_top_x, head[3][0][0][2][1] = back_right_top_y, head[3][0][0][2][2] = back_right_top_z;

	head[3][0][1][0][0] = back_right_top_x, head[3][0][1][0][1] = back_right_top_y, head[3][0][1][0][2] = back_right_top_z;
	head[3][0][1][1][0] = back_left_down_x, head[3][0][1][1][1] = back_left_down_y, head[3][0][1][1][2] = back_left_down_z;
	head[3][0][1][2][0] = back_right_down_x, head[3][0][1][2][1] = back_right_down_y, head[3][0][1][2][2] = back_right_down_z;

	// 후면 색상
	head[3][1][0][0][0] = 0.0f, head[3][1][0][0][1] = 0.0f, head[3][1][0][0][2] = -1.0f;
	head[3][1][0][1][0] = 0.0f, head[3][1][0][1][1] = 0.0f, head[3][1][0][1][2] = -1.0f;
	head[3][1][0][2][0] = 0.0f, head[3][1][0][2][1] = 0.0f, head[3][1][0][2][2] = -1.0f;
																				  
	head[3][1][1][0][0] = 0.0f, head[3][1][1][0][1] = 0.0f, head[3][1][1][0][2] = -1.0f;
	head[3][1][1][1][0] = 0.0f, head[3][1][1][1][1] = 0.0f, head[3][1][1][1][2] = -1.0f;
	head[3][1][1][2][0] = 0.0f, head[3][1][1][2][1] = 0.0f, head[3][1][1][2][2] = -1.0f;

	// 하단 좌표
	head[4][0][0][0][0] = back_right_down_x, head[4][0][0][0][1] = back_right_down_y, head[4][0][0][0][2] = back_right_down_z;
	head[4][0][0][1][0] = front_right_down_x, head[4][0][0][1][1] = front_right_down_y, head[4][0][0][1][2] = front_right_down_z;
	head[4][0][0][2][0] = front_left_down_x, head[4][0][0][2][1] = front_left_down_y, head[4][0][0][2][2] = front_left_down_z;

	head[4][0][1][0][0] = front_left_down_x, head[4][0][1][0][1] = front_left_down_y, head[4][0][1][0][2] = front_left_down_z;
	head[4][0][1][1][0] = back_left_down_x, head[4][0][1][1][1] = back_left_down_y, head[4][0][1][1][2] = back_left_down_z;
	head[4][0][1][2][0] = back_right_down_x, head[4][0][1][2][1] = back_right_down_y, head[4][0][1][2][2] = back_right_down_z;

	// 하단 색상
	head[4][1][0][0][0] = 0.0f, head[4][1][0][0][1] = -1.0f, head[4][1][0][0][2] = 0.0f;
	head[4][1][0][1][0] = 0.0f, head[4][1][0][1][1] = -1.0f, head[4][1][0][1][2] = 0.0f;
	head[4][1][0][2][0] = 0.0f, head[4][1][0][2][1] = -1.0f, head[4][1][0][2][2] = 0.0f;
													  
	head[4][1][1][0][0] = 0.0f, head[4][1][1][0][1] = -1.0f, head[4][1][1][0][2] = 0.0f;
	head[4][1][1][1][0] = 0.0f, head[4][1][1][1][1] = -1.0f, head[4][1][1][1][2] = 0.0f;
	head[4][1][1][2][0] = 0.0f, head[4][1][1][2][1] = -1.0f, head[4][1][1][2][2] = 0.0f;

	// 우측 좌표
	head[5][0][0][0][0] = back_right_down_x, head[5][0][0][0][1] = back_right_down_y, head[5][0][0][0][2] = back_right_down_z;
	head[5][0][0][1][0] = back_right_top_x, head[5][0][0][1][1] = back_right_top_y, head[5][0][0][1][2] = back_right_top_z;
	head[5][0][0][2][0] = front_right_down_x, head[5][0][0][2][1] = front_right_down_y, head[5][0][0][2][2] = front_right_down_z;

	head[5][0][1][0][0] = front_right_down_x, head[5][0][1][0][1] = front_right_down_y, head[5][0][1][0][2] = front_right_down_z;
	head[5][0][1][1][0] = back_right_top_x, head[5][0][1][1][1] = back_right_top_y, head[5][0][1][1][2] = back_right_top_z;
	head[5][0][1][2][0] = front_right_top_x, head[5][0][1][2][1] = front_right_top_y, head[5][0][1][2][2] = front_right_top_z;

	// 우측 색상
	head[5][1][0][0][0] = 1.0f, head[5][1][0][0][1] = 0.0f, head[5][1][0][0][2] = 0.0f;
	head[5][1][0][1][0] = 1.0f, head[5][1][0][1][1] = 0.0f, head[5][1][0][1][2] = 0.0f;
	head[5][1][0][2][0] = 1.0f, head[5][1][0][2][1] = 0.0f, head[5][1][0][2][2] = 0.0f;
						  
	head[5][1][1][0][0] = 1.0f, head[5][1][1][0][1] = 0.0f, head[5][1][1][0][2] = 0.0f;
	head[5][1][1][1][0] = 1.0f, head[5][1][1][1][1] = 0.0f, head[5][1][1][1][2] = 0.0f;
	head[5][1][1][2][0] = 1.0f, head[5][1][1][2][1] = 0.0f, head[5][1][1][2][2] = 0.0f;


	// 코 좌표
	head[6][0][0][0][0] = -0.001f, head[6][0][0][0][1] = -0.001f, head[6][0][0][0][2] = 0.011f;
	head[6][0][0][1][0] = 0.001f, head[6][0][0][1][1] = -0.001f, head[6][0][0][1][2] = 0.011f;
	head[6][0][0][2][0] = -0.001f, head[6][0][0][2][1] = 0.001f, head[6][0][0][2][2] = 0.011f;

	head[6][0][1][0][0] = -0.001f, head[6][0][1][0][1] = -0.001f, head[6][0][1][0][2] = 0.011f;
	head[6][0][1][1][0] = 0.001f, head[6][0][1][1][1] = -0.001f, head[6][0][1][1][2] = 0.011f;
	head[6][0][1][2][0] = 0.001f, head[6][0][1][2][1] = 0.001f, head[6][0][1][2][2] = 0.011f;

	// 코 노말
	head[6][1][0][0][0] = 0.0f, head[6][1][0][0][1] = 0.0f, head[6][1][0][0][2] = 1.0f;
	head[6][1][0][1][0] = 0.0f, head[6][1][0][1][1] = 0.0f, head[6][1][0][1][2] = 1.0f;
	head[6][1][0][2][0] = 0.0f, head[6][1][0][2][1] = 0.0f, head[6][1][0][2][2] = 1.0f;

	head[6][1][1][0][0] = 0.0f, head[6][1][1][0][1] = 0.0f, head[6][1][1][0][2] = 1.0f;
	head[6][1][1][1][0] = 0.0f, head[6][1][1][1][1] = 0.0f, head[6][1][1][1][2] = 1.0f;
	head[6][1][1][2][0] = 0.0f, head[6][1][1][2][1] = 0.0f, head[6][1][1][2][2] = 1.0f;

	// leftarm

	front_left_down_x = -0.005f, front_left_down_y = -0.02f, front_left_down_z = 0.005f;		// 직육면체를 만들고 싶을 때 적절히 수정해줍니다.
	front_left_top_x = -0.005f, front_left_top_y = 0.02f, front_left_top_z = 0.005f;
	front_right_down_x = 0.005f, front_right_down_y = -0.02f, front_right_down_z = 0.005f;
	front_right_top_x = 0.005f, front_right_top_y = 0.02f, front_right_top_z = 0.005f;
	back_left_down_x = -0.005f, back_left_down_y = -0.02f, back_left_down_z = -0.005f;
	back_left_top_x = -0.005f, back_left_top_y = 0.02f, back_left_top_z = -0.005f;
	back_right_down_x = 0.005f, back_right_down_y = -0.02f, back_right_down_z = -0.005f;
	back_right_top_x = 0.005f, back_right_top_y = 0.02f, back_right_top_z = -0.005f;

	// 전면 좌표
	leftarm[0][0][0][0][0] = front_left_down_x, leftarm[0][0][0][0][1] = front_left_down_y, leftarm[0][0][0][0][2] = front_left_down_z;
	leftarm[0][0][0][1][0] = front_right_down_x, leftarm[0][0][0][1][1] = front_right_down_y, leftarm[0][0][0][1][2] = front_right_down_z;
	leftarm[0][0][0][2][0] = front_left_top_x, leftarm[0][0][0][2][1] = front_left_top_y, leftarm[0][0][0][2][2] = front_left_top_z;

	leftarm[0][0][1][0][0] = front_left_top_x, leftarm[0][0][1][0][1] = front_left_top_y, leftarm[0][0][1][0][2] = front_left_top_z;
	leftarm[0][0][1][1][0] = front_right_down_x, leftarm[0][0][1][1][1] = front_right_down_y, leftarm[0][0][1][1][2] = front_right_down_z;
	leftarm[0][0][1][2][0] = front_right_top_x, leftarm[0][0][1][2][1] = front_right_top_y, leftarm[0][0][1][2][2] = front_right_top_z;

	// 전면 색상
	leftarm[0][1][0][0][0] = 0.0f, leftarm[0][1][0][0][1] = 0.0f, leftarm[0][1][0][0][2] = 1.0f;
	leftarm[0][1][0][1][0] = 0.0f, leftarm[0][1][0][1][1] = 0.0f, leftarm[0][1][0][1][2] = 1.0f;
	leftarm[0][1][0][2][0] = 0.0f, leftarm[0][1][0][2][1] = 0.0f, leftarm[0][1][0][2][2] = 1.0f;
																						   
	leftarm[0][1][1][0][0] = 0.0f, leftarm[0][1][1][0][1] = 0.0f, leftarm[0][1][1][0][2] = 1.0f;
	leftarm[0][1][1][1][0] = 0.0f, leftarm[0][1][1][1][1] = 0.0f, leftarm[0][1][1][1][2] = 1.0f;
	leftarm[0][1][1][2][0] = 0.0f, leftarm[0][1][1][2][1] = 0.0f, leftarm[0][1][1][2][2] = 1.0f;


	// 상단 좌표
	leftarm[1][0][0][0][0] = front_right_top_x, leftarm[1][0][0][0][1] = front_right_top_y, leftarm[1][0][0][0][2] = front_right_top_z;
	leftarm[1][0][0][1][0] = back_right_top_x, leftarm[1][0][0][1][1] = back_right_top_y, leftarm[1][0][0][1][2] = back_right_top_z;
	leftarm[1][0][0][2][0] = front_left_top_x, leftarm[1][0][0][2][1] = front_left_top_y, leftarm[1][0][0][2][2] = front_left_top_z;

	leftarm[1][0][1][0][0] = front_left_top_x, leftarm[1][0][1][0][1] = front_left_top_y, leftarm[1][0][1][0][2] = front_left_top_z;
	leftarm[1][0][1][1][0] = back_right_top_x, leftarm[1][0][1][1][1] = back_right_top_y, leftarm[1][0][1][1][2] = back_right_top_z;
	leftarm[1][0][1][2][0] = back_left_top_x, leftarm[1][0][1][2][1] = back_left_top_y, leftarm[1][0][1][2][2] = back_left_top_z;

	// 상단 색상
	leftarm[1][1][0][0][0] = 0.0f, leftarm[1][1][0][0][1] = 1.0f, leftarm[1][1][0][0][2] = 0.0f;
	leftarm[1][1][0][1][0] = 0.0f, leftarm[1][1][0][1][1] = 1.0f, leftarm[1][1][0][1][2] = 0.0f;
	leftarm[1][1][0][2][0] = 0.0f, leftarm[1][1][0][2][1] = 1.0f, leftarm[1][1][0][2][2] = 0.0f;
															
	leftarm[1][1][1][0][0] = 0.0f, leftarm[1][1][1][0][1] = 1.0f, leftarm[1][1][1][0][2] = 0.0f;
	leftarm[1][1][1][1][0] = 0.0f, leftarm[1][1][1][1][1] = 1.0f, leftarm[1][1][1][1][2] = 0.0f;
	leftarm[1][1][1][2][0] = 0.0f, leftarm[1][1][1][2][1] = 1.0f, leftarm[1][1][1][2][2] = 0.0f;

	// 좌측 좌표
	leftarm[2][0][0][0][0] = back_left_top_x, leftarm[2][0][0][0][1] = back_left_top_y, leftarm[2][0][0][0][2] = back_left_top_z;
	leftarm[2][0][0][1][0] = back_left_down_x, leftarm[2][0][0][1][1] = back_left_down_y, leftarm[2][0][0][1][2] = back_left_down_z;
	leftarm[2][0][0][2][0] = front_left_down_x, leftarm[2][0][0][2][1] = front_left_down_y, leftarm[2][0][0][2][2] = front_left_down_z;

	leftarm[2][0][1][0][0] = front_left_down_x, leftarm[2][0][1][0][1] = front_left_down_y, leftarm[2][0][1][0][2] = front_left_down_z;
	leftarm[2][0][1][1][0] = front_left_top_x, leftarm[2][0][1][1][1] = front_left_top_y, leftarm[2][0][1][1][2] = front_left_top_z;
	leftarm[2][0][1][2][0] = back_left_top_x, leftarm[2][0][1][2][1] = back_left_top_y, leftarm[2][0][1][2][2] = back_left_top_z;

	// 좌측 색상
	leftarm[2][1][0][0][0] = -1.0f, leftarm[2][1][0][0][1] = 0.0f, leftarm[2][1][0][0][2] = 0.0f;
	leftarm[2][1][0][1][0] = -1.0f, leftarm[2][1][0][1][1] = 0.0f, leftarm[2][1][0][1][2] = 0.0f;
	leftarm[2][1][0][2][0] = -1.0f, leftarm[2][1][0][2][1] = 0.0f, leftarm[2][1][0][2][2] = 0.0f;
							 
	leftarm[2][1][1][0][0] = -1.0f, leftarm[2][1][1][0][1] = 0.0f, leftarm[2][1][1][0][2] = 0.0f;
	leftarm[2][1][1][1][0] = -1.0f, leftarm[2][1][1][1][1] = 0.0f, leftarm[2][1][1][1][2] = 0.0f;
	leftarm[2][1][1][2][0] = -1.0f, leftarm[2][1][1][2][1] = 0.0f, leftarm[2][1][1][2][2] = 0.0f;

	// 후면 좌표
	leftarm[3][0][0][0][0] = back_left_top_x, leftarm[3][0][0][0][1] = back_left_top_y, leftarm[3][0][0][0][2] = back_left_top_z;
	leftarm[3][0][0][1][0] = back_left_down_x, leftarm[3][0][0][1][1] = back_left_down_y, leftarm[3][0][0][1][2] = back_left_down_z;
	leftarm[3][0][0][2][0] = back_right_top_x, leftarm[3][0][0][2][1] = back_right_top_y, leftarm[3][0][0][2][2] = back_right_top_z;

	leftarm[3][0][1][0][0] = back_right_top_x, leftarm[3][0][1][0][1] = back_right_top_y, leftarm[3][0][1][0][2] = back_right_top_z;
	leftarm[3][0][1][1][0] = back_left_down_x, leftarm[3][0][1][1][1] = back_left_down_y, leftarm[3][0][1][1][2] = back_left_down_z;
	leftarm[3][0][1][2][0] = back_right_down_x, leftarm[3][0][1][2][1] = back_right_down_y, leftarm[3][0][1][2][2] = back_right_down_z;

	// 후면 색상
	leftarm[3][1][0][0][0] = 0.0f, leftarm[3][1][0][0][1] = 0.0f, leftarm[3][1][0][0][2] = -1.0f;
	leftarm[3][1][0][1][0] = 0.0f, leftarm[3][1][0][1][1] = 0.0f, leftarm[3][1][0][1][2] = -1.0f;
	leftarm[3][1][0][2][0] = 0.0f, leftarm[3][1][0][2][1] = 0.0f, leftarm[3][1][0][2][2] = -1.0f;
																						   
	leftarm[3][1][1][0][0] = 0.0f, leftarm[3][1][1][0][1] = 0.0f, leftarm[3][1][1][0][2] = -1.0f;
	leftarm[3][1][1][1][0] = 0.0f, leftarm[3][1][1][1][1] = 0.0f, leftarm[3][1][1][1][2] = -1.0f;
	leftarm[3][1][1][2][0] = 0.0f, leftarm[3][1][1][2][1] = 0.0f, leftarm[3][1][1][2][2] = -1.0f;

	// 하단 좌표
	leftarm[4][0][0][0][0] = back_right_down_x, leftarm[4][0][0][0][1] = back_right_down_y, leftarm[4][0][0][0][2] = back_right_down_z;
	leftarm[4][0][0][1][0] = front_right_down_x, leftarm[4][0][0][1][1] = front_right_down_y, leftarm[4][0][0][1][2] = front_right_down_z;
	leftarm[4][0][0][2][0] = front_left_down_x, leftarm[4][0][0][2][1] = front_left_down_y, leftarm[4][0][0][2][2] = front_left_down_z;

	leftarm[4][0][1][0][0] = front_left_down_x, leftarm[4][0][1][0][1] = front_left_down_y, leftarm[4][0][1][0][2] = front_left_down_z;
	leftarm[4][0][1][1][0] = back_left_down_x, leftarm[4][0][1][1][1] = back_left_down_y, leftarm[4][0][1][1][2] = back_left_down_z;
	leftarm[4][0][1][2][0] = back_right_down_x, leftarm[4][0][1][2][1] = back_right_down_y, leftarm[4][0][1][2][2] = back_right_down_z;

	// 하단 색상
	leftarm[4][1][0][0][0] = 0.0f, leftarm[4][1][0][0][1] = -1.0f, leftarm[4][1][0][0][2] = 0.0f;
	leftarm[4][1][0][1][0] = 0.0f, leftarm[4][1][0][1][1] = -1.0f, leftarm[4][1][0][1][2] = 0.0f;
	leftarm[4][1][0][2][0] = 0.0f, leftarm[4][1][0][2][1] = -1.0f, leftarm[4][1][0][2][2] = 0.0f;
															
	leftarm[4][1][1][0][0] = 0.0f, leftarm[4][1][1][0][1] = -1.0f, leftarm[4][1][1][0][2] = 0.0f;
	leftarm[4][1][1][1][0] = 0.0f, leftarm[4][1][1][1][1] = -1.0f, leftarm[4][1][1][1][2] = 0.0f;
	leftarm[4][1][1][2][0] = 0.0f, leftarm[4][1][1][2][1] = -1.0f, leftarm[4][1][1][2][2] = 0.0f;

	// 우측 좌표
	leftarm[5][0][0][0][0] = back_right_down_x, leftarm[5][0][0][0][1] = back_right_down_y, leftarm[5][0][0][0][2] = back_right_down_z;
	leftarm[5][0][0][1][0] = back_right_top_x, leftarm[5][0][0][1][1] = back_right_top_y, leftarm[5][0][0][1][2] = back_right_top_z;
	leftarm[5][0][0][2][0] = front_right_down_x, leftarm[5][0][0][2][1] = front_right_down_y, leftarm[5][0][0][2][2] = front_right_down_z;

	leftarm[5][0][1][0][0] = front_right_down_x, leftarm[5][0][1][0][1] = front_right_down_y, leftarm[5][0][1][0][2] = front_right_down_z;
	leftarm[5][0][1][1][0] = back_right_top_x, leftarm[5][0][1][1][1] = back_right_top_y, leftarm[5][0][1][1][2] = back_right_top_z;
	leftarm[5][0][1][2][0] = front_right_top_x, leftarm[5][0][1][2][1] = front_right_top_y, leftarm[5][0][1][2][2] = front_right_top_z;

	// 우측 색상
	leftarm[5][1][0][0][0] = 1.0f, leftarm[5][1][0][0][1] = 0.0f, leftarm[5][1][0][0][2] = 0.0f;
	leftarm[5][1][0][1][0] = 1.0f, leftarm[5][1][0][1][1] = 0.0f, leftarm[5][1][0][1][2] = 0.0f;
	leftarm[5][1][0][2][0] = 1.0f, leftarm[5][1][0][2][1] = 0.0f, leftarm[5][1][0][2][2] = 0.0f;
							 
	leftarm[5][1][1][0][0] = 1.0f, leftarm[5][1][1][0][1] = 0.0f, leftarm[5][1][1][0][2] = 0.0f;
	leftarm[5][1][1][1][0] = 1.0f, leftarm[5][1][1][1][1] = 0.0f, leftarm[5][1][1][1][2] = 0.0f;
	leftarm[5][1][1][2][0] = 1.0f, leftarm[5][1][1][2][1] = 0.0f, leftarm[5][1][1][2][2] = 0.0f;

	// leftleg

	front_left_down_x = -0.005f, front_left_down_y = -0.02f, front_left_down_z = 0.005f;		// 직육면체를 만들고 싶을 때 적절히 수정해줍니다.
	front_left_top_x = -0.005f, front_left_top_y = 0.02f, front_left_top_z = 0.005f;
	front_right_down_x = 0.005f, front_right_down_y = -0.02f, front_right_down_z = 0.005f;
	front_right_top_x = 0.005f, front_right_top_y = 0.02f, front_right_top_z = 0.005f;
	back_left_down_x = -0.005f, back_left_down_y = -0.02f, back_left_down_z = -0.005f;
	back_left_top_x = -0.005f, back_left_top_y = 0.02f, back_left_top_z = -0.005f;
	back_right_down_x = 0.005f, back_right_down_y = -0.02f, back_right_down_z = -0.005f;
	back_right_top_x = 0.005f, back_right_top_y = 0.02f, back_right_top_z = -0.005f;

	// 전면 좌표
	leftleg[0][0][0][0][0] = front_left_down_x, leftleg[0][0][0][0][1] = front_left_down_y, leftleg[0][0][0][0][2] = front_left_down_z;
	leftleg[0][0][0][1][0] = front_right_down_x, leftleg[0][0][0][1][1] = front_right_down_y, leftleg[0][0][0][1][2] = front_right_down_z;
	leftleg[0][0][0][2][0] = front_left_top_x, leftleg[0][0][0][2][1] = front_left_top_y, leftleg[0][0][0][2][2] = front_left_top_z;

	leftleg[0][0][1][0][0] = front_left_top_x, leftleg[0][0][1][0][1] = front_left_top_y, leftleg[0][0][1][0][2] = front_left_top_z;
	leftleg[0][0][1][1][0] = front_right_down_x, leftleg[0][0][1][1][1] = front_right_down_y, leftleg[0][0][1][1][2] = front_right_down_z;
	leftleg[0][0][1][2][0] = front_right_top_x, leftleg[0][0][1][2][1] = front_right_top_y, leftleg[0][0][1][2][2] = front_right_top_z;

	// 전면 색상
	leftleg[0][1][0][0][0] = 0.0f, leftleg[0][1][0][0][1] = 0.0f, leftleg[0][1][0][0][2] = 1.0f;
	leftleg[0][1][0][1][0] = 0.0f, leftleg[0][1][0][1][1] = 0.0f, leftleg[0][1][0][1][2] = 1.0f;
	leftleg[0][1][0][2][0] = 0.0f, leftleg[0][1][0][2][1] = 0.0f, leftleg[0][1][0][2][2] = 1.0f;
																						   
	leftleg[0][1][1][0][0] = 0.0f, leftleg[0][1][1][0][1] = 0.0f, leftleg[0][1][1][0][2] = 1.0f;
	leftleg[0][1][1][1][0] = 0.0f, leftleg[0][1][1][1][1] = 0.0f, leftleg[0][1][1][1][2] = 1.0f;
	leftleg[0][1][1][2][0] = 0.0f, leftleg[0][1][1][2][1] = 0.0f, leftleg[0][1][1][2][2] = 1.0f;


	// 상단 좌표
	leftleg[1][0][0][0][0] = front_right_top_x, leftleg[1][0][0][0][1] = front_right_top_y, leftleg[1][0][0][0][2] = front_right_top_z;
	leftleg[1][0][0][1][0] = back_right_top_x, leftleg[1][0][0][1][1] = back_right_top_y, leftleg[1][0][0][1][2] = back_right_top_z;
	leftleg[1][0][0][2][0] = front_left_top_x, leftleg[1][0][0][2][1] = front_left_top_y, leftleg[1][0][0][2][2] = front_left_top_z;

	leftleg[1][0][1][0][0] = front_left_top_x, leftleg[1][0][1][0][1] = front_left_top_y, leftleg[1][0][1][0][2] = front_left_top_z;
	leftleg[1][0][1][1][0] = back_right_top_x, leftleg[1][0][1][1][1] = back_right_top_y, leftleg[1][0][1][1][2] = back_right_top_z;
	leftleg[1][0][1][2][0] = back_left_top_x, leftleg[1][0][1][2][1] = back_left_top_y, leftleg[1][0][1][2][2] = back_left_top_z;

	// 상단 색상
	leftleg[1][1][0][0][0] = 0.0f, leftleg[1][1][0][0][1] = 1.0f, leftleg[1][1][0][0][2] = 0.0f;
	leftleg[1][1][0][1][0] = 0.0f, leftleg[1][1][0][1][1] = 1.0f, leftleg[1][1][0][1][2] = 0.0f;
	leftleg[1][1][0][2][0] = 0.0f, leftleg[1][1][0][2][1] = 1.0f, leftleg[1][1][0][2][2] = 0.0f;
															
	leftleg[1][1][1][0][0] = 0.0f, leftleg[1][1][1][0][1] = 1.0f, leftleg[1][1][1][0][2] = 0.0f;
	leftleg[1][1][1][1][0] = 0.0f, leftleg[1][1][1][1][1] = 1.0f, leftleg[1][1][1][1][2] = 0.0f;
	leftleg[1][1][1][2][0] = 0.0f, leftleg[1][1][1][2][1] = 1.0f, leftleg[1][1][1][2][2] = 0.0f;

	// 좌측 좌표
	leftleg[2][0][0][0][0] = back_left_top_x, leftleg[2][0][0][0][1] = back_left_top_y, leftleg[2][0][0][0][2] = back_left_top_z;
	leftleg[2][0][0][1][0] = back_left_down_x, leftleg[2][0][0][1][1] = back_left_down_y, leftleg[2][0][0][1][2] = back_left_down_z;
	leftleg[2][0][0][2][0] = front_left_down_x, leftleg[2][0][0][2][1] = front_left_down_y, leftleg[2][0][0][2][2] = front_left_down_z;

	leftleg[2][0][1][0][0] = front_left_down_x, leftleg[2][0][1][0][1] = front_left_down_y, leftleg[2][0][1][0][2] = front_left_down_z;
	leftleg[2][0][1][1][0] = front_left_top_x, leftleg[2][0][1][1][1] = front_left_top_y, leftleg[2][0][1][1][2] = front_left_top_z;
	leftleg[2][0][1][2][0] = back_left_top_x, leftleg[2][0][1][2][1] = back_left_top_y, leftleg[2][0][1][2][2] = back_left_top_z;

	// 좌측 색상
	leftleg[2][1][0][0][0] = -1.0f, leftleg[2][1][0][0][1] = 0.0f, leftleg[2][1][0][0][2] = 0.0f;
	leftleg[2][1][0][1][0] = -1.0f, leftleg[2][1][0][1][1] = 0.0f, leftleg[2][1][0][1][2] = 0.0f;
	leftleg[2][1][0][2][0] = -1.0f, leftleg[2][1][0][2][1] = 0.0f, leftleg[2][1][0][2][2] = 0.0f;
							 
	leftleg[2][1][1][0][0] = -1.0f, leftleg[2][1][1][0][1] = 0.0f, leftleg[2][1][1][0][2] = 0.0f;
	leftleg[2][1][1][1][0] = -1.0f, leftleg[2][1][1][1][1] = 0.0f, leftleg[2][1][1][1][2] = 0.0f;
	leftleg[2][1][1][2][0] = -1.0f, leftleg[2][1][1][2][1] = 0.0f, leftleg[2][1][1][2][2] = 0.0f;

	// 후면 좌표
	leftleg[3][0][0][0][0] = back_left_top_x, leftleg[3][0][0][0][1] = back_left_top_y, leftleg[3][0][0][0][2] = back_left_top_z;
	leftleg[3][0][0][1][0] = back_left_down_x, leftleg[3][0][0][1][1] = back_left_down_y, leftleg[3][0][0][1][2] = back_left_down_z;
	leftleg[3][0][0][2][0] = back_right_top_x, leftleg[3][0][0][2][1] = back_right_top_y, leftleg[3][0][0][2][2] = back_right_top_z;

	leftleg[3][0][1][0][0] = back_right_top_x, leftleg[3][0][1][0][1] = back_right_top_y, leftleg[3][0][1][0][2] = back_right_top_z;
	leftleg[3][0][1][1][0] = back_left_down_x, leftleg[3][0][1][1][1] = back_left_down_y, leftleg[3][0][1][1][2] = back_left_down_z;
	leftleg[3][0][1][2][0] = back_right_down_x, leftleg[3][0][1][2][1] = back_right_down_y, leftleg[3][0][1][2][2] = back_right_down_z;



	// 후면 색상
	leftleg[3][1][0][0][0] = 0.0f, leftleg[3][1][0][0][1] = 0.0f, leftleg[3][1][0][0][2] = 0.0f;
	leftleg[3][1][0][1][0] = 0.0f, leftleg[3][1][0][1][1] = 0.0f, leftleg[3][1][0][1][2] = 0.0f;
	leftleg[3][1][0][2][0] = 0.0f, leftleg[3][1][0][2][1] = 0.0f, leftleg[3][1][0][2][2] = 0.0f;

	leftleg[3][1][1][0][0] = 0.0f, leftleg[3][1][1][0][1] = 0.0f, leftleg[3][1][1][0][2] = 0.0f;
	leftleg[3][1][1][1][0] = 0.0f, leftleg[3][1][1][1][1] = 0.0f, leftleg[3][1][1][1][2] = 0.0f;
	leftleg[3][1][1][2][0] = 0.0f, leftleg[3][1][1][2][1] = 0.0f, leftleg[3][1][1][2][2] = 0.0f;

	// 하단 좌표
	leftleg[4][0][0][0][0] = back_right_down_x, leftleg[4][0][0][0][1] = back_right_down_y, leftleg[4][0][0][0][2] = back_right_down_z;
	leftleg[4][0][0][1][0] = front_right_down_x, leftleg[4][0][0][1][1] = front_right_down_y, leftleg[4][0][0][1][2] = front_right_down_z;
	leftleg[4][0][0][2][0] = front_left_down_x, leftleg[4][0][0][2][1] = front_left_down_y, leftleg[4][0][0][2][2] = front_left_down_z;

	leftleg[4][0][1][0][0] = front_left_down_x, leftleg[4][0][1][0][1] = front_left_down_y, leftleg[4][0][1][0][2] = front_left_down_z;
	leftleg[4][0][1][1][0] = back_left_down_x, leftleg[4][0][1][1][1] = back_left_down_y, leftleg[4][0][1][1][2] = back_left_down_z;
	leftleg[4][0][1][2][0] = back_right_down_x, leftleg[4][0][1][2][1] = back_right_down_y, leftleg[4][0][1][2][2] = back_right_down_z;

	// 하단 색상
	leftleg[4][1][0][0][0] = 0.0f, leftleg[4][1][0][0][1] = 0.0f, leftleg[4][1][0][0][2] = 0.0f;
	leftleg[4][1][0][1][0] = 0.0f, leftleg[4][1][0][1][1] = 0.0f, leftleg[4][1][0][1][2] = 0.0f;
	leftleg[4][1][0][2][0] = 0.0f, leftleg[4][1][0][2][1] = 0.0f, leftleg[4][1][0][2][2] = 0.0f;

	leftleg[4][1][1][0][0] = 0.0f, leftleg[4][1][1][0][1] = 0.0f, leftleg[4][1][1][0][2] = 0.0f;
	leftleg[4][1][1][1][0] = 0.0f, leftleg[4][1][1][1][1] = 0.0f, leftleg[4][1][1][1][2] = 0.0f;
	leftleg[4][1][1][2][0] = 0.0f, leftleg[4][1][1][2][1] = 0.0f, leftleg[4][1][1][2][2] = 0.0f;

	// 우측 좌표
	leftleg[5][0][0][0][0] = back_right_down_x, leftleg[5][0][0][0][1] = back_right_down_y, leftleg[5][0][0][0][2] = back_right_down_z;
	leftleg[5][0][0][1][0] = back_right_top_x, leftleg[5][0][0][1][1] = back_right_top_y, leftleg[5][0][0][1][2] = back_right_top_z;
	leftleg[5][0][0][2][0] = front_right_down_x, leftleg[5][0][0][2][1] = front_right_down_y, leftleg[5][0][0][2][2] = front_right_down_z;

	leftleg[5][0][1][0][0] = front_right_down_x, leftleg[5][0][1][0][1] = front_right_down_y, leftleg[5][0][1][0][2] = front_right_down_z;
	leftleg[5][0][1][1][0] = back_right_top_x, leftleg[5][0][1][1][1] = back_right_top_y, leftleg[5][0][1][1][2] = back_right_top_z;
	leftleg[5][0][1][2][0] = front_right_top_x, leftleg[5][0][1][2][1] = front_right_top_y, leftleg[5][0][1][2][2] = front_right_top_z;

	// 우측 색상
	leftleg[5][1][0][0][0] = 0.0f, leftleg[5][1][0][0][1] = 0.0f, leftleg[5][1][0][0][2] = 0.0f;
	leftleg[5][1][0][1][0] = 0.0f, leftleg[5][1][0][1][1] = 0.0f, leftleg[5][1][0][1][2] = 0.0f;
	leftleg[5][1][0][2][0] = 0.0f, leftleg[5][1][0][2][1] = 0.0f, leftleg[5][1][0][2][2] = 0.0f;

	leftleg[5][1][1][0][0] = 0.0f, leftleg[5][1][1][0][1] = 0.0f, leftleg[5][1][1][0][2] = 0.0f;
	leftleg[5][1][1][1][0] = 0.0f, leftleg[5][1][1][1][1] = 0.0f, leftleg[5][1][1][1][2] = 0.0f;
	leftleg[5][1][1][2][0] = 0.0f, leftleg[5][1][1][2][1] = 0.0f, leftleg[5][1][1][2][2] = 0.0f;

	// rightarm

	front_left_down_x = -0.005f, front_left_down_y = -0.02f, front_left_down_z = 0.005f;		// 직육면체를 만들고 싶을 때 적절히 수정해줍니다.
	front_left_top_x = -0.005f, front_left_top_y = 0.02f, front_left_top_z = 0.005f;
	front_right_down_x = 0.005f, front_right_down_y = -0.02f, front_right_down_z = 0.005f;
	front_right_top_x = 0.005f, front_right_top_y = 0.02f, front_right_top_z = 0.005f;
	back_left_down_x = -0.005f, back_left_down_y = -0.02f, back_left_down_z = -0.005f;
	back_left_top_x = -0.005f, back_left_top_y = 0.02f, back_left_top_z = -0.005f;
	back_right_down_x = 0.005f, back_right_down_y = -0.02f, back_right_down_z = -0.005f;
	back_right_top_x = 0.005f, back_right_top_y = 0.02f, back_right_top_z = -0.005f;

	// 전면 좌표
	rightarm[0][0][0][0][0] = front_left_down_x, rightarm[0][0][0][0][1] = front_left_down_y, rightarm[0][0][0][0][2] = front_left_down_z;
	rightarm[0][0][0][1][0] = front_right_down_x, rightarm[0][0][0][1][1] = front_right_down_y, rightarm[0][0][0][1][2] = front_right_down_z;
	rightarm[0][0][0][2][0] = front_left_top_x, rightarm[0][0][0][2][1] = front_left_top_y, rightarm[0][0][0][2][2] = front_left_top_z;

	rightarm[0][0][1][0][0] = front_left_top_x, rightarm[0][0][1][0][1] = front_left_top_y, rightarm[0][0][1][0][2] = front_left_top_z;
	rightarm[0][0][1][1][0] = front_right_down_x, rightarm[0][0][1][1][1] = front_right_down_y, rightarm[0][0][1][1][2] = front_right_down_z;
	rightarm[0][0][1][2][0] = front_right_top_x, rightarm[0][0][1][2][1] = front_right_top_y, rightarm[0][0][1][2][2] = front_right_top_z;

	// 전면 색상
	rightarm[0][1][0][0][0] = 0.0f, rightarm[0][1][0][0][1] = 0.0f, rightarm[0][1][0][0][2] = 0.0f;
	rightarm[0][1][0][1][0] = 0.0f, rightarm[0][1][0][1][1] = 0.0f, rightarm[0][1][0][1][2] = 0.0f;
	rightarm[0][1][0][2][0] = 0.0f, rightarm[0][1][0][2][1] = 0.0f, rightarm[0][1][0][2][2] = 0.0f;

	rightarm[0][1][1][0][0] = 0.0f, rightarm[0][1][1][0][1] = 0.0f, rightarm[0][1][1][0][2] = 0.0f;
	rightarm[0][1][1][1][0] = 0.0f, rightarm[0][1][1][1][1] = 0.0f, rightarm[0][1][1][1][2] = 0.0f;
	rightarm[0][1][1][2][0] = 0.0f, rightarm[0][1][1][2][1] = 0.0f, rightarm[0][1][1][2][2] = 0.0f;


	// 상단 좌표
	rightarm[1][0][0][0][0] = front_right_top_x, rightarm[1][0][0][0][1] = front_right_top_y, rightarm[1][0][0][0][2] = front_right_top_z;
	rightarm[1][0][0][1][0] = back_right_top_x, rightarm[1][0][0][1][1] = back_right_top_y, rightarm[1][0][0][1][2] = back_right_top_z;
	rightarm[1][0][0][2][0] = front_left_top_x, rightarm[1][0][0][2][1] = front_left_top_y, rightarm[1][0][0][2][2] = front_left_top_z;

	rightarm[1][0][1][0][0] = front_left_top_x, rightarm[1][0][1][0][1] = front_left_top_y, rightarm[1][0][1][0][2] = front_left_top_z;
	rightarm[1][0][1][1][0] = back_right_top_x, rightarm[1][0][1][1][1] = back_right_top_y, rightarm[1][0][1][1][2] = back_right_top_z;
	rightarm[1][0][1][2][0] = back_left_top_x, rightarm[1][0][1][2][1] = back_left_top_y, rightarm[1][0][1][2][2] = back_left_top_z;

	// 상단 색상
	rightarm[1][1][0][0][0] = 0.0f, rightarm[1][1][0][0][1] = 0.0f, rightarm[1][1][0][0][2] = 0.0f;
	rightarm[1][1][0][1][0] = 0.0f, rightarm[1][1][0][1][1] = 0.0f, rightarm[1][1][0][1][2] = 0.0f;
	rightarm[1][1][0][2][0] = 0.0f, rightarm[1][1][0][2][1] = 0.0f, rightarm[1][1][0][2][2] = 0.0f;

	rightarm[1][1][1][0][0] = 0.0f, rightarm[1][1][1][0][1] = 0.0f, rightarm[1][1][1][0][2] = 0.0f;
	rightarm[1][1][1][1][0] = 0.0f, rightarm[1][1][1][1][1] = 0.0f, rightarm[1][1][1][1][2] = 0.0f;
	rightarm[1][1][1][2][0] = 0.0f, rightarm[1][1][1][2][1] = 0.0f, rightarm[1][1][1][2][2] = 0.0f;

	// 좌측 좌표
	rightarm[2][0][0][0][0] = back_left_top_x, rightarm[2][0][0][0][1] = back_left_top_y, rightarm[2][0][0][0][2] = back_left_top_z;
	rightarm[2][0][0][1][0] = back_left_down_x, rightarm[2][0][0][1][1] = back_left_down_y, rightarm[2][0][0][1][2] = back_left_down_z;
	rightarm[2][0][0][2][0] = front_left_down_x, rightarm[2][0][0][2][1] = front_left_down_y, rightarm[2][0][0][2][2] = front_left_down_z;

	rightarm[2][0][1][0][0] = front_left_down_x, rightarm[2][0][1][0][1] = front_left_down_y, rightarm[2][0][1][0][2] = front_left_down_z;
	rightarm[2][0][1][1][0] = front_left_top_x, rightarm[2][0][1][1][1] = front_left_top_y, rightarm[2][0][1][1][2] = front_left_top_z;
	rightarm[2][0][1][2][0] = back_left_top_x, rightarm[2][0][1][2][1] = back_left_top_y, rightarm[2][0][1][2][2] = back_left_top_z;

	// 좌측 색상
	rightarm[2][1][0][0][0] = 0.0f, rightarm[2][1][0][0][1] = 0.0f, rightarm[2][1][0][0][2] = 0.0f;
	rightarm[2][1][0][1][0] = 0.0f, rightarm[2][1][0][1][1] = 0.0f, rightarm[2][1][0][1][2] = 0.0f;
	rightarm[2][1][0][2][0] = 0.0f, rightarm[2][1][0][2][1] = 0.0f, rightarm[2][1][0][2][2] = 0.0f;

	rightarm[2][1][1][0][0] = 0.0f, rightarm[2][1][1][0][1] = 0.0f, rightarm[2][1][1][0][2] = 0.0f;
	rightarm[2][1][1][1][0] = 0.0f, rightarm[2][1][1][1][1] = 0.0f, rightarm[2][1][1][1][2] = 0.0f;
	rightarm[2][1][1][2][0] = 0.0f, rightarm[2][1][1][2][1] = 0.0f, rightarm[2][1][1][2][2] = 0.0f;

	// 후면 좌표
	rightarm[3][0][0][0][0] = back_left_top_x, rightarm[3][0][0][0][1] = back_left_top_y, rightarm[3][0][0][0][2] = back_left_top_z;
	rightarm[3][0][0][1][0] = back_left_down_x, rightarm[3][0][0][1][1] = back_left_down_y, rightarm[3][0][0][1][2] = back_left_down_z;
	rightarm[3][0][0][2][0] = back_right_top_x, rightarm[3][0][0][2][1] = back_right_top_y, rightarm[3][0][0][2][2] = back_right_top_z;

	rightarm[3][0][1][0][0] = back_right_top_x, rightarm[3][0][1][0][1] = back_right_top_y, rightarm[3][0][1][0][2] = back_right_top_z;
	rightarm[3][0][1][1][0] = back_left_down_x, rightarm[3][0][1][1][1] = back_left_down_y, rightarm[3][0][1][1][2] = back_left_down_z;
	rightarm[3][0][1][2][0] = back_right_down_x, rightarm[3][0][1][2][1] = back_right_down_y, rightarm[3][0][1][2][2] = back_right_down_z;

	// 후면 색상
	rightarm[3][1][0][0][0] = 0.0f, rightarm[3][1][0][0][1] = 0.0f, rightarm[3][1][0][0][2] = 0.0f;
	rightarm[3][1][0][1][0] = 0.0f, rightarm[3][1][0][1][1] = 0.0f, rightarm[3][1][0][1][2] = 0.0f;
	rightarm[3][1][0][2][0] = 0.0f, rightarm[3][1][0][2][1] = 0.0f, rightarm[3][1][0][2][2] = 0.0f;

	rightarm[3][1][1][0][0] = 0.0f, rightarm[3][1][1][0][1] = 0.0f, rightarm[3][1][1][0][2] = 0.0f;
	rightarm[3][1][1][1][0] = 0.0f, rightarm[3][1][1][1][1] = 0.0f, rightarm[3][1][1][1][2] = 0.0f;
	rightarm[3][1][1][2][0] = 0.0f, rightarm[3][1][1][2][1] = 0.0f, rightarm[3][1][1][2][2] = 0.0f;

	// 하단 좌표
	rightarm[4][0][0][0][0] = back_right_down_x, rightarm[4][0][0][0][1] = back_right_down_y, rightarm[4][0][0][0][2] = back_right_down_z;
	rightarm[4][0][0][1][0] = front_right_down_x, rightarm[4][0][0][1][1] = front_right_down_y, rightarm[4][0][0][1][2] = front_right_down_z;
	rightarm[4][0][0][2][0] = front_left_down_x, rightarm[4][0][0][2][1] = front_left_down_y, rightarm[4][0][0][2][2] = front_left_down_z;

	rightarm[4][0][1][0][0] = front_left_down_x, rightarm[4][0][1][0][1] = front_left_down_y, rightarm[4][0][1][0][2] = front_left_down_z;
	rightarm[4][0][1][1][0] = back_left_down_x, rightarm[4][0][1][1][1] = back_left_down_y, rightarm[4][0][1][1][2] = back_left_down_z;
	rightarm[4][0][1][2][0] = back_right_down_x, rightarm[4][0][1][2][1] = back_right_down_y, rightarm[4][0][1][2][2] = back_right_down_z;

	// 하단 색상
	rightarm[4][1][0][0][0] = 0.0f, rightarm[4][1][0][0][1] = 0.0f, rightarm[4][1][0][0][2] = 0.0f;
	rightarm[4][1][0][1][0] = 0.0f, rightarm[4][1][0][1][1] = 0.0f, rightarm[4][1][0][1][2] = 0.0f;
	rightarm[4][1][0][2][0] = 0.0f, rightarm[4][1][0][2][1] = 0.0f, rightarm[4][1][0][2][2] = 0.0f;

	rightarm[4][1][1][0][0] = 0.0f, rightarm[4][1][1][0][1] = 0.0f, rightarm[4][1][1][0][2] = 0.0f;
	rightarm[4][1][1][1][0] = 0.0f, rightarm[4][1][1][1][1] = 0.0f, rightarm[4][1][1][1][2] = 0.0f;
	rightarm[4][1][1][2][0] = 0.0f, rightarm[4][1][1][2][1] = 0.0f, rightarm[4][1][1][2][2] = 0.0f;

	// 우측 좌표
	rightarm[5][0][0][0][0] = back_right_down_x, rightarm[5][0][0][0][1] = back_right_down_y, rightarm[5][0][0][0][2] = back_right_down_z;
	rightarm[5][0][0][1][0] = back_right_top_x, rightarm[5][0][0][1][1] = back_right_top_y, rightarm[5][0][0][1][2] = back_right_top_z;
	rightarm[5][0][0][2][0] = front_right_down_x, rightarm[5][0][0][2][1] = front_right_down_y, rightarm[5][0][0][2][2] = front_right_down_z;

	rightarm[5][0][1][0][0] = front_right_down_x, rightarm[5][0][1][0][1] = front_right_down_y, rightarm[5][0][1][0][2] = front_right_down_z;
	rightarm[5][0][1][1][0] = back_right_top_x, rightarm[5][0][1][1][1] = back_right_top_y, rightarm[5][0][1][1][2] = back_right_top_z;
	rightarm[5][0][1][2][0] = front_right_top_x, rightarm[5][0][1][2][1] = front_right_top_y, rightarm[5][0][1][2][2] = front_right_top_z;

	// 우측 색상
	rightarm[5][1][0][0][0] = 0.0f, rightarm[5][1][0][0][1] = 0.0f, rightarm[5][1][0][0][2] = 0.0f;
	rightarm[5][1][0][1][0] = 0.0f, rightarm[5][1][0][1][1] = 0.0f, rightarm[5][1][0][1][2] = 0.0f;
	rightarm[5][1][0][2][0] = 0.0f, rightarm[5][1][0][2][1] = 0.0f, rightarm[5][1][0][2][2] = 0.0f;

	rightarm[5][1][1][0][0] = 0.0f, rightarm[5][1][1][0][1] = 0.0f, rightarm[5][1][1][0][2] = 0.0f;
	rightarm[5][1][1][1][0] = 0.0f, rightarm[5][1][1][1][1] = 0.0f, rightarm[5][1][1][1][2] = 0.0f;
	rightarm[5][1][1][2][0] = 0.0f, rightarm[5][1][1][2][1] = 0.0f, rightarm[5][1][1][2][2] = 0.0f;

	//rightleg

	front_left_down_x = -0.005f, front_left_down_y = -0.02f, front_left_down_z = 0.005f;		// 직육면체를 만들고 싶을 때 적절히 수정해줍니다.
	front_left_top_x = -0.005f, front_left_top_y = 0.02f, front_left_top_z = 0.005f;
	front_right_down_x = 0.005f, front_right_down_y = -0.02f, front_right_down_z = 0.005f;
	front_right_top_x = 0.005f, front_right_top_y = 0.02f, front_right_top_z = 0.005f;
	back_left_down_x = -0.005f, back_left_down_y = -0.02f, back_left_down_z = -0.005f;
	back_left_top_x = -0.005f, back_left_top_y = 0.02f, back_left_top_z = -0.005f;
	back_right_down_x = 0.005f, back_right_down_y = -0.02f, back_right_down_z = -0.005f;
	back_right_top_x = 0.005f, back_right_top_y = 0.02f, back_right_top_z = -0.005f;

	// 전면 좌표
	rightleg[0][0][0][0][0] = front_left_down_x, rightleg[0][0][0][0][1] = front_left_down_y, rightleg[0][0][0][0][2] = front_left_down_z;
	rightleg[0][0][0][1][0] = front_right_down_x, rightleg[0][0][0][1][1] = front_right_down_y, rightleg[0][0][0][1][2] = front_right_down_z;
	rightleg[0][0][0][2][0] = front_left_top_x, rightleg[0][0][0][2][1] = front_left_top_y, rightleg[0][0][0][2][2] = front_left_top_z;

	rightleg[0][0][1][0][0] = front_left_top_x, rightleg[0][0][1][0][1] = front_left_top_y, rightleg[0][0][1][0][2] = front_left_top_z;
	rightleg[0][0][1][1][0] = front_right_down_x, rightleg[0][0][1][1][1] = front_right_down_y, rightleg[0][0][1][1][2] = front_right_down_z;
	rightleg[0][0][1][2][0] = front_right_top_x, rightleg[0][0][1][2][1] = front_right_top_y, rightleg[0][0][1][2][2] = front_right_top_z;

	// 전면 색상
	rightleg[0][1][0][0][0] = 0.0f, rightleg[0][1][0][0][1] = 0.0f, rightleg[0][1][0][0][2] = 0.0f;
	rightleg[0][1][0][1][0] = 0.0f, rightleg[0][1][0][1][1] = 0.0f, rightleg[0][1][0][1][2] = 0.0f;
	rightleg[0][1][0][2][0] = 0.0f, rightleg[0][1][0][2][1] = 0.0f, rightleg[0][1][0][2][2] = 0.0f;

	rightleg[0][1][1][0][0] = 0.0f, rightleg[0][1][1][0][1] = 0.0f, rightleg[0][1][1][0][2] = 0.0f;
	rightleg[0][1][1][1][0] = 0.0f, rightleg[0][1][1][1][1] = 0.0f, rightleg[0][1][1][1][2] = 0.0f;
	rightleg[0][1][1][2][0] = 0.0f, rightleg[0][1][1][2][1] = 0.0f, rightleg[0][1][1][2][2] = 0.0f;


	// 상단 좌표
	rightleg[1][0][0][0][0] = front_right_top_x, rightleg[1][0][0][0][1] = front_right_top_y, rightleg[1][0][0][0][2] = front_right_top_z;
	rightleg[1][0][0][1][0] = back_right_top_x, rightleg[1][0][0][1][1] = back_right_top_y, rightleg[1][0][0][1][2] = back_right_top_z;
	rightleg[1][0][0][2][0] = front_left_top_x, rightleg[1][0][0][2][1] = front_left_top_y, rightleg[1][0][0][2][2] = front_left_top_z;

	rightleg[1][0][1][0][0] = front_left_top_x, rightleg[1][0][1][0][1] = front_left_top_y, rightleg[1][0][1][0][2] = front_left_top_z;
	rightleg[1][0][1][1][0] = back_right_top_x, rightleg[1][0][1][1][1] = back_right_top_y, rightleg[1][0][1][1][2] = back_right_top_z;
	rightleg[1][0][1][2][0] = back_left_top_x, rightleg[1][0][1][2][1] = back_left_top_y, rightleg[1][0][1][2][2] = back_left_top_z;

	// 상단 색상
	rightleg[1][1][0][0][0] = 0.0f, rightleg[1][1][0][0][1] = 0.0f, rightleg[1][1][0][0][2] = 0.0f;
	rightleg[1][1][0][1][0] = 0.0f, rightleg[1][1][0][1][1] = 0.0f, rightleg[1][1][0][1][2] = 0.0f;
	rightleg[1][1][0][2][0] = 0.0f, rightleg[1][1][0][2][1] = 0.0f, rightleg[1][1][0][2][2] = 0.0f;

	rightleg[1][1][1][0][0] = 0.0f, rightleg[1][1][1][0][1] = 0.0f, rightleg[1][1][1][0][2] = 0.0f;
	rightleg[1][1][1][1][0] = 0.0f, rightleg[1][1][1][1][1] = 0.0f, rightleg[1][1][1][1][2] = 0.0f;
	rightleg[1][1][1][2][0] = 0.0f, rightleg[1][1][1][2][1] = 0.0f, rightleg[1][1][1][2][2] = 0.0f;

	// 좌측 좌표
	rightleg[2][0][0][0][0] = back_left_top_x, rightleg[2][0][0][0][1] = back_left_top_y, rightleg[2][0][0][0][2] = back_left_top_z;
	rightleg[2][0][0][1][0] = back_left_down_x, rightleg[2][0][0][1][1] = back_left_down_y, rightleg[2][0][0][1][2] = back_left_down_z;
	rightleg[2][0][0][2][0] = front_left_down_x, rightleg[2][0][0][2][1] = front_left_down_y, rightleg[2][0][0][2][2] = front_left_down_z;

	rightleg[2][0][1][0][0] = front_left_down_x, rightleg[2][0][1][0][1] = front_left_down_y, rightleg[2][0][1][0][2] = front_left_down_z;
	rightleg[2][0][1][1][0] = front_left_top_x, rightleg[2][0][1][1][1] = front_left_top_y, rightleg[2][0][1][1][2] = front_left_top_z;
	rightleg[2][0][1][2][0] = back_left_top_x, rightleg[2][0][1][2][1] = back_left_top_y, rightleg[2][0][1][2][2] = back_left_top_z;

	// 좌측 색상
	rightleg[2][1][0][0][0] = 0.0f, rightleg[2][1][0][0][1] = 0.0f, rightleg[2][1][0][0][2] = 0.0f;
	rightleg[2][1][0][1][0] = 0.0f, rightleg[2][1][0][1][1] = 0.0f, rightleg[2][1][0][1][2] = 0.0f;
	rightleg[2][1][0][2][0] = 0.0f, rightleg[2][1][0][2][1] = 0.0f, rightleg[2][1][0][2][2] = 0.0f;

	rightleg[2][1][1][0][0] = 0.0f, rightleg[2][1][1][0][1] = 0.0f, rightleg[2][1][1][0][2] = 0.0f;
	rightleg[2][1][1][1][0] = 0.0f, rightleg[2][1][1][1][1] = 0.0f, rightleg[2][1][1][1][2] = 0.0f;
	rightleg[2][1][1][2][0] = 0.0f, rightleg[2][1][1][2][1] = 0.0f, rightleg[2][1][1][2][2] = 0.0f;

	// 후면 좌표
	rightleg[3][0][0][0][0] = back_left_top_x, rightleg[3][0][0][0][1] = back_left_top_y, rightleg[3][0][0][0][2] = back_left_top_z;
	rightleg[3][0][0][1][0] = back_left_down_x, rightleg[3][0][0][1][1] = back_left_down_y, rightleg[3][0][0][1][2] = back_left_down_z;
	rightleg[3][0][0][2][0] = back_right_top_x, rightleg[3][0][0][2][1] = back_right_top_y, rightleg[3][0][0][2][2] = back_right_top_z;

	rightleg[3][0][1][0][0] = back_right_top_x, rightleg[3][0][1][0][1] = back_right_top_y, rightleg[3][0][1][0][2] = back_right_top_z;
	rightleg[3][0][1][1][0] = back_left_down_x, rightleg[3][0][1][1][1] = back_left_down_y, rightleg[3][0][1][1][2] = back_left_down_z;
	rightleg[3][0][1][2][0] = back_right_down_x, rightleg[3][0][1][2][1] = back_right_down_y, rightleg[3][0][1][2][2] = back_right_down_z;

	// 후면 색상
	rightleg[3][1][0][0][0] = 0.0f, rightleg[3][1][0][0][1] = 0.0f, rightleg[3][1][0][0][2] = 0.0f;
	rightleg[3][1][0][1][0] = 0.0f, rightleg[3][1][0][1][1] = 0.0f, rightleg[3][1][0][1][2] = 0.0f;
	rightleg[3][1][0][2][0] = 0.0f, rightleg[3][1][0][2][1] = 0.0f, rightleg[3][1][0][2][2] = 0.0f;

	rightleg[3][1][1][0][0] = 0.0f, rightleg[3][1][1][0][1] = 0.0f, rightleg[3][1][1][0][2] = 0.0f;
	rightleg[3][1][1][1][0] = 0.0f, rightleg[3][1][1][1][1] = 0.0f, rightleg[3][1][1][1][2] = 0.0f;
	rightleg[3][1][1][2][0] = 0.0f, rightleg[3][1][1][2][1] = 0.0f, rightleg[3][1][1][2][2] = 0.0f;

	// 하단 좌표
	rightleg[4][0][0][0][0] = back_right_down_x, rightleg[4][0][0][0][1] = back_right_down_y, rightleg[4][0][0][0][2] = back_right_down_z;
	rightleg[4][0][0][1][0] = front_right_down_x, rightleg[4][0][0][1][1] = front_right_down_y, rightleg[4][0][0][1][2] = front_right_down_z;
	rightleg[4][0][0][2][0] = front_left_down_x, rightleg[4][0][0][2][1] = front_left_down_y, rightleg[4][0][0][2][2] = front_left_down_z;

	rightleg[4][0][1][0][0] = front_left_down_x, rightleg[4][0][1][0][1] = front_left_down_y, rightleg[4][0][1][0][2] = front_left_down_z;
	rightleg[4][0][1][1][0] = back_left_down_x, rightleg[4][0][1][1][1] = back_left_down_y, rightleg[4][0][1][1][2] = back_left_down_z;
	rightleg[4][0][1][2][0] = back_right_down_x, rightleg[4][0][1][2][1] = back_right_down_y, rightleg[4][0][1][2][2] = back_right_down_z;

	// 하단 색상
	rightleg[4][1][0][0][0] = 0.0f, rightleg[4][1][0][0][1] = 0.0f, rightleg[4][1][0][0][2] = 0.0f;
	rightleg[4][1][0][1][0] = 0.0f, rightleg[4][1][0][1][1] = 0.0f, rightleg[4][1][0][1][2] = 0.0f;
	rightleg[4][1][0][2][0] = 0.0f, rightleg[4][1][0][2][1] = 0.0f, rightleg[4][1][0][2][2] = 0.0f;

	rightleg[4][1][1][0][0] = 0.0f, rightleg[4][1][1][0][1] = 0.0f, rightleg[4][1][1][0][2] = 0.0f;
	rightleg[4][1][1][1][0] = 0.0f, rightleg[4][1][1][1][1] = 0.0f, rightleg[4][1][1][1][2] = 0.0f;
	rightleg[4][1][1][2][0] = 0.0f, rightleg[4][1][1][2][1] = 0.0f, rightleg[4][1][1][2][2] = 0.0f;

	// 우측 좌표
	rightleg[5][0][0][0][0] = back_right_down_x, rightleg[5][0][0][0][1] = back_right_down_y, rightleg[5][0][0][0][2] = back_right_down_z;
	rightleg[5][0][0][1][0] = back_right_top_x, rightleg[5][0][0][1][1] = back_right_top_y, rightleg[5][0][0][1][2] = back_right_top_z;
	rightleg[5][0][0][2][0] = front_right_down_x, rightleg[5][0][0][2][1] = front_right_down_y, rightleg[5][0][0][2][2] = front_right_down_z;

	rightleg[5][0][1][0][0] = front_right_down_x, rightleg[5][0][1][0][1] = front_right_down_y, rightleg[5][0][1][0][2] = front_right_down_z;
	rightleg[5][0][1][1][0] = back_right_top_x, rightleg[5][0][1][1][1] = back_right_top_y, rightleg[5][0][1][1][2] = back_right_top_z;
	rightleg[5][0][1][2][0] = front_right_top_x, rightleg[5][0][1][2][1] = front_right_top_y, rightleg[5][0][1][2][2] = front_right_top_z;

	// 우측 색상
	rightleg[5][1][0][0][0] = 0.0f, rightleg[5][1][0][0][1] = 0.0f, rightleg[5][1][0][0][2] = 0.0f;
	rightleg[5][1][0][1][0] = 0.0f, rightleg[5][1][0][1][1] = 0.0f, rightleg[5][1][0][1][2] = 0.0f;
	rightleg[5][1][0][2][0] = 0.0f, rightleg[5][1][0][2][1] = 0.0f, rightleg[5][1][0][2][2] = 0.0f;

	rightleg[5][1][1][0][0] = 0.0f, rightleg[5][1][1][0][1] = 0.0f, rightleg[5][1][1][0][2] = 0.0f;
	rightleg[5][1][1][1][0] = 0.0f, rightleg[5][1][1][1][1] = 0.0f, rightleg[5][1][1][1][2] = 0.0f;
	rightleg[5][1][1][2][0] = 0.0f, rightleg[5][1][1][2][1] = 0.0f, rightleg[5][1][1][2][2] = 0.0f;
}

void Robot::allReset()
{
	movement = 0;
	xPos = 0.05f, yPos = 0.0f, zPos = 0.05f, rotation = 90.0f;
	HeightFromGround[0] = 0.05f;
	HeightFromGround[1] = 0.03f;
	HeightFromGround[2] = 0.0f;
	HeightFromGround[3] = -0.04f;
	HeightFromGround[4] = 0.0f;
	HeightFromGround[5] = -0.04f;
	hanging = true;
	jump = 0;
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

void Robot::update(GLfloat* mx, GLfloat* mz, GLint objectCount)
{
	
	if (movement == 0) {
		for (int i = 0; i < objectCount; i++) {
			if (xPos - 0.1f + 0.01f < mx[i] + 0.2f && xPos + 0.1f > mx[i] - 0.2f && zPos + 0.1f > mz[i] - 0.1f && zPos - 0.1f < mz[i] + 0.1f && yPos < 0.2f) {
				continue;
			}
			else if (xPos >= 3.0f) {
				xPos = -3.0f;
				break;
			}
			else {
				xPos += 0.01f;
				break;
			}
		}
		
	}
	else if (movement == 1) {
		for (int i = 0; i < objectCount; i++) {
			if (xPos - 0.1f < mx[i] + 0.2f && xPos + 0.1f - 0.01f > mx[i] - 0.2f && zPos + 0.1f > mz[i] - 0.1f && zPos - 0.1f < mz[i] + 0.1f && yPos < 0.2f) {
				continue;
			}
			else if (xPos <= -3.0f) {
				xPos = 3.0f;
				break;
			}
			else {
				xPos -= 0.01f;
				break;
			}
		}
	}
	else if (movement == 2) {
		for (int i = 0; i < objectCount; i++) {
			if (xPos - 0.1f < mx[i] + 0.2f && xPos + 0.1f > mx[i] - 0.2f && zPos + 0.1f > mz[i] - 0.1f && zPos - 0.1f + 0.01f < mz[i] + 0.1f && yPos < 0.2f) {
				continue;
			}
			else if (zPos >= 3.0f) {
				zPos = -3.0f;
				break;
			}
			else {
				zPos += 0.01f;
				break;
			}
		}
	}
	else if (movement == 3) {
		for (int i = 0; i < objectCount; i++) {
			if (xPos - 0.1f < mx[i] + 0.2f && xPos + 0.1f > mx[i] - 0.2f && zPos + 0.1f - 0.01f > mz[i] - 0.1f && zPos - 0.1f < mz[i] + 0.1f && yPos < 0.2f) {
				continue;
			}
			else if (zPos <= -3.0f) {
				zPos = 3.0f;
				break;
			}
			else {
				zPos -= 0.01f;
				break;
			}
		}
	}
	if (jump == 1) {
		if (yPos + 0.05f >= 0.5f) {
			jump = 2;
			yPos = 0.5f;
		}
		else {
			yPos += 0.05f;
		}
	}
	else if (jump == 2) {
		if (yPos - 0.05f <= 0.0f) {
			jump = 0;
			yPos = 0.0f;
		}
		else {
			for (int i = 0; i < objectCount; i++) {
				if (xPos - 0.1f < mx[i] + 0.2f && xPos + 0.1f > mx[i] - 0.2f && zPos + 0.1f - 0.01f > mz[i] - 0.1f && zPos - 0.1f < mz[i] + 0.1f && yPos - 0.05f < 0.2f) {

				}
				else {
					yPos -= 0.05f;
				}
			}
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