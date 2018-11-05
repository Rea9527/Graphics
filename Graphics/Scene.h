#pragma once

#include <glm/glm.hpp>
#include "Camera.h"

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
	virtual void update(float t, Camera &camera) = 0;
	//
	virtual void render() = 0;
	//
	virtual void resize(int, int) = 0;

	void animate(bool value) { m_animate = value; }
	bool animating() { return m_animate; }

protected:
	glm::mat4 model, view, projection;

	bool m_animate;
};