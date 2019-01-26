#pragma once

#include "Terrain.h"



class MultiTexTerrain : public Terrain {

public:
	MultiTexTerrain(GLuint gridX, GLuint gridZ, string heightMapPath, GLuint blendMapId, GLuint bgTexId, GLuint rTexId, GLuint gTexId, GLuint bTexId);


	GLuint getBgTextureId();
	GLuint getRTextureId();
	GLuint getGTextureId();
	GLuint getBTextureId();
	GLuint getBlendMapId();

private:

	// whether current terrain is using multiple textures
	bool multiTextures;
	// texture ids of the multiple textures(bgTexId: background texture)
	GLuint bgTexId, rTexId, gTexId, bTexId;
	// blend map indicating how the multiple textures are blended with each other
	GLuint blendMapId;

};