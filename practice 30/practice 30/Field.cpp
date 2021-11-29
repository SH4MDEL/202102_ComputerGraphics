#include "Field.h"

Field::Field()
{

	allReset();

	GLfloat linear = 40.0f;	// 정육면체를 만들고 싶을 때 원하는 길이의 절반을 입력해줍니다.

	//printf("%d\n", color(gen));

	// 전면 좌표
	data[0][0][0][0] = -linear, data[0][0][0][1] = -linear, data[0][0][0][2] = 0.0f;
	data[0][0][1][0] = linear, data[0][0][1][1] = -linear, data[0][0][1][2] = 0.0f;
	data[0][0][2][0] = -linear, data[0][0][2][1] = linear, data[0][0][2][2] = 0.0f;

	data[0][1][0][0] = -linear, data[0][1][0][1] = linear, data[0][1][0][2] = 0.0f;
	data[0][1][1][0] = linear, data[0][1][1][1] = -linear, data[0][1][1][2] = 0.0f;
	data[0][1][2][0] = linear, data[0][1][2][1] = linear, data[0][1][2][2] = 0.0f;

	// 전면 노멀
	data[1][0][0][0] = 0.0f, data[1][0][0][1] = 0.0f, data[1][0][0][2] = 1.0f;
	data[1][0][1][0] = 0.0f, data[1][0][1][1] = 0.0f, data[1][0][1][2] = 1.0f;
	data[1][0][2][0] = 0.0f, data[1][0][2][1] = 0.0f, data[1][0][2][2] = 1.0f;

	data[1][1][0][0] = 0.0f, data[1][1][0][1] = 0.0f, data[1][1][0][2] = 1.0f;
	data[1][1][1][0] = 0.0f, data[1][1][1][1] = 0.0f, data[1][1][1][2] = 1.0f;
	data[1][1][2][0] = 0.0f, data[1][1][2][1] = 0.0f, data[1][1][2][2] = 1.0f;

	// 전면 텍스처
	texture_data[0][0][0] = 0.0f, texture_data[0][0][1] = 0.0f;
	texture_data[0][1][0] = 1.0f, texture_data[0][1][1] = 0.0f;
	texture_data[0][2][0] = 0.0f, texture_data[0][2][1] = 1.0f;

	texture_data[1][0][0] = 0.0f, texture_data[1][0][1] = 1.0f;
	texture_data[1][1][0] = 1.0f, texture_data[1][1][1] = 0.0f;
	texture_data[1][2][0] = 1.0f, texture_data[1][2][1] = 1.0f;
}

void Field::initBuffer(GLuint s_program)
{
	glGenVertexArrays(1, &vao);

		glBindVertexArray(vao);
		glGenBuffers(3, vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), data[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), data[1], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), texture_data, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(2);


	glUseProgram(s_program);
	objColorLocation = glGetUniformLocation(s_program, "objectColor"); //--- object Color값 전달
}

void Field::initTexture(GLint s_program)
{
	glUseProgram(s_program);
	tLocation = glGetUniformLocation(s_program, "outTexture"); //--- outTexture 유니폼 샘플러의 위치를 가져옴
	glUniform1i(tLocation, 0);
}

void Field::draw()
{
	glUniform3f(objColorLocation, 1.0f, 1.0f, 1.0f);
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Field::allReset()
{

}

void Field::update()
{

}

void Field::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::translate(myFactor, glm::vec3(0.0f, 0.0f, -60.0f));
}

glm::mat4 Field::getFactor()
{
	return myFactor;
}
