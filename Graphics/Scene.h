#pragma once


#include <glm/glm.hpp>

class Scene {

public:
	int width;
	int height;

	Scene() : width(800), height(600) {}

	virtual ~Scene() {}

	void setDimensions(int w, int h) {
		this->width = w;
		this->height = h;
	}
	// Compile the shader, create data, bind data to buffer...
	virtual void initScene() = 0;
	//
	virtual void update(float t) = 0;
	//
	virtual void render() = 0;
	//
	virtual void resize(int, int) = 0;

};