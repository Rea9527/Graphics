#pragma once

#include "Drawable.h"
#include <GL_CORE/gl_core_4_3.h>


class SkyBox : public Drawable {

public:
	SkyBox();

	void render() const;

private:
	GLuint vao;

};