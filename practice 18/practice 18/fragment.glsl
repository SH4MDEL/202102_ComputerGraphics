#version 330
// out_Color :	���ؽ� ���̴����� �Է¹޴� ���� ��
// FragColor :	����� ������ ������ ������ ���۷� ���� ��.

in vec3 out_Color;			// ���ؽ� ���̴����Լ� ���� ����
out vec4 FragColor;			// ���� ���

uniform vec4 myColor;

void main(void) 
{
	FragColor = myColor;
}