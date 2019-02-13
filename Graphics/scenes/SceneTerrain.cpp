
#include "SceneTerrain.h"


SceneTerrain::SceneTerrain() : m_terrain(1200, "./medias/terrain/heightMap.png", true), m_teapot(20, mat4(1.0f)), m_sphere(2.0, 50, 50),
								m_gumTree("./medias/trees/gum_tree1.obj"),
								progModel("modelShader"), prog("terrainShader") { }

SceneTerrain::SceneTerrain(int w, int h) : Scene(w, h), m_terrain(1200, "./medias/terrain/heightMap.png", true), m_teapot(20, mat4(1.0f)), m_sphere(2.0, 50, 50),
								m_gumTree("./medias/trees/gum_tree1.obj"),
								progModel("modelShader"), prog("terrainShader") { }


void SceneTerrain::initScene() {
	glEnable(GL_DEPTH_TEST);

	this->compileAndLinkShaders();

	Camera* camera = Camera::getInstance();
	camera->init(glm::vec3(0.0, 80.0, 20.0), glm::vec3(0, 1.0, 0), -90, 0);

	this->prog.use();
	this->prog.setUniform("Light.Position", vec4(100.0f, 200.0f, 100.0f, 1.0f));
	this->prog.setUniform("Light.Intensity", vec3(0.9f, 0.9f, 0.9f));

	this->progModel.use();
	this->prog.setUniform("Light.Position", vec4(100.0f, 200.0f, 100.0f, 1.0f));
	this->prog.setUniform("Light.Intensity", vec3(0.9f, 0.9f, 0.9f));

	GLuint bgid, rid, gid, bid, blendid;
	// set textures
	bgid = Loader::loadTexture("./medias/terrain/flowers.png", GL_REPEAT);
	rid = Loader::loadTexture("./medias/terrain/mud.png", GL_REPEAT);
	gid = Loader::loadTexture("./medias/terrain/sand.jpg", GL_REPEAT);
	bid = Loader::loadTexture("./medias/terrain/path.png", GL_REPEAT);
	blendid = Loader::loadTexture("./medias/terrain/blendMap.png", GL_REPEAT);
	this->m_terrain.setMultiTexIds(bgid, rid, gid, bid, blendid);
	
}

void SceneTerrain::update(float dt) {
	this->view = Camera::getInstance()->getViewMat();
	this->projection = glm::perspective(glm::radians(Camera::getInstance()->getZoom()), (GLfloat)this->width / this->height, 0.1f, 1000.0f);
}

void SceneTerrain::render() {
	glClearColor(0.5, 0.5, 0.5, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	this->drawScene();
	
}

void SceneTerrain::drawScene() {
	glDisable(GL_BLEND);
	this->prog.use();
	this->prog.setUniform("Material.Ka", vec3(0.5f, 0.5f, 0.5f));
	this->prog.setUniform("Material.Ks", vec3(0.0f, 0.0f, 0.0f));
	this->prog.setUniform("Material.Shininess", 1.0f);

	// render terrain
	this->prog.setUniform("Material.Kd", vec3(0.7f, 0.7f, 0.7f));
	this->model = glm::translate(glm::mat4(1.0f), vec3(-800, 0, -800));
	this->setMatrices(prog.getName());
	this->m_terrain.render();


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// render gum tree
	this->progModel.use();
	this->model = glm::translate(glm::mat4(1.0f), vec3(0.0, 50.0, 0.0));
	this->setMatrices(progModel.getName());
	this->m_gumTree.render(this->progModel.getHandle());
	GLUtils::checkForOpenGLError(__FILE__, __LINE__);
}

void SceneTerrain::resize(int w, int h) {
	this->width = w;
	this->height = h;
	glViewport(0, 0, w, h);
	this->projection = glm::perspective(glm::radians(Camera::getInstance()->getZoom()), (float)w / h, 0.3f, 100.0f);
}

void SceneTerrain::setMatrices(string name) {
	ShaderProgram* program = this->programsList[name];
	glm::mat4 mv = this->view * this->model;
	program->setUniform("ModelViewMatrix", mv);
	program->setUniform("NormalMatrix",
		glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])));
	program->setUniform("MVP", this->projection * mv);
}

void SceneTerrain::compileAndLinkShaders() {

	try {
		this->prog.compileShader("./medias/terrainMtShader.vert", GLSLShader::VERTEX);
		this->prog.compileShader("./medias/terrainMtShader.frag", GLSLShader::FRAGMENT);
		this->prog.link();
		this->programsList.insert(std::pair<string, ShaderProgram*>(this->prog.getName(), &(this->prog)));

		this->progModel.compileShader("./medias/modelShader.vert", GLSLShader::VERTEX);
		this->progModel.compileShader("./medias/modelShader.frag", GLSLShader::FRAGMENT);
		this->progModel.link();
		this->programsList.insert(std::pair<string, ShaderProgram*>(this->progModel.getName(), &(this->progModel)));

		GLUtils::checkForOpenGLError(__FILE__, __LINE__);
	}
	catch (ShaderProgramException e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneTerrain::renderGUI() {

}