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
#include "GLUtils.h"


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
		int width, height;
		glfwGetFramebufferSize(window, &frame_size_width, &frame_size_height);
		glViewport(0, 0, frame_size_width, frame_size_height);
	}

	int run(Scene &scene) {
		scene.setDimensions(this->frame_size_width, this->frame_size_height);
		scene.initScene();
		scene.resize(this->frame_size_width, this->frame_size_height);
		//main loop
		this->mainLoop(this->window, scene);

		//close window and stop glfw
		glfwTerminate();
		
		return EXIT_SUCCESS;
	}


private:
	GLFWwindow *window;
	int frame_size_width, frame_size_height;

	
	void mainLoop(GLFWwindow* window, Scene &scene) {
		while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			GLUtils::checkForOpenGLError(__FILE__, __LINE__);
			scene.update(float(glfwGetTime()));
			scene.render();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
};
