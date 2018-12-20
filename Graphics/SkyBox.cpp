
#include "SkyBox.h"


SkyBox::SkyBox() {
	GLfloat side = 200.0f;
	GLfloat side2 = side / 2.0f;

	float vertices[24 * 3] = {
		// Front
	   -side2, -side2, side2,
		side2, -side2, side2,
		side2,  side2, side2,
	   -side2,  side2, side2,
	   // Right
		side2, -side2, side2,
		side2, -side2, -side2,
		side2,  side2, -side2,
		side2,  side2, side2,
		// Back
		-side2, -side2, -side2,
		-side2,  side2, -side2,
		 side2,  side2, -side2,
		 side2, -side2, -side2,
		 // Left
		 -side2, -side2, side2,
		 -side2,  side2, side2,
		 -side2,  side2, -side2,
		 -side2, -side2, -side2,
		 // Bottom
		 -side2, -side2, side2,
		 -side2, -side2, -side2,
		  side2, -side2, -side2,
		  side2, -side2, side2,
		  // Top
		  -side2,  side2, side2,
		   side2,  side2, side2,
		   side2,  side2, -side2,
		  -side2,  side2, -side2
	};

	GLuint el[] = {
		0,2,1,0,3,2,
		4,6,5,4,7,6,
		8,10,9,8,11,10,
		12,14,13,12,15,14,
		16,18,17,16,19,18,
		20,22,21,20,23,22
	};

	GLuint handle[2];
	glGenBuffers(2, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), el, GL_STATIC_DRAW);

	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[1]);

	glBindVertexArray(0);

}

void SkyBox::render() const {
	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}