#include "Quadrangular.h"

Quadrangular::Quadrangular()
{

	GLfloat linear = 0.5f;	// 정육면체를 만들고 싶을 때 원하는 길이의 절반을 입력해줍니다.

	// 하단 사각형 좌표
	data[0][0][0][0] = -linear, data[0][0][0][1] = -linear, data[0][0][0][2] = linear;
	data[0][0][1][0] = -linear, data[0][0][1][1] = -linear, data[0][0][1][2] = -linear;
	data[0][0][2][0] = linear, data[0][0][2][1] = -linear, data[0][0][2][2] = linear;

	data[1][0][0][0] = linear, data[1][0][0][1] = -linear, data[1][0][0][2] = linear;
	data[1][0][1][0] = -linear, data[1][0][1][1] = -linear, data[1][0][1][2] = -linear;
	data[1][0][2][0] = linear, data[1][0][2][1] = -linear, data[1][0][2][2] = -linear;

	// 하단 사각형 노멀
	data[0][1][0][0] = 0.0f, data[0][1][0][1] = -1.0f, data[0][1][0][2] = 0.0f;
	data[0][1][1][0] = 0.0f, data[0][1][1][1] = -1.0f, data[0][1][1][2] = 0.0f;
	data[0][1][2][0] = 0.0f, data[0][1][2][1] = -1.0f, data[0][1][2][2] = 0.0f;
		
	data[1][1][0][0] = 0.0f, data[1][1][0][1] = -1.0f, data[1][1][0][2] = 0.0f;
	data[1][1][1][0] = 0.0f, data[1][1][1][1] = -1.0f, data[1][1][1][2] = 0.0f;
	data[1][1][2][0] = 0.0f, data[1][1][2][1] = -1.0f, data[1][1][2][2] = 0.0f;

	// 우측 삼각형 좌표
	data[2][0][0][0] = linear, data[2][0][0][1] = -linear, data[2][0][0][2] = -linear;
	data[2][0][1][0] = 0.0f, data[2][0][1][1] = linear, data[2][0][1][2] = 0.0f;
	data[2][0][2][0] = linear, data[2][0][2][1] = -linear, data[2][0][2][2] = linear;

	// 우측 삼각형 노멀
	data[2][1][0][0] = 1.0f, data[2][1][0][1] = 0.0f, data[2][1][0][2] = 0.0f;
	data[2][1][1][0] = 1.0f, data[2][1][1][1] = 0.0f, data[2][1][1][2] = 0.0f;
	data[2][1][2][0] = 1.0f, data[2][1][2][1] = 0.0f, data[2][1][2][2] = 0.0f;

	// 정면 삼각형 좌표
	data[3][0][0][0] = linear, data[3][0][0][1] = -linear, data[3][0][0][2] = linear;
	data[3][0][1][0] = 0.0f, data[3][0][1][1] = linear, data[3][0][1][2] = 0.0f;
	data[3][0][2][0] = -linear, data[3][0][2][1] = -linear, data[3][0][2][2] = linear;

	// 정면 삼각형 노멀
	data[3][1][0][0] = 0.0f, data[3][1][0][1] = 0.0f, data[3][1][0][2] = 1.0f;
	data[3][1][1][0] = 0.0f, data[3][1][1][1] = 0.0f, data[3][1][1][2] = 1.0f;
	data[3][1][2][0] = 0.0f, data[3][1][2][1] = 0.0f, data[3][1][2][2] = 1.0f;

	// 좌측 삼각형 좌표
	data[4][0][0][0] = -linear, data[4][0][0][1] = -linear, data[4][0][0][2] = linear;
	data[4][0][1][0] = 0.0f, data[4][0][1][1] = linear, data[4][0][1][2] = 0.0f;
	data[4][0][2][0] = -linear, data[4][0][2][1] = -linear, data[4][0][2][2] = -linear;

	// 좌측 삼각형 노멀
	data[4][1][0][0] = -1.0f, data[4][1][0][1] = 0.0f, data[4][1][0][2] = 0.0f;
	data[4][1][1][0] = -1.0f, data[4][1][1][1] = 0.0f, data[4][1][1][2] = 0.0f;
	data[4][1][2][0] = -1.0f, data[4][1][2][1] = 0.0f, data[4][1][2][2] = 0.0f;

	// 후면 삼각형 좌표
	data[5][0][0][0] = -linear, data[5][0][0][1] = -linear, data[5][0][0][2] = -linear;
	data[5][0][1][0] = 0.0f, data[5][0][1][1] = linear, data[5][0][1][2] = 0.0f;
	data[5][0][2][0] = linear, data[5][0][2][1] = -linear, data[5][0][2][2] = -linear;

	// 후면 삼각형 노멀
	data[5][1][0][0] = 0.0f, data[5][1][0][1] = 0.0f, data[5][1][0][2] = -1.0f;
	data[5][1][1][0] = 0.0f, data[5][1][1][1] = 0.0f, data[5][1][1][2] = -1.0f;
	data[5][1][2][0] = 0.0f, data[5][1][2][1] = 0.0f, data[5][1][2][2] = -1.0f;
}

void Quadrangular::initBuffer(GLuint s_program)
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

	glUseProgram(s_program);
	objColorLocation = glGetUniformLocation(s_program, "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
}

void Quadrangular::draw()
{
	if (drawed) {
		glUniform3f(objColorLocation, 0.1, 0.1, 0.8);
		glBindVertexArray(vao[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(vao[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}

void Quadrangular::rdraw()
{
	if (drawed) {
		glUniform3f(objColorLocation, 0.1, 0.1, 0.8);
		glBindVertexArray(vao[2]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}

void Quadrangular::fdraw()
{
	if (drawed) {
		glUniform3f(objColorLocation, 0.1, 0.1, 0.8);
		glBindVertexArray(vao[3]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}

void Quadrangular::ldraw()
{
	if (drawed) {
		glUniform3f(objColorLocation, 0.1, 0.1, 0.8);
		glBindVertexArray(vao[4]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}

void Quadrangular::bdraw()
{
	if (drawed) {
		glUniform3f(objColorLocation, 0.1, 0.1, 0.8);
		glBindVertexArray(vao[5]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}

void Quadrangular::allReset()
{
	drawed = false;
	rotate = false;
	open = false;
	openPos = 0.0f;
}

void Quadrangular::update()
{
	if (rotate) {
		rotatePos += 1.0f;
	}
	if (open) {
		if (openPos + 1.0f > 233.14f) {
			openPos = 233.14f;
		}
		else {
			openPos += 1.0f;
		}
	}
	else {
		if (openPos - 1.0f < 0.0f) {
			openPos = 0.0f;
		}
		else {
			openPos -= 1.0f;
		}
	}
}

void Quadrangular::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::rotate(myFactor, glm::radians(rotatePos), glm::vec3(0.0f, 1.0f, 0.0f));

	myRFactor = myFactor;
	myRFactor = glm::translate(myRFactor, glm::vec3(0.5f, -0.5f, 0.0f));
	myRFactor = glm::rotate(myRFactor, glm::radians(-openPos), glm::vec3(0.0f, 0.0f, 1.0f));
	myRFactor = glm::translate(myRFactor, glm::vec3(-0.5f, 0.5f, 0.0f));

	myFFactor = myFactor;
	myFFactor = glm::translate(myFFactor, glm::vec3(0.0f, -0.5f, 0.5f));
	myFFactor = glm::rotate(myFFactor, glm::radians(openPos), glm::vec3(1.0f, 0.0f, 0.0f));
	myFFactor = glm::translate(myFFactor, glm::vec3(0.0f, 0.5f, -0.5f));

	myLFactor = myFactor;
	myLFactor = glm::translate(myLFactor, glm::vec3(-0.5f, -0.5f, 0.0f));
	myLFactor = glm::rotate(myLFactor, glm::radians(openPos), glm::vec3(0.0f, 0.0f, 1.0f));
	myLFactor = glm::translate(myLFactor, glm::vec3(0.5f, 0.5f, 0.0f));

	myBFactor = myFactor;
	myBFactor = glm::translate(myBFactor, glm::vec3(0.0f, -0.5f, -0.5f));
	myBFactor = glm::rotate(myBFactor, glm::radians(-openPos), glm::vec3(1.0f, 0.0f, 0.0f));
	myBFactor = glm::translate(myBFactor, glm::vec3(0.0f, 0.5f, 0.5f));
}

glm::mat4 Quadrangular::getFactor()
{
	return myFactor;
}