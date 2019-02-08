#pragma once

#include <GL_CORE/gl_core_4_3.h>

#include <string>

class Texture {
public:
	Texture();
	Texture(GLuint id, std::string type, std::string path);


	GLuint id;
	std::string type;
	std::string path;
};