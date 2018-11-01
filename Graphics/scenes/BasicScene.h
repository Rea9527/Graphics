#pragma once

// GL CORE
#include <GL_CORE/gl_core_4_3.h>

#include <glm/gtc/matrix_transform.hpp>

#include "../shaderProgram.h"
#include "../Scene.h"
#include "../Plane.h"

class BasicScene : public Scene {

public:
	BasicScene();

	void initScene();
	void update(float t);
	void render();
	void resize(int w, int h);

private:
	ShaderProgram prog;

	Plane plane;

	float angle;

	void setMatrices();
	void compile();
};