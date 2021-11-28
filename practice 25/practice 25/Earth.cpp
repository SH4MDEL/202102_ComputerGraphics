#include "Earth.h"

Earth::Earth()
{
	allReset();
}

void Earth::initBuffer(int s_program)
{
	object = objReader.loadObj_normalize_center("sphere.obj");

	//// 5.1. VAO 객체 생성 및 바인딩
	glGenVertexArrays(1, &vao);

	// 2 triangles for quad floor
	glUseProgram(s_program);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outvertex.size() * sizeof(glm::vec3), &objReader.outvertex[0], GL_STATIC_DRAW);
	GLint pAttribute = glGetAttribLocation(s_program, "vPos");
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute);

	glGenBuffers(1, &vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, objReader.outnormal.size() * sizeof(glm::vec3), &objReader.outnormal[0], GL_STATIC_DRAW);
	GLint nAttribute = glGetAttribLocation(s_program, "vNormal");
	glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(nAttribute);

	objColorLocation = glGetUniformLocation(s_program, "objectColor"); //--- object Color값 전달
}

void Earth::draw()
{
	glUniform3f(objColorLocation, 0.1f, 0.1f, 1.0f);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, object);
}

void Earth::allReset()
{

}

void Earth::update()
{

}

void Earth::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::translate(myFactor, glm::vec3(-1.5f, 0.0f, 0.0f));
	myFactor = scale(myFactor, glm::vec3(0.2f, 0.2f, 0.2f));
}

glm::mat4 Earth::getFactor()
{
	return myFactor;
}