#pragma once

#include "mMesh.h"
#include "Loader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/gtc/constants.hpp>
#include <glm/glm.hpp>
using namespace glm;



class Model {

public:
	Model(string path);

	void render(GLuint handle) const;
	void renderInstances(GLuint handle, GLuint count) const;
	void loadInstanceTranslationMat(glm::mat4 *modelMats, int count);

private:
	vector<mMesh> m_meshes;
	vector<Texture> m_textures;

	// directory of model
	string m_dir;

	
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	mMesh processMesh(aiMesh* mesh, const aiScene* scene);

	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};