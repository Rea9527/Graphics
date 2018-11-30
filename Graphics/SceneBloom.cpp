#include "SceneBloom.h"


SceneBloom::SceneBloom() : teapot(12, glm::mat4(1.0)), FBO(800, 600, 1, 1) { }

SceneBloom::SceneBloom(int w, int h) : teapot(12, glm::mat4(1.0)), FBO(800, 600, 1, 1), width(w), height(h) { }

SceneBloom::~SceneBloom() {}

void SceneBloom::initScene(Camera &camera) {

	this->compileAndLinkShaders();


}

void SceneBloom::update(float t, Camera &camera) {

}

void SceneBloom::render() {

}

void SceneBloom::renderPass() {

}
void SceneBloom::brightPass() {

}
void SceneBloom::verGaussPass() {

}
void SceneBloom::horGaussPass() {

}
void SceneBloom::tonePass() {

}


void SceneBloom::resize(int w, int h) {

}

void SceneBloom::setMatrices(string pname) {

}
void SceneBloom::compileAndLinkShaders() {

}
void SceneBloom::renderGUI() {

}