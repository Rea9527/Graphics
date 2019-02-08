#pragma once

#include <GL_CORE/gl_core_4_3.h>
#include <string>

class Loader {

public:

	static GLuint loadTexture(const std::string & fName);
	static GLuint loadCubeMap(const std::string & baseName);
	static unsigned char * loadPixels(const std::string & fName, int & w, int & h, int &bytesPerPix);
};