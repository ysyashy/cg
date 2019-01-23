#version 330 core
out vec4 FragColor;

in vec3 outColor;
in vec2 outTexCoor;

uniform sampler2D texture1;


void main()
{
	FragColor = texture(texture1, outTexCoor) * vec4(outColor, 1.0);
	// FragColor = vec4(outColor, 1.0);
}