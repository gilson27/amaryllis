/**
\file Texture example
*/

#include "texture.h"

void frame_buffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);

/**
Settings
*/
const unsigned int SCR_WIDTH = 400;
const unsigned int SCR_HEIGHT = 300;

/**
Main function
*/
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreviousInstance,
	LPSTR lpCmdLine,
	int nCmdShow
	) {

	/**
	Initialize and setup Window
	*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
	/**
	Create GLFW window
	*/
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Texture Example", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create window. Terminating..." << endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

	/**
	GLAD:: Load all openGL glad libraries
	*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to load GL procedures. Exiting...";
		return 1;
	}

	/**
	Create shader objects
	*/
	Shader shaderObj("texture.vs", "texture.fs");

	/**
	Define vertices for the rectangle
	*/
	float vertices[] = {
		// positions          // colors           // texture coords
		-1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	/**
	Create vertex array object and bind buffer object
	*/
	unsigned int VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/**
	Add Attributes
	*/
	/**
	Position
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	/**
	Color
	*/
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	/**
	Texture
	*/
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	/**
	Load and Create Texture for video Frame
	*/
	unsigned int videoFrame, overlayImage;





	/**
	Load image generate texture and mipmaps
	*/
	int width, height, nrChannels;
	char *baseFileName = "frames/";
	char *overlayFileName = "container.jpg";
	char frameFileName[100];
	int frameNum = 1;
	int maxFrames = 300;
	/**
	Render Loop
	*/
	while (!glfwWindowShouldClose(window)) {
		/**
		process input
		*/
		process_input(window);

		/**
		Render
		*/
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glGenTextures(1, &videoFrame);

		glBindTexture(GL_TEXTURE_2D, videoFrame); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

		/**
		Set texture attributes or parameters
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		sprintf_s(frameFileName, "%s%d.jpg", baseFileName, frameNum);
		unsigned char* textureDataFrame = stbi_load(frameFileName, &width, &height, &nrChannels, 0);
		if (textureDataFrame) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureDataFrame);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			cout << "Error:: Failed to load image.." << endl;
		}
		stbi_image_free(textureDataFrame);

		/**
		Render video texture
		*/
		glTexCoordP2ui(0.0, 0.0);
		glTexCoordP2ui(0.0, 0.5);
		glTexCoordP2ui(0.5, 0.5);
		glTexCoordP2ui(0.5, 0.0);

		glGenTextures(1, &overlayImage);

		glBindTexture(GL_TEXTURE_2D, overlayImage); 

		/**
		Set texture attributes or parameters
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unsigned char* textureDataOverlay = stbi_load(overlayFileName, &width, &height, &nrChannels, 0);
		if (textureDataOverlay) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureDataOverlay);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			cout << "Error:: Failed to load image.." << endl;
		}
		stbi_image_free(textureDataOverlay);
		//glTexCoordP2ui();
		/**
			Render Vertex array and texture
		*/

		// glTexCoordP2ui(0.5, 0.5);
		// glTexCoordP2ui(0.5, 1.0);
		// glTexCoordP2ui(1.0, 1.0);
		// glTexCoordP2ui(1.0, 0.5);
		shaderObj.use();
		shaderObj.setInt("videoFrame", 0);
		shaderObj.setInt("overlayImage", 1);

		glActivateTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, videoFrame);
		glActivateTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, overlayImage);


		shaderObj.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
		if (frameNum <= maxFrames) {
			frameNum++;
		}
		Sleep(30);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
}


/**
Frame resize callback
*/
void frame_buffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

/**
Process keyboard and mouse input to the window
*/
void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}