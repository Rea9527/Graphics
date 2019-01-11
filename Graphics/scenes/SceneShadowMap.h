#pragma once

#include "../Scene.h"
#include "../Camera.h"
#include "../shaderProgram.h"
#include "../BufferObject.h"
#include "../Texture.h"
#include "../Frustum.h"

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

	void initScene();
	void update(float t);
	void render();
	void resize(int w, int h);

private:
	int width, height;

	Frustum lightFrustum;

	Plane plane;
	Teapot teapot;
	Sphere sphere;
	GLuint quadVAO;

	map<string, ShaderProgram*> programsList;
	ShaderProgram prog;

	// FBO
	GLuint FBO;
	GLuint shadowTex;

	// subroutines index
	GLuint recordPassInx, shadowPassInx;

	// shadow para
	GLuint shadowmapWidth, shadowmapHeight;
	glm::mat4 shadowBias;
	glm::mat4 lightBPV;


	// func
	void compileAndLinkShaders();
	void setMatrices(string name);
	void renderGUI();
	void drawScene();

	void setupFBO();
	
};