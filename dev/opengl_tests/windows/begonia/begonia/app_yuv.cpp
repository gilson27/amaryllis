#include "app_yuv.h"
using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

/**
Window Settings
*/
const unsigned int SCR_WIDTH = 1080;
const unsigned int SCR_HEIGHT = 840;

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

/**
Main Function To draw triangle
*/
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow) {
	/**
	glfw Initializationa and configuration
	*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/**
	glfw window creation
	*/
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/**
	glad load all OpenGL function pointers
	*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	/**
	Build and Compile our shader program
	vertex shader
	*/
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	/**
	Check for shader compile errors
	*/
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	/**
	Fragment Shader
	*/
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/**
	Check for shader compiler shader errors
	*/
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << infoLog << endl;
	}

	/**
	link shades
	*/
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	/**
	Check for shader liking errors
	*/
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/**
	Initialize vertex data and configure vertex attributes
	*/
	/**
	* Define vertices for a triangle
	*/
	float vertices[] = {
		0.5f, 0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f, 0.5f, 0.0f   // top left 
	};

	float indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	/**
	Bind the array object and then allocate attributes and set the buffers
	*/
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/**
	Render Loop
	*/
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/**
	GL deallocate buffers
	*/
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}


// process all input: query glfw whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		cout << "escape pressed...";
		glfwSetWindowShouldClose(window, true);
	}

}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
//
///**
//* main function of the graphics application
//*/
//int winapi winmain(
//	hinstance hinstance,
//	hinstance hprevinstance,
//	lpstr lpcmdline,
//	int ncmdshow) 
//{
//	int a;
//	glfwinit();
//	glfwwindowhint(glfw_context_version_major, 3);
//	glfwwindowhint(glfw_context_version_minor, 3);
//	glfwwindowhint(glfw_opengl_profile, glfw_opengl_core_profile);
//	//glfwwindowhint(glfw_opengl_forward_compat, gl_true);
//
//	glfwwindow* window = glfwcreatewindow(800, 600, "learnopengl", null, null);
//	if (window == null)
//	{
//		cout << "failed to create glfw window" << std::endl;
//		glfwterminate();
//		return -1;
//	}
//	glfwmakecontextcurrent(window);
//	if (!gladloadglloader((gladloadproc)glfwgetprocaddress))
//	{
//		std::cout << "failed to initialize glad" << std::endl;
//		return -1;
//	}
//	glviewport(0, 0, 800, 600);
//	glfwsetframebuffersizecallback(window, framebuffer_size_callback);
//	while (!glfwwindowshouldclose(window))
//	{
//		processinput(window);
//		glfwswapbuffers(window);
//		glfwpollevents();
//	}
//
//	glfwterminate();
//	return 0;
//}


