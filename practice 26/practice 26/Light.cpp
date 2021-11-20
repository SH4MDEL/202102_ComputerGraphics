#include "Light.h"

Light::Light()
{

	allReset();

	GLfloat linear = 0.05f;	// 정육면체를 만들고 싶을 때 원하는 길이의 절반을 입력해줍니다.

	GLfloat front_left_down_x = -linear, front_left_down_y = -linear, front_left_down_z = linear;		// 정육면체를 만들고 싶을 때 주석 해제합니다.
	GLfloat front_left_top_x = -linear, front_left_top_y = linear, front_left_top_z = linear;
	GLfloat front_right_down_x = linear, front_right_down_y = -linear, front_right_down_z = linear;
	GLfloat front_right_top_x = linear, front_right_top_y = linear, front_right_top_z = linear;
	GLfloat back_left_down_x = -linear, back_left_down_y = -linear, back_left_down_z = -linear;
	GLfloat back_left_top_x = -linear, back_left_top_y = linear, back_left_top_z = -linear;
	GLfloat back_right_down_x = linear, back_right_down_y = -linear, back_right_down_z = -linear;
	GLfloat back_right_top_x = linear, back_right_top_y = linear, back_right_top_z = -linear;

	//GLfloat front_left_down_x = -0.2f, front_left_down_y = -0.2f, front_left_down_z = 0.1f;		// 직육면체를 만들고 싶을 때 적절히 수정해줍니다.
	//GLfloat front_left_top_x = -0.2f, front_left_top_y = 0.2f, front_left_top_z = 0.1f;
	//GLfloat front_right_down_x = 0.2f, front_right_down_y = -0.2f, front_right_down_z = 0.1f;
	//GLfloat front_right_top_x = 0.2f, front_right_top_y = 0.2f, front_right_top_z = 0.1f;
	//GLfloat back_left_down_x = -0.2f, back_left_down_y = -0.2f, back_left_down_z = -0.1f;
	//GLfloat back_left_top_x = -0.2f, back_left_top_y = 0.2f, back_left_top_z = -0.1f;
	//GLfloat back_right_down_x = 0.2f, back_right_down_y = -0.2f, back_right_down_z = -0.1f;
	//GLfloat back_right_top_x = 0.2f, back_right_top_y = 0.2f, back_right_top_z = -0.1f;

	//printf("%d\n", color(gen));

	// 전면 좌표
	data[0][0][0][0][0] = front_left_down_x, data[0][0][0][0][1] = front_left_down_y, data[0][0][0][0][2] = front_left_down_z;
	data[0][0][0][1][0] = front_right_down_x, data[0][0][0][1][1] = front_right_down_y, data[0][0][0][1][2] = front_right_down_z;
	data[0][0][0][2][0] = front_left_top_x, data[0][0][0][2][1] = front_left_top_y, data[0][0][0][2][2] = front_left_top_z;

	data[0][0][1][0][0] = front_left_top_x, data[0][0][1][0][1] = front_left_top_y, data[0][0][1][0][2] = front_left_top_z;
	data[0][0][1][1][0] = front_right_down_x, data[0][0][1][1][1] = front_right_down_y, data[0][0][1][1][2] = front_right_down_z;
	data[0][0][1][2][0] = front_right_top_x, data[0][0][1][2][1] = front_right_top_y, data[0][0][1][2][2] = front_right_top_z;

	// 전면 노멀
	data[0][1][0][0][0] = 0.0f, data[0][1][0][0][1] = 0.0f, data[0][1][0][0][2] = 1.0f;
	data[0][1][0][1][0] = 0.0f, data[0][1][0][1][1] = 0.0f, data[0][1][0][1][2] = 1.0f;
	data[0][1][0][2][0] = 0.0f, data[0][1][0][2][1] = 0.0f, data[0][1][0][2][2] = 1.0f;

	data[0][1][1][0][0] = 0.0f, data[0][1][1][0][1] = 0.0f, data[0][1][1][0][2] = 1.0f;
	data[0][1][1][1][0] = 0.0f, data[0][1][1][1][1] = 0.0f, data[0][1][1][1][2] = 1.0f;
	data[0][1][1][2][0] = 0.0f, data[0][1][1][2][1] = 0.0f, data[0][1][1][2][2] = 1.0f;


	// 상단 좌표
	data[1][0][0][0][0] = front_right_top_x, data[1][0][0][0][1] = front_right_top_y, data[1][0][0][0][2] = front_right_top_z;
	data[1][0][0][1][0] = back_right_top_x, data[1][0][0][1][1] = back_right_top_y, data[1][0][0][1][2] = back_right_top_z;
	data[1][0][0][2][0] = front_left_top_x, data[1][0][0][2][1] = front_left_top_y, data[1][0][0][2][2] = front_left_top_z;

	data[1][0][1][0][0] = front_left_top_x, data[1][0][1][0][1] = front_left_top_y, data[1][0][1][0][2] = front_left_top_z;
	data[1][0][1][1][0] = back_right_top_x, data[1][0][1][1][1] = back_right_top_y, data[1][0][1][1][2] = back_right_top_z;
	data[1][0][1][2][0] = back_left_top_x, data[1][0][1][2][1] = back_left_top_y, data[1][0][1][2][2] = back_left_top_z;

	// 상단 노멀
	data[1][1][0][0][0] = 0.0f, data[1][1][0][0][1] = 1.0f, data[1][1][0][0][2] = 0.0f;
	data[1][1][0][1][0] = 0.0f, data[1][1][0][1][1] = 1.0f, data[1][1][0][1][2] = 0.0f;
	data[1][1][0][2][0] = 0.0f, data[1][1][0][2][1] = 1.0f, data[1][1][0][2][2] = 0.0f;

	data[1][1][1][0][0] = 0.0f, data[1][1][1][0][1] = 1.0f, data[1][1][1][0][2] = 0.0f;
	data[1][1][1][1][0] = 0.0f, data[1][1][1][1][1] = 1.0f, data[1][1][1][1][2] = 0.0f;
	data[1][1][1][2][0] = 0.0f, data[1][1][1][2][1] = 1.0f, data[1][1][1][2][2] = 0.0f;

	// 좌측 좌표
	data[2][0][0][0][0] = back_left_top_x, data[2][0][0][0][1] = back_left_top_y, data[2][0][0][0][2] = back_left_top_z;
	data[2][0][0][1][0] = back_left_down_x, data[2][0][0][1][1] = back_left_down_y, data[2][0][0][1][2] = back_left_down_z;
	data[2][0][0][2][0] = front_left_down_x, data[2][0][0][2][1] = front_left_down_y, data[2][0][0][2][2] = front_left_down_z;

	data[2][0][1][0][0] = front_left_down_x, data[2][0][1][0][1] = front_left_down_y, data[2][0][1][0][2] = front_left_down_z;
	data[2][0][1][1][0] = front_left_top_x, data[2][0][1][1][1] = front_left_top_y, data[2][0][1][1][2] = front_left_top_z;
	data[2][0][1][2][0] = back_left_top_x, data[2][0][1][2][1] = back_left_top_y, data[2][0][1][2][2] = back_left_top_z;

	// 좌측 노멀
	data[2][1][0][0][0] = -1.0f, data[2][1][0][0][1] = 0.0f, data[2][1][0][0][2] = 0.0f;
	data[2][1][0][1][0] = -1.0f, data[2][1][0][1][1] = 0.0f, data[2][1][0][1][2] = 0.0f;
	data[2][1][0][2][0] = -1.0f, data[2][1][0][2][1] = 0.0f, data[2][1][0][2][2] = 0.0f;

	data[2][1][1][0][0] = -1.0f, data[2][1][1][0][1] = 0.0f, data[2][1][1][0][2] = 0.0f;
	data[2][1][1][1][0] = -1.0f, data[2][1][1][1][1] = 0.0f, data[2][1][1][1][2] = 0.0f;
	data[2][1][1][2][0] = -1.0f, data[2][1][1][2][1] = 0.0f, data[2][1][1][2][2] = 0.0f;

	// 후면 좌표
	data[3][0][0][0][0] = back_left_top_x, data[3][0][0][0][1] = back_left_top_y, data[3][0][0][0][2] = back_left_top_z;
	data[3][0][0][1][0] = back_left_down_x, data[3][0][0][1][1] = back_left_down_y, data[3][0][0][1][2] = back_left_down_z;
	data[3][0][0][2][0] = back_right_top_x, data[3][0][0][2][1] = back_right_top_y, data[3][0][0][2][2] = back_right_top_z;

	data[3][0][1][0][0] = back_right_top_x, data[3][0][1][0][1] = back_right_top_y, data[3][0][1][0][2] = back_right_top_z;
	data[3][0][1][1][0] = back_left_down_x, data[3][0][1][1][1] = back_left_down_y, data[3][0][1][1][2] = back_left_down_z;
	data[3][0][1][2][0] = back_right_down_x, data[3][0][1][2][1] = back_right_down_y, data[3][0][1][2][2] = back_right_down_z;

	// 후면 노멀
	data[3][1][0][0][0] = 0.0f, data[3][1][0][0][1] = 0.0f, data[3][1][0][0][2] = -1.0f;
	data[3][1][0][1][0] = 0.0f, data[3][1][0][1][1] = 0.0f, data[3][1][0][1][2] = -1.0f;
	data[3][1][0][2][0] = 0.0f, data[3][1][0][2][1] = 0.0f, data[3][1][0][2][2] = -1.0f;

	data[3][1][1][0][0] = 0.0f, data[3][1][1][0][1] = 0.0f, data[3][1][1][0][2] = -1.0f;
	data[3][1][1][1][0] = 0.0f, data[3][1][1][1][1] = 0.0f, data[3][1][1][1][2] = -1.0f;
	data[3][1][1][2][0] = 0.0f, data[3][1][1][2][1] = 0.0f, data[3][1][1][2][2] = -1.0f;

	// 하단 좌표
	data[4][0][0][0][0] = back_right_down_x, data[4][0][0][0][1] = back_right_down_y, data[4][0][0][0][2] = back_right_down_z;
	data[4][0][0][1][0] = front_right_down_x, data[4][0][0][1][1] = front_right_down_y, data[4][0][0][1][2] = front_right_down_z;
	data[4][0][0][2][0] = front_left_down_x, data[4][0][0][2][1] = front_left_down_y, data[4][0][0][2][2] = front_left_down_z;

	data[4][0][1][0][0] = front_left_down_x, data[4][0][1][0][1] = front_left_down_y, data[4][0][1][0][2] = front_left_down_z;
	data[4][0][1][1][0] = back_left_down_x, data[4][0][1][1][1] = back_left_down_y, data[4][0][1][1][2] = back_left_down_z;
	data[4][0][1][2][0] = back_right_down_x, data[4][0][1][2][1] = back_right_down_y, data[4][0][1][2][2] = back_right_down_z;

	// 하단 노멀
	data[4][1][0][0][0] = 0.0f, data[4][1][0][0][1] = -1.0f, data[4][1][0][0][2] = 0.0f;
	data[4][1][0][1][0] = 0.0f, data[4][1][0][1][1] = -1.0f, data[4][1][0][1][2] = 0.0f;
	data[4][1][0][2][0] = 0.0f, data[4][1][0][2][1] = -1.0f, data[4][1][0][2][2] = 0.0f;

	data[4][1][1][0][0] = 0.0f, data[4][1][1][0][1] = -1.0f, data[4][1][1][0][2] = 0.0f;
	data[4][1][1][1][0] = 0.0f, data[4][1][1][1][1] = -1.0f, data[4][1][1][1][2] = 0.0f;
	data[4][1][1][2][0] = 0.0f, data[4][1][1][2][1] = -1.0f, data[4][1][1][2][2] = 0.0f;

	// 우측 좌표
	data[5][0][0][0][0] = back_right_down_x, data[5][0][0][0][1] = back_right_down_y, data[5][0][0][0][2] = back_right_down_z;
	data[5][0][0][1][0] = back_right_top_x, data[5][0][0][1][1] = back_right_top_y, data[5][0][0][1][2] = back_right_top_z;
	data[5][0][0][2][0] = front_right_down_x, data[5][0][0][2][1] = front_right_down_y, data[5][0][0][2][2] = front_right_down_z;

	data[5][0][1][0][0] = front_right_down_x, data[5][0][1][0][1] = front_right_down_y, data[5][0][1][0][2] = front_right_down_z;
	data[5][0][1][1][0] = back_right_top_x, data[5][0][1][1][1] = back_right_top_y, data[5][0][1][1][2] = back_right_top_z;
	data[5][0][1][2][0] = front_right_top_x, data[5][0][1][2][1] = front_right_top_y, data[5][0][1][2][2] = front_right_top_z;

	// 우측 노멀
	data[5][1][0][0][0] = 1.0f, data[5][1][0][0][1] = 0.0f, data[5][1][0][0][2] = 0.0f;
	data[5][1][0][1][0] = 1.0f, data[5][1][0][1][1] = 0.0f, data[5][1][0][1][2] = 0.0f;
	data[5][1][0][2][0] = 1.0f, data[5][1][0][2][1] = 0.0f, data[5][1][0][2][2] = 0.0f;

	data[5][1][1][0][0] = 1.0f, data[5][1][1][0][1] = 0.0f, data[5][1][1][0][2] = 0.0f;
	data[5][1][1][1][0] = 1.0f, data[5][1][1][1][1] = 0.0f, data[5][1][1][1][2] = 0.0f;
	data[5][1][1][2][0] = 1.0f, data[5][1][1][2][1] = 0.0f, data[5][1][1][2][2] = 0.0f;
}

void Light::initBuffer(GLuint s_program)
{
	glGenVertexArrays(6, vao);
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(vao[i]);
		glGenBuffers(2, vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), data[i][j], GL_STATIC_DRAW);
			if (j == 0) {
				glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			}
			else {
				glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, (void*)(3 * sizeof(float)));
			}
			glEnableVertexAttribArray(j);
		}
	}

	glUseProgram(s_program);
	lightPosLocation = glGetUniformLocation(s_program, "lightPos"); //--- lightPos 값 전달
	lightColorLocation = glGetUniformLocation(s_program, "lightColor"); //--- lightColor 값 전달
	objColorLocation = glGetUniformLocation(s_program, "objectColor"); //--- object Color값 전달
}

void Light::draw()
{
	glUniform3f(objColorLocation, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(vao[i]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void Light::allReset()
{
	rotate = false;
	rotatePos = 90.0f;
	zPos = 2.5f;
	colorType = 1;
	rCol = 1.0f, gCol = 0.3f, bCol = 0.3f;
	lightOn = true;
}

void Light::update()
{
	if (rotate) {
		rotatePos += 1.0f;
	}
	if (lightOn) {
		glUniform3f(lightColorLocation, rCol, gCol, bCol);
	}
	else {
		glUniform3f(lightColorLocation, 0.0f, 0.0f, 0.0f);
	}
	glUniform3f(lightPosLocation, (zPos - 0.2f) * cos(2 * 3.14159265358979 / 360 * rotatePos), 0.5f, (zPos - 0.2f) * sin(2 * 3.14159265358979 / 360 * rotatePos));
}

void Light::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::translate(myFactor, glm::vec3(zPos * cos(2 * 3.14159265358979 / 360 * rotatePos), 0.5f, zPos * sin(2 * 3.14159265358979 / 360 * rotatePos)));
}

glm::mat4 Light::getFactor()
{
	return myFactor;
}