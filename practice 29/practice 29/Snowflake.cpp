#include "Snowflake.h"

objRead Snowflake::objReader;
GLuint Snowflake::object = objReader.loadObj_normalize_center("sphere.obj");

Snowflake::Snowflake()
{
	allReset();
}

void Snowflake::initBuffer(int s_program, GLint object)
{

	//// 5.1. VAO 객체 생성 및 바인딩
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

	objColorLocation = glGetUniformLocation(s_program, "objectColor"); //--- object Color값 전달
}

void Snowflake::draw()
{
	glUniform4f(objColorLocation, 5.0f, 5.0f, 5.0f, 1.0f);
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, object);
}

void Snowflake::allReset()
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> coordinate(-2, 2);

	xPos = (float)coordinate(dre);
	yPos = 1.0f + (float)coordinate(dre);
	zPos = (float)coordinate(dre);
}

void Snowflake::update()
{
	if (yPos - 0.01f <= 0.0f) {
		yPos = 2.0f;
	}
	else {
		yPos -= 0.01f;
	}
}

void Snowflake::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::translate(myFactor, glm::vec3(xPos, yPos, zPos));
	myFactor = scale(myFactor, glm::vec3(0.05f, 0.05f, 0.05f));
}

glm::mat4 Snowflake::getFactor()
{
	return myFactor;
}
