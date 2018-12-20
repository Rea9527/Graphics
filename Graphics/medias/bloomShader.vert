#version 430

layout(location=0) in vec3 VertexPosition;
layout(location=1) in vec3 VertexNormal;
layout(location=2) in vec2 VertexTexCoord;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;
out vec3 reflectDir;

uniform bool drawSkyBox;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main() {

	if (drawSkyBox) {
		reflectDir = VertexPosition;
	} else {
		reflectDir = vec3(0.0, 0.0, 0.0);
	}

	Position = vec3(ModelViewMatrix * vec4(VertexPosition, 1.0f));
	Normal = NormalMatrix * VertexNormal;

	TexCoord = VertexTexCoord;

	gl_Position = MVP * vec4(VertexPosition, 1.0f);

}