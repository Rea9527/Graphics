#pragma once


#include "Scene.h"
#include "Camera.h"
#include "shaderProgram.h"
#include "FrameBuffer.h"
#include "BufferObject.h"

#include "teapot.h"

#include "GLUtils.h"


class SceneBloom : public Scene {

public:
	SceneBloom();
	SceneBloom(int w, int h);
	~SceneBloom();

	void initScene(Camera &camera);
	void update(float t, Camera &camera);
	void render();
	void resize(int w, int h);


private:
	int width, height;

	map<string, ShaderProgram*> programsList;
	ShaderProgram prog;

	Teapot teapot;

	// frame buffer
	FrameBuffer FBO;
	GLuint quadVAO;

	// five pass
	GLuint renderPassInx, brightPassInx, verGaussPassInx, horGaussPassInx, tonePassInx;
	void renderPass();
	void brightPass();
	void verGaussPass();
	void horGaussPass();
	void tonePass();

	void setMatrices(string pname);
	void compileAndLinkShaders();
	void renderGUI();
};