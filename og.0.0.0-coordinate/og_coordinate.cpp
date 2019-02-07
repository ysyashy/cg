#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <Shader.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "triangle", nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (GLEW_OK != glewInit()) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0);\n"
		"	ourColor = aColor;"
		"}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourColor;"
		// "uniform vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		// "	FragColor = vec4(1.0, 0, 0, 1.0);\n"
		"	FragColor = vec4(ourColor, 1.0);"
		"}\n\0";
	int compileStatus;
	char infoLog[512];

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "vertex shader error: " << infoLog << std::endl;
	}

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "fragment shader error: " << infoLog << std::endl;
	}

	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &compileStatus);
	if (!compileStatus) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "link error: " << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/*float vertices[] = {
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f
	};*/
	//float vertices[] = {
	//	// Î»ÖÃ              // ÑÕÉ«
	//	0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   
	//	0.5f, -0.5f, 0.0f, 0.5f, 1.0f, 0.0f,   
	//	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  
	//	-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f
	//};
	const int v = INT_MAX / 2;
	GLint vertices_int[] = {
		/*0.5, 0.5, 0,
		0.5, -0.5, 0,
		-0.5, -0.5, 0,
		-0.5, 0.5, 0*/
		v, v, 0,
		v, -v, 0,
		-v, -v, 0,
		-v, v, 0
	};
	GLubyte colors_ubyte[] = {
		255, 0, 0,
		128, 1, 0,
		0, 0, 255,
		255, 255, 0
	};
	unsigned int indices[] = {
		1, 2, 3,
		0, 1, 3
	};
	unsigned int vbo, vao, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_int) + sizeof(colors_ubyte), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices_int), vertices_int);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices_int), sizeof(colors_ubyte), colors_ubyte);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_INT, GL_TRUE, 3 * sizeof(GLint), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, 3 * sizeof(GLubyte), (void*)sizeof(vertices_int));
	glEnableVertexAttribArray(1);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)NULL);
	// glEnableVertexAttribArray(0);
	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		//double timeValue = glfwGetTime();
		//double greenValue = sin(timeValue) / 2.0 + 0.5;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glDrawArrays(GL_TRIANGLES, 0, 3);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	glfwTerminate();

}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
		glfwSetWindowShouldClose(window, true);
	}
}