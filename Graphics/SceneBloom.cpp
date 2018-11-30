#include "SceneBloom.h"


SceneBloom::SceneBloom() : teapot(12, glm::mat4(1.0)), FBO(800, 600, 1, 1) { }

SceneBloom::~SceneBloom() {}

void SceneBloom::initScene(Camera &camera) {

	this->compileAndLinkShaders();

	
}