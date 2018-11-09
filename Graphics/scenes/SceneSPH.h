#pragma once

// This is a scene for SPH fluid simulation

#include <glm/gtc/matrix_transform.hpp>

#include "../Scene.h"
#include "../Plane.h"
#include "../GLGUI.h"

#include "../shaderProgram.h"


class SceneSPH : public Scene {

public:
	SceneSPH();

	void initScene(int w, int h, Camera &camera);
	

	void update(float dt, Camera &camera);
	void render();
	void resize(int w, int h);

private:
	ShaderProgram prog, progIntegrate, progPres, progForce;

	GLuint nParticles;

	void initBuffers();
	void setMatrices();
	void compileAndLinkShaders();

	void renderGUI();

};