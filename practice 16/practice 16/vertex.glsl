#version 330
// in_Position	: attribute index 0 
// in_Color		: attribute index 1

layout(location = 0) in vec3 in_Position;		// ��ġ ����: attribute position 0
layout(location = 1) in vec3 in_Color;			// �÷� ����: attribute position 1
out vec3 out_Color;								// �����׸�Ʈ ���̴����� ����

uniform mat4 backgroundModelTransform;
uniform mat4 firstModelTransform;
uniform mat4 secondModelTransform;

uniform int modelSelect = 0;

void main(void)
{
	gl_Position = backgroundModelTransform * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
	out_Color = in_Color;
	if (modelSelect == 1) {
		gl_Position = firstModelTransform * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
		out_Color = in_Color;
	}
	else if (modelSelect == 2) {
		gl_Position = secondModelTransform * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
		out_Color = in_Color;
	}
}