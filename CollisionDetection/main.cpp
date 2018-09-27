// CollisionDetection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Shader.hpp"
#include "Camera.hpp"
#include "CollisionDetection.h"

#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

//glm
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoff, double yoff);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

//==============camera========================================================
bool keys[1024];

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
GLfloat lastX = WIDTH / 2, lastY = HEIGHT / 2;
bool firstMouse = true;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
Camera myCamera(cameraPos, cameraUp, -180.0f, 0.0f);
// update camera move
void updateCameraMove();
//================================================================================

// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "CollisionDetection", nullptr, nullptr);
	glfwMakeContextCurrent(window);


	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	Shader myShader("medias/vertexshader.vs", "medias/fragmentshader.frag");



	// Set up vertex data (and buffer(s)) and attribute pointers
	// We add a new set of vertices to form a second triangle (a total of 6 vertices); the vertex attribute configuration remains the same (still one 3-float position vector per vertex)
	float cube[] = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f, 

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};
	GLfloat secondTriangle[] = {
		0.0f, -0.5f, 0.0f,
		0.9f, -0.5f, 0.0f,
		0.45f, 0.5f, 0.0f
	};
	GLuint VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	// ================================
	// First Triangle setup
	// ===============================
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);   // Vertex attributes stay the same
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	// ================================
	// Second Triangle setup
	// ===============================
	glBindVertexArray(VAOs[1]); // Note that we bind to a different VAO now
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); // And a different VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); // Because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out.
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		updateCameraMove();

		myShader.Use();

		
		glm::mat4 view = myCamera.getViewMat();
		GLfloat angle = glm::radians(myCamera.Zoom);
		glm::mat4 projection = glm::perspective(angle, (GLfloat) WIDTH / HEIGHT, 0.1f, 100.0f);
		glm::mat4 projectionViewMat = projection * view;
		
		myShader.setMat4(myShader.getUniformLocation("projectionView"), projectionViewMat);


		// Now when we want to draw the triangle we first use the vertex and orange fragment shader from the first program.
		
		// Draw the first triangle using the data from our first VAO
		glBindVertexArray(VAOs[0]);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0, 0, 0.0f));
		myShader.setMat4(myShader.getUniformLocation("model"), model);
		glDrawArrays(GL_TRIANGLES, 0, 36);   


		glBindVertexArray(VAOs[1]);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0, 0));
		myShader.setMat4(myShader.getUniformLocation("model"), model);
		glDrawArrays(GL_TRIANGLES, 0, 36);   // This call should output a yellow triangle
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
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (action == GLFW_PRESS) {
		keys[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		keys[key] = false;
	}
}

void updateCameraMove() {
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (keys[GLFW_KEY_W])
		myCamera.move(CAM_FOWARD, deltaTime);
	else if (keys[GLFW_KEY_S])
		myCamera.move(CAM_BACKWARD, deltaTime);
	else if (keys[GLFW_KEY_A])
		myCamera.move(CAM_LEFT, deltaTime);
	else if (keys[GLFW_KEY_D])
		myCamera.move(CAM_RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	GLfloat offset_x, offset_y;
	//    std::cout << xpos << " " << ypos << std::endl;
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	offset_x = xpos - lastX;
	offset_y = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	myCamera.rotate(offset_x, offset_y);
}

void scroll_callback(GLFWwindow *window, double xoff, double yoff) {
	myCamera.zoom(yoff);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

	glViewport(0, 0, width, height);
}