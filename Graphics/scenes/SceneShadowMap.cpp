#include "SceneShadowMap.h"


SceneShadowMap::SceneShadowMap() : plane(20.0f, 10.0f, 1, 1), teapot(12, glm::mat4(1.0)), sphere(2.0f, 50, 50),
								prog("shadowShader") {}

SceneShadowMap::SceneShadowMap(int w, int h) : plane(20.0f, 10.0f, 1, 1), teapot(12, glm::mat4(1.0)), sphere(2.0f, 50, 50),
										prog("shadowShader"), width(w), height(h) {}


void SceneShadowMap::initScene(Camera &camera) {
	
	this->compileAndLinkShaders();

	camera.init(glm::vec3(0, 0.0, 30.0), glm::vec3(0, 1.0, 0), -90, 0);

	// create quad
	this->quadVAO = BufferObject::genQuadBufferObject();

	// setup FBO
	this->setupFBO();




}

void SceneShadowMap::setupFBO() {

}

void SceneShadowMap::update(float dt, Camera &camera) {
	this->view = camera.getViewMat();
	this->projection = glm::perspective(glm::radians(60.0f), (float)this->width / this->height, 0.3f, 100.0f);
}

void SceneShadowMap::render() {

}

void SceneShadowMap::resize(int w, int h) {
	this->width = w;
	this->height = h;
	glViewport(0, 0, w, h);
	// should adjust according to camera TODO
	this->projection = glm::perspective(glm::radians(60.0f), (float)w / h, 0.3f, 100.0f);
}

void SceneShadowMap::setMatrics(string name) {
	ShaderProgram* program = this->programsList[name];
	glm::mat4 mv = this->view * this->model;
	program->setUniform("ModelViewMatrix", mv);
	program->setUniform("NormalMatrix",
		glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])));
	program->setUniform("MVP", this->projection * mv);

}

void SceneShadowMap::compileAndLinkShaders() {

	try {
		this->prog.compileShader("./medias/shadowShader.vert", GLSLShader::VERTEX);
		this->prog.compileShader("./medias/shadowShader.frag", GLSLShader::FRAGMENT);
		this->prog.link();
		this->programsList.insert(std::pair<string, ShaderProgram*>(this->prog.getName(), &this->prog));
	}
	catch (ShaderProgramException e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneShadowMap::renderGUI() {

}