#define GLEW_STATIC

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "Shader.h"

const GLchar* vertexShaderSource = "#version 330 core \n"
"layout(location = 0) in vec3 position; \n"
"void main() \n"
"{\n"
"gl_Position = vec4(position.x,position.y,position.z,1.0f); \n"
"}\0";

const GLchar* fragmentShaderSourceOne = "#version 330 core \n"
"out vec4 color; \n"
"void main() \n"
"{\n"
"color = vec4(1.0f,0.5f,0.2f,1.0f); \n"
"}\0";

const GLchar* fragmentShaderSourceTwo = "#version 330 core \n"
"out vec4 color; \n"
"void main() \n"
"{ \n"
"color = vec4(1.0f,1.0f,0.0f,1.0f); \n"
"} \0";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL window", nullptr, nullptr);

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	if (window == nullptr)
	{
		std::cout << "CANNOT CREATE WINDOW" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW NOT INIT PROPERLY" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetKeyCallback(window, key_callback);

	Shader* shaderProgram = new Shader("Shaders/shader.vs", "Shaders/shader.frag");

	/*GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "VERTEX SHADER ERROR! " << infoLog << std::endl;
	}

	GLuint fragmentShaderOne;
	fragmentShaderOne = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderOne, 1, &fragmentShaderSourceOne, NULL);
	glCompileShader(fragmentShaderOne);
	glGetShaderiv(fragmentShaderOne, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderOne, 512, NULL, infoLog);
		std::cout << "FRAGMENT SHADER 1 ERROR! " << infoLog << std::endl;
	}

	GLuint fragmentShaderTwo;
	fragmentShaderTwo = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderTwo, 1, &fragmentShaderSourceTwo, NULL);
	glCompileShader(fragmentShaderTwo);
	glGetShaderiv(fragmentShaderTwo, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderTwo, 512, NULL, infoLog);
		std::cout << "FRAGMENT SHADER 2 ERROR! " << infoLog << std::endl;
	}

	GLuint shaderProgramOne;
	shaderProgramOne = glCreateProgram();
	glAttachShader(shaderProgramOne, vertexShader);
	glAttachShader(shaderProgramOne, fragmentShaderOne);
	glLinkProgram(shaderProgramOne);
	glGetProgramiv(shaderProgramOne, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramOne, 512, NULL, infoLog);
		std::cout << "PROGRAM LINK ERROR! " << infoLog << std::endl;
	}

	GLuint shaderProgramTwo;
	shaderProgramTwo = glCreateProgram();
	glAttachShader(shaderProgramTwo, vertexShader);
	glAttachShader(shaderProgramTwo, fragmentShaderTwo);
	glLinkProgram(shaderProgramTwo);
	glGetProgramiv(shaderProgramTwo, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramTwo, 512, NULL, infoLog);
		std::cout << "PROGRAM 2 LINK ERROR! " << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderOne);
	glDeleteShader(fragmentShaderTwo);*/



	/*GLfloat vertices[] = { 0.5f,0.5f,0.0f,
						   0.5f,-0.5f,0.0f,
						  -0.5f,-0.5f,0.0f,
						  -0.5f,0.5f,0.0f };*/

	GLfloat vertices[] = {
		0.5f,-0.5f,0.0f, 1.0f,0.0f,0.0f,
		-0.5f,-0.5f,0.0f, 0.0f,1.0f,0.0f,
		0.0f,0.5f,0.0f, 0.0f,0.0f,1.0f
	};

	GLuint VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)( 3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram->Use();

		GLfloat timValue = glfwGetTime();
		GLfloat greenValue = (sin(timValue) / 2) + 0.5;
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram->program, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
