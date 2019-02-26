#pragma once

#include <GL_CORE/gl_core_4_3.h>
#include <glm/glm.hpp>

namespace BufferObject {

	GLuint genQuadBufferObject(bool normals = false, bool tangents = false);
}