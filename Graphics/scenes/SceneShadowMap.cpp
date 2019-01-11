#include "SceneShadowMap.h"

using glm::vec4;
using glm::vec3;
using glm::mat4;
using glm::mat3;

SceneShadowMap::SceneShadowMap() : plane(20.0f, 10.0f, 1, 1), teapot(12, glm::mat4(1.0)), sphere(2.0f, 50, 50),
								 shadowmapWidth(512), shadowmapHeight(512), prog("shadowShader") {}

SceneShadowMap::SceneShadowMap(int w, int h) : plane(20.0f, 10.0f, 1, 1), teapot(12, glm::mat4(1.0)), sphere(2.0f, 50, 50),
										prog("shadowShader"), shadowmapWidth(512), shadowmapHeight(512), width(w), height(h) {}


void SceneShadowMap::initScene() {
	
	this->compileAndLinkShaders();

	Camera* camera = Camera::getInstance();
	camera->init(glm::vec3(0, 0.0, 30.0), glm::vec3(0, 1.0, 0), -90, 0);

	// create quad
	this->quadVAO = BufferObject::genQuadBufferObject();

	// setup FBO
	this->setupFBO();

	// get subroutines index
	GLuint handle = this->prog.getHandle();
	this->recordPassInx = glGetSubroutineIndex(handle, GL_FRAGMENT_SHADER, "recordPass");
	this->shadowPassInx = glGetSubroutineIndex(handle, GL_FRAGMENT_SHADER, "shadowPass");

	// shadow bias matrix to alter clip coordinates between 0 to 1
	this->shadowBias = mat4(vec4(0.5f, 0.0f, 0.0f, 0.0f),
							vec4(0.0f, 0.5f, 0.0f, 0.0f),
							vec4(0.0f, 0.0f, 0.5f, 0.0f),
							vec4(0.5f, 0.5f, 0.5f, 1.0f)
							);

	// light frustum settings
	vec3 lightPos = vec3(8.0f, 8.0f, 5.0f);
	this->lightFrustum.orient(lightPos, vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
	this->lightFrustum.setPerspective(50.0f, 1.0f, 1.0f, 25.0f);
	this->lightBPV = this->shadowBias * this->lightFrustum.getProjectionMatrix() * this->lightFrustum.getViewMatrix();

	// set uniforms
	this->prog.setUniform("Light.Intensity", vec3(0.8f, 0.8f, 0.8f));
	this->prog.setUniform("shadowMap", 0);

}

void SceneShadowMap::setupFBO() {

	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	GLfloat borderCol[] = {1.0f, 0.0f, 0.0f, 0.0f};
	// create depth map
	GLuint depthTex;
	glGenTextures(1, &depthTex);
	glBindTexture(GL_TEXTURE_2D, depthTex);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, this->shadowmapWidth, this->shadowmapHeight);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderCol);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthTex);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);

	GLenum drawBuffers[] = { GL_NONE };
	glDrawBuffers(1, drawBuffers);

	// check buffer status
	GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (result == GL_FRAMEBUFFER_COMPLETE) {
		printf("Framebuffer is complete.\n");
	}
	else {
		printf("Framebuffer is not complete.\n");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SceneShadowMap::update(float dt) {
	Camera* camera = Camera::getInstance();
	this->view = camera->getViewMat();
	this->projection = glm::perspective(glm::radians(camera->getZoom()), (float)this->width / this->height, 0.3f, 100.0f);
}

void SceneShadowMap::render() {
	this->prog.use();

	// pass 1 - record depth pass
	this->view = lightFrustum.getViewMatrix();
	this->projection = lightFrustum.getProjectionMatrix();

	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &this->recordPassInx);
	glBindFramebuffer(GL_FRAMEBUFFER, this->FBO);
	glViewport(0, 0, this->shadowmapWidth, this->shadowmapHeight);
	glClear(GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(2.5f, 10.0f);

	this->drawScene();
	
	glCullFace(GL_BACK);
	glFlush();


	// pass 2 - shadow shading pass
	
}

void SceneShadowMap::drawScene() {

	this->prog.setUniform("Material.Ka", glm::vec3(0.05, 0.05, 0.05));
	this->prog.setUniform("Material.Kd", glm::vec3(0.25, 0.25, 0.25));
	this->prog.setUniform("Material.Ks", glm::vec3(0.0, 0.0, 0.0));
	this->prog.setUniform("Material.Shininess", 1.0f);

	// render planes
	// bottom plane
	this->model = glm::mat4(1.0f);
	this->model = glm::translate(this->model, glm::vec3(0.0f, -5.0f, 0.0f));
	this->setMatrices(this->prog.getName());
	this->plane.render();
	// back plane
	this->model = glm::translate(this->model, glm::vec3(0.0f, 5.0f, -5.0f));
	this->model = glm::rotate(this->model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	this->setMatrices(this->prog.getName());
	this->plane.render();

	
	this->prog.setUniform("Material.Ka", glm::vec3(0.2, 0.2, 0.2));
	this->prog.setUniform("Material.Ks", glm::vec3(0.2, 0.2, 0.2));
	this->prog.setUniform("Material.Shininess", 25.0f);
	// render teapot
	this->prog.setUniform("Material.Kd", glm::vec3(0.4f, 0.9f, 0.4f));
	this->model = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, -5.0f, 0.0f));
	this->model = glm::rotate(this->model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	this->setMatrices(this->prog.getName());
	this->teapot.render();

	// render sphere
	this->prog.setUniform("Material.Kd", glm::vec3(0.4f, 0.4f, 0.9f));
	this->model = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, -3.0f, 0.0f));
	this->setMatrices(this->prog.getName());
	this->sphere.render();
}

void SceneShadowMap::resize(int w, int h) {
	this->width = w;
	this->height = h;
	glViewport(0, 0, w, h);
	// should adjust according to camera TODO
	this->projection = glm::perspective(glm::radians(60.0f), (float)w / h, 0.3f, 100.0f);
}

void SceneShadowMap::setMatrices(string name) {
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