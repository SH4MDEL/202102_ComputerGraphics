#include "Hexahedron.h"

Hexahedron::Hexahedron()
{

	allReset();

	GLfloat linear = 0.5f;	// ������ü�� ����� ���� �� ���ϴ� ������ ������ �Է����ݴϴ�.

	GLfloat front_left_down_x = -linear, front_left_down_y = -linear, front_left_down_z = linear;		// ������ü�� ����� ���� �� �ּ� �����մϴ�.
	GLfloat front_left_top_x = -linear, front_left_top_y = linear, front_left_top_z = linear;
	GLfloat front_right_down_x = linear, front_right_down_y = -linear, front_right_down_z = linear;
	GLfloat front_right_top_x = linear, front_right_top_y = linear, front_right_top_z = linear;
	GLfloat back_left_down_x = -linear, back_left_down_y = -linear, back_left_down_z = -linear;
	GLfloat back_left_top_x = -linear, back_left_top_y = linear, back_left_top_z = -linear;
	GLfloat back_right_down_x = linear, back_right_down_y = -linear, back_right_down_z = -linear;
	GLfloat back_right_top_x = linear, back_right_top_y = linear, back_right_top_z = -linear;

	//GLfloat front_left_down_x = -0.2f, front_left_down_y = -0.2f, front_left_down_z = 0.1f;		// ������ü�� ����� ���� �� ������ �������ݴϴ�.
	//GLfloat front_left_top_x = -0.2f, front_left_top_y = 0.2f, front_left_top_z = 0.1f;
	//GLfloat front_right_down_x = 0.2f, front_right_down_y = -0.2f, front_right_down_z = 0.1f;
	//GLfloat front_right_top_x = 0.2f, front_right_top_y = 0.2f, front_right_top_z = 0.1f;
	//GLfloat back_left_down_x = -0.2f, back_left_down_y = -0.2f, back_left_down_z = -0.1f;
	//GLfloat back_left_top_x = -0.2f, back_left_top_y = 0.2f, back_left_top_z = -0.1f;
	//GLfloat back_right_down_x = 0.2f, back_right_down_y = -0.2f, back_right_down_z = -0.1f;
	//GLfloat back_right_top_x = 0.2f, back_right_top_y = 0.2f, back_right_top_z = -0.1f;

	//printf("%d\n", color(gen));

	// ���� ��ǥ
	data[0][0][0][0][0] = front_left_down_x, data[0][0][0][0][1] = front_left_down_y, data[0][0][0][0][2] = front_left_down_z;
	data[0][0][0][1][0] = front_right_down_x, data[0][0][0][1][1] = front_right_down_y, data[0][0][0][1][2] = front_right_down_z;
	data[0][0][0][2][0] = front_left_top_x, data[0][0][0][2][1] = front_left_top_y, data[0][0][0][2][2] = front_left_top_z;

	data[0][0][1][0][0] = front_left_top_x, data[0][0][1][0][1] = front_left_top_y, data[0][0][1][0][2] = front_left_top_z;
	data[0][0][1][1][0] = front_right_down_x, data[0][0][1][1][1] = front_right_down_y, data[0][0][1][1][2] = front_right_down_z;
	data[0][0][1][2][0] = front_right_top_x, data[0][0][1][2][1] = front_right_top_y, data[0][0][1][2][2] = front_right_top_z;

	// ���� ���
	data[0][1][0][0][0] = 0.0f, data[0][1][0][0][1] = 0.0f, data[0][1][0][0][2] = 1.0f;
	data[0][1][0][1][0] = 0.0f, data[0][1][0][1][1] = 0.0f, data[0][1][0][1][2] = 1.0f;
	data[0][1][0][2][0] = 0.0f, data[0][1][0][2][1] = 0.0f, data[0][1][0][2][2] = 1.0f;

	data[0][1][1][0][0] = 0.0f, data[0][1][1][0][1] = 0.0f, data[0][1][1][0][2] = 1.0f;
	data[0][1][1][1][0] = 0.0f, data[0][1][1][1][1] = 0.0f, data[0][1][1][1][2] = 1.0f;
	data[0][1][1][2][0] = 0.0f, data[0][1][1][2][1] = 0.0f, data[0][1][1][2][2] = 1.0f;

	// ���� �ؽ�ó
	texture_data[0][0][0][0] = 0.0f, texture_data[0][0][0][1] = 0.0f;
	texture_data[0][0][1][0] = 1.0f, texture_data[0][0][1][1] = 0.0f;
	texture_data[0][0][2][0] = 0.0f, texture_data[0][0][2][1] = 1.0f;

	texture_data[0][1][0][0] = 0.0f, texture_data[0][1][0][1] = 1.0f;
	texture_data[0][1][1][0] = 1.0f, texture_data[0][1][1][1] = 0.0f;
	texture_data[0][1][2][0] = 1.0f, texture_data[0][1][2][1] = 1.0f;


	// ��� ��ǥ
	data[1][0][0][0][0] = front_right_top_x, data[1][0][0][0][1] = front_right_top_y, data[1][0][0][0][2] = front_right_top_z;
	data[1][0][0][1][0] = back_right_top_x, data[1][0][0][1][1] = back_right_top_y, data[1][0][0][1][2] = back_right_top_z;
	data[1][0][0][2][0] = front_left_top_x, data[1][0][0][2][1] = front_left_top_y, data[1][0][0][2][2] = front_left_top_z;

	data[1][0][1][0][0] = front_left_top_x, data[1][0][1][0][1] = front_left_top_y, data[1][0][1][0][2] = front_left_top_z;
	data[1][0][1][1][0] = back_right_top_x, data[1][0][1][1][1] = back_right_top_y, data[1][0][1][1][2] = back_right_top_z;
	data[1][0][1][2][0] = back_left_top_x, data[1][0][1][2][1] = back_left_top_y, data[1][0][1][2][2] = back_left_top_z;

	// ��� ���
	data[1][1][0][0][0] = 0.0f, data[1][1][0][0][1] = 1.0f, data[1][1][0][0][2] = 0.0f;
	data[1][1][0][1][0] = 0.0f, data[1][1][0][1][1] = 1.0f, data[1][1][0][1][2] = 0.0f;
	data[1][1][0][2][0] = 0.0f, data[1][1][0][2][1] = 1.0f, data[1][1][0][2][2] = 0.0f;
		
	data[1][1][1][0][0] = 0.0f, data[1][1][1][0][1] = 1.0f, data[1][1][1][0][2] = 0.0f;
	data[1][1][1][1][0] = 0.0f, data[1][1][1][1][1] = 1.0f, data[1][1][1][1][2] = 0.0f;
	data[1][1][1][2][0] = 0.0f, data[1][1][1][2][1] = 1.0f, data[1][1][1][2][2] = 0.0f;

	// ��� �ؽ�ó
	texture_data[1][0][0][0] = 1.0f, texture_data[1][0][0][1] = 0.0f;
	texture_data[1][0][1][0] = 1.0f, texture_data[1][0][1][1] = 1.0f;
	texture_data[1][0][2][0] = 0.0f, texture_data[1][0][2][1] = 0.0f;
	
	texture_data[1][1][0][0] = 0.0f, texture_data[1][1][0][1] = 0.0f;
	texture_data[1][1][1][0] = 1.0f, texture_data[1][1][1][1] = 1.0f;
	texture_data[1][1][2][0] = 0.0f, texture_data[1][1][2][1] = 1.0f;


	// ���� ��ǥ
	data[2][0][0][0][0] = back_left_top_x, data[2][0][0][0][1] = back_left_top_y, data[2][0][0][0][2] = back_left_top_z;
	data[2][0][0][1][0] = back_left_down_x, data[2][0][0][1][1] = back_left_down_y, data[2][0][0][1][2] = back_left_down_z;
	data[2][0][0][2][0] = front_left_down_x, data[2][0][0][2][1] = front_left_down_y, data[2][0][0][2][2] = front_left_down_z;

	data[2][0][1][0][0] = front_left_down_x, data[2][0][1][0][1] = front_left_down_y, data[2][0][1][0][2] = front_left_down_z;
	data[2][0][1][1][0] = front_left_top_x, data[2][0][1][1][1] = front_left_top_y, data[2][0][1][1][2] = front_left_top_z;
	data[2][0][1][2][0] = back_left_top_x, data[2][0][1][2][1] = back_left_top_y, data[2][0][1][2][2] = back_left_top_z;

	// ���� ���
	data[2][1][0][0][0] = -1.0f, data[2][1][0][0][1] = 0.0f, data[2][1][0][0][2] = 0.0f;
	data[2][1][0][1][0] = -1.0f, data[2][1][0][1][1] = 0.0f, data[2][1][0][1][2] = 0.0f;
	data[2][1][0][2][0] = -1.0f, data[2][1][0][2][1] = 0.0f, data[2][1][0][2][2] = 0.0f;
							
	data[2][1][1][0][0] = -1.0f, data[2][1][1][0][1] = 0.0f, data[2][1][1][0][2] = 0.0f;
	data[2][1][1][1][0] = -1.0f, data[2][1][1][1][1] = 0.0f, data[2][1][1][1][2] = 0.0f;
	data[2][1][1][2][0] = -1.0f, data[2][1][1][2][1] = 0.0f, data[2][1][1][2][2] = 0.0f;

	// ���� �ؽ�ó
	texture_data[2][0][0][0] = 0.0f, texture_data[2][0][0][1] = 1.0f;
	texture_data[2][0][1][0] = 0.0f, texture_data[2][0][1][1] = 0.0f;
	texture_data[2][0][2][0] = 1.0f, texture_data[2][0][2][1] = 0.0f;

	texture_data[2][1][0][0] = 1.0f, texture_data[2][1][0][1] = 0.0f;
	texture_data[2][1][1][0] = 1.0f, texture_data[2][1][1][1] = 1.0f;
	texture_data[2][1][2][0] = 0.0f, texture_data[2][1][2][1] = 1.0f;


	// �ĸ� ��ǥ
	data[3][0][0][0][0] = back_left_top_x, data[3][0][0][0][1] = back_left_top_y, data[3][0][0][0][2] = back_left_top_z;
	data[3][0][0][1][0] = back_left_down_x, data[3][0][0][1][1] = back_left_down_y, data[3][0][0][1][2] = back_left_down_z;
	data[3][0][0][2][0] = back_right_top_x, data[3][0][0][2][1] = back_right_top_y, data[3][0][0][2][2] = back_right_top_z;

	data[3][0][1][0][0] = back_right_top_x, data[3][0][1][0][1] = back_right_top_y, data[3][0][1][0][2] = back_right_top_z;
	data[3][0][1][1][0] = back_left_down_x, data[3][0][1][1][1] = back_left_down_y, data[3][0][1][1][2] = back_left_down_z;
	data[3][0][1][2][0] = back_right_down_x, data[3][0][1][2][1] = back_right_down_y, data[3][0][1][2][2] = back_right_down_z;

	// �ĸ� ���
	data[3][1][0][0][0] = 0.0f, data[3][1][0][0][1] = 0.0f, data[3][1][0][0][2] = -1.0f;
	data[3][1][0][1][0] = 0.0f, data[3][1][0][1][1] = 0.0f, data[3][1][0][1][2] = -1.0f;
	data[3][1][0][2][0] = 0.0f, data[3][1][0][2][1] = 0.0f, data[3][1][0][2][2] = -1.0f;

	data[3][1][1][0][0] = 0.0f, data[3][1][1][0][1] = 0.0f, data[3][1][1][0][2] = -1.0f;
	data[3][1][1][1][0] = 0.0f, data[3][1][1][1][1] = 0.0f, data[3][1][1][1][2] = -1.0f;
	data[3][1][1][2][0] = 0.0f, data[3][1][1][2][1] = 0.0f, data[3][1][1][2][2] = -1.0f;

	// �ĸ� �ؽ�ó
	texture_data[3][0][0][0] = 0.0f, texture_data[3][0][0][1] = 1.0f;
	texture_data[3][0][1][0] = 0.0f, texture_data[3][0][1][1] = 0.0f;
	texture_data[3][0][2][0] = 1.0f, texture_data[3][0][2][1] = 1.0f;

	texture_data[3][1][0][0] = 1.0f, texture_data[3][1][0][1] = 1.0f;
	texture_data[3][1][1][0] = 0.0f, texture_data[3][1][1][1] = 0.0f;
	texture_data[3][1][2][0] = 1.0f, texture_data[3][1][2][1] = 0.0f;


	// �ϴ� ��ǥ
	data[4][0][0][0][0] = back_right_down_x, data[4][0][0][0][1] = back_right_down_y, data[4][0][0][0][2] = back_right_down_z;
	data[4][0][0][1][0] = front_right_down_x, data[4][0][0][1][1] = front_right_down_y, data[4][0][0][1][2] = front_right_down_z;
	data[4][0][0][2][0] = front_left_down_x, data[4][0][0][2][1] = front_left_down_y, data[4][0][0][2][2] = front_left_down_z;

	data[4][0][1][0][0] = front_left_down_x, data[4][0][1][0][1] = front_left_down_y, data[4][0][1][0][2] = front_left_down_z;
	data[4][0][1][1][0] = back_left_down_x, data[4][0][1][1][1] = back_left_down_y, data[4][0][1][1][2] = back_left_down_z;
	data[4][0][1][2][0] = back_right_down_x, data[4][0][1][2][1] = back_right_down_y, data[4][0][1][2][2] = back_right_down_z;

	// �ϴ� ����
	data[4][1][0][0][0] = 0.0f, data[4][1][0][0][1] = -1.0f, data[4][1][0][0][2] = 0.0f;
	data[4][1][0][1][0] = 0.0f, data[4][1][0][1][1] = -1.0f, data[4][1][0][1][2] = 0.0f;
	data[4][1][0][2][0] = 0.0f, data[4][1][0][2][1] = -1.0f, data[4][1][0][2][2] = 0.0f;

	data[4][1][1][0][0] = 0.0f, data[4][1][1][0][1] = -1.0f, data[4][1][1][0][2] = 0.0f;
	data[4][1][1][1][0] = 0.0f, data[4][1][1][1][1] = -1.0f, data[4][1][1][1][2] = 0.0f;
	data[4][1][1][2][0] = 0.0f, data[4][1][1][2][1] = -1.0f, data[4][1][1][2][2] = 0.0f;

	// �ϴ� �ؽ�ó
	texture_data[4][0][0][0] = 0.0f, texture_data[4][0][0][1] = 1.0f;
	texture_data[4][0][1][0] = 0.0f, texture_data[4][0][1][1] = 0.0f;
	texture_data[4][0][2][0] = 1.0f, texture_data[4][0][2][1] = 0.0f;

	texture_data[4][1][0][0] = 1.0f, texture_data[4][1][0][1] = 0.0f;
	texture_data[4][1][1][0] = 1.0f, texture_data[4][1][1][1] = 1.0f;
	texture_data[4][1][2][0] = 0.0f, texture_data[4][1][2][1] = 1.0f;


	// ���� ��ǥ
	data[5][0][0][0][0] = back_right_down_x, data[5][0][0][0][1] = back_right_down_y, data[5][0][0][0][2] = back_right_down_z;
	data[5][0][0][1][0] = back_right_top_x, data[5][0][0][1][1] = back_right_top_y, data[5][0][0][1][2] = back_right_top_z;
	data[5][0][0][2][0] = front_right_down_x, data[5][0][0][2][1] = front_right_down_y, data[5][0][0][2][2] = front_right_down_z;

	data[5][0][1][0][0] = front_right_down_x, data[5][0][1][0][1] = front_right_down_y, data[5][0][1][0][2] = front_right_down_z;
	data[5][0][1][1][0] = back_right_top_x, data[5][0][1][1][1] = back_right_top_y, data[5][0][1][1][2] = back_right_top_z;
	data[5][0][1][2][0] = front_right_top_x, data[5][0][1][2][1] = front_right_top_y, data[5][0][1][2][2] = front_right_top_z;

	// ���� ����
	data[5][1][0][0][0] = 1.0f, data[5][1][0][0][1] = 0.0f, data[5][1][0][0][2] = 0.0f;
	data[5][1][0][1][0] = 1.0f, data[5][1][0][1][1] = 0.0f, data[5][1][0][1][2] = 0.0f;
	data[5][1][0][2][0] = 1.0f, data[5][1][0][2][1] = 0.0f, data[5][1][0][2][2] = 0.0f;

	data[5][1][1][0][0] = 1.0f, data[5][1][1][0][1] = 0.0f, data[5][1][1][0][2] = 0.0f;
	data[5][1][1][1][0] = 1.0f, data[5][1][1][1][1] = 0.0f, data[5][1][1][1][2] = 0.0f;
	data[5][1][1][2][0] = 1.0f, data[5][1][1][2][1] = 0.0f, data[5][1][1][2][2] = 0.0f;

	// ���� �ؽ�ó
	texture_data[5][0][0][0] = 1.0f, texture_data[5][0][0][1] = 0.0f;
	texture_data[5][0][1][0] = 1.0f, texture_data[5][0][1][1] = 1.0f;
	texture_data[5][0][2][0] = 0.0f, texture_data[5][0][2][1] = 0.0f;

	texture_data[5][1][0][0] = 0.0f, texture_data[5][1][0][1] = 0.0f;
	texture_data[5][1][1][0] = 1.0f, texture_data[5][1][1][1] = 1.0f;
	texture_data[5][1][2][0] = 0.0f, texture_data[5][1][2][1] = 1.0f;
}

void Hexahedron::initBuffer(GLuint s_program)
{
	glGenVertexArrays(6, vao);
	for (int i = 0; i < 6; i++) {
		glBindVertexArray(vao[i]);
		glGenBuffers(3, vbo[i]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[i][0]);
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), data[i][0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[i][1]);
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), data[i][1], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[i][2]);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), texture_data[i], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(2);
	}

	glUseProgram(s_program);
	objColorLocation = glGetUniformLocation(s_program, "objectColor"); //--- object Color�� ����
}

void Hexahedron::initTexture(GLint s_program)
{
	glUseProgram(s_program);
	tLocation = glGetUniformLocation(s_program, "outTexture"); //--- outTexture ������ ���÷��� ��ġ�� ������
	glUniform1i(tLocation, 0);
}

void Hexahedron::draw()
{
	if (drawed) {
		for (int i = 0; i < 6; i++) {
			glUniform3f(objColorLocation, 1.0f, 1.0f, 1.0f);
			glBindVertexArray(vao[i]);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture[i]);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
}

void Hexahedron::allReset()
{
	drawed = true;
	Xrotate = false;
	XrotatePos = 0.0f;
	Yrotate = false;
	YrotatePos = 0.0f;
}

void Hexahedron::update()
{
	if (Xrotate) {
		XrotatePos += 1.0f;
	}
	if (Yrotate) {
		YrotatePos += 1.0f;
	}
}

void Hexahedron::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::rotate(myFactor, glm::radians(XrotatePos), glm::vec3(1.0f, 0.0f, 0.0f));
	myFactor = glm::rotate(myFactor, glm::radians(YrotatePos), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Hexahedron::getFactor()
{
	return myFactor;
}