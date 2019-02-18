#pragma once

#include <vector>
using namespace std;

#include <GL_CORE/gl_core_4_3.h>
#include <glm/glm.hpp>

#include "Drawable.h"


class TriangleMesh : public Drawable {

public:
	virtual ~TriangleMesh();
	virtual void render() const;
	virtual void renderInstances(GLuint count) const;
	virtual void loadInstanceMats(glm::mat4* modelMats, GLuint count) const;
	GLuint getVAO() { return this->vao; }

protected:
	GLuint vertex_num;
	GLuint vao;

	// vertex buffer
	vector<GLuint> buffers;

	virtual void initBuffers(vector<GLuint> *indices, vector<GLfloat> *points,
		vector<GLfloat> *normals, vector<GLfloat> *texcoords = nullptr,
		vector<GLfloat> *tangents = nullptr);

	virtual void deleteBuffers();

};