#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <map>

#include "../shaderProgram.h"
#include "../FrameBuffer.h"
#include "../BufferObject.h"

#include "../Scene.h"
#include "../Plane.h"
#include "../teapot.h"
#include "../GLGUI.h"

#include "../GLUtils.h"

class SceneBasic : public Scene {

public:
	SceneBasic();

	void initScene(Camera &camera);
	void update(float t, Camera &camera);
	void render();
	void resize(int w, int h);


private:
	map<string, ShaderProgram*> programs;
	ShaderProgram prog, progToon;

	FrameBuffer FBO;
	// quad for filterPass
	GLuint quadVAO;

	Plane plane;
	Teapot teapot;

	void filterPass();
	void shadingPass();
	GLuint filterPassInx;
	GLuint shadingPassInx;

	void setMatrices(string pname);
	void compileAndLinkShaders();

	void renderGUI();
};