#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

const float near = 0.1;
const float far = 100.0;

float LinearizeDepth(float depth){
	float z = depth * 2.0 - 1.0;	// back to NDC
	return (2.0 * near * far) / (far + near - z * (far-near));
}

void main()
{    
	FragColor = vec4(0.0, 1.0, 0.0, 1.0);
    // FragColor = texture(texture1, TexCoords);
	// float depth = LinearizeDepth(gl_FragCoord.z) / far;
	// FragColor = vec4(vec3(depth), 1.0);
}