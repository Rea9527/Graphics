#pragma once
#include <vector>

#include "Drawable.h"
#include <GL_CORE/gl_core_4_3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Frustum : public Drawable {

private:
	GLuint vao;
	glm::vec3 center, u, v, n;
	float mNear, mFar, fovy, asp;
	std::vector<GLuint> buffers;


public:

	Frustum();
	~Frustum();

	void orient(const glm::vec3 &pos, const glm::vec3 &at, const glm::vec3 &up);
	void setPerspective(float, float, float, float);

	glm::mat4 getViewMatrix() const;
	glm::mat4 getInverseViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	glm::vec3 getOrigin() const;

	void render() const override;
	void deleteBuffers();
};