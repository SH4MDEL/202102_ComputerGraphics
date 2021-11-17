#include "Orbit.h"

Orbit::Orbit()
{
	allReset();

	for (int i = 0; i < 20; i++) {
		data[i][0][0][0] = (GLfloat)(r * glm::cos(2 * M_PI / 20 * i));
		data[i][0][0][1] = 0.0f;
		data[i][0][0][2] = (GLfloat)(r * glm::sin(2 * M_PI / 20 * i));

		data[i][0][1][0] = (GLfloat)(r * glm::cos(2 * M_PI / 20 * (i + 1)));
		data[i][0][1][1] = 0.0f;
		data[i][0][1][2] = (GLfloat)(r * glm::sin(2 * M_PI / 20 * (i + 1)));

		data[i][1][0][0] = 1.0f;
		data[i][1][0][1] = 1.0f;
		data[i][1][0][2] = 1.0f;

		data[i][1][1][0] = 1.0f;
		data[i][1][1][1] = 1.0f;
		data[i][1][1][2] = 1.0f;
	}
}

void Orbit::initBuffer(GLuint s_program)
{
	glGenVertexArrays(20, vao);
	for (int i = 0; i < 20; i++) {
		glBindVertexArray(vao[i]);
		glGenBuffers(2, vbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), data[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}

	glUseProgram(s_program);
	objColorLocation = glGetUniformLocation(s_program, "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
}

void Orbit::draw()
{
	glUniform3f(objColorLocation, 0.8f, 0.8f, 0.8f);
	for (int i = 0; i < 20; i++) {
		glBindVertexArray(vao[i]);
		glDrawArrays(GL_LINES, 0, 2);
	}
}

void Orbit::allReset()
{
	r = 1.5f;
	scalePos = 1.0f;
}

void Orbit::update()
{

}

void Orbit::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = scale(myFactor, glm::vec3(scalePos, 1.0f, scalePos));
}

glm::mat4 Orbit::getFactor()
{
	return myFactor;
}