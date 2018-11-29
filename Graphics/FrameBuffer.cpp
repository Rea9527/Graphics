
#include "FrameBuffer.h"


// set current active texture to texture id 2
unsigned int FrameBuffer::s_curActiveTexId = GL_TEXTURE2;


FrameBuffer::FrameBuffer(GLuint w, GLuint h, bool useDepth, bool fullScreen, GLuint rrtFormat)
	: m_width(w), m_height(h), m_handle(0), m_depthHandle(0),
	m_rrtFormat(rrtFormat), m_fullScreen(fullScreen) {

	this->setupFBO();
}

FrameBuffer::~FrameBuffer() {
	glDeleteFramebuffers(1, &this->m_handle);
	if (this->m_hasDepthBuf) glDeleteBuffers(1, &this->m_depthHandle);
}

void FrameBuffer::setupFBO() {

	glGenFramebuffers(1, &this->m_handle);
	this->bind();

	// create render texture target
	glGenTextures(1, &this->m_rrtHandle);
	glBindTexture(GL_TEXTURE_2D, this->m_rrtHandle);

	// texture parameter
	glTexStorage2D(GL_TEXTURE_2D, 1, this->m_rrtFormat, this->m_width, this->m_height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_rrtHandle, 0);

	if (m_hasDepthBuf) {
		// create depth buffer object
		GLuint depthBuf;
		glGenRenderbuffers(1, &depthBuf);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuf);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->m_width, this->m_height);

		// bind the depth buffer to FBO
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuf);

	}

	// set the target for the fragment shader outputs
	GLenum drawBufs[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBufs);

	this->unbind();
}

void FrameBuffer::bind() {
	// set the viewport
	if (!m_fullScreen) {
		glViewport(0, 0, this->m_width, this->m_height);
	}

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, this->m_handle);
}

void FrameBuffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}