#pragma once

#include "TriangleMesh.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <vector>
#include <string>

#include <glm/glm.hpp>

using namespace std;
using namespace glm;


class Terrain : public TriangleMesh {

public:
	
	Terrain();
	Terrain(GLuint gridX, GLuint gridZ, string heightMapPath, GLuint texId);
	

	virtual GLfloat getHeight(GLfloat worldX, GLfloat worldZ);
	
	GLuint getTextureId();

protected:
	// Terrain parameters

	// 1. Terrain vertex count in one dimension
	GLuint m_vertex_countx, m_vertex_countz;
	// 2. Terrain unit size (to multiply with grid size)
	GLuint m_size;
	// 3. Terrain Max Height
	GLint m_max_height;
	// 4. Max pixel color value of height map (0-256, RGB, then max = 256 * 256 * 256), for generating the heights from height map
	GLint m_max_pcolor_value;
	// 5. Terrain total size in x and z
	GLint m_x, m_z;
	
	// heights generated from height map
	vector<vector<GLfloat>> m_heights;
	// heights of each gridX and each gridZ for retrieving height faster, precomputed
	vector<vector<GLfloat>> m_heights_grid;

	
	// generate the terrain vertices, normals and texcoords
	virtual void generateTerrain(string heightMapPath = "");

private:
	// Texture Id
	GLuint m_texId;

	// compute m_heights (heightMapWidth * heightMapLength)
	float computeHeight(int z, int x, unsigned char* pixels);
	// bary-centric method for computing the height of a point in the triangle mesh
	GLfloat baryCentric(vec3 v1, vec3 v2, vec3 v3, vec2 pos);

	// compute normal for a single vertex
	vec3 computeNormal(int z, int x, unsigned char* pixels);
	
};