#pragma once


#include "Scene.h"
#include "Camera.h"
#include "shaderProgram.h"



class SceneHDR : public Scene {

public:
	SceneHDR();
	~SceneHDR();

	void initScene(Camera &camera);
	void update(float t, Camera &camera);
	void render();
	void resize(int w, int h);


private:
	map<string, ShaderProgram*> programsList;
	ShaderProgram prog, progToon;
};