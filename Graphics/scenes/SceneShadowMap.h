#pragma once

#include "../Scene.h"
#include "../Camera.h"
#include "../shaderProgram.h"
#include "../BufferObject.h"
#include "../Texture.h"

#include "../teapot.h"
#include "../Sphere.h"
#include "../Plane.h"

#include "../GLGUI.h"
#include "../GLUtils.h"


class SceneShadowMap : public Scene {

public:

	SceneShadowMap();
	SceneShadowMap(int w, int h);
	~SceneShadowMap() {}

	void initScene(Camera &camera);
	void update(float t, Camera &camera);
	void render();
	void resize(int w, int h);

private:
	int width, height;

	Plane plane;
	Teapot teapot;
	Sphere sphere;
	GLuint quadVAO;

	map<string, ShaderProgram*> programsList;
	ShaderProgram prog;

	// FBO
	GLuint FBO;
	GLuint shadowTex;

	// shadow para
	glm::mat4 shadowBias;


	// func
	void compileAndLinkShaders();
	void setMatrics(string name);
	void renderGUI();

	void setupFBO();
	
};