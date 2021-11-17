#include "Hexahedron.h"

Hexahedron::Hexahedron()
{

	allReset();

	GLfloat linear = 0.5f;	// 정육면체를 만들고 싶을 때 원하는 길이의 절반을 입력해줍니다.

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

	// 하단 색상
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

	// 우측 색상
	data[5][1][0][0][0] = 1.0f, data[5][1][0][0][1] = 0.0f, data[5][1][0][0][2] = 0.0f;
	data[5][1][0][1][0] = 1.0f, data[5][1][0][1][1] = 0.0f, data[5][1][0][1][2] = 0.0f;
	data[5][1][0][2][0] = 1.0f, data[5][1][0][2][1] = 0.0f, data[5][1][0][2][2] = 0.0f;

	data[5][1][1][0][0] = 1.0f, data[5][1][1][0][1] = 0.0f, data[5][1][1][0][2] = 0.0f;
	data[5][1][1][1][0] = 1.0f, data[5][1][1][1][1] = 0.0f, data[5][1][1][1][2] = 0.0f;
	data[5][1][1][2][0] = 1.0f, data[5][1][1][2][1] = 0.0f, data[5][1][1][2][2] = 0.0f;
}

void Hexahedron::initBuffer(GLuint s_program)
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
				glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			}
			glEnableVertexAttribArray(j);
		}
	}

	glUseProgram(s_program);
	objColorLocation = glGetUniformLocation(s_program, "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
}

void Hexahedron::ReBuffer()
{
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
				glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			}
			glEnableVertexAttribArray(j);
		}
	}
}

void Hexahedron::draw()
{

	if (drawed) {
		glUniform3f(objColorLocation, 0.1f, 0.8f, 0.1f);
		glBindVertexArray(vao[3]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(vao[4]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void Hexahedron::headdraw()
{
	if (drawed) {
		glUniform3f(objColorLocation, 0.1f, 0.8f, 0.1f);
		glBindVertexArray(vao[1]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void Hexahedron::slidedraw()
{
	if (drawed) {
		glUniform3f(objColorLocation, 0.1f, 0.8f, 0.1f);
		glBindVertexArray(vao[2]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(vao[5]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void Hexahedron::frontdraw()
{
	if (drawed) {
		glUniform3f(objColorLocation, 0.1f, 0.8f, 0.1f);
		glBindVertexArray(vao[0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void Hexahedron::allReset()
{
	drawed = true;
	rotate = false;
	rotatePos = 0.0f;
	head = false;
	headPos = 0.0f;
	slide = false;
	slidePos = 0.0f;
	front = false;
	frontPos = 0.0f;
}

void Hexahedron::update()
{
	if (rotate) {
		rotatePos += 1.0f;
	}
	if (head) {
		headPos += 1.0f;
	}
	if (slide) {
		if (slidePos + 0.02f > 1.0f) {
			slidePos = 1.0f;
		}
		else {
			slidePos += 0.02f;
		}
	}
	else {
		if (slidePos - 0.02f < 0.0f) {
			slidePos = 0.0f;
		}
		else {
			slidePos -= 0.02f;
		}
	}
	if (front) {
		if (frontPos + 1.0f > 90.0f) {
			frontPos = 90.0f;
		}
		else {
			frontPos += 1.0f;
		}
	}
	else {
		if (frontPos - 1.0f < 0.0f) {
			frontPos = 0.0f;
		}
		else {
			frontPos -= 1.0f;
		}
	}
}

void Hexahedron::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::rotate(myFactor, glm::radians(rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Hexahedron::putHeadFactor(glm::mat4 inputFactor)
{
	myHeadFactor = inputFactor;
	myHeadFactor = glm::translate(myHeadFactor, glm::vec3(0.0f, 0.5f, 0.0f));
	myHeadFactor = glm::rotate(myHeadFactor, glm::radians(headPos), glm::vec3(1.0f, 0.0f, 0.0f));
	myHeadFactor = glm::translate(myHeadFactor, glm::vec3(0.0f, -0.5f, 0.0f));
}

void Hexahedron::putSlideFactor(glm::mat4 inputFactor)
{
	mySlideFactor = inputFactor;
	mySlideFactor = glm::translate(mySlideFactor, glm::vec3(0.0f, slidePos, 0.0f));
}

void Hexahedron::putFrontFactor(glm::mat4 inputFactor)
{
	myFrontFactor = inputFactor;
	myFrontFactor = glm::translate(myFrontFactor, glm::vec3(0.0f, -0.5f, 0.5f));
	myFrontFactor = glm::rotate(myFrontFactor, glm::radians(frontPos), glm::vec3(1.0f, 0.0f, 0.0f));
	myFrontFactor = glm::translate(myFrontFactor, glm::vec3(0.0f, 0.5f, -0.5f));
}

glm::mat4 Hexahedron::getFactor()
{
	return myFactor;
}

glm::mat4 Hexahedron::getHeadFactor()
{
	return myHeadFactor;
}

glm::mat4 Hexahedron::getSlideFactor()
{
	return mySlideFactor;
}

glm::mat4 Hexahedron::getFrontFactor()
{
	return myFrontFactor;
}