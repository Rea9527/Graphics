
#include <iostream>
using namespace std;

#include "SceneBasic.h"


SceneBasic::SceneBasic() : plane(10.0f, 10.0f, 100, 100){ }

void SceneBasic::initScene(int w, int h, Camera &camera) {

	this->win_width = w;
	this->win_height = h;

	// compile and link the shader
	this->compileAndLinkShaders();

	glEnable(GL_DEPTH_TEST);

	camera.init(glm::vec3(0.5f, 10.0f, 4.9f), glm::vec3(0.0f, 1.0f, 0.0f), -20.f, 0.0f);
	this->view = camera.getViewMat();
	this->projection = glm::perspective(glm::radians(camera.getZoom()), w / (float)h, 0.1f, 1000.0f);

	this->angle = 0.957283f;

	prog.setUniform("LightIntensity", glm::vec3(0.9f, 0.9f, 0.9f));
	glm::vec4 lightPos = glm::vec4(10.0f * cos(angle), 10.0f, 10.0f * sin(angle), 1.0f);
	prog.setUniform("LightPosition", view * lightPos);

	prog.setUniform("Kd", 0.7f, 0.7f, 0.7f);
	prog.setUniform("Ka", 0.2f, 0.2f, 0.2f);
	prog.setUniform("Ks", 0.2f, 0.2f, 0.2f);
	prog.setUniform("Shininess", 180.0f);
}


void SceneBasic::update(float dt, Camera &camera) {
	this->view = camera.getViewMat();
	this->projection = glm::perspective(glm::radians(camera.getZoom()), this->win_width / (float)this->win_height, 0.1f, 1000.0f);
}

void SceneBasic::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->renderGUI();

	this->model = glm::mat4(1.0f);
	this->model = glm::translate(model, glm::vec3(0.0f, -0.9f, 0.0f));
	this->setMatrices();
	this->plane.render();

}

void SceneBasic::renderGUI() {
	// add a new frame
	ImGui_ImplGlfwGL3_NewFrame("Menu");

	if (ImGui::BeginMainMenuBar()) {

		if (ImGui::BeginMenu("Subdivision")) {
			if (ImGui::MenuItem("Enable")) {}
			if (ImGui::MenuItem("Disable")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	//render the frame
	ImGui::Render();
}

void SceneBasic::setMatrices() {
	glm::mat4 mv = this->view * this->model;
	prog.setUniform("ModelViewMatrix", mv);
	prog.setUniform("NormalMatrix",
		glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])));
	prog.setUniform("MVP", this->projection * mv);
}

void SceneBasic::resize(int w, int h) {
	glViewport(0, 0, w, h);
	this->width = w;
	this->height = h;
	this->projection = glm::perspective(glm::radians(60.0f), (float)w / h, 0.3f, 100.0f);
}

void SceneBasic::compileAndLinkShaders() {
	try {
		prog.compileShader("./medias/SceneBasic/plane.vert", GLSLShader::VERTEX);
		prog.compileShader("./medias/SceneBasic/plane.frag", GLSLShader::FRAGMENT);
		prog.link();
		prog.use();
	}
	catch (ShaderProgramException & e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}
