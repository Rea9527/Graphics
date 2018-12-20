#include "SceneBloom.h"


SceneBloom::SceneBloom() : teapot(12, glm::mat4(1.0)), FBO(800, 600, 1, 1), prog("bloomShader") { }

SceneBloom::SceneBloom(int w, int h) : teapot(12, glm::mat4(1.0)), FBO(800, 600, 1, 1), prog("bloomShader"), width(w), height(h) { }

SceneBloom::~SceneBloom() {}

void SceneBloom::initScene(Camera &camera) {

	this->compileAndLinkShaders();

	camera.init(glm::vec3(0, 10.0, 10.0), glm::vec3(0, 1.0, 0), 0, 0);
	
	// create quad for store texture
	this->quadVAO = BufferObject::genQuadBufferObject();

	// set uniforms
	this->prog.use();
	this->prog.setUniform("Light.Position", glm::vec3(0.0, 10.0, -10.0));
	this->prog.setUniform("Light.Intensity", glm::vec3(0.9, 0.9, 0.9));
	this->prog.setUniform("Material.Ka", glm::vec3(0.2, 0.2, 0.2));
	this->prog.setUniform("Material.Kd", glm::vec3(0.5, 0.5, 0.5));
	this->prog.setUniform("Material.Ks", glm::vec3(0.7, 0.7, 0.7));
	this->prog.setUniform("Material.Shininess", 180.0f);

	// get subroutineIndices
	GLuint handle = this->prog.getHandle();
	this->renderPassInx = glGetSubroutineIndex(handle, GL_FRAGMENT_SHADER, "renderPass");
	this->brightPassInx = glGetSubroutineIndex(handle, GL_FRAGMENT_SHADER, "brightPass");
	this->verGaussPassInx = glGetSubroutineIndex(handle, GL_FRAGMENT_SHADER, "verGaussPass");
	this->horGaussPassInx = glGetSubroutineIndex(handle, GL_FRAGMENT_SHADER, "horGaussPass");
	this->tonePassInx = glGetSubroutineIndex(handle, GL_FRAGMENT_SHADER, "tonePass");

	// bind cubemap texture
	glActiveTexture(GL_TEXTURE0);
	Texture::loadCubeMap("./medias/textures/cubemap_night/night");

	GLUtils::checkForOpenGLError(__FILE__, __LINE__);
}

void SceneBloom::update(float t, Camera &camera) {
	this->view = camera.getViewMat();
	this->projection = glm::perspective(glm::radians(camera.getZoom()), this->width / (float)this->height, 0.1f, 1000.0f);
}

void SceneBloom::render() {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->renderGUI();

	// render CubeMap
	this->prog.setUniform("drawSkyBox", true);
	this->model = glm::mat4(1.0f);
	this->setMatrices(this->prog.getName());
	this->skybox.render();
	this->prog.setUniform("drawSkyBox", false);

	GLUtils::checkForOpenGLError(__FILE__, __LINE__);

	//this->renderPass();
	//glFlush();
	//this->brightPass();
	//glFlush();
	//this->verGaussPass();
	//glFlush();
	//this->horGaussPass();
	//glFlush();
	//this->tonePass();

	//GLUtils::checkForOpenGLError(__FILE__, __LINE__);
}

void SceneBloom::renderPass() {
	this->FBO.bind();
	
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &this->renderPassInx);
	this->prog.use();
	this->model = glm::mat4(1.0f);
	this->setMatrices(this->prog.getName());
	this->teapot.render();

}
void SceneBloom::brightPass() {
	//this->FBO.unbind();

}
void SceneBloom::verGaussPass() {
	this->FBO.unbind();

}
void SceneBloom::horGaussPass() {

}
void SceneBloom::tonePass() {

}


void SceneBloom::resize(int w, int h) {
	glViewport(0, 0, w, h);
	this->width = w;
	this->height = h;
	// should adjust according to camera TODO
	this->projection = glm::perspective(glm::radians(60.0f), (float)w / h, 0.3f, 100.0f);
}

void SceneBloom::setMatrices(string pname) {
	ShaderProgram* program = this->programsList[pname];
	glm::mat4 mv = this->view * this->model;
	program->setUniform("ModelViewMatrix", mv);
	program->setUniform("NormalMatrix",
		glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])));
	program->setUniform("MVP", this->projection * mv);
}
void SceneBloom::compileAndLinkShaders() {
	try {
		this->prog.compileShader("./medias/bloomShader.vert", GLSLShader::VERTEX);
		this->prog.compileShader("./medias/bloomShader.frag", GLSLShader::FRAGMENT);
		this->prog.link();
		this->programsList.insert(std::pair<string, ShaderProgram*>(this->prog.getName(), &this->prog));
	}
	catch (ShaderProgramException &e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);

	}
}
void SceneBloom::renderGUI() {

}