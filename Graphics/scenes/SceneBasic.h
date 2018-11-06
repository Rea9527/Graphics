#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include "../shaderProgram.h"

#include "../Scene.h"
#include "../Plane.h"
#include "../GLGUI.h"

class SceneBasic : public Scene {

public:
	SceneBasic();

	void initScene(int w, int h, Camera &camera);
	void update(float t, Camera &camera);
	void render();
	void resize(int w, int h);


private:

	ShaderProgram prog;

	Plane plane;

	float angle;

	void setMatrices();
	void compileAndLinkShaders();

	void renderGUI();
};