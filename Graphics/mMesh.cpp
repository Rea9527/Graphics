
#include "mMesh.h"
#include <iostream>

mMesh::mMesh(vector<GLfloat> pos, vector<GLfloat> normals, vector<GLfloat> texcoords, 
			vector<GLuint> indices, vector<Texture> textures, vector<Material> materials)
				: m_textures(textures), m_materials(materials) {

	this->initBuffers(&indices, &pos, &normals, &texcoords);
	
	
}

// materials and textures
void mMesh::prepare(GLuint handle) const {
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	GLuint normalNr = 1;
	GLuint heightNr = 1;


	for (GLuint i = 0; i < this->m_textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);

		string number;
		string name = this->m_textures[i].type;
		if (name == "texture_diffuse")
			number = to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = to_string(specularNr++);
		else if (name == "texture_normal")
			number = to_string(normalNr++);
		else if (name == "texture_height")
			number = to_string(heightNr++);

		glUniform1i(glGetUniformLocation(handle, (name+number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, this->m_textures[i].id);
	}


	glUniform3fv(glGetUniformLocation(handle, "Material.Ka"), 1, glm::value_ptr(this->m_materials[0].ambient));
	glUniform3fv(glGetUniformLocation(handle, "Material.Kd"), 1, glm::value_ptr(this->m_materials[0].diffuse));
	glUniform3fv(glGetUniformLocation(handle, "Material.Ks"), 1, glm::value_ptr(this->m_materials[0].specular));

	glUniform1f(glGetUniformLocation(handle, "Material.Shininess"), this->m_materials[0].shininess);
}

void mMesh::finish() const {
	for (GLuint i = 0; i < this->m_textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}