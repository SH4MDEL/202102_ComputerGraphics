#include "Crane_Mid.h"

Crane_Mid::Crane_Mid()
{
	allReset();

	// ���� ��ǥ
	data[0][0][0][0][0] = -0.2f, data[0][0][0][0][1] = -0.1f, data[0][0][0][0][2] = 0.2f;
	data[0][0][0][1][0] = 0.2f, data[0][0][0][1][1] = -0.1f, data[0][0][0][1][2] = 0.2f;
	data[0][0][0][2][0] = -0.2f, data[0][0][0][2][1] = 0.1f, data[0][0][0][2][2] = 0.2f;

	data[0][0][1][0][0] = -0.2f, data[0][0][1][0][1] = 0.1f, data[0][0][1][0][2] = 0.2f;
	data[0][0][1][1][0] = 0.2f, data[0][0][1][1][1] = -0.1f, data[0][0][1][1][2] = 0.2f;
	data[0][0][1][2][0] = 0.2f, data[0][0][1][2][1] = 0.1f, data[0][0][1][2][2] = 0.2f;

	// ���� ���
	data[0][1][0][0][0] = 0.0f, data[0][1][0][0][1] = 0.0f, data[0][1][0][0][2] = 1.0f;
	data[0][1][0][1][0] = 0.0f, data[0][1][0][1][1] = 0.0f, data[0][1][0][1][2] = 1.0f;
	data[0][1][0][2][0] = 0.0f, data[0][1][0][2][1] = 0.0f, data[0][1][0][2][2] = 1.0f;

	data[0][1][1][0][0] = 0.0f, data[0][1][1][0][1] = 0.0f, data[0][1][1][0][2] = 1.0f;
	data[0][1][1][1][0] = 0.0f, data[0][1][1][1][1] = 0.0f, data[0][1][1][1][2] = 1.0f;
	data[0][1][1][2][0] = 0.0f, data[0][1][1][2][1] = 0.0f, data[0][1][1][2][2] = 1.0f;


	// ��� ��ǥ
	data[1][0][0][0][0] = 0.2f, data[1][0][0][0][1] = 0.1f, data[1][0][0][0][2] = 0.2f;
	data[1][0][0][1][0] = 0.2f, data[1][0][0][1][1] = 0.1f, data[1][0][0][1][2] = -0.2f;
	data[1][0][0][2][0] = -0.2f, data[1][0][0][2][1] = 0.1f, data[1][0][0][2][2] = 0.2f;

	data[1][0][1][0][0] = -0.2f, data[1][0][1][0][1] = 0.1f, data[1][0][1][0][2] = 0.2f;
	data[1][0][1][1][0] = 0.2f, data[1][0][1][1][1] = 0.1f, data[1][0][1][1][2] = -0.2f;
	data[1][0][1][2][0] = -0.2f, data[1][0][1][2][1] = 0.1f, data[1][0][1][2][2] = -0.2f;

	// ��� ���
	data[1][1][0][0][0] = 0.0f, data[1][1][0][0][1] = 1.0f, data[1][1][0][0][2] = 0.0f;
	data[1][1][0][1][0] = 0.0f, data[1][1][0][1][1] = 1.0f, data[1][1][0][1][2] = 0.0f;
	data[1][1][0][2][0] = 0.0f, data[1][1][0][2][1] = 1.0f, data[1][1][0][2][2] = 0.0f;

	data[1][1][1][0][0] = 0.0f, data[1][1][1][0][1] = 1.0f, data[1][1][1][0][2] = 0.0f;
	data[1][1][1][1][0] = 0.0f, data[1][1][1][1][1] = 1.0f, data[1][1][1][1][2] = 0.0f;
	data[1][1][1][2][0] = 0.0f, data[1][1][1][2][1] = 1.0f, data[1][1][1][2][2] = 0.0f;

	// ���� ��ǥ
	data[2][0][0][0][0] = -0.2f, data[2][0][0][0][1] = 0.1f, data[2][0][0][0][2] = -0.2f;
	data[2][0][0][1][0] = -0.2f, data[2][0][0][1][1] = -0.1f, data[2][0][0][1][2] = -0.2f;
	data[2][0][0][2][0] = -0.2f, data[2][0][0][2][1] = -0.1f, data[2][0][0][2][2] = 0.2f;

	data[2][0][1][0][0] = -0.2f, data[2][0][1][0][1] = -0.1f, data[2][0][1][0][2] = 0.2f;
	data[2][0][1][1][0] = -0.2f, data[2][0][1][1][1] = 0.1f, data[2][0][1][1][2] = 0.2f;
	data[2][0][1][2][0] = -0.2f, data[2][0][1][2][1] = 0.1f, data[2][0][1][2][2] = -0.2f;

	// ���� ���
	data[2][1][0][0][0] = -1.0f, data[2][1][0][0][1] = 0.0f, data[2][1][0][0][2] = 0.0f;
	data[2][1][0][1][0] = -1.0f, data[2][1][0][1][1] = 0.0f, data[2][1][0][1][2] = 0.0f;
	data[2][1][0][2][0] = -1.0f, data[2][1][0][2][1] = 0.0f, data[2][1][0][2][2] = 0.0f;

	data[2][1][1][0][0] = -1.0f, data[2][1][1][0][1] = 0.0f, data[2][1][1][0][2] = 0.0f;
	data[2][1][1][1][0] = -1.0f, data[2][1][1][1][1] = 0.0f, data[2][1][1][1][2] = 0.0f;
	data[2][1][1][2][0] = -1.0f, data[2][1][1][2][1] = 0.0f, data[2][1][1][2][2] = 0.0f;

	// �ĸ� ��ǥ
	data[3][0][0][0][0] = -0.2f, data[3][0][0][0][1] = 0.1f, data[3][0][0][0][2] = -0.2f;
	data[3][0][0][1][0] = -0.2f, data[3][0][0][1][1] = -0.1f, data[3][0][0][1][2] = -0.2f;
	data[3][0][0][2][0] = 0.2f, data[3][0][0][2][1] = 0.1f, data[3][0][0][2][2] = -0.2f;

	data[3][0][1][0][0] = 0.2f, data[3][0][1][0][1] = 0.1f, data[3][0][1][0][2] = -0.2f;
	data[3][0][1][1][0] = -0.2f, data[3][0][1][1][1] = -0.1f, data[3][0][1][1][2] = -0.2f;
	data[3][0][1][2][0] = 0.2f, data[3][0][1][2][1] = -0.1f, data[3][0][1][2][2] = -0.2f;

	// �ĸ� ���
	data[3][1][0][0][0] = 0.0f, data[3][1][0][0][1] = 0.0f, data[3][1][0][0][2] = -1.0f;
	data[3][1][0][1][0] = 0.0f, data[3][1][0][1][1] = 0.0f, data[3][1][0][1][2] = -1.0f;
	data[3][1][0][2][0] = 0.0f, data[3][1][0][2][1] = 0.0f, data[3][1][0][2][2] = -1.0f;

	data[3][1][1][0][0] = 0.0f, data[3][1][1][0][1] = 0.0f, data[3][1][1][0][2] = -1.0f;
	data[3][1][1][1][0] = 0.0f, data[3][1][1][1][1] = 0.0f, data[3][1][1][1][2] = -1.0f;
	data[3][1][1][2][0] = 0.0f, data[3][1][1][2][1] = 0.0f, data[3][1][1][2][2] = -1.0f;

	// �ϴ� ��ǥ
	data[4][0][0][0][0] = 0.2f, data[4][0][0][0][1] = -0.1f, data[4][0][0][0][2] = -0.2f;
	data[4][0][0][1][0] = 0.2f, data[4][0][0][1][1] = -0.1f, data[4][0][0][1][2] = 0.2f;
	data[4][0][0][2][0] = -0.2f, data[4][0][0][2][1] = -0.1f, data[4][0][0][2][2] = 0.2f;

	data[4][0][1][0][0] = -0.2f, data[4][0][1][0][1] = -0.1f, data[4][0][1][0][2] = 0.2f;
	data[4][0][1][1][0] = -0.2f, data[4][0][1][1][1] = -0.1f, data[4][0][1][1][2] = -0.2f;
	data[4][0][1][2][0] = 0.2f, data[4][0][1][2][1] = -0.1f, data[4][0][1][2][2] = -0.2f;

	// �ϴ� ���
	data[4][1][0][0][0] = 0.0f, data[4][1][0][0][1] = -1.0f, data[4][1][0][0][2] = 0.0f;
	data[4][1][0][1][0] = 0.0f, data[4][1][0][1][1] = -1.0f, data[4][1][0][1][2] = 0.0f;
	data[4][1][0][2][0] = 0.0f, data[4][1][0][2][1] = -1.0f, data[4][1][0][2][2] = 0.0f;

	data[4][1][1][0][0] = 0.0f, data[4][1][1][0][1] = -1.0f, data[4][1][1][0][2] = 0.0f;
	data[4][1][1][1][0] = 0.0f, data[4][1][1][1][1] = -1.0f, data[4][1][1][1][2] = 0.0f;
	data[4][1][1][2][0] = 0.0f, data[4][1][1][2][1] = -1.0f, data[4][1][1][2][2] = 0.0f;

	// ���� ��ǥ
	data[5][0][0][0][0] = 0.2f, data[5][0][0][0][1] = -0.1f, data[5][0][0][0][2] = -0.2f;
	data[5][0][0][1][0] = 0.2f, data[5][0][0][1][1] = 0.1f, data[5][0][0][1][2] = -0.2f;
	data[5][0][0][2][0] = 0.2f, data[5][0][0][2][1] = -0.1f, data[5][0][0][2][2] = 0.2f;

	data[5][0][1][0][0] = 0.2f, data[5][0][1][0][1] = -0.1f, data[5][0][1][0][2] = 0.2f;
	data[5][0][1][1][0] = 0.2f, data[5][0][1][1][1] = 0.1f, data[5][0][1][1][2] = -0.2f;
	data[5][0][1][2][0] = 0.2f, data[5][0][1][2][1] = 0.1f, data[5][0][1][2][2] = 0.2f;

	// ���� ���
	data[5][1][0][0][0] = 1.0f, data[5][1][0][0][1] = 0.0f, data[5][1][0][0][2] = 0.0f;
	data[5][1][0][1][0] = 1.0f, data[5][1][0][1][1] = 0.0f, data[5][1][0][1][2] = 0.0f;
	data[5][1][0][2][0] = 1.0f, data[5][1][0][2][1] = 0.0f, data[5][1][0][2][2] = 0.0f;

	data[5][1][1][0][0] = 1.0f, data[5][1][1][0][1] = 0.0f, data[5][1][1][0][2] = 0.0f;
	data[5][1][1][1][0] = 1.0f, data[5][1][1][1][1] = 0.0f, data[5][1][1][1][2] = 0.0f;
	data[5][1][1][2][0] = 1.0f, data[5][1][1][2][1] = 0.0f, data[5][1][1][2][2] = 0.0f;
}

void Crane_Mid::initBuffer(GLuint s_program)
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
	objColorLocation = glGetUniformLocation(s_program, "objectColor"); //--- object Color�� ����
}

void Crane_Mid::draw()
{
	glUniform3f(objColorLocation, 0.0f, 1.0f, 0.0f);
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(vao[i]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void Crane_Mid::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::translate(myFactor, glm::vec3(0, HeightFromGround, 0));
	myFactor = glm::rotate(myFactor, glm::radians(rMovePos), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Crane_Mid::getFactor()
{
	return myFactor;
}

void Crane_Mid::allReset()
{
	HeightFromGround = 0.2f;
	rMove = 0;
	rMovePos = 0.0f;
}

void Crane_Mid::update()
{
	if (rMove == 1) {
		rMovePos += 1.0f;
	}
	else if (rMove == 2) {
		rMovePos -= 1.0f;
	}
}