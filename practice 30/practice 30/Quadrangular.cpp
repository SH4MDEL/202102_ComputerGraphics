#include "Quadrangular.h"

Quadrangular::Quadrangular()
{

	GLfloat linear = 0.5f;	// ������ü�� ����� ���� �� ���ϴ� ������ ������ �Է����ݴϴ�.

	// �ϴ� �簢�� ��ǥ
	data[0][0][0][0] = -linear, data[0][0][0][1] = -linear, data[0][0][0][2] = linear;
	data[0][0][1][0] = -linear, data[0][0][1][1] = -linear, data[0][0][1][2] = -linear;
	data[0][0][2][0] = linear, data[0][0][2][1] = -linear, data[0][0][2][2] = linear;

	data[1][0][0][0] = linear, data[1][0][0][1] = -linear, data[1][0][0][2] = linear;
	data[1][0][1][0] = -linear, data[1][0][1][1] = -linear, data[1][0][1][2] = -linear;
	data[1][0][2][0] = linear, data[1][0][2][1] = -linear, data[1][0][2][2] = -linear;

	// �ϴ� �簢�� ���
	data[0][1][0][0] = 0.0f, data[0][1][0][1] = -1.0f, data[0][1][0][2] = 0.0f;
	data[0][1][1][0] = 0.0f, data[0][1][1][1] = -1.0f, data[0][1][1][2] = 0.0f;
	data[0][1][2][0] = 0.0f, data[0][1][2][1] = -1.0f, data[0][1][2][2] = 0.0f;
		
	data[1][1][0][0] = 0.0f, data[1][1][0][1] = -1.0f, data[1][1][0][2] = 0.0f;
	data[1][1][1][0] = 0.0f, data[1][1][1][1] = -1.0f, data[1][1][1][2] = 0.0f;
	data[1][1][2][0] = 0.0f, data[1][1][2][1] = -1.0f, data[1][1][2][2] = 0.0f;

	// �ϴ� �簢�� �ؽ�ó
	texture_data[0][0][0] = 0.0f, texture_data[0][0][1] = 1.0f;
	texture_data[0][1][0] = 0.0f, texture_data[0][1][1] = 0.0f;
	texture_data[0][2][0] = 1.0f, texture_data[0][2][1] = 0.0f;

	texture_data[1][0][0] = 1.0f, texture_data[1][0][1] = 0.0f;
	texture_data[1][1][0] = 1.0f, texture_data[1][1][1] = 1.0f;
	texture_data[1][2][0] = 0.0f, texture_data[1][2][1] = 1.0f;


	// ���� �ﰢ�� ��ǥ
	data[2][0][0][0] = linear, data[2][0][0][1] = -linear, data[2][0][0][2] = -linear;
	data[2][0][1][0] = 0.0f, data[2][0][1][1] = linear, data[2][0][1][2] = 0.0f;
	data[2][0][2][0] = linear, data[2][0][2][1] = -linear, data[2][0][2][2] = linear;

	// ���� �ﰢ�� ���
	data[2][1][0][0] = 1.0f, data[2][1][0][1] = 1.0f, data[2][1][0][2] = 0.0f;
	data[2][1][1][0] = 1.0f, data[2][1][1][1] = 1.0f, data[2][1][1][2] = 0.0f;
	data[2][1][2][0] = 1.0f, data[2][1][2][1] = 1.0f, data[2][1][2][2] = 0.0f;

	// ���� �ﰢ�� �ؽ�ó
	texture_data[2][0][0] = 1.0f, texture_data[2][0][1] = 0.0f;
	texture_data[2][1][0] = 0.5f, texture_data[2][1][1] = 1.0f;
	texture_data[2][2][0] = 0.0f, texture_data[2][2][1] = 0.0f;


	// ���� �ﰢ�� ��ǥ
	data[3][0][0][0] = linear, data[3][0][0][1] = -linear, data[3][0][0][2] = linear;
	data[3][0][1][0] = 0.0f, data[3][0][1][1] = linear, data[3][0][1][2] = 0.0f;
	data[3][0][2][0] = -linear, data[3][0][2][1] = -linear, data[3][0][2][2] = linear;

	// ���� �ﰢ�� ���
	data[3][1][0][0] = 0.0f, data[3][1][0][1] = 1.0f, data[3][1][0][2] = 1.0f;
	data[3][1][1][0] = 0.0f, data[3][1][1][1] = 1.0f, data[3][1][1][2] = 1.0f;
	data[3][1][2][0] = 0.0f, data[3][1][2][1] = 1.0f, data[3][1][2][2] = 1.0f;

	// ���� �ﰢ�� �ؽ�ó
	texture_data[3][0][0] = 1.0f, texture_data[3][0][1] = 0.0f;
	texture_data[3][1][0] = 0.5f, texture_data[3][1][1] = 1.0f;
	texture_data[3][2][0] = 0.0f, texture_data[3][2][1] = 0.0f;


	// ���� �ﰢ�� ��ǥ
	data[4][0][0][0] = -linear, data[4][0][0][1] = -linear, data[4][0][0][2] = linear;
	data[4][0][1][0] = 0.0f, data[4][0][1][1] = linear, data[4][0][1][2] = 0.0f;
	data[4][0][2][0] = -linear, data[4][0][2][1] = -linear, data[4][0][2][2] = -linear;

	// ���� �ﰢ�� ���
	data[4][1][0][0] = -1.0f, data[4][1][0][1] = 1.0f, data[4][1][0][2] = 0.0f;
	data[4][1][1][0] = -1.0f, data[4][1][1][1] = 1.0f, data[4][1][1][2] = 0.0f;
	data[4][1][2][0] = -1.0f, data[4][1][2][1] = 1.0f, data[4][1][2][2] = 0.0f;

	// ���� �ﰢ�� �ؽ�ó
	texture_data[4][0][0] = 1.0f, texture_data[4][0][1] = 0.0f;
	texture_data[4][1][0] = 0.5f, texture_data[4][1][1] = 1.0f;
	texture_data[4][2][0] = 0.0f, texture_data[4][2][1] = 0.0f;

	// �ĸ� �ﰢ�� ��ǥ
	data[5][0][0][0] = -linear, data[5][0][0][1] = -linear, data[5][0][0][2] = -linear;
	data[5][0][1][0] = 0.0f, data[5][0][1][1] = linear, data[5][0][1][2] = 0.0f;
	data[5][0][2][0] = linear, data[5][0][2][1] = -linear, data[5][0][2][2] = -linear;

	// �ĸ� �ﰢ�� ���
	data[5][1][0][0] = 0.0f, data[5][1][0][1] = 1.0f, data[5][1][0][2] = -1.0f;
	data[5][1][1][0] = 0.0f, data[5][1][1][1] = 1.0f, data[5][1][1][2] = -1.0f;
	data[5][1][2][0] = 0.0f, data[5][1][2][1] = 1.0f, data[5][1][2][2] = -1.0f;

	// �ĸ� �ﰢ�� �ؽ�ó
	texture_data[5][0][0] = 1.0f, texture_data[5][0][1] = 0.0f;
	texture_data[5][1][0] = 0.5f, texture_data[5][1][1] = 1.0f;
	texture_data[5][2][0] = 0.0f, texture_data[5][2][1] = 0.0f;
}

void Quadrangular::initBuffer(GLuint s_program)
{
	glGenVertexArrays(6, vao);
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(vao[i]);
		glGenBuffers(3, vbo[i]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[i][0]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), data[i][0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[i][1]);
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), data[i][1], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[i][2]);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), texture_data[i], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(2);
	}
	glUseProgram(s_program);
	objColorLocation = glGetUniformLocation(s_program, "objectColor"); //--- object Color�� ����: (1.0, 0.5, 0.3)�� ��
}

void Quadrangular::initTexture(GLint s_program)
{

	glUseProgram(s_program);
	tLocation = glGetUniformLocation(s_program, "outTexture"); //--- outTexture ������ ���÷��� ��ġ�� ������
	glUniform1i(tLocation, 0);
}

void Quadrangular::draw()
{
	if (drawed) {
		for (int i = 0; i < 6; i++) {
			glUniform3f(objColorLocation, 1.0f, 1.0f, 1.0f);
			glBindVertexArray(vao[i]);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture[i]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}
}

void Quadrangular::allReset()
{
	drawed = false;
	Xrotate = false;
	XrotatePos = 0.0f;
	Yrotate = false;
	YrotatePos = 0.0f;
}

void Quadrangular::update()
{
	if (Xrotate) {
		XrotatePos += 1.0f;
	}
	if (Yrotate) {
		YrotatePos += 1.0f;
	}
}

void Quadrangular::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::rotate(myFactor, glm::radians(XrotatePos), glm::vec3(1.0f, 0.0f, 0.0f));
	myFactor = glm::rotate(myFactor, glm::radians(YrotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Quadrangular::getFactor()
{
	return myFactor;
}