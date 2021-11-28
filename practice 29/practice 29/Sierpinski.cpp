#include "Sierpinski.h"

Sierpinski::Sierpinski(GLint level)
{
	this->level = level;

	base[0][0][0] = -1.0f, base[0][0][1] = -1.0f, base[0][0][2] = 1.0f;
	base[0][1][0] = -1.0f, base[0][1][1] = -1.0f, base[0][1][2] = -1.0f;
	base[0][2][0] = 1.0f, base[0][2][1] = -1.0f, base[0][2][2] = 1.0f;

	base[0][0][0] = 1.0f, base[0][0][1] = -1.0f, base[0][0][2] = 1.0f;
	base[0][1][0] = -1.0f, base[0][1][1] = -1.0f, base[0][1][2] = -1.0f;
	base[0][2][0] = 1.0f, base[0][2][1] = -1.0f, base[0][2][2] = -1.0f;

	base[1][0][0] = 0.0f, base[1][0][1] = -1.0f, base[1][0][2] = 0.0f;
	base[1][1][0] = 0.0f, base[1][1][1] = -1.0f, base[1][1][2] = 0.0f;
	base[1][2][0] = 0.0f, base[1][2][1] = -1.0f, base[1][2][2] = 0.0f;

	base[1][0][0] = 0.0f, base[1][0][1] = -1.0f, base[1][0][2] = 0.0f;
	base[1][1][0] = 0.0f, base[1][1][1] = -1.0f, base[1][1][2] = 0.0f;
	base[1][2][0] = 0.0f, base[1][2][1] = -1.0f, base[1][2][2] = 0.0f;

	count = 0;
	make_sierpinski_right(level, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f);
	count = 0;
	make_sierpinski_front(level, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	count = 0;
	make_sierpinski_left(level, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f);
	count = 0;
	make_sierpinski_back(level, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, -1.0f);
}

void Sierpinski::make_sierpinski_right(GLint level, GLfloat upx, GLfloat upy, GLfloat upz, GLfloat leftx, GLfloat lefty, GLfloat leftz, GLfloat rightx, GLfloat righty, GLfloat rightz)
{
	if (level == 0) {

		right[0][count][0][0] = upx, right[0][count][0][1] = upy, right[0][count][0][2] = upz;
		right[0][count][1][0] = leftx, right[0][count][1][1] = lefty, right[0][count][1][2] = leftz;
		right[0][count][2][0] = rightx, right[0][count][2][1] = righty, right[0][count][2][2] = rightz;

		right[1][count][0][0] = 1.0f, right[1][count][0][1] = 1.0f, right[1][count][0][2] = 0.0f;
		right[1][count][1][0] = 1.0f, right[1][count][1][1] = 1.0f, right[1][count][1][2] = 0.0f;
		right[1][count][2][0] = 1.0f, right[1][count][2][1] = 1.0f, right[1][count][2][2] = 0.0f;
		count++;
		return;
	}

	int scale = level - 1;
	make_sierpinski_right(scale, upx, upy, upz, (leftx + upx) / 2.0f, (lefty + upy) / 2.0f, (leftz + upz) / 2.0f,
		(rightx + upx) / 2.0f, (righty + upy) / 2.0f, (rightz + upz) / 2.0f);
	make_sierpinski_right(scale, (leftx + upx) / 2.0f, (lefty + upy) / 2.0f, (leftz + upz) / 2.0f,
		leftx, lefty, leftz, (leftx + rightx) / 2.0f, (lefty + righty) / 2.0f, (leftz + rightz) / 2.0f);
	make_sierpinski_right(scale, (rightx + upx) / 2.0f, (righty + upy) / 2.0f, (rightz + upz) / 2.0f,
		(leftx + rightx) / 2.0f, (lefty + righty) / 2.0f, (leftz + rightz) / 2.0f, rightx, righty, rightz);
}

void Sierpinski::make_sierpinski_front(GLint level, GLfloat upx, GLfloat upy, GLfloat upz, GLfloat leftx, GLfloat lefty, GLfloat leftz, GLfloat rightx, GLfloat righty, GLfloat rightz)
{
	if (level == 0) {
		front[0][count][0][0] = upx, front[0][count][0][1] = upy, front[0][count][0][2] = upz;
		front[0][count][1][0] = leftx, front[0][count][1][1] = lefty, front[0][count][1][2] = leftz;
		front[0][count][2][0] = rightx, front[0][count][2][1] = righty, front[0][count][2][2] = rightz;

		front[1][count][0][0] = 0.0f, front[1][count][0][1] = 1.0f, front[1][count][0][2] = 1.0f;
		front[1][count][1][0] = 0.0f, front[1][count][1][1] = 1.0f, front[1][count][1][2] = 1.0f;
		front[1][count][2][0] = 0.0f, front[1][count][2][1] = 1.0f, front[1][count][2][2] = 1.0f;
		count++;
		return;
	}
	
	int scale = level - 1;
	make_sierpinski_front(scale, upx, upy, upz, (leftx + upx) / 2.0f, (lefty + upy) / 2.0f, (leftz + upz) / 2.0f,
		(rightx + upx) / 2.0f, (righty + upy) / 2.0f, (rightz + upz) / 2.0f);
	make_sierpinski_front(scale, (leftx + upx) / 2.0f, (lefty + upy) / 2.0f, (leftz + upz) / 2.0f,
		leftx, lefty, leftz, (leftx + rightx) / 2.0f, (lefty + righty) / 2.0f, (leftz + rightz) / 2.0f);
	make_sierpinski_front(scale, (rightx + upx) / 2.0f, (righty + upy) / 2.0f, (rightz + upz) / 2.0f,
		(leftx + rightx) / 2.0f, (lefty + righty) / 2.0f, (leftz + rightz) / 2.0f, rightx, righty, rightz);

}

void Sierpinski::make_sierpinski_left(GLint level, GLfloat upx, GLfloat upy, GLfloat upz, GLfloat leftx, GLfloat lefty, GLfloat leftz, GLfloat rightx, GLfloat righty, GLfloat rightz)
{
	if (level == 0) {
		// GLfloat front[729][2][3][3];
		left[0][count][0][0] = upx, left[0][count][0][1] = upy, left[0][count][0][2] = upz;
		left[0][count][1][0] = leftx, left[0][count][1][1] = lefty, left[0][count][1][2] = leftz;
		left[0][count][2][0] = rightx, left[0][count][2][1] = righty, left[0][count][2][2] = rightz;

		left[1][count][0][0] = -1.0f, left[1][count][0][1] = 1.0f, left[1][count][0][2] = 0.0f;
		left[1][count][1][0] = -1.0f, left[1][count][1][1] = 1.0f, left[1][count][1][2] = 0.0f;
		left[1][count][2][0] = -1.0f, left[1][count][2][1] = 1.0f, left[1][count][2][2] = 0.0f;
		count++;
		return;
	}

	int scale = level - 1;
	make_sierpinski_left(scale, upx, upy, upz, (leftx + upx) / 2.0f, (lefty + upy) / 2.0f, (leftz + upz) / 2.0f,
		(rightx + upx) / 2.0f, (righty + upy) / 2.0f, (rightz + upz) / 2.0f);
	make_sierpinski_left(scale, (leftx + upx) / 2.0f, (lefty + upy) / 2.0f, (leftz + upz) / 2.0f,
		leftx, lefty, leftz, (leftx + rightx) / 2.0f, (lefty + righty) / 2.0f, (leftz + rightz) / 2.0f);
	make_sierpinski_left(scale, (rightx + upx) / 2.0f, (righty + upy) / 2.0f, (rightz + upz) / 2.0f,
		(leftx + rightx) / 2.0f, (lefty + righty) / 2.0f, (leftz + rightz) / 2.0f, rightx, righty, rightz);
}

void Sierpinski::make_sierpinski_back(GLint level, GLfloat upx, GLfloat upy, GLfloat upz, GLfloat leftx, GLfloat lefty, GLfloat leftz, GLfloat rightx, GLfloat righty, GLfloat rightz)
{
	if (level == 0) {
		// GLfloat front[729][2][3][3];
		back[0][count][0][0] = upx, back[0][count][0][1] = upy, back[0][count][0][2] = upz;
		back[0][count][1][0] = leftx, back[0][count][1][1] = lefty, back[0][count][1][2] = leftz;
		back[0][count][2][0] = rightx, back[0][count][2][1] = righty, back[0][count][2][2] = rightz;

		back[1][count][0][0] = 0.0f, back[1][count][0][1] = 1.0f, back[1][count][0][2] = -1.0f;
		back[1][count][1][0] = 0.0f, back[1][count][1][1] = 1.0f, back[1][count][1][2] = -1.0f;
		back[1][count][2][0] = 0.0f, back[1][count][2][1] = 1.0f, back[1][count][2][2] = -1.0f;
		count++;
		return;
	}

	int scale = level - 1;
	make_sierpinski_back(scale, upx, upy, upz, (leftx + upx) / 2.0f, (lefty + upy) / 2.0f, (leftz + upz) / 2.0f,
		(rightx + upx) / 2.0f, (righty + upy) / 2.0f, (rightz + upz) / 2.0f);
	make_sierpinski_back(scale, (leftx + upx) / 2.0f, (lefty + upy) / 2.0f, (leftz + upz) / 2.0f,
		leftx, lefty, leftz, (leftx + rightx) / 2.0f, (lefty + righty) / 2.0f, (leftz + rightz) / 2.0f);
	make_sierpinski_back(scale, (rightx + upx) / 2.0f, (righty + upy) / 2.0f, (rightz + upz) / 2.0f,
		(leftx + rightx) / 2.0f, (lefty + righty) / 2.0f, (leftz + rightz) / 2.0f, rightx, righty, rightz);

}

void Sierpinski::initBuffer(GLuint s_program)
{
	glGenVertexArrays(2, bvao);
	for (int i = 0; i < 2; i++) {
		glBindVertexArray(bvao[i]);
		glGenBuffers(2, bvbo[i]);
		for (int j = 0; j < 2; j++) {
			glBindBuffer(GL_ARRAY_BUFFER, vbo[i][j]);
			glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), base[i][j], GL_STATIC_DRAW);
			glVertexAttribPointer(j, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(j);
		}
	}

	glGenVertexArrays(4, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(2, vbo[0]);
	for (int i = 0; i < 2; i++) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0][i]);
		glBufferData(GL_ARRAY_BUFFER, (int)pow(3, this->level) * 18 * sizeof(GLfloat), right[i], GL_STATIC_DRAW);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(i);
	}

	glBindVertexArray(vao[1]);
	glGenBuffers(2, vbo[1]);
	for (int i = 0; i < 2; i++) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1][i]);
		glBufferData(GL_ARRAY_BUFFER, (int)pow(3, this->level) * 18 * sizeof(GLfloat), front[i], GL_STATIC_DRAW);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(i);
	}

	glBindVertexArray(vao[2]);
	glGenBuffers(2, vbo[2]);
	for (int i = 0; i < 2; i++) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2][i]);
		glBufferData(GL_ARRAY_BUFFER, (int)pow(3, this->level) * 18 * sizeof(GLfloat), left[i], GL_STATIC_DRAW);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(i);
	}

	glBindVertexArray(vao[3]);
	glGenBuffers(2, vbo[3]);
	for (int i = 0; i < 2; i++) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[3][i]);
		glBufferData(GL_ARRAY_BUFFER, (int)pow(3, this->level) * 18 * sizeof(GLfloat), back[i], GL_STATIC_DRAW);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(i);
	}

	glUseProgram(s_program);
	objColorLocation = glGetUniformLocation(s_program, "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
}

void Sierpinski::draw()
{
	glUniform4f(objColorLocation, 0.8f, 0.8f, 0.8f, 0.8f);
	for (int i = 0; i < 2; i++) {
		glBindVertexArray(bvao[i]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	for (int i = 0; i < 4; i++) {
		glBindVertexArray(vao[i]);
		glDrawArrays(GL_TRIANGLES, 0, (int)pow(3, this->level) * 3);
	}
}

void Sierpinski::update()
{
	
}

void Sierpinski::putFactor(glm::mat4 inputFactor)
{
	myFactor = inputFactor;
	myFactor = glm::translate(myFactor, glm::vec3(0.0f, 0.0f, 0.0f));
}

glm::mat4 Sierpinski::getFactor()
{
	return myFactor;
}