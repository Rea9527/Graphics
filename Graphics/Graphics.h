#pragma once


#include <iostream>
#include <string>
#include <vector>

using namespace std;

// GL CORE
#include <GL_CORE/gl_core_4_3.h>
// GLFW
#include <GLFW/glfw3.h>

// include user define files
#include "SceneManager.h"
#include "scenes/BasicScene.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
