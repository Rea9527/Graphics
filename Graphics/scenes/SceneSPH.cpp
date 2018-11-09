
#include "SceneSPH.h"


SceneSPH::SceneSPH() : nParticles(4028) { }

void SceneSPH::initScene(int w, int h, Camera &camera) {

	glEnable(GL_DEPTH_TEST);

	this->compileAndLinkShaders();
	this->initBuffers();

}

void SceneSPH::update(float dt, Camera &camera) {


}

void SceneSPH::render() {

}

void SceneSPH::resize(int w, int h) {

}


void SceneSPH::setMatrices() {

}
	
void SceneSPH::compileAndLinkShaders() {

}

	
void SceneSPH::renderGUI() {

}