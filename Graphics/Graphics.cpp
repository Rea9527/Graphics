// Graphics.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Graphics.h"


// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// gl load generator setting
	int ogl_loaded = ogl_LoadFunctions();
	if (ogl_loaded == ogl_LOAD_FAILED) {
		glfwDestroyWindow(window);
		return -1;
	}
	int num_failed = ogl_loaded - ogl_LOAD_SUCCEEDED;
	cout << "Number of functions that failed to load: " << num_failed << endl;

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);


	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	// Build and compile the shader programs (we ignored compile log checks for readability (if you do encounter issues, add the compile-checks!))
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER); // The first fragment shader that outputs the color orange
	GLuint fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER); // The second fragment shader that outputs the color yellow
	GLuint shaderProgramOrange = glCreateProgram();
	GLuint shaderProgramYellow = glCreateProgram(); // The second shader program
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
	glCompileShader(fragmentShaderOrange);
	glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
	glCompileShader(fragmentShaderYellow);
	// Link the first program object
	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	glLinkProgram(shaderProgramOrange);
	// Then link the second program object using a different fragment shader (but same vertex shader) this time.
	// This is perfectly allowed since the inputs and outputs of both the vertex and fragment shaders are equally matched.
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);


	// Set up vertex data (and buffer(s)) and attribute pointers
	// We add a new set of vertices to form a second triangle (a total of 6 vertices); the vertex attribute configuration remains the same (still one 3-float position vector per vertex)
	GLfloat firstTriangle[] = {
		-0.9f, -0.5f, 0.0f,  // Left 
		-0.0f, -0.5f, 0.0f,  // Right
		-0.45f, 0.5f, 0.0f,  // Top 
	};
	GLfloat secondTriangle[] = {
		0.0f, -0.5f, 0.0f,  // Left
		0.9f, -0.5f, 0.0f,  // Right
		0.45f, 0.5f, 0.0f   // Top 
	};
	GLuint VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	// ================================
	// First Triangle setup
	// ===============================
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);   // Vertex attributes stay the same
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	// ================================
	// Second Triangle setup
	// ===============================
	glBindVertexArray(VAOs[1]); // Note that we bind to a different VAO now
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); // And a different VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); // Because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out.
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Now when we want to draw the triangle we first use the vertex and orange fragment shader from the first program.
		glUseProgram(shaderProgramOrange);
		// Draw the first triangle using the data from our first VAO
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);   // This call should output an orange triangle
											// Then we draw the second triangle using the data from the second VAO
											// When we draw the second triangle we want to use a different shader program so we switch to the shader program with our yellow fragment shader.
		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);   // This call should output a yellow triangle
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

