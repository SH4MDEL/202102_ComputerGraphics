#include "Field.h"

Field::Field()
{
	data[0][0][0][0] = -3.0f, data[0][0][0][1] = 0.0f, data[0][0][0][2] = 3.0f;
	data[0][0][1][0] = 3.0f, data[0][0][1][1] = 0.0f, data[0][0][1][2] = 3.0f;
	data[0][0][2][0] = -3.0f, data[0][0][2][1] = 0.0f, data[0][0][2][2] = -3.0f;

	data[0][1][0][0] = -3.0f, data[0][1][0][1] = 0.0f, data[0][1][0][2] = -3.0f;
	data[0][1][1][0] = 3.0f, data[0][1][1][1] = 0.0f, data[0][1][1][2] = 3.0f;
	data[0][1][2][0] = 3.0f, data[0][1][2][1] = 0.0f, data[0][1][2][2] = -3.0f;

	data[1][0][0][0] = 0.0f, data[1][0][0][1] = 1.0f, data[1][0][0][2] = 0.0f;
	data[1][0][1][0] = 0.0f, data[1][0][1][1] = 1.0f, data[1][0][1][2] = 0.0f;
	data[1][0][2][0] = 0.0f, data[1][0][2][1] = 1.0f, data[1][0][2][2] = 0.0f;

	data[1][1][0][0] = 0.0f, data[1][1][0][1] = 1.0f, data[1][1][0][2] = 0.0f;
	data[1][1][1][0] = 0.0f, data[1][1][1][1] = 1.0f, data[1][1][1][2] = 0.0f;
	data[1][1][2][0] = 0.0f, data[1][1][2][1] = 1.0f, data[1][1][2][2] = 0.0f;
}

void Field::initBuffer(GLuint s_program)
{
	this->s_program = s_program;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(2, vbo);
	for (int i = 0; i < 2; i++) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), data[i], GL_STATIC_DRAW);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(i);
	}

	glUseProgram(s_program);
	objColorLocation = glGetUniformLocation(s_program, "objectColor"); //--- object Color°ª Àü´Þ
}

void Field::draw()
{
	glUniform4f(objColorLocation, 0.84f, 0.84f, 0.84f, 1.0f);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Field::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
}

glm::mat4 Field::getFactor()
{
	return myFactor;
}