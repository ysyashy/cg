#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

const float offset = 1.0/300.0;

void main()
{
    // vec3 col = texture(screenTexture, TexCoords).rgb;
	// normal
    // FragColor = vec4(col, 1.0);
	
	// inversion
	// FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);
	
	// grayscale
	// float average = 0.2126*col.r + 0.7152*col.g + 0.0722*col.b;
	// FragColor = vec4(average,average,average,1.0);
	
	// kernel
	vec2 offsets[9] = vec2[](
		vec2(-offset, offset),
		vec2(0.0f, offset),
		vec2(offset, offset),
		vec2(-offset, 0.0f),
		vec2(0.0f, 0.0f),
		vec2(offset, 0.0f),
		vec2(-offset, -offset),
		vec2(0.0f, -offset),
		vec2(offset, -offset)
	);
	// sharp
	float sharpKernel[9] = float[](
		-1, -1, -1,
		-1,  9, -1,
		-1, -1, -1
	);
	// blur
	float blurKernel[9] = float[](
		1.0/16, 2.0/16, 1.0/16,
		2.0/16, 4.0/16, 2.0/16,
		1.0/16, 2.0/16, 1.0/16
	);
	// edge-detection
	float edgeKernel[9] = float[](
		1, 1, 1,
		1, -8, 1,
		1, 1, 1
	);
	vec3 col = vec3(0.0);
	for(int i=0; i<9; i++){
		// col += vec3(texture(screenTexture, TexCoords.st+offsets[i])) * sharpKernel[i];
		// col += vec3(texture(screenTexture, TexCoords.st+offsets[i])) * blurKernel[i];
		col += vec3(texture(screenTexture, TexCoords.st+offsets[i])) * edgeKernel[i];
	}
	FragColor = vec4(col, 1.0);
} 