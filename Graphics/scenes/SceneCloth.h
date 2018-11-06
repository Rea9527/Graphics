#pragma once

#include "../Scene.h"
#include "../GLGUI.h"

#include "../shaderProgram.h"


class SceneCloth : public Scene {

public:
	SceneCloth();

	void initScene(int w, int h, Camera &camera);
	void update(float dt, Camera &camera);
	void render();
	void resize(int w, int h);

private:
	ShaderProgram prog, progCloth, progClothNorm;
	
	float angle;

	void initBuffers();
	void setMatrices();
	void compileAndLinkShaders();

	void renderGUI();
};