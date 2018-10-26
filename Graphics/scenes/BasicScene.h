#pragma once

// GL CORE
#include <GL_CORE/gl_core_4_3.h>
#include "../shaderProgram.h"
#include "../Scene.h"

class BasicScene : public Scene {

public:
	BasicScene();

	void initScene();
	void update(float t);
	void render();
	void resize(int w, int h);

private:
	GLuint vao;
	ShaderProgram prog;

	void compile();
};