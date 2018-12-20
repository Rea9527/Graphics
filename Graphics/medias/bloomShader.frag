#version 430

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

in vec3 reflectDir;

struct LightInfo {
	vec3 Position;
	vec3 Intensity;
};
uniform LightInfo Light;

struct LightMaterial {
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;
};
uniform LightMaterial Material;

// whether to draw skybox
uniform bool drawSkyBox;
layout(binding=0) uniform samplerCube cubemapTex;

layout(location=0) out vec4 FragColor;

// subroutine definition
subroutine vec4 BloomPassType();
subroutine uniform BloomPassType bloomPass;

// First Pass - rendering basics
subroutine (BloomPassType)
vec4 renderPass() {

	return vec4(1.0f);
}

// Second Pass - extract the bright part
subroutine (BloomPassType)
vec4 brightPass() {

	return vec4(1.0f);
}

subroutine (BloomPassType)
vec4 verGaussPass() {

	return vec4(1.0f);
}

subroutine (BloomPassType)
vec4 horGaussPass() {

	return vec4(1.0f);
}

subroutine (BloomPassType)
vec4 tonePass() {

	return vec4(1.0f);
}


void main() {
	vec4 cubemapColor = texture(cubemapTex, reflectDir);
	if (drawSkyBox) {
		FragColor = cubemapColor;
	} else {
		FragColor = bloomPass();
	}

}