#include "Earth.h"

Earth::Earth()
{
	allReset();
}

void Earth::initBuffer(int s_program, GLint object)
{
	this->object = objReader.loadObj_normalize_center("sphere.obj");

	//// 5.1. VAO ��ü ���� �� ���ε�
	glGenVertexArrays(3, vao);
	glGenBuffers(3, vbo[0]);
	glGenBuffers(3, vbo[1]);

	// 2 triangles for quad floor
	glUseProgram(s_program);
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0][0]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outvertex.size() * sizeof(glm::vec3), &objReader.outvertex[0], GL_STATIC_DRAW);
	GLint pAttribute = glGetAttribLocation(s_program, "vPos");
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1][0]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outnormal.size() * sizeof(glm::vec3), &objReader.outnormal[0], GL_STATIC_DRAW);
	GLint nAttribute = glGetAttribLocation(s_program, "vNormal");
	glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(nAttribute);

	objColorLocation = glGetUniformLocation(s_program, "objectColor"); //--- object Color�� ����
}

void Earth::draw()
{
	glUniform3f(objColorLocation, 0.1f, 0.1f, 1.0f);
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, object);
}

void Earth::allReset()
{
	rotatePos = 130.0f;
}

void Earth::update()
{
	rotatePos += 1.0f;
}

void Earth::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::translate(myFactor, glm::vec3(7.0f * cos(2 * 3.14159265358979 / 360 * rotatePos), 0.0f, 7.0f * sin(2 * 3.14159265358979 / 360 * rotatePos)));
	myFactor = scale(myFactor, glm::vec3(0.2f, 0.2f, 0.2f));
}

glm::mat4 Earth::getFactor()
{
	return myFactor;
}