
#include "SceneCloth.h"

SceneCloth::SceneCloth() {}

void SceneCloth::initScene(int w, int h, Camera &camera) {

	this->compileAndLinkShaders();
	this->initBuffers();

	glEnable(GL_DEPTH_TEST);

	camera.init(glm::vec3(0.5f, 10.0f, 4.9f), glm::vec3(0.0f, 1.0f, 0.0f), -20.f, 0.0f);
	this->view = camera.getViewMat();
	this->projection = glm::mat4(1.0f);


}

void SceneCloth::update(float dt, Camera &camera) {

}

void SceneCloth::render() {

}

void SceneCloth::resize(int w, int h) {

}


void SceneCloth::initBuffers() {

}

void SceneCloth::setMatrices() {

}

void SceneCloth::compileAndLinkShaders() {

}


void SceneCloth::renderGUI() {

}