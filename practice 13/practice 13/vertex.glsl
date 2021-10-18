#version 330
// in_Position	: attribute index 0 
// in_Color		: attribute index 1

layout(location = 0) in vec3 in_Position;		// ��ġ ����: attribute position 0
layout(location = 1) in vec3 in_Color;			// �÷� ����: attribute position 1
out vec3 out_Color;								// �����׸�Ʈ ���̴����� ����

uniform mat4 modelTransform;

void main(void)
{
	if (in_Position.x == -1.0f || in_Position.x == 1.0f || in_Position.y == -1.0f || in_Position.y == 1.0f) {
		gl_Position = vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
	}
	else {
		gl_Position = modelTransform * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
	}
	out_Color = in_Color;
}