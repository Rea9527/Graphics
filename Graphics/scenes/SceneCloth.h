#pragma once

#include <iostream>
#include <vector>

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

	GLuint readBuf;
	GLuint posBufs[2], velBufs[2];
	GLuint normBuf, texcBuf, elBuf;

	GLuint clothVAO;
	glm::vec2 nParticles;
	glm::vec2 clothSize;
	GLuint numElements;


	void initBuffers();
	void setMatrices();
	void compileAndLinkShaders();

	void renderGUI();
};