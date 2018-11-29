#pragma once

#include <GL_CORE/gl_core_4_3.h>

#include "Scene.h"

class FrameBuffer {

public:

	FrameBuffer(GLuint w, GLuint h, bool useDepth, bool fullscreen, GLuint rrtFormat = GL_RGBA8);
	~FrameBuffer();

	// return render texture target handle
	GLuint getRRTHandle() const { return this->m_rrtHandle; }

	// bind FBO for rendering
	void bind();

	// unbind FBO, set back to default frame buffer
	void unbind();

	static unsigned int s_curActiveTexId;

private:

	GLuint m_handle;
	GLuint m_rrtHandle;
	GLuint m_depthHandle;
	GLuint m_rrtFormat;

	GLuint m_width;
	GLuint m_height;

	bool m_hasDepthBuf;
	bool m_fullScreen;

	// set up FBO
	void setupFBO();

};