#pragma once

#include <GL_CORE/gl_core_4_3.h>
#include <cstdio>

namespace GLUtils {
	int checkForOpenGLError(const char*, int);

	void dumpGLInfo(bool dumpExtensions = false);
}