#include "Frustum.h"
using glm::vec3;
using glm::mat4;

Frustum::Frustum() : vao(0) {
	this->orient(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	this->setPerspective(50.0f, 1.0f, 0.5f, 100.0f);
}

Frustum::~Frustum() {
	this->deleteBuffers();
}



