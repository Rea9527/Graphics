#pragma once

#include "../Scene.h"
#include "../Camera.h"
#include "../shaderProgram.h"
#include "../BufferObject.h"
#include "../Loader.h"

#include "../teapot.h"
#include "../Sphere.h"
#include "../Plane.h"

#include "../GLGUI.h"
#include "../GLUtils.h"

#include "../Terrain.h"



class SceneTerrain : public Scene {

public:
	SceneTerrain();
	SceneTerrain(int width, int height);

	void initScene();
	void update(float dt);
	void render();
	void resize(int w, int h);


private:

	map<string, ShaderProgram*> programsList;
	ShaderProgram prog;

	Terrain m_terrain;
	Sphere m_sphere;
	Teapot m_teapot;

	// func
	void compileAndLinkShaders();
	void setMatrices(string name);
	void renderGUI();
	void drawScene();
};