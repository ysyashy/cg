#version 330 core

in vec3 aPos;
in vec3 aColor;
in vec2 aTexCoor;

out vec3 outColor;
out vec2 outTexCoor;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	outColor = aColor;
	outTexCoor = aTexCoor;
}