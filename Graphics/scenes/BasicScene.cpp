
#include <iostream>
using namespace std;

#include "BasicScene.h"


BasicScene::BasicScene() : plane(10.0f, 10.0f, 100, 100){ }

void BasicScene::initScene() {

	// compile and link the shader
	this->compile();

	glEnable(GL_DEPTH_TEST);

	this->view = glm::lookAt(glm::vec3(0.5f, 10.0f, 4.9f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	this->projection = glm::mat4(1.0f);

	this->angle = 0.957283f;

	prog.setUniform("LightIntensity", glm::vec3(0.9f, 0.9f, 0.9f));

}


void BasicScene::update(float dt, Camera &camera) {
	this->view = camera.getViewMat();
}

void BasicScene::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::vec4 lightPos = glm::vec4(10.0f * cos(angle), 10.0f, 10.0f * sin(angle), 1.0f);
	prog.setUniform("LightPosition", view * lightPos);

	prog.setUniform("Kd", 0.7f, 0.7f, 0.7f);
	prog.setUniform("Ka", 0.2f, 0.2f, 0.2f);
	prog.setUniform("Ks", 0.2f, 0.2f, 0.2f);
	prog.setUniform("Shininess", 180.0f);

	this->model = glm::mat4(1.0f);
	this->model = glm::translate(model, glm::vec3(0.0f, -0.9f, 0.0f));
	this->setMatrices();
	this->plane.render();

}

void BasicScene::setMatrices() {
	glm::mat4 mv = this->view * this->model;
	prog.setUniform("ModelViewMatrix", mv);
	prog.setUniform("NormalMatrix",
		glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])));
	prog.setUniform("MVP", this->projection * mv);
}

void BasicScene::resize(int w, int h) {
	glViewport(0, 0, w, h);
	this->width = w;
	this->height = h;
	this->projection = glm::perspective(glm::radians(60.0f), (float)w / h, 0.3f, 100.0f);
}

void BasicScene::compile() {
	try {
		prog.compileShader("./medias/BasicScene/plane.vert", GLSLShader::VERTEX);
		prog.compileShader("./medias/BasicScene/plane.frag", GLSLShader::FRAGMENT);
		prog.link();
		prog.use();
	}
	catch (ShaderProgramException & e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}
