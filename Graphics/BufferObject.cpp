#include "BufferObject.h"


namespace BufferObject {

	GLuint genQuadBufferObject() {
		GLuint vao;

		GLfloat verts[] = {
		-1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f
		};
		GLfloat tc[] = {
			0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		// Set up the buffers

		unsigned int handle[2];
		glGenBuffers(2, handle);

		glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
		glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(float), verts, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
		glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), tc, GL_STATIC_DRAW);

		// Set up the vertex array object

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);  // Vertex position

		glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
		glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);  // Texture coordinates

		glBindVertexArray(0);

		return vao;
	}
}