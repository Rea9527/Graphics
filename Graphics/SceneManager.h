#pragma once

#include <iostream>
#include <string>
using namespace std;

// GL CORE
#include <GL_CORE/gl_core_4_3.h>
#include <GL_CORE/gl_core_4_3.c>
// GLFW
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "Camera.h"
#include "GLUtils.h"
#include "GLGUI.h"



class SceneManager {

public:

	SceneManager(int width, int height, const string title) {
		if (!glfwInit()) { exit(EXIT_FAILURE); }

		// Set all the required options for GLFW, using OpenGL 4.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		// Create window
		this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		// Ogl loader
		int ogl_loaded = ogl_LoadFunctions();
		if (ogl_loaded == ogl_LOAD_FAILED) {
			glfwDestroyWindow(window);
			exit(EXIT_FAILURE);
		}
		int num_failed = ogl_loaded - ogl_LOAD_SUCCEEDED;
		cerr << "Number of functions that failed to load: " << num_failed << endl;
		// get frame buffer size
		glfwGetFramebufferSize(window, &frame_size_width, &frame_size_height);
		glViewport(0, 0, frame_size_width, frame_size_height);

		// camera
		this->deltaTime = 0.0f;
		this->lastFrame = 0.0f;
		this->lastX = frame_size_width / 2;
		this->lastY = frame_size_height / 2;
		this->firstMouse = true;


		//set keycallback
		glfwSetKeyCallback(window, key_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
		
		// init GUI
		ImGui_ImplGlfwGL3_Init(window, false);
	}

	int run(Scene &scene) {
		GLUtils::checkForOpenGLError(__FILE__, __LINE__);
		scene.setDimensions(this->frame_size_width, this->frame_size_height);
		scene.initScene();
		scene.resize(this->frame_size_width, this->frame_size_height);
		//main loop
		Camera::getInstance()->use();
		this->mainLoop(this->window, scene);

		// shut down GUI
		ImGui_ImplGlfwGL3_Shutdown();
		//close window and stop glfw
		glfwTerminate();
		
		return EXIT_SUCCESS;
	}


private:
	GLFWwindow *window;
	int frame_size_width, frame_size_height;

	//camera
	static bool keys[1024];
	static GLfloat deltaTime;
	static GLfloat lastFrame;
	static GLfloat lastX;
	static GLfloat lastY;
	static bool firstMouse;

	
	void mainLoop(GLFWwindow* window, Scene &scene) {
		while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			//GLUtils::checkForOpenGLError(__FILE__, __LINE__);
			glfwPollEvents();
			updateMovement();
			scene.update(float(glfwGetTime()));
			scene.render();
			glfwSwapBuffers(window);
		}
	}

	inline static void updateMovement() {
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		Camera* camera = Camera::getInstance();

		if (keys[GLFW_KEY_W])
			camera->translate(CAM_FOWARD, deltaTime);
		else if (keys[GLFW_KEY_S])
			camera->translate(CAM_BACKWARD, deltaTime);
		else if (keys[GLFW_KEY_A])
			camera->translate(CAM_LEFT, deltaTime);
		else if (keys[GLFW_KEY_D])
			camera->translate(CAM_RIGHT, deltaTime);

	}

	inline static auto key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);

		if (action == GLFW_PRESS) {
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			keys[key] = false;
		}
	}

	inline static auto mouse_callback(GLFWwindow* window, double xpos, double ypos) -> void {
		GLfloat offset_x, offset_y;
		if (firstMouse) {
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}
		offset_x = xpos - lastX;
		offset_y = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		Camera* camera = Camera::getInstance();
		camera->rotate(offset_x, offset_y);
	}
	inline static auto scroll_callback(GLFWwindow* window, double xoff, double yoff) -> void {
		Camera* camera = Camera::getInstance();
		camera->zoom(yoff);
	}


};


// camera
GLfloat SceneManager::deltaTime = 0.0f;
GLfloat SceneManager::lastFrame = 0.0f;
GLfloat SceneManager::lastX = 0.0f;
GLfloat SceneManager::lastY = 0.0f;
bool SceneManager::firstMouse = false;
bool SceneManager::keys[1024] = {0};