#pragma once


#include <iostream>
#include <string>

using namespace std;

// GL CORE
#include <GL_CORE/gl_core_4_3.h>
#include <GL_CORE/gl_core_4_3.c>
// GLFW
#include <GLFW/glfw3.h>


// include user define files
#include "shaderProgram/shaderProgram.h"


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
