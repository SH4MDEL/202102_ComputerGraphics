#include "Sun.h"
#include "ObjRead.h"

std::vector< glm::vec3 > outvertex, outnormal;

Sun::Sun()
{
	
}

void Sun::initBuffer(int s_program)
{
	object = loadObj_normalize_center("sphere.obj");

	//// 5.1. VAO 객체 생성 및 바인딩
	glGenVertexArrays(3, vao);
	glGenBuffers(3, vbo[0]);
	glGenBuffers(3, vbo[1]);

	// 2 triangles for quad floor
	glUseProgram(s_program);
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0][0]);
	glBufferData(GL_ARRAY_BUFFER, outvertex.size() * sizeof(glm::vec3), &outvertex[0], GL_STATIC_DRAW);
	GLint pAttribute = glGetAttribLocation(s_program, "vPos");
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1][0]);
	glBufferData(GL_ARRAY_BUFFER, outnormal.size() * sizeof(glm::vec3), &outnormal[0], GL_STATIC_DRAW);
	GLint nAttribute = glGetAttribLocation(s_program, "vNormal");
	glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(nAttribute);

	objColorLocation = glGetUniformLocation(s_program, "objectColor"); //--- object Color값 전달
}

void Sun::draw()
{
	glUniform3f(objColorLocation, 1.0f, 0.1f, 0.1f);
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, object);
}

void Sun::allReset()
{
	
}

void Sun::update()
{
	
}

void Sun::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
}

glm::mat4 Sun::getFactor()
{
	return myFactor;
}